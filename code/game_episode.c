
void game_episode_initialize()
{
    episodes_found_txt = txt_create(MAX_EPISODES_TO_LOAD, 0);
    episode_list_refresh();

    playing_music_volume = MUSIC_DEF_VOLUME;
    music_found_txt = txt_create(MAX_AMOUNT_OF_MUSIC_TO_LOAD, 0);
    music_list_refresh();
}

void game_episode_destroy()
{
    if (episodes_found_txt)
    {
        ptr_remove(episodes_found_txt);
        episodes_found_txt = NULL;
    }

    if (music_found_txt)
    {
        ptr_remove(music_found_txt);
        music_found_txt = NULL;
    }
}

int scan_episode_folder()
{
    STRING *temp_str = "#256";
    str_cpy(temp_str, episode_save_folder_str);
    str_cat(temp_str, "*");
    str_cat(temp_str, episode_extension_str);
    path_make_absolute(temp_str);

    return txt_for_dir(episodes_found_txt, temp_str);
}

void episode_list_reset_selection()
{
    found_episode_index = -1;
}

void episode_list_refresh()
{
    found_episode_index = -1;
    found_episodes_total = 0;
    found_episodes_total = scan_episode_folder();

    int i = 0;
    for (i = 0; i < found_episodes_total; i++) // remove file extension from the filename
    {
        STRING *temp_str = "";
        str_cpy(temp_str, (episodes_found_txt->pstring)[i]);
        var num = str_len(episode_extension_str);
        str_trunc(temp_str, num);
        str_cpy((episodes_found_txt->pstring)[i], temp_str);
    }

    for (i = 0; i < found_episodes_total; i++) // refresh listbox
    {
        found_episodes_listbox[i] = _chr((episodes_found_txt->pstring)[i]);
    }
}

int scan_music_folder()
{
    STRING *temp_str = "#256";
    str_cpy(temp_str, episode_music_folder_str);
    str_cat(temp_str, "*");
    str_cat(temp_str, music_extension_str);

    return txt_for_dir(music_found_txt, temp_str);
}

void music_list_reset_selection()
{
    found_music_index = -1;
}

void music_list_refresh()
{
    found_music_index = -1;
    found_music_total = 0;
    found_music_total = scan_music_folder();

    int i = 0;
    for (i = 0; i < found_music_total; i++)
    {
        found_music_listbox[i] = _chr((music_found_txt->pstring)[i]);
    }
}

void play_selection_from_music_list()
{
    STRING *music_to_play_str = "";
    str_cpy(music_to_play_str, episode_music_folder_str);
    str_cat(music_to_play_str, selected_music);
    playing_music_handle = media_loop(music_to_play_str, NULL, playing_music_volume);
    playing_music_index = found_music_index;
}

void player_music_from_map(Map *map)
{
    if (!map)
    {
        return;
    }

    if (editor_state != EDITOR_STATE_TO_BUILD)
    {
        return;
    }

    STRING *music_to_play_str = "";
    str_cpy(music_to_play_str, _str(map->music));
    playing_music_handle = media_loop(music_to_play_str, NULL, playing_music_volume);
}

void stop_playing_music()
{
    media_stop(playing_music_handle);
}

int is_game_episode_loaded()
{
    return strlen(ep_save_name) > 0;
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

void map_copy(Map *to, Map *from)
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

    to->is_ceiling_visible = from->is_ceiling_visible;

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

    map_copy(map, NULL);

    int x = 0, y = 0, id = 0;
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

void episode_save_name_udpate_to(STRING *filename)
{
    strcpy(ep_save_name, _chr(filename));
}

void episode_change_info(Episode *episode, char *name, char *story_start, char *story_end, int map_count)
{
    if (!episode)
    {
        return;
    }

    strcpy(episode->name, name);
    strcpy(episode->story_start, story_start);
    strcpy(episode->story_end, story_end);
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

    int i = 0;
    for (i = 0; i < MAX_MAPS_PER_EPISODE; i++)
    {
        map_reset(&episode->map[i]);
    }
}

int episode_save(STRING *file_name, Episode *episode)
{
    if (!episode)
    {
        return false;
    }

    STRING *temp_str = "#256";
    str_cpy(temp_str, episode_save_folder_str);
    str_cat(temp_str, file_name);
    str_cat(temp_str, episode_extension_str);
    path_make_absolute(temp_str); // add 'save_dir' full path (in documents folder)

    void *returned_buffer = file_save(temp_str, episode, sizeof(Episode));
    if (returned_buffer == NULL)
    {
        return false;
    }

    return true;
}

int episode_load(STRING *file_name, Episode *episode)
{
    if (!episode)
    {
        return false;
    }

    STRING *temp_str = "#256";
    str_cpy(temp_str, episode_save_folder_str);
    str_cat(temp_str, file_name);
    str_cat(temp_str, episode_extension_str);
    path_make_absolute(temp_str); // add 'save_dir' full path (in documents folder)

    if (!file_exists(temp_str))
    {
        return false;
    }

    long _size = 0;
    void *buffer = file_load(temp_str, NULL, &_size);
    memcpy(episode, buffer, sizeof(Episode));
    void *returned_buffer = file_load(NULL, buffer, &_size);
    if (returned_buffer == NULL)
    {
        return false;
    }

    return true;
}