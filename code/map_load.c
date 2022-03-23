
void map_floor_ent_fnc()
{
    set(my, PASSABLE | INVISIBLE | LIGHT | NOFILTER | UNLIT | DECAL);
    my->material = mtl_solid;
    my->tilt = 90;
}

void map_ceiling_ent_fnc()
{
    set(my, PASSABLE | INVISIBLE | LIGHT | NOFILTER | UNLIT | DECAL);
    my->material = mtl_solid;
    my->tilt = -90;
}

void map_solid_ent_fnc()
{
    set(my, PASSABLE | LIGHT | NOFILTER | UNLIT | DECAL);
    vec_fill(&my->scale_x, 0.5);
    my->material = mtl_solid;
}

void map_fixed_rotation_ent_fnc()
{
    set(my, PASSABLE | LIGHT | NOFILTER | UNLIT | DECAL);
    vec_fill(&my->scale_x, 0.5);
    my->material = mtl_two_sided;
}

void map_camera_facing_ent_fnc()
{
    set(my, PASSABLE | LIGHT | NOFILTER | UNLIT);
    vec_fill(&my->scale_x, 0.5);
    my->material = mtl_solid;
}

void map_secret_wall_ent_fnc()
{
    set(my, PASSABLE | LIGHT | NOFILTER | UNLIT);
    my->material = mtl_solid;
}

void map_finish_wall_ent_fnc()
{
    set(my, PASSABLE | LIGHT | NOFILTER | UNLIT);
    my->material = mtl_solid;
}

void map_info_bbox_ent_fnc()
{
    set(my, POLYGON | TRANSLUCENT);
    vec_fill(&my->scale_x, 1);
    c_setminmax(my);
    my->alpha = 0.1;
}

void ceiling_update_from_map(Map *map)
{
    if (!map)
    {
        return;
    }

    if (ceiling_ent)
    {
        if (map->is_ceiling_visible == true && map->weather_id <= WEATHER_CLEAR)
        {
            if (is(ceiling_ent, INVISIBLE))
            {
                reset(ceiling_ent, INVISIBLE);
            }
        }
        else
        {
            if (!is(ceiling_ent, INVISIBLE))
            {
                set(ceiling_ent, INVISIBLE);
            }
        }

        change_color_from_hsv(&ceiling_ent->blue, map->ceiling_color[0], map->ceiling_color[1], map->ceiling_color[2]);
    }
}

void floor_update_from_map(Map *map)
{
    if (!map)
    {
        return;
    }

    if (floor_ent)
    {
        if (is(floor_ent, INVISIBLE))
        {
            reset(floor_ent, INVISIBLE);
        }

        change_color_from_hsv(&floor_ent->blue, map->floor_color[0], map->floor_color[1], map->floor_color[2]);
    }
}

void object_attach_to_wall(ENTITY *ent)
{
    if (!ent)
    {
        return;
    }

    VECTOR pos;
    vec_set(&pos, vector((MAP_CELL_SIZE / 2) - OBJECT_OFFSET_FROM_WALL, 0, 0));
    vec_rotate(&pos, &ent->pan);
    vec_add(&pos, &ent->x);

    vec_set(&ent->x, &pos);
    ent->pan += 180;
}

void object_change_skin_to(ENTITY *ent, STRING *bmap_filename, BMAP *bmap)
{
    if (!ent || !bmap_filename || !bmap)
    {
        return;
    }

    ent_cloneskin(ent);

    // first we remove the old skin...
    BMAP *old = ent_getskin(ent, 1);
    ptr_remove(old);
    old = NULL;

    // then we create a new one from the assets
    BMAP *new = bmap_create(bmap_filename);
    bmap_blit(new, bmap, NULL, NULL);

    // and we assign it
    ent_setskin(ent, new, 1);
}

