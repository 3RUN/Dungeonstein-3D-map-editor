
void editor_switch_popup_to(int state)
{
    is_popup_opened = true;
    draw_popup_old_state = draw_popup_state;
    draw_popup_state = state;
}

void editor_popups(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    if (is_popup_opened == true)
    {
        imgui_open_popup(editor_draw_popup_id);
    }

    int editor_pause_popup_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;
    if (imgui_begin_popup_modals_params(editor_draw_popup_id, NULL, editor_pause_popup_flags))
    {
        switch (draw_popup_state)
        {
        case DRAW_POPUP_OPEN:
            popup_open(episode);
            break;

        case DRAW_POPUP_SURE_OPEN:
            popup_open_sure();
            break;

        case DRAW_POPUP_NEW:
            popup_new(episode);
            break;

        case DRAW_POPUP_SURE_NEW:
            popup_new_sure();
            break;

        case DRAW_POPUP_SAVE_AS:
            popup_save_as(episode);
            break;

        case DRAW_POPUP_SETTINGS:
            popup_settings();
            break;

        case DRAW_POPUP_EXIT:
            popup_exit();
            break;

        case DRAW_POPUP_EP_RESET:
            popup_ep_reset(episode);
            break;

        case DRAW_POPUP_EP_EDIT:
            popup_ep_edit(episode);
            break;

        case DRAW_POPUP_MAP_RESET:
            popup_map_reset(episode);
            break;

        case DRAW_POPUP_HELP:
            popups_help();
            break;

        case DRAW_POPUP_WAIT_FOR_INPUT:
            popups_wait_for_input();
            break;
        }
        imgui_end_popup();
    }
}

void editor_top_bar(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    imgui_set_next_window_pos(0, 0, ImGuiCond_Always);
    imgui_set_next_window_size(screen_size.x, EDITOR_TOP_BAR_HEIGHT * config_saved.font_scale, ImGuiCond_Always);
    int top_bar_window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoFocusOnAppearing;
    imgui_begin(editor_top_bar_id, NULL, top_bar_window_flags);

    is_top_bar_used = false;

    if (imgui_begin_menu_bar())
    {
        if (imgui_begin_menu("File", 1))
        {
            is_top_bar_used = true;

            if (imgui_menu_item("Open", "", 0, 1))
            {
                if (is_game_episode_loaded() == true)
                {
                    editor_switch_popup_to(DRAW_POPUP_SURE_OPEN);
                }
                else
                {
                    editor_switch_popup_to(DRAW_POPUP_OPEN);
                }
            }
            if (imgui_menu_item("New", "", 0, 1))
            {
                if (is_game_episode_loaded() == true)
                {
                    editor_switch_popup_to(DRAW_POPUP_SURE_NEW);
                }
                else
                {
                    editor_switch_popup_to(DRAW_POPUP_NEW);
                }
            }
            imgui_separator();
            if (is_game_episode_loaded() == true)
            {
                if (imgui_menu_item("Save", "", 0, 1))
                {
                    editor_switch_state_to(EDITOR_STATE_SAVE);
                }
            }
            if (imgui_menu_item("Save as", "", 0, 1))
            {
                strcpy(save_as_filename, ep_save_name);
                editor_switch_popup_to(DRAW_POPUP_SAVE_AS);
            }
            imgui_separator();
            if (imgui_menu_item("Settings", "", 0, 1))
            {
                editor_switch_popup_to(DRAW_POPUP_SETTINGS);
            }
            imgui_separator();
            if (imgui_menu_item("Exit", "", 0, 1))
            {
                editor_switch_popup_to(DRAW_POPUP_EXIT);
            }
            imgui_end_menu();
        }

        if (imgui_begin_menu("View", 1))
        {
            is_top_bar_used = true;

            imgui_checkbox("Grid", &is_grid_visible);
            if (imgui_checkbox("Walls", &is_walls_visible) || imgui_checkbox("Objects", &is_objects_visible))
            {
            }
            imgui_checkbox("Object connections", &is_cell_links_visible);
            imgui_checkbox("Debug panel", &is_debug_panel_visible);
            imgui_end_menu();
        }

        if (imgui_begin_menu("Episode", 1))
        {
            is_top_bar_used = true;

            if (imgui_menu_item("Reset", "", 0, 1))
            {
                editor_switch_popup_to(DRAW_POPUP_EP_RESET);
            }
            if (imgui_menu_item("Edit", "", 0, 1))
            {
                strcpy(episode_edit_name, episode->name);
                strcpy(episode_edit_story_start, episode->story_start);
                strcpy(episode_edit_story_end, episode->story_end);
                episode_edit_map_count = episode->map_count;
                editor_switch_popup_to(DRAW_POPUP_EP_EDIT);
            }
            imgui_end_menu();
        }

        if (imgui_begin_menu("Map", 1))
        {
            is_top_bar_used = true;

            if (imgui_menu_item("Reset", "", 0, 1))
            {
                editor_switch_popup_to(DRAW_POPUP_MAP_RESET);
            }
            if (imgui_menu_item("Settings", "", 0, 1))
            {
                editor_switch_state_to(EDITOR_STATE_TO_MAP_SETTINGS);
            }
            if (imgui_menu_item("Test run", "", 0, 1))
            {
                editor_switch_state_to(EDITOR_STATE_TO_BUILD);
            }
            imgui_end_menu();
        }

        if (imgui_begin_menu("About", 1))
        {
            is_top_bar_used = true;

            if (imgui_menu_item("Help", "", 0, 1))
            {
                editor_switch_popup_to(DRAW_POPUP_HELP);
            }
            imgui_end_menu();
        }

        imgui_end_menu_bar();
    }

    imgui_end();
}

void editor_draw_update(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    imgui_start_imode();
    editor_top_bar(episode);
    editor_popups(episode);
    imgui_end_imode();
}