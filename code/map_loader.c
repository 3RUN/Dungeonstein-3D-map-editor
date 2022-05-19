
void map_loader_initialize()
{
    vec_set(&cardinal_dir[TOP], vector(0, -1, 0));   // top
    vec_set(&cardinal_dir[RIGHT], vector(1, 0, 0));  // right
    vec_set(&cardinal_dir[BOTTOM], vector(0, 1, 0)); // bottom
    vec_set(&cardinal_dir[LEFT], vector(-1, 0, 0));  // left

    cardinal_rot[TOP] = 90;     // top
    cardinal_rot[RIGHT] = 0;    // right
    cardinal_rot[BOTTOM] = 270; // bottom
    cardinal_rot[LEFT] = 180;   // left
}

void bmap_fix_overlay(BMAP *bmap)
{
    var format = bmap_lock(bmap, 0);

    int x = 0, y = 0;
    for (x = 0; x < bmap_width(bmap); x++)
    {
        for (y = 0; y < bmap_height(bmap); y++)
        {
            COLOR color;
            var pixel = pixel_for_bmap(bmap, x, y);
            pixel_to_vec(&color, NULL, format, pixel);

            if (color.red <= 8 && color.green <= 8 && color.blue <= 8) // overlay ?
            {
                var write = pixel_for_vec(&color, 0, format);
                pixel_to_bmap(bmap, x, y, write);
            }
            else
            {
                var write = pixel_for_vec(&color, 100, format);
                pixel_to_bmap(bmap, x, y, write);
            }
        }
    }

    bmap_unlock(bmap);
}

void ent_change_skin(ENTITY *ent, BMAP *bmap)
{
    BMAP *old_skin = ent_getskin(ent, 1); // first we remove the old skin...
    ptr_remove(old_skin);
    old_skin = NULL;

    BMAP *new_skin = bmap_createblack(bmap_width(bmap), bmap_height(bmap), bmap_format(bmap)); // then we create a new one
    bmap_blit(new_skin, bmap, NULL, NULL);
    bmap_fix_overlay(new_skin);

    ent_setskin(ent, new_skin, 1); // and we assign it
}

void ent_set_object_skills(ENTITY *ent, Object *object)
{
    if (!ent || !object)
    {
        return;
    }

    if (is_rotatable(object->type, object->index))
    {
        set(ent, DECAL);
    }

    ent->OBJ_TYPE = object->type;
    ent->OBJ_INDEX = object->index;
    ent->OBJ_FLAG_0 = object->flag[0];
    ent->OBJ_FLAG_1 = object->flag[1];
    ent->OBJ_FLAG_2 = object->flag[2];
    ent->OBJ_FLAG_3 = object->flag[3];
}

void map_face_fnc()
{
    set(my, PASSABLE | OVERLAY | NOFILTER | DECAL);
    my->flags2 |= UNTOUCHABLE;
    vec_fill(&my->scale_x, 0.5);
    ent_cloneskin(my);
    vec_set(&my->blue, COLOR_BLACK);
    my->material = mtl_solid;

    my->skill44 = floatv(has_no_ceiling(&my->x));
}

void map_water_fnc()
{
    set(my, PASSABLE | OVERLAY | NOFILTER | DECAL);
    my->flags2 |= UNTOUCHABLE;
    ent_cloneskin(my);
    vec_set(&my->blue, COLOR_BLACK);
    my->material = mtl_water;

    VECTOR brightness;
    vec_set(&brightness, COLOR_GREEN);
    my->lightrange = WATER_LIGHTRANGE;

    while (my)
    {
        my->blue = brightness.x * global_light_factor;
        my->green = brightness.y * global_light_factor;
        my->red = brightness.z * global_light_factor;

        my->skill41 = floatv(water_amplitude);
        my->skill42 = floatv(water_speed);
        my->skill43 = floatv(water_modulation);
        my->skill44 = floatv(has_no_ceiling(&my->x));
        wait(1);
    }
}

