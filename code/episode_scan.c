
void episode_scanner_initialize()
{
    episodes_found_txt = txt_create(MAX_EPISODES_TO_LOAD, 0);
    episode_list_refresh();

    music_found_txt = txt_create(MAX_AMOUNT_OF_MUSIC_TO_LOAD, 0);
    music_list_refresh();
}

void episode_scanner_destroy()
{
    safe_remove(episodes_found_txt);
    safe_remove(music_found_txt);
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