void object_update_skills(ENTITY *ent, var pan, int id, int type, int asset, int flag, int e_type, int e_id, int temp_skill)
{
    if (!ent)
    {
        return;
    }

    if (is(ent, DECAL))
    {
        ent->pan = pan;
    }

    ent->OBJ_ID = id;
    ent->OBJ_TYPE = type;
    ent->OBJ_ASSET = asset;
    ent->OBJ_FLAG = flag;
    ent->OBJ_EVENT_TYPE = e_type;
    ent->OBJ_EVENT_ID = e_id;
    ent->OBJ_TEMP_SKILL = temp_skill;
}

void map_loader_initialize(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    Map *active_map = map_get_active(episode);
    if (!active_map)
    {
        return;
    }

    vec_set(&cardinal_dir[TOP], vector(0, -1, 0));   // top
    vec_set(&cardinal_dir[RIGHT], vector(1, 0, 0));  // right
    vec_set(&cardinal_dir[BOTTOM], vector(0, 1, 0)); // bottom
    vec_set(&cardinal_dir[LEFT], vector(-1, 0, 0));  // left

    cardinal_rot[TOP] = 270;   // top
    cardinal_rot[RIGHT] = 180; // right
    cardinal_rot[BOTTOM] = 90; // bottom
    cardinal_rot[LEFT] = 0;    // left

    // find center of the map
    VECTOR temp_center;
    vec_set(&temp_center, vector((MAP_WIDTH / 2) * MAP_CELL_SIZE, -(MAP_HEIGHT / 2) * MAP_CELL_SIZE, MAP_Z_POS));

    // find scale factor
    var size_width = MAP_WIDTH * MAP_CELL_SIZE;
    var size_height = MAP_HEIGHT * MAP_CELL_SIZE;
    var target_size_width = size_width / ASSET_PREVIEW_IMAGE_WIDTH;
    var target_size_height = size_height / ASSET_PREVIEW_IMAGE_HEIGHT;

    floor_ent = ent_create(empty_sprite_pcx, vector(temp_center.x, temp_center.y, temp_center.z - (MAP_CELL_SIZE / 2)), map_floor_ent_fnc);
    vec_set(&floor_ent->scale_x, vector(target_size_height, target_size_width, 1));
    change_color_from_hsv(&floor_ent->blue, active_map->floor_color[0], active_map->floor_color[1], active_map->floor_color[2]);

    ceiling_ent = ent_create(empty_sprite_pcx, vector(temp_center.x, temp_center.y, temp_center.z + (MAP_CELL_SIZE / 2)), map_ceiling_ent_fnc);
    vec_set(&ceiling_ent->scale_x, vector(target_size_height, target_size_width, 1));
    change_color_from_hsv(&ceiling_ent->blue, active_map->ceiling_color[0], active_map->ceiling_color[1], active_map->ceiling_color[2]);

    // arrays
    map_walls = array_create(ENTITY *, 1);
    map_props = array_create(ENTITY *, 1);
    map_events = array_create(ENTITY *, 1);
    map_effects = array_create(ENTITY *, 1);
    map_items = array_create(ENTITY *, 1);
    map_enemies = array_create(ENTITY *, 1);
    map_bosses = array_create(ENTITY *, 1);
    map_bboxes = array_create(ENTITY *, 1);
}

void map_loader_free_array(array_t *array)
{
    if (!array)
    {
        return;
    }

    array_enumerate_begin(ENTITY *, array, v)
    {
        if (v)
        {
            safe_remove(v);
        }
    }
    array_enumerate_end(array);
}

void map_loader_destroy_array(array_t *array)
{
    if (!array)
    {
        return;
    }

    map_loader_free_array(array);
    array_destroy(array);
}

void map_loader_destroy()
{
    if (floor_ent)
    {
        safe_remove(floor_ent);
    }

    if (ceiling_ent)
    {
        safe_remove(ceiling_ent);
    }

    map_loader_destroy_array(map_walls);
    map_walls = NULL;

    map_loader_destroy_array(map_props);
    map_props = NULL;

    map_loader_destroy_array(map_events);
    map_events = NULL;

    map_loader_destroy_array(map_effects);
    map_effects = NULL;

    map_loader_destroy_array(map_items);
    map_items = NULL;

    map_loader_destroy_array(map_enemies);
    map_enemies = NULL;

    map_loader_destroy_array(map_bosses);
    map_bosses = NULL;

    map_loader_destroy_array(map_bboxes);
    map_bboxes = NULL;
}

