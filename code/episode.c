
Map *map_get_active(Episode *e)
{
    if (!e)
    {
        return NULL;
    }

    return &e->map[map_id];
}

void map_reset(Map *m)
{
    if (!m)
    {
        return;
    }

    m->weather_id = WEATHER_CLEAR;
    m->fog_start = FOG_DEF_START;
    m->fog_end = FOG_DEF_END;

    int i = 0;
    for (i = 0; i < 3; i++)
    {
        m->fog_color[i] = get_hsv_from_color(128);
        m->sky_color[i] = get_hsv_from_color(32);
    }

    strcpy(m->music, "");

    int x = 0, y = 0, id = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            Cell *cell = &m->cell[x][y];

            vec_set(&cell->worldpos, vector((MAP_CELL_SIZE * x), -(MAP_CELL_SIZE * y), 0));
            cell->pan = 0;

            cell->id = id;
            cell->x = x;
            cell->y = y;

            cell->type = TYPE_NONE;
            cell->asset = ASSET_NONE;

            cell->skill_x = 0;
            cell->skill_y = 0;
            cell->skill_z = 0;

            id++;
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
        map_reset(&e->map[i]);
    }
}