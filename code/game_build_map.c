
void game_build_map_initialize()
{
    vec_set(&cardinal_dir[TOP], vector(0, -1, 0));   // top
    vec_set(&cardinal_dir[RIGHT], vector(1, 0, 0));  // right
    vec_set(&cardinal_dir[BOTTOM], vector(0, 1, 0)); // bottom
    vec_set(&cardinal_dir[LEFT], vector(-1, 0, 0));  // left

    cardinal_rot[TOP] = 270;   // top
    cardinal_rot[RIGHT] = 180; // right
    cardinal_rot[BOTTOM] = 90; // bottom
    cardinal_rot[LEFT] = 0;    // left

    map_solid = array_create(ENTITY *, 1);
    map_props = array_create(ENTITY *, 1);
    map_events = array_create(ENTITY *, 1);
    map_items = array_create(ENTITY *, 1);
    map_enemies = array_create(ENTITY *, 1);
    map_bosses = array_create(ENTITY *, 1);
}

void game_build_free_array(array_t *array)
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

void game_build_destroy_array(array_t *array)
{
    if (!array)
    {
        return;
    }

    game_build_free_array(array);
    array_destroy(array);
}

void game_build_map_free()
{
    game_build_free_array(map_solid);
    game_build_free_array(map_props);
    game_build_free_array(map_events);
    game_build_free_array(map_items);
    game_build_free_array(map_enemies);
    game_build_free_array(map_bosses);
}

void game_build_map_destroy()
{
    game_build_destroy_array(map_solid);
    game_build_destroy_array(map_props);
    game_build_destroy_array(map_events);
    game_build_destroy_array(map_items);
    game_build_destroy_array(map_enemies);
    game_build_destroy_array(map_bosses);
}

int game_build_check_direction(Map *map, VECTOR *pos, VECTOR *dir)
{
    if (!map)
    {
        return false;
    }

    VECTOR endpos, tempdir;

    vec_set(&tempdir, dir);
    vec_set(&endpos, pos);
    vec_add(&endpos, &tempdir);

    if (endpos.x < 0 || endpos.x >= MAP_WIDTH || endpos.y < 0 || endpos.y >= MAP_HEIGHT)
    {
        return false;
    }

    int x = endpos.x;
    int y = endpos.y;

    return map->cell[x][y].type != ASSET_TYPE_WALLS;
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

    if (endpos.x < 0 || endpos.x >= MAP_WIDTH || endpos.y < 0 || endpos.y >= MAP_HEIGHT)
    {
        return false;
    }

    int x = endpos.x;
    int y = endpos.y;

    int type = map->cell[x][y].type;
    int asset = map->cell[x][y].asset;

    return is_a_door(type, asset);
}

int is_a_door(int type, int asset)
{
    if (type != ASSET_TYPE_PROPS)
    {
        return false;
    }

    if (asset != PROPS_DOOR && asset != PROPS_DOOR_ELEVATOR && asset != PROPS_DOOR_ENTRANCE && asset != PROPS_DOOR_LOCKED)
    {
        return false;
    }

    return true;
}

int is_a_fence(int type, int asset)
{
    if (type != ASSET_TYPE_PROPS)
    {
        return false;
    }

    if (asset != PROPS_FENCE && asset != PROPS_FENCE_DIRTY)
    {
        return false;
    }

    return true;
}

int is_npc(int type, int asset)
{
    if (type != ASSET_TYPE_ENEMIES && type != ASSET_TYPE_BOSSES) // all enemies/bosses
    {
        return false;
    }

    return true;
}

void solid_ent_fnc()
{
    set(my, PASSABLE | NOFILTER | UNLIT | DECAL);
    my->ambient = 100;
    vec_fill(&my->blue, 255);
    vec_fill(&my->scale_x, 0.5);
}