int is_neighbour_solid(Map *map, VECTOR *pos, VECTOR *dir)
{
    if (!map || !pos || !dir)
    {
        return false;
    }

    VECTOR endpos, tempdir;

    vec_set(&tempdir, dir);
    vec_set(&endpos, pos);
    vec_add(&endpos, &tempdir);

    if (is_pos_on_grid(&endpos) == false)
    {
        return false;
    }

    int x = endpos.x;
    int y = endpos.y;

    Cell *cell = &map->cell[x][y];
    if (!cell)
    {
        return false;
    }

    if (cell->type == ASSET_TYPE_WALLS && cell->asset != TOTAL_WALL_TEXTURES - 1 && cell->flag == false)
    {
        return false;
    }

    return true;
}

int is_neighbour_is_door(Map *map, VECTOR *pos, VECTOR *dir)
{
    if (!map)
    {
        return false;
    }

    VECTOR endpos, tempdir;

    vec_set(&tempdir, dir);
    vec_set(&endpos, pos);
    vec_add(&endpos, &tempdir);

    if (is_pos_on_grid(&endpos) == false)
    {
        return false;
    }

    int x = endpos.x;
    int y = endpos.y;

    int type = map->cell[x][y].type;
    int asset = map->cell[x][y].asset;

    return is_door(type, asset);
}

void map_create_walls(Map *map, Cell *cell)
{
    if (!map || !cell)
    {
        return;
    }

    var cell_pan = cell->pan;

    int cell_id = cell->id;
    int cell_x = cell->x;
    int cell_y = cell->y;

    int cell_type = cell->type;
    int cell_asset = cell->asset;

    int cell_flag = cell->flag;
    int cell_event_type = cell->event_type;
    int cell_event_id = cell->event_id;
    int cell_temp_skill = cell->temp_skill;

    if (is_secret_wall(cell) == true)
    {
        ENTITY *ent = ent_create(wall_mdl, &cell->worldpos, map_secret_wall_ent_fnc);
        object_change_skin_to(ent, asset_get_filename(cell_type, cell_asset), asset_get_bmap(cell_type, cell_asset));
        object_update_skills(ent, cell_pan, cell_id, cell_type, cell_asset, cell_flag, cell_event_type, cell_event_id, cell_temp_skill);
        array_add(ENTITY *, map_walls, ent);
        secrets_count++;
    }
    else if (is_finish_elevator(cell_type, cell_asset) == true)
    {
        ENTITY *ent = ent_create(wall_mdl, &cell->worldpos, map_finish_wall_ent_fnc);
        object_change_skin_to(ent, asset_get_filename(cell_type, cell_asset), asset_get_bmap(cell_type, cell_asset));
        object_update_skills(ent, cell_pan, cell_id, cell_type, cell_asset, cell_flag, cell_event_type, cell_event_id, cell_temp_skill);
        array_add(ENTITY *, map_walls, ent);
        is_finish_found = true;
    }
    else
    {
        int i = 0;
        for (i = 0; i < MAX_DIRECTION_STEP; i++)
        {
            if (is_neighbour_solid(map, vector(cell_x, cell_y, 0), &cardinal_dir[i]) == true)
            {
                int neighbour_x = cell_x + cardinal_dir[i].x;
                int neighbour_y = cell_y + cardinal_dir[i].y;
                if (is_pos_on_grid(vector(neighbour_x, neighbour_y, 0)) == false)
                {
                    continue;
                }

                Cell *neighbour = &map->cell[neighbour_x][neighbour_y];
                if (!neighbour)
                {
                    continue;
                }

                VECTOR spawn_dir;
                vec_set(&spawn_dir, vec_diff(NULL, &neighbour->worldpos, &cell->worldpos));
                vec_normalize(&spawn_dir, 1);

                VECTOR spawn_pos;
                vec_set(&spawn_pos, &spawn_dir);
                vec_scale(&spawn_pos, MAP_CELL_SIZE / 2);
                vec_add(&spawn_pos, &cell->worldpos);

                if (is_neighbour_is_door(map, vector(cell_x, cell_y, 0), &cardinal_dir[i]) == true) // make sure to place a doorway texture
                {
                    ENTITY *ent = ent_create(wall_doorway_pcx, &spawn_pos, map_solid_ent_fnc);
                    object_update_skills(ent, (cardinal_rot[i] - 180), cell_id, cell_type, cell_asset, cell_flag, cell_event_type, cell_event_id, cell_temp_skill);
                    array_add(ENTITY *, map_walls, ent);
                }
                else
                {
                    ENTITY *ent = ent_create(asset_get_filename(cell_type, cell_asset), &spawn_pos, map_solid_ent_fnc);
                    object_update_skills(ent, (cardinal_rot[i] - 180), cell_id, cell_type, cell_asset, cell_flag, cell_event_type, cell_event_id, cell_temp_skill);
                    array_add(ENTITY *, map_walls, ent);
                }
            }
        }
    }
}

