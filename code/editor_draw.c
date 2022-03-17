
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
                    // sure ?
                }
                else
                {
                    // open
                }
            }
            if (imgui_menu_item("New", "", 0, 1))
            {
                if (is_game_episode_loaded() == true)
                {
                    // sure ?
                }
                else
                {
                    // new
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
            }
            imgui_separator();
            if (imgui_menu_item("Settings", "", 0, 1))
            {
            }
            imgui_separator();
            if (imgui_menu_item("Exit", "", 0, 1))
            {
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
            }
            if (imgui_menu_item("Edit", "", 0, 1))
            {
            }
            imgui_end_menu();
        }

        if (imgui_begin_menu("Map", 1))
        {
            is_top_bar_used = true;

            if (imgui_menu_item("Reset", "", 0, 1))
            {
            }
            if (imgui_menu_item("Settings", "", 0, 1))
            {
            }
            if (imgui_menu_item("Test run", "", 0, 1))
            {
            }
            imgui_end_menu();
        }

        if (imgui_begin_menu("About", 1))
        {
            is_top_bar_used = true;

            if (imgui_menu_item("Help", "", 0, 1))
            {
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
    imgui_end_imode();
}