void map_marker_fnc()
{
    set(my, PASSABLE | OVERLAY | NOFILTER);
    my->flags2 |= UNTOUCHABLE;
    vec_fill(&my->scale_x, 0.5);
    ent_cloneskin(my);
    vec_set(&my->blue, COLOR_WHITE);
    my->material = mtl_marker;

    if (is_markers_visible == false)
    {
        set(my, INVISIBLE);
    }
}

void map_toggle_marker_visibility(int is_visible)
{
    int x = 0, y = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            if (mesh[x][y].marker)
            {
                if (is_visible == true)
                {
                    reset(mesh[x][y].marker, INVISIBLE);
                }
                else
                {
                    set(mesh[x][y].marker, INVISIBLE);
                }
            }

            if (mesh[x][y].rotation)
            {
                if (is_visible == true)
                {
                    reset(mesh[x][y].rotation, INVISIBLE);
                }
                else
                {
                    set(mesh[x][y].rotation, INVISIBLE);
                }
            }
        }
    }
}

void map_toggle_bbox_visibility(int is_visible)
{
    int x = 0, y = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            if (mesh[x][y].object)
            {
                int type = mesh[x][y].object->OBJ_TYPE;
                int index = mesh[x][y].object->OBJ_INDEX;

                if (is_teleport_in(type, index) || is_secret_wall(type, index) || is_light(type, index))
                {
                    continue;
                }

                if (is_decor_on_wall(type, index) || is_ceiling_support(type, index))
                {
                    continue;
                }

                if (is_visible == true)
                {
                    reset(mesh[x][y].object, INVISIBLE);
                }
                else
                {
                    set(mesh[x][y].object, INVISIBLE);
                }
            }
        }
    }
}

void map_remove_solid(Map *map, Cell *cell)
{
    if (!map || !cell)
    {
        return;
    }

    VECTOR cell_pos;
    vec_set(&cell_pos, &cell->pos);

    int x = cell->x;
    int y = cell->y;

    int i = 0;
    for (i = 0; i < MAX_FACES_PER_CELL; i++)
    {
        safe_remove(mesh[x][y].face[i]);
    }

    for (i = 0; i < MAX_DIRECTION_STEP; i++)
    {
        VECTOR pos;
        vec_set(&pos, vector(MAP_CELL_SIZE / 2, 0, 0));
        vec_rotate(&pos, vector(cardinal_rot[i], 0, 0));
        vec_add(&pos, &cell_pos);
        pos.z = MAP_Z_POS + MAP_CELL_SIZE / 2;

        Cell *neighbour = map_get_neighbours(map, vector(x, y, 0), &cardinal_dir[i], 1);
        if (!neighbour)
        {
            continue;
        }

        if (neighbour->is_solid == true)
        {
            continue;
        }

        int id = i - 2;
        id = cycle(id, 0, MAX_DIRECTION_STEP);

        int neighbour_x = neighbour->x;
        int neighbour_y = neighbour->y;

        if (mesh[neighbour_x][neighbour_y].face[id])
        {
            safe_remove(mesh[neighbour_x][neighbour_y].face[id]);
        }

        int type = ASSET_WALLS;
        int index = neighbour->wall_index;

        // if neighbour has a door ?
        // then create a doorway texture for it !
        if (is_door(neighbour->object.type, neighbour->object.index))
        {
            mesh[neighbour_x][neighbour_y].face[id] = ent_create(empty_pcx, &pos, map_face_fnc);
            mesh[neighbour_x][neighbour_y].face[id]->pan = cycle(cardinal_rot[id] - 180, 0, 360);
            ent_change_skin(mesh[neighbour_x][neighbour_y].face[id], doorway_wall_pcx);
        }
        else
        {
            mesh[neighbour_x][neighbour_y].face[id] = ent_create(empty_pcx, &pos, map_face_fnc);
            mesh[neighbour_x][neighbour_y].face[id]->pan = cycle(cardinal_rot[id] - 180, 0, 360);
            ent_change_skin(mesh[neighbour_x][neighbour_y].face[id], asset_get_texture(type, index));
        }
    }

    map_remove_object(map, cell);
    object_copy(&cell->object, NULL);
}