void map_create_props(Map *map, Cell *cell)
{
    if (!map || !cell)
    {
        return;
    }

    var cell_pan = cell->pan;

    int cell_id = cell->id;
    int cell_x = cell->x;
    int cell_y = cell->y;

    int cell_type = cell->type;
    int cell_asset = cell->asset;

    int cell_flag = cell->flag;
    int cell_event_type = cell->event_type;
    int cell_event_id = cell->event_id;
    int cell_temp_skill = cell->temp_skill;

    if (is_rotatable(cell_type, cell_asset) == true)
    {
        ENTITY *ent = ent_create(asset_get_filename(cell_type, cell_asset), &cell->worldpos, map_fixed_rotation_ent_fnc);
        if (is_switch(cell_type, cell_asset) == true || is_decal(cell_type, cell_asset) == true)
        {
            object_update_skills(ent, cell_pan, cell_id, cell_type, cell_asset, cell_flag, cell_event_type, cell_event_id, cell_temp_skill);
            object_attach_to_wall(ent);
        }
        else if (is_door(cell_type, cell_asset) == true || is_fence(cell_type, cell_asset) == true)
        {
            object_update_skills(ent, (cell_pan - 90), cell_id, cell_type, cell_asset, cell_flag, cell_event_type, cell_event_id, cell_temp_skill);

            if (cell_asset == PROPS_DOOR_LOCKED)
            {
                if (cell_event_type == 0) // blue
                {
                    vec_set(&ent->blue, DOOR_LOCKED_BLUE);
                }
                else if (cell_event_type == 1) // red
                {
                    vec_set(&ent->blue, DOOR_LOCKED_RED);
                }
                else if (cell_event_type == 2) // yellow
                {
                    vec_set(&ent->blue, DOOR_LOCKED_YELLOW);
                }
            }
        }
        array_add(ENTITY *, map_props, ent);
        props_count++;
    }
    else
    {
        ENTITY *ent = ent_create(asset_get_filename(cell_type, cell_asset), &cell->worldpos, map_camera_facing_ent_fnc);
        object_update_skills(ent, cell_pan, cell_id, cell_type, cell_asset, cell_flag, cell_event_type, cell_event_id, cell_temp_skill);
        array_add(ENTITY *, map_props, ent);
        props_count++;
    }
}

