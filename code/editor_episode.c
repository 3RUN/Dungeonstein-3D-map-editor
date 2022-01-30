
void editor_episode_update(Episode *e)
{
    if (!e)
    {
        return;
    }

    imgui_start_imode();
    imgui_set_next_window_pos((screen_size.x / 2) - (EPISODE_WINDOW_WIDTH / 2), (screen_size.y / 2) - (EPISODE_WINDOW_HEIGHT / 2), ImGuiCond_Always);
    imgui_set_next_window_size(EPISODE_WINDOW_WIDTH, EPISODE_WINDOW_HEIGHT, ImGuiCond_Always);
    int side_bar_flags = ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing;
    imgui_begin("Create Episode", NULL, side_bar_flags);

    imgui_text("Name");
    imgui_same_line();
    editor_help_maker(_chr(str_printf(NULL, "The name of the episode. Character limit %d.", (long)EPISODE_NAME_LENGTH)));
    imgui_push_item_width(-1);
    imgui_input_text("##Name", e->name, EPISODE_NAME_LENGTH, NULL);
    imgui_pop_item_width();

    imgui_text("Short story");
    imgui_same_line();
    editor_help_maker(_chr(str_printf(NULL, "Short episode story. Character limit %d.", (long)EPISODE_STORY_LENGTH)));
    imgui_input_text_multiline("##Multiline", e->story, EPISODE_STORY_LENGTH, -1, 128, NULL);

    imgui_text("Map count");
    imgui_same_line();
    editor_help_maker(_chr(str_printf(NULL, "Amount of maps in the episode. Max %d.", (long)MAX_MAPS_PER_EPISODE)));
    imgui_push_item_width(-1);
    imgui_slider_int("##Slider_01", &e->map_count, 1, MAX_MAPS_PER_EPISODE);
    imgui_pop_item_width();

    var button_width = ((EPISODE_WINDOW_WIDTH - (engine_theme_win_padding[0] * 2)) / 2) - 2.5;
    var button_height = 24;

    if (imgui_button_withsize("Create", button_width, button_height))
    {
        if (strlen(e->name) > 0 && strlen(e->story) > 0)
        {
            editor_switch_state_to(STATE_EDITOR);
        }
        else
        {
            episode_button_id = EPISODE_BUTTON_CREATE_ID;
            str_cpy(episode_popup_str, episode_create_popup_str);
            imgui_open_popup("##Episode popup");
        }
    }
    imgui_same_line();
    if (imgui_button_withsize("Exit", button_width, button_height))
    {
        episode_button_id = EPISODE_BUTTON_EXIT_ID;
        str_cpy(episode_popup_str, episode_exit_popup_str);
        imgui_open_popup("##Episode popup");
    }

    int popup_modal_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;
    if (imgui_begin_popup_modals_params("##Episode popup", NULL, popup_modal_flags))
    {
        imgui_text(_chr(episode_popup_str));

        if (episode_button_id == EPISODE_BUTTON_EXIT_ID)
        {
            if (imgui_button_withsize("Yes", -1, button_height))
            {
                sys_exit("");
            }

            if (imgui_button_withsize("No", -1, button_height) || key_esc)
            {
                imgui_close_current_popup();
            }
        }
        else if (episode_button_id == EPISODE_BUTTON_CREATE_ID)
        {
            if (imgui_button_withsize("Ok", -1, button_height) || key_esc)
            {
                imgui_close_current_popup();
            }
        }

        imgui_end_popup();
    }

    imgui_end();
    imgui_end_imode();
}