void map_create_solid(Map *map, Cell *cell)
{
    if (!map || !cell)
    {
        return;
    }

    VECTOR cell_pos;
    vec_set(&cell_pos, &cell->pos);

    int x = cell->x;
    int y = cell->y;

    int i = 0;
    for (i = 0; i < MAX_FACES_PER_CELL; i++)
    {
        safe_remove(mesh[x][y].face[i]);
    }

    for (i = 0; i < MAX_DIRECTION_STEP; i++)
    {
        int type = ASSET_WALLS;
        int index = cell->wall_index;

        VECTOR pos;
        vec_set(&pos, vector(MAP_CELL_SIZE / 2, 0, 0));
        vec_rotate(&pos, vector(cardinal_rot[i], 0, 0));
        vec_add(&pos, &cell_pos);
        pos.z = MAP_Z_POS + MAP_CELL_SIZE / 2;

        Cell *neighbour = map_get_neighbours(map, vector(x, y, 0), &cardinal_dir[i], 1);
        if (!neighbour)
        {
            mesh[x][y].face[i] = ent_create(empty_pcx, &pos, map_face_fnc);
            mesh[x][y].face[i]->pan = cycle(cardinal_rot[i] - 180, 0, 360);
            ent_change_skin(mesh[x][y].face[i], asset_get_texture(type, index));
            continue;
        }

        if (neighbour->is_solid == false)
        {
            int id = i - 2;
            id = cycle(id, 0, MAX_DIRECTION_STEP);

            int neighbour_x = neighbour->x;
            int neighbour_y = neighbour->y;

            if (mesh[neighbour_x][neighbour_y].face[id])
            {
                safe_remove(mesh[neighbour_x][neighbour_y].face[id]);
            }

            continue;
        }

        if (is_door(cell->object.type, cell->object.index))
        {
            mesh[x][y].face[i] = ent_create(empty_pcx, &pos, map_face_fnc);
            mesh[x][y].face[i]->pan = cycle(cardinal_rot[i] - 180, 0, 360);
            ent_change_skin(mesh[x][y].face[i], doorway_wall_pcx);
        }
        else
        {
            mesh[x][y].face[i] = ent_create(empty_pcx, &pos, map_face_fnc);
            mesh[x][y].face[i]->pan = cycle(cardinal_rot[i] - 180, 0, 360);
            ent_change_skin(mesh[x][y].face[i], asset_get_texture(type, index));
        }
    }

    if (is_toxic_waste(ASSET_FLOORS, cell->ceiling_index))
    {
        mesh[x][y].face[MESH_CEILING_FACE] = ent_create(water_mdl, &cell_pos, map_water_fnc);
        mesh[x][y].face[MESH_CEILING_FACE]->tilt = -180;
        mesh[x][y].face[MESH_CEILING_FACE]->z += MAP_CELL_SIZE / 2;
        ent_change_skin(mesh[x][y].face[MESH_CEILING_FACE], asset_get_texture(ASSET_FLOORS, cell->ceiling_index));
    }
    else
    {
        if (is_door(cell->object.type, cell->object.index))
        {
            mesh[x][y].face[MESH_CEILING_FACE] = ent_create(empty_pcx, &cell_pos, map_face_fnc);
            mesh[x][y].face[MESH_CEILING_FACE]->pan = cycle(cell->object.pan + 90, 0, 360);
            mesh[x][y].face[MESH_CEILING_FACE]->tilt = -90;
            mesh[x][y].face[MESH_CEILING_FACE]->z += MAP_CELL_SIZE;
            ent_change_skin(mesh[x][y].face[MESH_CEILING_FACE], doorway_floor_pcx);
        }
        else
        {
            mesh[x][y].face[MESH_CEILING_FACE] = ent_create(empty_pcx, &cell_pos, map_face_fnc);
            mesh[x][y].face[MESH_CEILING_FACE]->tilt = -90;
            mesh[x][y].face[MESH_CEILING_FACE]->z += MAP_CELL_SIZE;
            ent_change_skin(mesh[x][y].face[MESH_CEILING_FACE], asset_get_texture(ASSET_FLOORS, cell->ceiling_index));
        }
    }

    if (is_toxic_waste(ASSET_FLOORS, cell->floor_index))
    {
        mesh[x][y].face[MESH_FLOOR_FACE] = ent_create(water_mdl, &cell_pos, map_water_fnc);
        mesh[x][y].face[MESH_FLOOR_FACE]->z += MAP_CELL_SIZE / 2;
        ent_change_skin(mesh[x][y].face[MESH_FLOOR_FACE], asset_get_texture(ASSET_FLOORS, cell->floor_index));
    }
    else
    {
        if (is_door(cell->object.type, cell->object.index))
        {
            mesh[x][y].face[MESH_FLOOR_FACE] = ent_create(empty_pcx, &cell_pos, map_face_fnc); // floor
            mesh[x][y].face[MESH_FLOOR_FACE]->pan = cycle(cell->object.pan + 90, 0, 360);
            mesh[x][y].face[MESH_FLOOR_FACE]->tilt = 90;
            ent_change_skin(mesh[x][y].face[MESH_FLOOR_FACE], doorway_floor_pcx);
        }
        else
        {
            mesh[x][y].face[MESH_FLOOR_FACE] = ent_create(empty_pcx, &cell_pos, map_face_fnc); // floor
            mesh[x][y].face[MESH_FLOOR_FACE]->tilt = 90;
            ent_change_skin(mesh[x][y].face[MESH_FLOOR_FACE], asset_get_texture(ASSET_FLOORS, cell->floor_index));
        }
    }
}

