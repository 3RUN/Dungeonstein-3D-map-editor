
int is_game_episode_loaded()
{
    return strlen(episode_save_name) > 0;
}

void episode_save_name_udpate(STRING *filename)
{
    strcpy(episode_save_name, _chr(filename));
}

void cell_copy(Cell *to, Cell *from)
{
    if (!to)
    {
        return;
    }

    if (from == NULL)
    {
        to->type = TYPE_NONE;
        to->asset = ASSET_NONE;

        to->flag = EP_FLAG_NONE;
        to->event_type = EP_EVENT_TYPE;
        to->event_id = EP_EVENT_ID;
        to->temp_skill = 0;
        return;
    }

    to->type = from->type;
    to->asset = from->asset;

    to->flag = from->flag;
    to->event_type = from->event_type;
    to->event_id = from->event_id;
    to->temp_skill = from->temp_skill;
}

Map *map_get_active(Episode *episode)
{
    if (!episode)
    {
        return NULL;
    }

    return &episode->map[current_map_id];
}

void map_copy_weather(Map *to, Map *from)
{
    if (!to)
    {
        return;
    }

    if (from == NULL)
    {
        to->weather_id = WEATHER_CLEAR;

        to->fog_start = FOG_DEF_START;
        to->fog_end = FOG_DEF_END;

        int i = 0;
        for (i = 0; i < 3; i++)
        {
            to->fog_color[i] = get_hsv_from_color(FOG_DEF_COLOR);
            to->floor_color[i] = get_hsv_from_color(FLOOR_DEF_COLOR);
            to->ceiling_color[i] = get_hsv_from_color(CEILING_DEF_COLOR);
        }

        strcpy(to->music, "");
        return;
    }

    to->weather_id = from->weather_id;

    to->fog_start = from->fog_start;
    to->fog_end = from->fog_end;

    int i = 0;
    for (i = 0; i < 3; i++)
    {
        to->fog_color[i] = from->fog_color[i];
        to->floor_color[i] = from->floor_color[i];
        to->ceiling_color[i] = from->ceiling_color[i];
    }

    strcpy(to->music, from->music);
}

void map_reset(Map *map)
{
    if (!map)
    {
        return;
    }

    map->weather_id = WEATHER_CLEAR;

    map->fog_start = FOG_DEF_START;
    map->fog_end = FOG_DEF_END;

    int i = 0;
    for (i = 0; i < 3; i++)
    {
        map->fog_color[i] = get_hsv_from_color(FOG_DEF_COLOR);
        map->floor_color[i] = get_hsv_from_color(FLOOR_DEF_COLOR);
        map->ceiling_color[i] = get_hsv_from_color(CEILING_DEF_COLOR);
    }

    strcpy(map->music, "");

    int x = 0, y = 0, id = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            Cell *cell = &map->cell[x][y];

            vec_set(&cell->worldpos, vector((MAP_CELL_SIZE * x), -(MAP_CELL_SIZE * y), 0));
            cell->pan = CELL_DEF_PAN;

            cell->id = id;
            cell->x = x;
            cell->y = y;

            cell_copy(cell, NULL);

            id++;
        }
    }
}

void episode_change_info(Episode *episode, STRING *name, STRING *story, int map_count)
{
    if (!episode)
    {
        return;
    }

    strcpy(episode->name, name);
    strcpy(episode->story, story);
    episode->map_count = map_count;
}

void episode_reset(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    current_map_id = 0;

    strcpy(episode->name, "");
    strcpy(episode->story, "");
    episode->map_count = 1;

    int i = 0;
    for (i = 0; i < MAX_MAPS_PER_EPISODE; i++)
    {
        map_reset(&episode->map[i]);
    }
}