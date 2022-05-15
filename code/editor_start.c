
void editor_start_popups(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    if (is_popup_opened == true)
    {
        imgui_open_popup("##editor empty popup id");
    }

    int editor_empty_popup_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;
    if (imgui_begin_popup_modals_params("##editor empty popup id", NULL, editor_empty_popup_flags))
    {
        switch (editor_popup_state)
        {
        case EDITOR_POPUP_STATE_NEW:
            popup_new(episode);
            break;

        case EDITOR_POPUP_STATE_OPEN:
            popup_open(episode);
            break;

        case EDITOR_POPUP_STATE_SETTINGS:
            popup_settings();
            break;

        case EDITOR_POPUP_STATE_EXIT:
            popup_exit();
            break;

        case EDITOR_POPUP_STATE_WAIT_FOR_INPUT:
            popup_wait_for_input();
            break;

        case EDITOR_POPUP_STATE_HELP:
            popup_help();
            break;
        }
        imgui_end_popup();
    }
}

void editor_start_update(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    imgui_start_imode();

    var window_pos_x = (screen_size.x / 2) - ((START_WINDOW_WIDTH * config_current.font_scale) / 2);
    var window_pos_y = (screen_size.y / 2) - ((START_WINDOW_HEIGHT * config_current.font_scale) / 2);

    imgui_set_next_window_pos(window_pos_x, window_pos_y, ImGuiCond_Always);
    imgui_set_next_window_size(START_WINDOW_WIDTH * config_saved.font_scale, START_WINDOW_HEIGHT * config_saved.font_scale, ImGuiCond_Always);
    int empty_window_flags = ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing;
    imgui_begin("##Episode editor", NULL, empty_window_flags);
    imgui_text_centered("Episode editor");
    imgui_separator();

    var button_height = EDITOR_BUTTON_HEIGHT * config_saved.font_scale;
    if (imgui_button_withsize("New", -1, button_height))
    {
        editor_switch_popup_to(EDITOR_POPUP_STATE_NEW);
    }

    if (imgui_button_withsize("Open", -1, button_height))
    {
        editor_switch_popup_to(EDITOR_POPUP_STATE_OPEN);
    }

    if (imgui_button_withsize("Settings", -1, button_height))
    {
        editor_switch_popup_to(EDITOR_POPUP_STATE_SETTINGS);
    }

    if (imgui_button_withsize("Exit", -1, button_height))
    {
        editor_switch_popup_to(EDITOR_POPUP_STATE_EXIT);
    }

    editor_start_popups(episode);

    imgui_end();
    imgui_end_imode();

    // handle esc without on_esc
    // because on_ engine events are handled after imgui
    // I've also separated esc from popup esc
    if (is_popup_opened == false)
    {
        is_esc_popup_allowed = false;

        if (key_esc)
        {
            if (is_esc_allowed == true)
            {
                editor_switch_popup_to(EDITOR_POPUP_STATE_EXIT);
                is_esc_allowed = false;
            }
        }
        else
        {
            is_esc_allowed = true;
        }
    }
    else // this part is used in popup functions
    {
        is_esc_allowed = false;

        if (key_esc)
        {
            if (is_esc_popup_allowed == true)
            {
                is_esc_popup_allowed = false;
            }
        }
        else
        {
            is_esc_popup_allowed = true;
        }
    }
}