void map_remove_object(Map *map, Cell *cell)
{
    if (!map && !cell)
    {
        return;
    }

    int x = cell->x;
    int y = cell->y;

    int type = cell->object.type;
    int index = cell->object.index;

    // if doorway ?
    // then change textures back to normal
    if (is_door(type, index))
    {
        int i = 0;
        for (i = 0; i < MAX_DIRECTION_STEP; i++)
        {
            if (mesh[x][y].face[i])
            {
                ent_change_skin(mesh[x][y].face[i], asset_get_texture(ASSET_WALLS, cell->wall_index));
            }
        }

        if (mesh[x][y].face[MESH_CEILING_FACE])
        {
            ent_change_skin(mesh[x][y].face[MESH_CEILING_FACE], asset_get_texture(ASSET_FLOORS, cell->ceiling_index));
        }

        if (mesh[x][y].face[MESH_FLOOR_FACE])
        {
            ent_change_skin(mesh[x][y].face[MESH_FLOOR_FACE], asset_get_texture(ASSET_FLOORS, cell->floor_index));
        }
    }

    vec_set(&mesh[x][y].pos, nullvector);

    if (mesh[x][y].object)
    {
        safe_remove(mesh[x][y].object->parent);
        safe_remove(mesh[x][y].object);
    }

    safe_remove(mesh[x][y].marker);
    safe_remove(mesh[x][y].rotation);
}

