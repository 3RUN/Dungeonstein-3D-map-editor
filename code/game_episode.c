void map_initialize(Map *m)
{
    if (!m)
    {
        return;
    }

    m->fog_start = FOG_DEF_START;
    m->fog_end = FOG_DEF_END;

    int i = 0;
    for (i = 0; i < 3; i++)
    {
        m->fog_color[i] = 0;
    }

    m->sky_cube = SKY_CLEAR;
    m->weather = WEATHER_CLEAR;

    strcpy(m->music, "");

    int x = 0, y = 0, id = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            vec_set(&m->cells[x][y].worldpos, vector((MAP_CELL_SIZE * x), -(MAP_CELL_SIZE * y), 0));
            m->cells[x][y].id = id;
            m->cells[x][y].x = x;
            m->cells[x][y].y = y;

            m->cells[x][y].base_type_index = INDEX_NONE;
            m->cells[x][y].wall_asset_index = INDEX_NONE;
            m->cells[x][y].floor_asset_index = INDEX_NONE;
            m->cells[x][y].ceiling_asset_index = INDEX_NONE;

            m->cells[x][y].obj_type_index = INDEX_NONE;
            m->cells[x][y].obj_asset_index = INDEX_NONE;
            m->cells[x][y].obj_id = INDEX_NONE;
            m->cells[x][y].obj_pan = 0;
            m->cells[x][y].obj_skill_x = 0;
            m->cells[x][y].obj_skill_y = 0;
            m->cells[x][y].obj_skill_z = 0;
        }
    }
}

void episode_reset(Episode *e)
{
    if (!e)
    {
        return;
    }

    strcpy(e->name, "");
    strcpy(e->story, "");
    e->map_count = 1;

    int i = 0;
    for (i = 0; i < MAX_MAPS_PER_EPISODE; i++)
    {
        map_initialize(&e->maps[i]);
    }
}