void map_create_events(Map *map, Cell *cell)
{
    if (!map || !cell)
    {
        return;
    }

    var cell_pan = cell->pan;

    int cell_id = cell->id;
    int cell_x = cell->x;
    int cell_y = cell->y;

    int cell_type = cell->type;
    int cell_asset = cell->asset;

    int cell_flag = cell->flag;
    int cell_event_type = cell->event_type;
    int cell_event_id = cell->event_id;
    int cell_temp_skill = cell->temp_skill;

    if (is_rotatable(cell_type, cell_asset) == true)
    {
        if (is_player_start(cell_type, cell_asset) == true)
        {
            is_player_found = true;
        }

        ENTITY *ent = ent_create(asset_get_filename(cell_type, cell_asset), &cell->worldpos, map_fixed_rotation_ent_fnc);
        object_update_skills(ent, cell_pan, cell_id, cell_type, cell_asset, cell_flag, cell_event_type, cell_event_id, cell_temp_skill);
        ent->pan = cell_pan;
        array_add(ENTITY *, map_events, ent);
        event_count++;
    }
    else
    {
        ENTITY *ent = ent_create(asset_get_filename(cell_type, cell_asset), &cell->worldpos, map_camera_facing_ent_fnc);
        object_update_skills(ent, cell_pan, cell_id, cell_type, cell_asset, cell_flag, cell_event_type, cell_event_id, cell_temp_skill);
        array_add(ENTITY *, map_events, ent);
        event_count++;
    }
}

void map_create_effects(Map *map, Cell *cell)
{
    if (!map || !cell)
    {
        return;
    }

    var cell_pan = cell->pan;

    int cell_id = cell->id;
    int cell_x = cell->x;
    int cell_y = cell->y;

    int cell_type = cell->type;
    int cell_asset = cell->asset;

    int cell_flag = cell->flag;
    int cell_event_type = cell->event_type;
    int cell_event_id = cell->event_id;
    int cell_temp_skill = cell->temp_skill;

    ENTITY *ent = ent_create(asset_get_filename(cell_type, cell_asset), &cell->worldpos, map_camera_facing_ent_fnc);
    object_update_skills(ent, cell_pan, cell_id, cell_type, cell_asset, cell_flag, cell_event_type, cell_event_id, cell_temp_skill);
    array_add(ENTITY *, map_effects, ent);
    effect_count++;
}

void map_create_items(Map *map, Cell *cell)
{
    if (!map || !cell)
    {
        return;
    }

    var cell_pan = cell->pan;

    int cell_id = cell->id;
    int cell_x = cell->x;
    int cell_y = cell->y;

    int cell_type = cell->type;
    int cell_asset = cell->asset;

    int cell_flag = cell->flag;
    int cell_event_type = cell->event_type;
    int cell_event_id = cell->event_id;
    int cell_temp_skill = cell->temp_skill;

    if (is_treasure(cell_type, cell_asset) == true)
    {
        treasure_count++;
    }

    ENTITY *ent = ent_create(asset_get_filename(cell_type, cell_asset), &cell->worldpos, map_camera_facing_ent_fnc);
    object_update_skills(ent, cell_pan, cell_id, cell_type, cell_asset, cell_flag, cell_event_type, cell_event_id, cell_temp_skill);
    array_add(ENTITY *, map_items, ent);
    items_count++;
}

void map_create_enemies(Map *map, Cell *cell)
{
    if (!map || !cell)
    {
        return;
    }

    var cell_pan = cell->pan;

    int cell_id = cell->id;
    int cell_x = cell->x;
    int cell_y = cell->y;

    int cell_type = cell->type;
    int cell_asset = cell->asset;

    int cell_flag = cell->flag;
    int cell_event_type = cell->event_type;
    int cell_event_id = cell->event_id;
    int cell_temp_skill = cell->temp_skill;

    ENTITY *ent = ent_create(asset_get_filename(cell_type, cell_asset), &cell->worldpos, map_camera_facing_ent_fnc);
    object_update_skills(ent, cell_pan, cell_id, cell_type, cell_asset, cell_flag, cell_event_type, cell_event_id, cell_temp_skill);
    array_add(ENTITY *, map_enemies, ent);
    enemies_cout++;
}

