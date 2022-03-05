
void editor_empty_popup(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    if (is_popup_opened)
    {
        imgui_open_popup(empty_popup_id_str);
    }

    int editor_map_popup_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;
    if (imgui_begin_popup_modals_params(empty_popup_id_str, NULL, editor_map_popup_flags))
    {
        switch (empty_popup_state)
        {
        case EMPTY_POPUP_OPEN:
            editor_popup_open(episode);
            break;

        case EMPTY_POPUP_NEW:
            editor_popup_new(episode);
            break;

        case EMPTY_POPUP_SETTINGS:
            editor_popup_settings(episode);
            break;

        case EMPTY_POPUP_ABOUT:
            editor_popup_about();
            break;

        case EMPTY_POPUP_EXIT:
            editor_popup_exit();
            break;
        }

        imgui_end_popup();
    }
}

void editor_empty_top_bar()
{
    imgui_set_next_window_pos(0, 0, ImGuiCond_Always);
    imgui_set_next_window_size(screen_size.x, EDITOR_TOP_BAR_HEIGHT, ImGuiCond_Always);
    int top_bar_window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoFocusOnAppearing;
    imgui_begin(empty_top_bar_id_str, NULL, top_bar_window_flags);

    is_top_bar_used = false;

    if (imgui_begin_menu_bar())
    {
        if (imgui_begin_menu(_chr(editor_file_str), 1))
        {
            is_top_bar_used = true;

            if (imgui_menu_item(_chr(editor_open_str), "", 0, 1))
            {
                empty_popup_state = EMPTY_POPUP_OPEN;
                is_popup_opened = true;
            }
            if (imgui_menu_item(_chr(editor_new_str), "", 0, 1))
            {
                empty_popup_state = EMPTY_POPUP_NEW;
                is_popup_opened = true;
            }
            imgui_separator();
            if (imgui_menu_item(_chr(editor_preferences_str), "", 0, 1))
            {
                empty_popup_state = EMPTY_POPUP_SETTINGS;
                is_popup_opened = true;
            }
            imgui_separator();
            if (imgui_menu_item(_chr(editor_exit_str), "", 0, 1))
            {
                empty_popup_state = EMPTY_POPUP_EXIT;
                is_popup_opened = true;
            }
            imgui_end_menu();
        }

        if (imgui_begin_menu(_chr(editor_about_str), 1))
        {
            is_top_bar_used = true;

            if (imgui_menu_item(_chr(editor_help_str), "", 0, 1))
            {
                empty_popup_state = EMPTY_POPUP_ABOUT;
                is_popup_opened = true;
            }
            imgui_end_menu();
        }
        imgui_end_menu_bar();
    }

    imgui_end();
}

void editor_empty_background()
{
    camera->fog_end = FOG_MAX_END;
    camera->fog_start = FOG_MAX_END;

    camera->clip_near = 0.1;
    camera->clip_far = FOG_MAX_END * 1.25;

    fog_color = 4;
    vec_set(&sky_color, EMPTY_BACKGROUND_COLOR);
    vec_set(&d3d_fogcolor4, &sky_color);
}

void editor_empty_update(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    imgui_start_imode();
    editor_empty_top_bar();
    editor_empty_popup(episode);
    editor_empty_background();
    imgui_end_imode();
}