void map_rotate_object(Cell *cell)
{
    if (!cell)
    {
        return;
    }

    int x = cell->x;
    int y = cell->y;

    if (!mesh[x][y].object)
    {
        return;
    }

    VECTOR cell_pos;
    vec_set(&cell_pos, &cell->pos);

    var pan = cell->object.pan;

    int type = cell->object.type;
    int index = cell->object.index;

    if (!is_on_wall(type, index) && !is_teleport_in(type, index))
    {
        mesh[x][y].object->pan = pan;
        if (mesh[x][y].object->parent)
        {
            mesh[x][y].object->parent->pan = pan;
        }
        if (mesh[x][y].rotation)
        {
            if (is_door(type, index))
            {
                mesh[x][y].rotation->pan = cycle(pan + 90, 0, 360);
            }
            else
            {
                mesh[x][y].rotation->pan = pan;
            }
        }

        if (is_door(type, index))
        {
            if (mesh[x][y].face[MESH_CEILING_FACE])
            {
                mesh[x][y].face[MESH_CEILING_FACE]->pan = cycle(mesh[x][y].object->pan + 90, 0, 360);
            }

            if (mesh[x][y].face[MESH_FLOOR_FACE])
            {
                mesh[x][y].face[MESH_FLOOR_FACE]->pan = cycle(mesh[x][y].object->pan + 90, 0, 360);
            }
        }
        return;
    }

    if (is_teleport_in(type, index))
    {
        vec_set(&mesh[x][y].pos, vector(0, 0, MAP_CELL_SIZE / 2));
        vec_rotate(&mesh[x][y].pos, vector(pan, 0, 0));
        vec_add(&mesh[x][y].pos, &cell_pos);

        vec_set(&mesh[x][y].object->x, &mesh[x][y].pos);
        mesh[x][y].object->pan = pan;
        if (mesh[x][y].object->parent)
        {
            mesh[x][y].object->parent->pan = pan;
            vec_set(&mesh[x][y].object->parent->x, &mesh[x][y].pos);
        }

        return;
    }

    vec_set(&mesh[x][y].pos, vector(MAP_CELL_SIZE / 2.01, 0, MAP_CELL_SIZE / 2));
    vec_rotate(&mesh[x][y].pos, vector(pan, 0, 0));
    vec_add(&mesh[x][y].pos, &cell_pos);

    vec_set(&mesh[x][y].object->x, &mesh[x][y].pos);
    mesh[x][y].object->pan = cycle(pan - 180, 0, 360);

    if (mesh[x][y].object->parent)
    {
        mesh[x][y].object->parent->pan = cycle(pan - 180, 0, 360);
        vec_set(&mesh[x][y].object->parent->x, &mesh[x][y].pos);
    }
}

