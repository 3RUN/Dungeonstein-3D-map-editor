
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

void map_secret_wall_ent_fnc()
{
    set(my, POLYGON | LIGHT | NOFILTER | UNLIT);
    my->material = mtl_solid;
}

void map_finish_wall_ent_fnc()
{
    set(my, POLYGON | LIGHT | NOFILTER | UNLIT);
    my->material = mtl_solid;
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
    map_items = array_create(ENTITY *, 1);
    map_enemies = array_create(ENTITY *, 1);
    map_bosses = array_create(ENTITY *, 1);
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
    map_loader_destroy_array(map_props);
    map_loader_destroy_array(map_events);
    map_loader_destroy_array(map_items);
    map_loader_destroy_array(map_enemies);
    map_loader_destroy_array(map_bosses);
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
    map_loader_free_array(map_items);
    map_loader_free_array(map_enemies);
    map_loader_free_array(map_bosses);
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

void map_load(Map *map)
{
    if (!map)
    {
        return;
    }

    if (is(floor_ent, INVISIBLE))
    {
        reset(floor_ent, INVISIBLE);
    }

    if (map->weather_id <= WEATHER_CLEAR && map->is_ceiling_visible == true)
    {
        if (is(ceiling_ent, INVISIBLE))
        {
            reset(ceiling_ent, INVISIBLE);
        }
    }

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

            var cell_pan = cell->pan;

            int cell_id = cell->id;

            int cell_type = cell->type;
            int cell_asset = cell->asset;

            int cell_flag = cell->flag;
            int cell_event_type = cell->event_type;
            int cell_event_id = cell->event_id;
            int cell_temp_skill = cell->temp_skill;

            if (cell_type == ASSET_TYPE_WALLS)
            {
                if (is_secret_wall(cell) == true)
                {
                    ENTITY *ent = ent_create(wall_mdl, &cell->worldpos, map_secret_wall_ent_fnc);
                    ent_cloneskin(ent);
                    ent_setskin(ent, asset_get_bmap(cell_type, cell_asset), 1);
                    array_add(ENTITY *, map_walls, ent);
                }
                else if (is_finish_elevator(cell_type, cell_asset) == true)
                {
                    ENTITY *ent = ent_create(wall_mdl, &cell->worldpos, map_finish_wall_ent_fnc);
                    ent_cloneskin(ent);
                    ent_setskin(ent, asset_get_bmap(cell_type, cell_asset), 1);
                    array_add(ENTITY *, map_walls, ent);
                }
                else
                {
                    int i = 0;
                    for (i = 0; i < MAX_DIRECTION_STEP; i++)
                    {
                        if (is_neighbour_solid(map, vector(x, y, 0), &cardinal_dir[i]) == true)
                        {
                            int neighbour_x = x + cardinal_dir[i].x;
                            int neighbour_y = y + cardinal_dir[i].y;
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

                            if (is_neighbour_is_door(map, vector(x, y, 0), &cardinal_dir[i]) == true) // make sure to place a doorway texture
                            {
                                ENTITY *ent = ent_create(wall_doorway_pcx, &spawn_pos, map_solid_ent_fnc);
                                ent->pan = cardinal_rot[i] - 180;
                                array_add(ENTITY *, map_walls, ent);
                            }
                            else
                            {
                                ENTITY *ent = ent_create(asset_get_filename(cell_type, cell_asset), &spawn_pos, map_solid_ent_fnc);
                                ent->pan = cardinal_rot[i] - 180;
                                array_add(ENTITY *, map_walls, ent);
                            }
                        }
                    }
                }
            }
            else if (cell_type == ASSET_TYPE_PROPS)
            {
                if (is_rotatable(cell_type, cell_asset) == true)
                {
                }
                else
                {
                }
            }
            else if (cell_type == ASSET_TYPE_EVENTS)
            {
                if (is_rotatable(cell_type, cell_asset) == true)
                {
                }
                else
                {
                }
            }
            else if (cell_type == ASSET_TYPE_ITEMS) // all NOT rotatable
            {
            }
            else if (cell_type == ASSET_TYPE_ENEMIES) // all rotatable
            {
            }
            else if (cell_type == ASSET_TYPE_BOSSES) // all rotatable
            {
            }
        }
    }
}