void map_create_bosses(Map *map, Cell *cell)
{
    if (!map || !cell)
    {
        return;
    }

    var cell_pan = cell->pan;

    int cell_id = cell->id;
    int cell_x = cell->x;
    int cell_y = cell->y;

    int cell_type = cell->type;
    int cell_asset = cell->asset;

    int cell_flag = cell->flag;
    int cell_event_type = cell->event_type;
    int cell_event_id = cell->event_id;
    int cell_temp_skill = cell->temp_skill;

    ENTITY *ent = ent_create(asset_get_filename(cell_type, cell_asset), &cell->worldpos, map_camera_facing_ent_fnc);
    object_update_skills(ent, cell_pan, cell_id, cell_type, cell_asset, cell_flag, cell_event_type, cell_event_id, cell_temp_skill);
    array_add(ENTITY *, map_bosses, ent);
    bosses_count++;
}

void map_create_bbox(Map *map, Cell *cell)
{
    if (!map || !cell)
    {
        return;
    }

    var cell_pan = cell->pan;

    int cell_id = cell->id;
    int cell_x = cell->x;
    int cell_y = cell->y;

    int cell_type = cell->type;
    int cell_asset = cell->asset;

    int cell_flag = cell->flag;
    int cell_event_type = cell->event_type;
    int cell_event_id = cell->event_id;
    int cell_temp_skill = cell->temp_skill;

    ENTITY *ent = ent_create(wall_mdl, &cell->worldpos, map_info_bbox_ent_fnc);
    object_update_skills(ent, cell_pan, cell_id, cell_type, cell_asset, cell_flag, cell_event_type, cell_event_id, cell_temp_skill);
    array_add(ENTITY *, map_bboxes, ent);
}

void map_reset_statistic()
{
    is_player_found = false;
    is_finish_found = false;

    props_count = 0;
    event_count = 0;
    items_count = 0;
    enemies_cout = 0;
    bosses_count = 0;
    secrets_count = 0;
    treasure_count = 0;
}

void map_load(Map *map)
{
    if (!map)
    {
        return;
    }

    map_reset_statistic();
    weather_play_sound(map->weather_id);
    player_music_from_map(map);
    ceiling_update_from_map(map);
    floor_update_from_map(map);

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

            if (cell->type == ASSET_TYPE_WALLS)
            {
                map_create_walls(map, cell);
                map_create_bbox(map, cell);
            }
            else if (cell->type == ASSET_TYPE_PROPS)
            {
                map_create_props(map, cell);
                map_create_bbox(map, cell);
            }
            else if (cell->type == ASSET_TYPE_EVENTS)
            {
                map_create_events(map, cell);
                map_create_bbox(map, cell);
            }
            else if (cell->type == ASSET_TYPE_EFFECT)
            {
                map_create_effects(map, cell);
                map_create_bbox(map, cell);
            }
            else if (cell->type == ASSET_TYPE_ITEMS) // all NOT rotatable
            {
                map_create_items(map, cell);
                map_create_bbox(map, cell);
            }
            else if (cell->type == ASSET_TYPE_ENEMIES) // all rotatable
            {
                map_create_enemies(map, cell);
                map_create_bbox(map, cell);
            }
            else if (cell->type == ASSET_TYPE_BOSSES) // all rotatable
            {
                map_create_bosses(map, cell);
                map_create_bbox(map, cell);
            }
        }
    }
}

void map_destroy(Map *map)
{
    if (!map)
    {
        return;
    }

    if (!is(floor_ent, INVISIBLE))
    {
        set(floor_ent, INVISIBLE);
    }

    if (!is(ceiling_ent, INVISIBLE))
    {
        set(ceiling_ent, INVISIBLE);
    }

    map_loader_free_array(map_walls);
    map_loader_free_array(map_props);
    map_loader_free_array(map_events);
    map_loader_free_array(map_effects);
    map_loader_free_array(map_items);
    map_loader_free_array(map_enemies);
    map_loader_free_array(map_bosses);
    map_loader_free_array(map_bboxes);
}

void map_update(Map *map)
{
    if (!map)
    {
        return;
    }

    weather_update(map->weather_id);
}