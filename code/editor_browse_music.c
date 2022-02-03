
void editor_browse_music_initialize()
{
    music_list_txt = txt_create(MAX_AMOUNT_OF_MUSIC_TO_LOAD, 0);
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
    str_cat(temp_str, music_extension_str);

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

void editor_browser_play_music()
{
    STRING *music_to_play_str = "";
    str_cpy(music_to_play_str, "music\\");
    str_cat(music_to_play_str, selected_music);
    playing_music_handle = media_play(music_to_play_str, NULL, playing_music_volume);
    playing_music_index = found_music_index;
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
    imgui_set_next_window_size(MUSIC_BROWSER_WINDOW_WIDTH, -1, ImGuiCond_Appearing);
    int music_browser_window_flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing;
    imgui_begin("Music browser", &is_music_browser_opened, music_browser_window_flags);

    int music_browser_child_window_flags = ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
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

    if (media_playing(playing_music_handle))
    {
        str_cpy(currently_playing_str, "Currently playing: ");
        str_cat(currently_playing_str, _str(found_music_listbox[playing_music_index]));
        imgui_text(_chr(currently_playing_str));
    }
    else
    {
        str_cpy(currently_playing_str, "Currently playing: none");
        imgui_text(_chr(currently_playing_str));
    }

    imgui_text("Volume: ");
    imgui_same_line();
    imgui_push_item_width(-1);
    imgui_slider_var("##Music volume", &playing_music_volume, 0, 100);
    imgui_pop_item_width();

    imgui_separator();

    var button_width = ((MUSIC_BROWSER_WINDOW_WIDTH - (engine_theme_win_padding[0] * 2)) / 4) - 3;
    if (imgui_button_withsize("Refresh", button_width, MUSIC_BROWSER_WINDOW_BUTTON_HEIGHT))
    {
        episode_selecting_playing_failed = false;
        editor_browser_music_refresh_list();
    }
    imgui_same_line();
    if (imgui_button_withsize("Play/Stop", button_width, MUSIC_BROWSER_WINDOW_BUTTON_HEIGHT))
    {
        if (found_music_index >= 0)
        {
            episode_selecting_playing_failed = false;

            if (media_playing(playing_music_handle))
            {
                media_stop(playing_music_handle);

                if (playing_music_index != found_music_index)
                {
                    editor_browser_play_music();
                }
            }
            else
            {
                editor_browser_play_music();
            }
        }
        else
        {
            episode_selecting_playing_failed = true;
            media_stop(playing_music_handle);
        }
    }
    imgui_same_line();
    if (imgui_button_withsize("Use", button_width, MUSIC_BROWSER_WINDOW_BUTTON_HEIGHT))
    {
        if (found_music_index >= 0)
        {
            media_stop(playing_music_handle);
            episode_selecting_playing_failed = false;
            is_music_browser_opened = false;

            Map *current_map = map_get_active(e);
            if (!current_map)
            {
                return;
            }

            STRING *music_to_use_str = "";
            str_cpy(music_to_use_str, "music\\");
            str_cat(music_to_use_str, selected_music);

            strcpy(current_map->music, _chr(music_to_use_str));
        }
        else
        {
            episode_selecting_playing_failed = true;
        }
    }
    imgui_same_line();
    if (imgui_button_withsize("Close", button_width, MUSIC_BROWSER_WINDOW_BUTTON_HEIGHT))
    {
        media_stop(playing_music_handle);
        episode_selecting_playing_failed = false;
        is_music_browser_opened = false;
    }

    if (media_playing(playing_music_handle))
    {
        master_vol = playing_music_volume;
        media_tune(playing_music_handle, playing_music_volume, 0, 0);
    }

    if (episode_selecting_playing_failed == true)
    {
        imgui_push_style_color(ImGuiCol_TextDisabled, color4_red);
        imgui_text_disabled("         Please, select music file to play/use.");
        imgui_pop_style_color(1);
    }

    imgui_end();
}