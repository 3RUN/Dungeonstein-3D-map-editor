
void episode_list_initialize()
{
    episodes_found_txt = txt_create(MAX_EPISODES_TO_LOAD, 0);
    episode_list_refresh();
}

void episode_list_destroy()
{
    if (episodes_found_txt)
    {
        ptr_remove(episodes_found_txt);
        episodes_found_txt = NULL;
    }
}

var episode_list_load()
{
    STRING *temp_str = "#256";
    str_cpy(temp_str, episode_save_folder_str);
    str_cat(temp_str, "*");
    str_cat(temp_str, episode_extension_str);
    path_make_absolute(temp_str);

    return txt_for_dir(episodes_found_txt, temp_str);
}

void episode_selection_reset()
{
    found_episode_index = -1;
}

void episode_list_refresh()
{
    found_episode_index = -1;
    found_episodes_total = 0;
    found_episodes_total = episode_list_load();

    var i = 0;
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