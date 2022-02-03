
void editor_browse_music_initialize()
{
    music_list_txt = txt_create(MAX_AMOUNT_OF_MUSIC_TO_LOAD, 0);
    set(music_list_txt, SHOW);
}

void editor_browse_music_destroy()
{
    if (music_list_txt)
    {
        ptr_remove(music_list_txt);
        music_list_txt = NULL;
    }
}

int editor_load_music()
{
    STRING *temp_str = "#256";
    str_cpy(temp_str, "music\\*");
    str_cat(temp_str, ".*");

    path_make_absolute(temp_str);

    cprintf0(temp_str);
    cprintf0("\n");

    return txt_for_dir(music_list_txt, temp_str);
}

void editor_browser_music_refresh_list()
{
    found_music_index = -1;
    found_music_total = 0;
    found_music_total = editor_load_music();

    int i = 0;
    for (i = 0; i < found_music_total; i++)
    {
        found_music_listbox[i] = _chr((music_list_txt->pstring)[i]);
    }
}

void editor_browser_music_update(Episode *e)
{
    if (!e)
    {
        return;
    }

    if (is_music_browser_opened == false)
    {
        return;
    }

    imgui_set_next_window_pos((screen_size.x / 2) - (MUSIC_BROWSER_WINDOW_WIDTH / 2), (screen_size.y / 2) - (MUSIC_BROWSER_WINDOW_HEIGHT / 2), ImGuiCond_Appearing);
    imgui_set_next_window_size(MUSIC_BROWSER_WINDOW_WIDTH, MUSIC_BROWSER_WINDOW_HEIGHT, ImGuiCond_Appearing);
    int music_browser_window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoSavedSettings;
    imgui_begin("Music browser", &is_music_browser_opened, music_browser_window_flags);

    int music_browser_child_window_flags = ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
    var editor_music_browser_width = imgui_get_content_region_avail_width();
    imgui_begin_child("##Editor Music Browser Child", vector(editor_music_browser_width, MUSIC_BROWSER_WINDOW_HEIGHT - 60, 0), 1, music_browser_child_window_flags);

    if (found_music_total <= 0)
    {
        imgui_text("'Music' - folder is empty.");
    }
    else
    {
        imgui_push_item_width(-1);
        if (imgui_list_box("##Editor Music Browser Listbox", &found_music_index, found_music_listbox, found_music_total, found_music_total))
        {
            int i = 0;
            for (i = 0; i < found_music_total; i++)
            {
                if (found_music_index == i)
                {
                    selected_music = found_music_listbox[i];
                }
            }
        }
        imgui_pop_item_width();
    }

    imgui_end_child();

    var button_width = ((MUSIC_BROWSER_WINDOW_HEIGHT - (engine_theme_win_padding[0] * 2)) / 4) - 3;
    if (imgui_button_withsize("Refresh", button_width, MUSIC_BROWSER_WINDOW_BUTTON_HEIGHT))
    {
        editor_browser_music_refresh_list();
    }
    imgui_same_line();
    if (imgui_button_withsize("Play/Stop", button_width, MUSIC_BROWSER_WINDOW_BUTTON_HEIGHT))
    {
    }
    imgui_same_line();
    if (imgui_button_withsize("Select", button_width, MUSIC_BROWSER_WINDOW_BUTTON_HEIGHT))
    {
    }
    imgui_same_line();
    if (imgui_button_withsize("Close", button_width, MUSIC_BROWSER_WINDOW_BUTTON_HEIGHT))
    {
    }

    imgui_end();
}