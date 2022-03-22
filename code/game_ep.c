
var is_game_episode_loaded()
{
    return strlen(ep_save_name) > 0;
}

void episode_save_name_udpate_to(STRING *filename)
{
    strcpy(ep_save_name, _chr(filename));
}

void cell_copy(Cell *to, Cell *from)
{
    if (!to)
    {
        return;
    }

    if (from == NULL)
    {
        to->pan = DEF_CELL_PAN;

        to->type = CELL_TYPE_NONE;
        to->asset = CELL_ASSET_NONE;

        to->flag = EP_FLAG_NONE;
        to->event_type = EP_EVENT_TYPE;
        to->event_id = EP_EVENT_ID;
        to->temp_skill = 0;
        return;
    }

    to->pan = from->pan;

    to->type = from->type;
    to->asset = from->asset;

    to->flag = from->flag;
    to->event_type = from->event_type;
    to->event_id = from->event_id;

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

    return &episode->map[active_map_id];
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

        to->is_ceiling_visible = true;

        var i = 0;
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

    to->is_ceiling_visible = from->is_ceiling_visible;

    var i = 0;
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

    map_copy_weather(map, NULL);

    var x = 0, y = 0, id = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            Cell *cell = &map->cell[x][y];

            vec_set(&cell->worldpos, vector((MAP_CELL_SIZE * x), -(MAP_CELL_SIZE * y), MAP_Z_POS));
            cell->pan = DEF_CELL_PAN;

            cell->id = id;
            cell->x = x;
            cell->y = y;

            cell_copy(cell, NULL);

            id++;
        }
    }
}

void episode_change_info(Episode *episode, STRING *name, STRING *story_start, STRING *story_end, var map_count)
{
    if (!episode)
    {
        return;
    }

    strcpy(episode->name, _chr(name));
    strcpy(episode->story_start, _chr(story_start));
    strcpy(episode->story_end, _chr(story_end));
    episode->map_count = map_count;
}

void episode_reset(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    active_map_id = 0;
    episode_change_info(episode, "", "", "", 1);

    var i = 0;
    for (i = 0; i < MAX_MAPS_PER_EPISODE; i++)
    {
        map_reset(&episode->map[i]);
    }
}