void map_create_object(Map *map, Cell *cell)
{
    if (!map && !cell)
    {
        return;
    }

    int x = cell->x;
    int y = cell->y;

    map_remove_object(map, cell);
    wait_for(map_remove_object);

    VECTOR cell_pos;
    vec_set(&cell_pos, &cell->pos);

    var pan = cell->object.pan;

    int type = cell->object.type;
    int index = cell->object.index;

    vec_set(&mesh[x][y].pos, &cell_pos);

    if (type == ASSET_EVENTS)
    {
        mesh[x][y].marker = ent_create(empty_pcx, &mesh[x][y].pos, map_marker_fnc);
        mesh[x][y].marker->z += MAP_CELL_SIZE / 2;
        ent_change_skin(mesh[x][y].marker, asset_get_texture(type, index));

        if (index == EVENTS_PLAYER)
        {
            mesh[x][y].object = ent_create(bbox_npc_mdl, &mesh[x][y].pos, player_controller);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;
            mesh[x][y].object->pan = pan;

            mesh[x][y].rotation = ent_create(direction_pcx, &cell_pos, map_marker_fnc);
            mesh[x][y].rotation->pan = pan;
            mesh[x][y].rotation->tilt = 90;
            mesh[x][y].rotation->z += ROTATION_POS_Z;
        }
        else if (index == EVENTS_LEVEL_FINISH)
        {
            vec_set(&mesh[x][y].pos, vector(MAP_CELL_SIZE / 2.01, 0, MAP_CELL_SIZE / 2));
            vec_rotate(&mesh[x][y].pos, vector(pan, 0, 0));
            vec_add(&mesh[x][y].pos, &cell_pos);

            mesh[x][y].object = ent_create(bbox_switch_mdl, &mesh[x][y].pos, level_finish);
            mesh[x][y].object->pan = cycle(pan - 180, 0, 360);

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->pan = cycle(pan - 180, 0, 360);
            ent_change_skin(mesh[x][y].object->parent, elevator_switch_off);
        }
        else if (index == EVENTS_TRIGGER_ZONE)
        {
            mesh[x][y].object = ent_create(bbox_cell_mdl, &mesh[x][y].pos, trigger_zone);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;
        }
        else if (index == EVENTS_OBJECT_SPAWN_POINT)
        {
            mesh[x][y].object = ent_create(bbox_cell_mdl, &mesh[x][y].pos, object_spawn_point);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;
        }
        else if (index == EVENTS_SECRET_WALL)
        {
            mesh[x][y].object = ent_create(secret_wall_mdl, &mesh[x][y].pos, secret_wall);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object, asset_get_texture(ASSET_WALLS, cell->wall_index));
        }
        else if (index == EVENTS_TELEPORT_IN)
        {
            vec_set(&mesh[x][y].pos, vector(0, 0, MAP_CELL_SIZE / 2));
            vec_rotate(&mesh[x][y].pos, vector(pan, 0, 0));
            vec_add(&mesh[x][y].pos, &cell_pos);

            mesh[x][y].object = ent_create(teleport_in_frame_mdl, &mesh[x][y].pos, teleport_in);
            mesh[x][y].object->pan = pan;
        }
        else if (index == EVENTS_TELEPORT_OUT)
        {
            mesh[x][y].object = ent_create(secret_wall_mdl, &mesh[x][y].pos, teleport_out);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;
            mesh[x][y].object->pan = pan;

            mesh[x][y].rotation = ent_create(direction_pcx, &cell_pos, map_marker_fnc);
            mesh[x][y].rotation->pan = pan;
            mesh[x][y].rotation->tilt = 90;
            mesh[x][y].rotation->z += ROTATION_POS_Z;
        }
    }
    else if (type == ASSET_PROPS)
    {
        if (index == PROPS_LIGHT)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, props_light);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_light_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == PROPS_COLUMN)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, props_column);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == PROPS_BARREL)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, props_barrel);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == PROPS_TABLE)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, props_table);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == PROPS_VASE)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, props_vase);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == PROPS_DOOR)
        {
            mesh[x][y].object = ent_create(bbox_door_mdl, &mesh[x][y].pos, props_door);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;
            mesh[x][y].object->pan = pan;

            mesh[x][y].object->parent = ent_create(decor_mdl, &mesh[x][y].pos, props_sprite);
            vec_fill(&mesh[x][y].object->parent->scale_x, 1);
            mesh[x][y].object->parent->pan = pan;
            set(mesh[x][y].object->parent, DECAL);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;

            if (cell->object.flag[0] == 3) // uses keys ?
            {
                set(mesh[x][y].object->parent, LIGHT);

                if (cell->object.flag[1] == 0)
                {
                    ent_change_skin(mesh[x][y].object->parent, door_key_blue_pcx);
                }
                else if (cell->object.flag[1] == 1)
                {
                    ent_change_skin(mesh[x][y].object->parent, door_key_red_pcx);
                }
                else if (cell->object.flag[1] == 2)
                {
                    ent_change_skin(mesh[x][y].object->parent, door_key_yellow_pcx);
                }
            }
            else
            {
                ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
            }

            mesh[x][y].rotation = ent_create(direction_pcx, &cell_pos, map_marker_fnc);
            mesh[x][y].rotation->pan = cycle(pan + 90, 0, 360);
            mesh[x][y].rotation->tilt = 90;
            mesh[x][y].rotation->z += ROTATION_POS_Z;

            int i = 0;
            for (i = 0; i < MAX_DIRECTION_STEP; i++)
            {
                Cell *neighbour = map_get_neighbours(map, vector(x, y, 0), &cardinal_dir[i], 1);
                if (!neighbour)
                {
                    if (mesh[x][y].face[i])
                    {
                        ent_change_skin(mesh[x][y].face[i], doorway_wall_pcx);
                    }
                    continue;
                }

                if (neighbour->is_solid == false)
                {
                    continue;
                }

                if (mesh[x][y].face[i])
                {
                    ent_change_skin(mesh[x][y].face[i], doorway_wall_pcx);
                }
            }

            if (mesh[x][y].face[MESH_CEILING_FACE])
            {
                ent_change_skin(mesh[x][y].face[MESH_CEILING_FACE], doorway_floor_pcx);
            }

            if (mesh[x][y].face[MESH_FLOOR_FACE])
            {
                ent_change_skin(mesh[x][y].face[MESH_FLOOR_FACE], doorway_floor_pcx);
            }
        }
        else if (index == PROPS_GATE)
        {
            mesh[x][y].object = ent_create(bbox_door_mdl, &mesh[x][y].pos, props_gate);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;
            mesh[x][y].object->pan = pan;

            mesh[x][y].object->parent = ent_create(decor_mdl, &mesh[x][y].pos, props_sprite);
            vec_fill(&mesh[x][y].object->parent->scale_x, 1);
            mesh[x][y].object->parent->pan = pan;
            set(mesh[x][y].object->parent, DECAL);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == PROPS_CEILING_SUPPORT)
        {
            mesh[x][y].object = ent_create(bbox_cell_mdl, &mesh[x][y].pos, props_ceiling_support);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;
            mesh[x][y].object->pan = pan;

            mesh[x][y].object->parent = ent_create(decor_mdl, &mesh[x][y].pos, props_sprite);
            set(mesh[x][y].object->parent, DECAL);
            vec_fill(&mesh[x][y].object->parent->scale_x, 1);
            mesh[x][y].object->parent->pan = pan;
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == PROPS_WINDOW_BLOCK || index == PROPS_WINDOW_BRICK_BLUE || index == PROPS_WINDOW_BRICK_RED || index == PROPS_WINDOW_BRICK_GREY || index == PROPS_WINDOW_DIRT || index == PROPS_WINDOW_METAL)
        {
            vec_set(&mesh[x][y].pos, vector(MAP_CELL_SIZE / 2, 0, MAP_CELL_SIZE / 2));
            vec_rotate(&mesh[x][y].pos, vector(pan, 0, 0));
            vec_add(&mesh[x][y].pos, &cell_pos);

            mesh[x][y].object = ent_create(bbox_door_mdl, &mesh[x][y].pos, props_window);
            mesh[x][y].object->pan = pan;

            mesh[x][y].object->parent = ent_create(decor_mdl, &mesh[x][y].pos, props_sprite);
            vec_fill(&mesh[x][y].object->parent->scale_x, 1);
            mesh[x][y].object->parent->pan = pan;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == PROPS_DECOR_ON_WALL)
        {
            vec_set(&mesh[x][y].pos, vector(MAP_CELL_SIZE / 2.01, 0, MAP_CELL_SIZE / 2));
            vec_rotate(&mesh[x][y].pos, vector(pan, 0, 0));
            vec_add(&mesh[x][y].pos, &cell_pos);

            mesh[x][y].object = ent_create(bbox_cell_mdl, &mesh[x][y].pos, props_decor_on_wall);
            mesh[x][y].object->pan = pan;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->pan = cycle(pan - 180, 0, 360);
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(cell->object.type, cell->object.index));
        }
        else if (index == PROPS_SWITCH)
        {
            vec_set(&mesh[x][y].pos, vector(MAP_CELL_SIZE / 2.01, 0, MAP_CELL_SIZE / 2));
            vec_rotate(&mesh[x][y].pos, vector(pan, 0, 0));
            vec_add(&mesh[x][y].pos, &cell_pos);

            mesh[x][y].object = ent_create(bbox_switch_mdl, &mesh[x][y].pos, props_switch);
            mesh[x][y].object->pan = cycle(pan - 180, 0, 360);

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            set(mesh[x][y].object->parent, DECAL);
            mesh[x][y].object->parent->pan = cycle(pan - 180, 0, 360);
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(cell->object.type, cell->object.index));
        }
    }
    else if (type == ASSET_ITEMS)
    {
        if (index == ITEMS_KEY_BLUE)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, item_key_blue);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == ITEMS_KEY_RED)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, item_key_red);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == ITEMS_KEY_YELLOW)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, item_key_yellow);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == ITEMS_HEALTH_BONUS)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, item_health_bonus);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == ITEMS_MEDKIT_SMALL)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, item_medkit_small);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == ITEMS_MEDKIT_BIG)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, item_medkit_big);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == ITEMS_AMMO_BULLETS_SMALL)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, item_ammo_bullets_small);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == ITEMS_AMMO_BULLETS_BIG)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, item_ammo_bullets_big);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == ITEMS_AMMO_SHELLS_SMALL)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, item_ammo_shells_small);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == ITEMS_AMMO_SHELLS_BIG)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, item_ammo_shells_big);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == ITEMS_AMMO_ROCKETS_SMALL)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, item_ammo_rockets_small);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == ITEMS_AMMO_ROCKETS_BIG)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, item_ammo_rockets_big);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == ITEMS_TREASURE)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, item_treasure);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == ITEMS_POWERUP_MAP)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, item_powerup_map);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == ITEMS_POWERUP_SUIT)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, item_powerup_suit);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == ITEMS_POWERUP_CHICKEN)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, item_powerup_chicken);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == ITEMS_POWERUP_LANTERN)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, item_powerup_lantern);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == ITEMS_POWERUP_MUSHROOM)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, item_powerup_mushroom);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == ITEMS_WEAPON_PISTOL)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, item_weapon_pistol);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == ITEMS_WEAPON_SHOTGUN)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, item_weapon_shotgun);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == ITEMS_WEAPON_CHAINGUN)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, item_weapon_chaingun);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == ITEMS_WEAPON_ROCKETLAUNCHER)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, item_weapon_rocketlauncher);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
    }
    else if (type == ASSET_ENEMIES)
    {
        if (index == ASSET_ENEMY_BAT)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, enemy_bat);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == ASSET_ENEMY_BOXER)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, enemy_boxer);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == ASSET_ENEMY_BUM)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, enemy_bum);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == ASSET_ENEMY_MAGE)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, enemy_mage);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == ASSET_ENEMY_HUMAN_PISTOL)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, enemy_human_pistol);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == ASSET_ENEMY_HUMAN_SHOTGUN)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, enemy_human_shotgun);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == ASSET_ENEMY_SKELETON)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, enemy_skeleton);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == ASSET_ENEMY_SLIME_FIRE)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, enemy_slime_fire);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == ASSET_ENEMY_SLIME_ICE)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, enemy_slime_ice);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == ASSET_ENEMY_ZOMBIE)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, enemy_zombie);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
    }
    else if (type == ASSET_BOSSES)
    {
        if (index == ASSET_BOSS_HUMAN_CHAINGUN)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, boss_human_chaingun);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == ASSET_BOSS_HUMAN_ROCKETLAUNCHER)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, boss_human_rocketlauncher);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == ASSET_BOSS_SLIME_TOXIC)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, boss_slime_toxic);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
        else if (index == ASSET_BOSS_MEGAEYE)
        {
            mesh[x][y].object = ent_create(bbox_props_mdl, &mesh[x][y].pos, boss_megaeye);
            mesh[x][y].object->z += MAP_CELL_SIZE / 2;

            mesh[x][y].object->parent = ent_create(empty_pcx, &mesh[x][y].pos, props_sprite);
            mesh[x][y].object->parent->z += MAP_CELL_SIZE / 2;
            ent_change_skin(mesh[x][y].object->parent, asset_get_texture(type, index));
        }
    }

    if (mesh[x][y].object)
    {
        ent_set_object_skills(mesh[x][y].object, &cell->object);

        if (mesh[x][y].object->parent)
        {
            ent_set_object_skills(mesh[x][y].object->parent, &cell->object);
        }
    }
}

void map_load(Map *map)
{
    if (!map)
    {
        return;
    }

    map_destroy();

    int x = 0, y = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            Cell *cell = &map->cell[x][y];
            if (!cell)
            {
                continue;
            }

            if (cell->is_solid == true)
            {
                continue;
            }

            map_create_solid(map, cell);

            if (cell->object.is_occupied == true)
            {
                map_create_object(map, cell);
            }
        }
    }
}

void map_destroy()
{
    int x = 0, y = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            vec_set(&mesh[x][y].pos, nullvector);

            int i = 0;
            for (i = 0; i < MAX_FACES_PER_CELL; i++)
            {
                safe_remove(mesh[x][y].face[i]);
            }

            if (mesh[x][y].object)
            {
                safe_remove(mesh[x][y].object->parent);
                safe_remove(mesh[x][y].object);
            }

            safe_remove(mesh[x][y].marker);
            safe_remove(mesh[x][y].rotation);
        }
    }
}