void game_build_walls(Map *map, Cell *cell)
{
    if (!map || !cell)
    {
        return;
    }

    int x = cell->x;
    int y = cell->y;

    int type = cell->type;
    int asset = cell->asset;

    VECTOR pos;
    vec_set(&pos, vector(x, y, 0));

    VECTOR world_pos;
    vec_set(&world_pos, &cell->worldpos);

    int i = 0;
    for (i = 0; i < MAX_DIRECTION_STEP; i++)
    {
        if (game_build_check_direction(map, &pos, &cardinal_dir[i]) == true)
        {
            int n_x = x + cardinal_dir[i].x;
            int n_y = y + cardinal_dir[i].y;

            Cell *neighbour = &map->cell[n_x][n_y];

            VECTOR spawn_dir;
            vec_set(&spawn_dir, vec_diff(NULL, &neighbour->worldpos, &world_pos));
            vec_normalize(&spawn_dir, 1);

            VECTOR spawn_pos;
            vec_set(&spawn_pos, &spawn_dir);
            vec_scale(&spawn_pos, MAP_CELL_SIZE / 2);
            vec_add(&spawn_pos, &world_pos);

            if (is_neighbour_is_door(map, &pos, &cardinal_dir[i]) == true) // make sure to place a doorway texture
            {
                ENTITY *ent = ent_create(wall_doorway_pcx, &spawn_pos, solid_ent_fnc);
                ent->pan = cardinal_rot[i] - 180;
                array_add(ENTITY *, map_solid, ent);
            }
            else
            {
                ENTITY *ent = ent_create(asset_get_filename(type, asset), &spawn_pos, solid_ent_fnc);
                ent->pan = cardinal_rot[i] - 180;
                array_add(ENTITY *, map_solid, ent);
            }
        }
    }
}

void dynamic_object_fnc()
{
    set(my, PASSABLE | NOFILTER | UNLIT);
    my->ambient = 100;
    vec_fill(&my->blue, 255);
    vec_fill(&my->scale_x, 0.5);
}

void game_build_dynamic_objects(Cell *cell)
{
    if (!cell)
    {
        return;
    }

    int type = cell->type;
    int asset = cell->asset;

    VECTOR spawn_pos;
    vec_set(&spawn_pos, &cell->worldpos);

    ENTITY *ent = ent_create(asset_get_filename(type, asset), &spawn_pos, dynamic_object_fnc);

    if (is_cell_allowed_rotation(type, asset) == true && is_npc(type, asset) == false) // but ignore enemies/bosses
    {
        set(ent, DECAL);
        ent->pan = cell->pan;
        if (is_a_door(type, asset) == true || is_a_fence(type, asset) == true)
        {
            ent->pan = cell->pan - 90; // correct door position
            ent->pan = cycle(ent->pan, 0, 360);
        }
    }

    switch (type)
    {
    case ASSET_TYPE_PROPS:
        array_add(ENTITY *, map_props, ent);
        break;

    case ASSET_TYPE_EVENTS:
        array_add(ENTITY *, map_events, ent);
        break;

    case ASSET_TYPE_ITEMS:
        array_add(ENTITY *, map_items, ent);
        break;

    case ASSET_TYPE_ENEMIES:
        array_add(ENTITY *, map_enemies, ent);
        break;

    case ASSET_TYPE_BOSSES:
        array_add(ENTITY *, map_bosses, ent);
        break;
    }
}

void game_build_map(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    Map *current_map = map_get_active(episode);
    if (!current_map)
    {
        return;
    }

    int x = 0, y = 0, id = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            Cell *cell = &current_map->cell[x][y];

            if (cell->type == TYPE_NONE)
            {
                continue;
            }

            if (cell->type == ASSET_TYPE_WALLS)
            {
                game_build_walls(current_map, cell);
            }
            else
            {
                game_build_dynamic_objects(cell);
            }
        }
    }
}

void game_build_map_update(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    if (key_esc)
    {
        editor_switch_state_to(EDITOR_STATE_FROM_TEST_BUILD);
    }
}