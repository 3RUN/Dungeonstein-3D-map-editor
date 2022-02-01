
void obj_reset(Obj *o)
{
    if (!o)
    {
        return;
    }

    o->pan = 0;

    o->asset_index = INDEX_NONE;

    o->skill_x = 0;
    o->skill_y = 0;
    o->skill_z = 0;
}

void cell_reset(Cell *c)
{
    if (!c)
    {
        return;
    }

    vec_set(&c->worldpos, nullvector);

    c->id = INDEX_NONE;
    c->x = INDEX_NONE;
    c->y = INDEX_NONE;
    c->type = TYPE_NONE;
    c->asset_index = INDEX_NONE;

    c->skill_x = 0;
    c->skill_y = 0;
    c->skill_z = 0;

    obj_reset(&c->object);
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

    m->fog_color[0] = get_hsv_from_color(0);
    m->fog_color[1] = get_hsv_from_color(0);
    m->fog_color[2] = get_hsv_from_color(0);

    m->sky_color[0] = get_hsv_from_color(32);
    m->sky_color[1] = get_hsv_from_color(32);
    m->sky_color[2] = get_hsv_from_color(32);

    strcpy(m->music, "");

    int x = 0, y = 0, id = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            cell_reset(&m->cells[x][y]);

            vec_set(&m->cells[x][y].worldpos, vector((MAP_CELL_SIZE * x), -(MAP_CELL_SIZE * y), 0));
            m->cells[x][y].id = id;
            m->cells[x][y].x = x;
            m->cells[x][y].y = y;
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