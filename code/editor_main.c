
void editor_tile_preview()
{
}

void editor_side_bar(Episode *e)
{
    imgui_set_next_window_pos(screen_size.x - EDITOR_SIDE_BAR_WIDTH, EDITOR_TOP_BAR_HEIGHT, ImGuiCond_Always);
    imgui_set_next_window_size(EDITOR_SIDE_BAR_WIDTH, screen_size.y - EDITOR_TOP_BAR_HEIGHT, ImGuiCond_Always);
    int side_bar_flags = ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing;
    imgui_begin("##Side Bar", NULL, side_bar_flags);

    if (imgui_collapsing_header("Preview", NULL, ImGuiTreeNodeFlags_DefaultOpen))
    {
        editor_tile_preview();
    }
    imgui_separator();

    if (imgui_collapsing_header("Assets", NULL, ImGuiTreeNodeFlags_DefaultOpen))
    {
    }
    imgui_separator();

    if (imgui_collapsing_header("Map settings", NULL, ImGuiTreeNodeFlags_DefaultOpen))
    {
    }
    imgui_separator();

    imgui_end();
}

void editor_settings_refresh()
{
    // resolution
    int i = 0;
    STRING *temp_resolution = "";
    for (i = 0; i < screen_resolutions_total; i++)
    {
        str_cpy(temp_resolution, str_for_num(NULL, screen_resolution_available_list[SCREEN_RESOLUTION_WIDTH][i]));
        str_cat(temp_resolution, "x");
        str_cat(temp_resolution, str_for_num(NULL, screen_resolution_available_list[SCREEN_RESOLUTION_HEIGHT][i]));

        // updated selected one
        if (config_current.graphics_video_res_id == i)
        {
            str_cpy(graphics_resolution_currently_used_str, temp_resolution);
        }
    }

    // display modes
    for (i = 0; i < DISPLAY_MODES_MAX; i++)
    {
        // update selected one
        if (config_current.graphics_display_mode == i)
        {
            str_cpy(graphics_display_currently_used_str, graphics_display_mode_list_str[i]);
        }
    }
}

void editor_settings_window()
{
    if (is_settings_opened == false)
    {
        return;
    }

    int window_width = 480;
    int window_height = 240;
    imgui_set_next_window_pos((screen_size.x / 2) - (window_width / 2), (screen_size.y / 2) - (window_height / 2), ImGuiCond_Appearing);
    imgui_set_next_window_size(window_width, window_height, ImGuiCond_Appearing);
    int settings_window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoSavedSettings;
    imgui_begin("Settings##Settings window", &is_settings_opened, settings_window_flags);
    imgui_separator();

    var settings_child_height = window_height - ((BUTTON_HEIGHT * 2) + engine_theme_win_padding[1]);
    int settings_child_flags = ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
    imgui_begin_child("##Settings Child", vector(-1, settings_child_height, 0), 1, settings_child_flags);

    // display mode here
    imgui_text(_chr(graphics_display_mode_str));
    imgui_same_line();
    imgui_align_right_with_offset(COMBOBOX_WIDTH);
    imgui_push_item_width(COMBOBOX_WIDTH - 1);
    if (imgui_begin_combo("##Display mode Combo", _chr(graphics_display_currently_used_str), ImGuiComboFlags_HeightSmall))
    {
        int n = 0;
        for (n = 0; n < DISPLAY_MODES_MAX; n++)
        {
            BOOL is_selected = str_cmp(graphics_display_currently_used_str, graphics_display_mode_list_str[n]);
            if (imgui_selectable(_chr(graphics_display_mode_list_str[n]), &is_selected, 0))
            {
                config_current.graphics_display_mode = n; // currently used display mode setting
                str_cpy(graphics_display_currently_used_str, graphics_display_mode_list_str[n]);

                // reset screen resolution to the first one from the list
                str_cpy(graphics_resolution_currently_used_str, graphics_resolution_available_list_str[0]);
                config_current.graphics_video_res_id = 0;
            }
            if (is_selected)
            {
                imgui_set_item_default_focus();
            }
        }
        imgui_end_combo();
    }
    imgui_pop_item_width();

    // screen resolution
    // only if in windowed mode
    if (config_current.graphics_display_mode == DISPLAY_MODE_WINDOWED)
    {
        imgui_text(_chr(graphics_res_str));
        imgui_same_line();
        imgui_align_right_with_offset(COMBOBOX_WIDTH);
        imgui_push_item_width(COMBOBOX_WIDTH - 1);
        if (imgui_begin_combo("##Resolution Combo", _chr(graphics_resolution_currently_used_str), ImGuiComboFlags_HeightSmall))
        {
            int n = 0;
            for (n = 0; n < screen_resolutions_total; n++)
            {
                // if in windowed mode then make sure to clip resolutions equal or higher than the desktop resolutions
                if (config_current.graphics_display_mode == DISPLAY_MODE_WINDOWED)
                {
                    if (n >= desktop_resolution_id)
                    {
                        continue;
                    }
                }

                // if in windowed fullscreen (borderless) then make sure to clip resolutions higher than the desktop resolution
                if (config_current.graphics_display_mode == DISPLAY_MODE_WINDOWED_FULLSCREEN)
                {
                    if (n > desktop_resolution_id)
                    {
                        continue;
                    }
                }

                BOOL is_selected = str_cmp(graphics_resolution_currently_used_str, graphics_resolution_available_list_str[n]);
                if (imgui_selectable(_chr(graphics_resolution_available_list_str[n]), &is_selected, 0))
                {
                    config_current.graphics_video_res_id = n; // currently used resolution ID
                    str_cpy(graphics_resolution_currently_used_str, graphics_resolution_available_list_str[n]);
                }
                if (is_selected)
                {
                    imgui_set_item_default_focus();
                }
            }
            imgui_end_combo();
        }
        imgui_pop_item_width();
    }
    imgui_separator();

    // tooltip
    imgui_text("Hovering cell tooltip: ");
    imgui_same_line();
    imgui_align_right_with_offset(150);
    imgui_radiobutton("Enabled", &config_current.is_cell_tooltip_enabled, true);
    imgui_same_line();
    imgui_radiobutton("Disabled", &config_current.is_cell_tooltip_enabled, false);
    imgui_separator();

    imgui_end_child();

    // reset to defaults button
    if (imgui_button_withsize("Defaults", BUTTON_WIDTH, 32))
    {
        config_reset_to_default();
        editor_settings_refresh();
    }

    imgui_same_line();
    imgui_align_right_with_offset(BUTTON_WIDTH * 2 + engine_theme_item_spacing[1]);

    // apply and save
    if (imgui_button_withsize("Ok", BUTTON_WIDTH, 32))
    {
        config_save_n_apply();
        editor_settings_refresh();
        is_settings_opened = false;
    }

    imgui_same_line();

    // cancel changes
    if (imgui_button_withsize("Cancel", BUTTON_WIDTH, 32))
    {
        config_reset_to_saved();
        editor_settings_refresh();
        is_settings_opened = false;
    }

    imgui_end();
}

void editor_help_window()
{
    if (is_help_opened == false)
    {
        return;
    }

    int window_width = 128;
    int window_height = 64;
    imgui_set_next_window_pos((screen_size.x / 2) - (window_width / 2), (screen_size.y / 2) - (window_height / 2), ImGuiCond_Appearing);
    imgui_set_next_window_size(window_width, window_height, ImGuiCond_Appearing);
    int about_window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoSavedSettings;
    imgui_begin("About##About window", &is_help_opened, about_window_flags);

    imgui_text("blahblahblah");

    imgui_end();
}

void editor_top_bar(Episode *e)
{
    imgui_set_next_window_pos(0, 0, ImGuiCond_Always);
    imgui_set_next_window_size(screen_size.x, EDITOR_TOP_BAR_HEIGHT, ImGuiCond_Always);
    int top_bar_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoFocusOnAppearing;
    imgui_begin("##Top bar", NULL, top_bar_flags);

    if (imgui_begin_menu_bar())
    {
        if (imgui_begin_menu("File", 1))
        {
            if (imgui_menu_item("Save", "", 0, 1))
            {
                editor_switch_state_to(STATE_SAVE);
            }
            if (imgui_menu_item("Load", "", 0, 1))
            {
                editor_switch_state_to(STATE_LOAD);
            }
            imgui_separator();
            if (imgui_menu_item("Exit", "", 0, 1))
            {
                is_popup_opened = true;
            }
            imgui_end_menu();
        }

        if (imgui_begin_menu("View", 1))
        {
            imgui_checkbox("Grid", &is_grid_visible);
            imgui_checkbox("Walls", &is_walls_visible);
            imgui_checkbox("Objects", &is_objects_visible);
            imgui_end_menu();
        }

        if (imgui_begin_menu("Editor", 1))
        {
            if (imgui_menu_item("Settings", "", 0, 1))
            {
                is_settings_opened = 1 - is_settings_opened;
            }
            imgui_end_menu();
        }

        if (imgui_begin_menu("Help", 1))
        {
            if (imgui_menu_item("About", "", 0, 1))
            {
                is_help_opened = 1 - is_help_opened;
            }
            imgui_end_menu();
        }

        imgui_end_menu_bar();
    }

    editor_settings_window();
    editor_help_window();

    if (is_popup_opened == true)
    {
        imgui_open_popup("##Editor main popup");
    }

    int popup_modal_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;
    if (imgui_begin_popup_modals_params("##Editor main popup", NULL, popup_modal_flags))
    {
        imgui_text(_chr(editor_back_to_menu_popup_str));

        if (imgui_button_withsize("Yes", -1, MENU_WINDOW_BUTTON_HEIGHT))
        {
            is_popup_opened = false;
            episode_reset(e);
            editor_main_reset();
            editor_switch_state_to(STATE_MENU);
        }

        if (imgui_button_withsize("No", -1, MENU_WINDOW_BUTTON_HEIGHT))
        {
            is_popup_opened = false;
            imgui_close_current_popup();
        }

        imgui_end_popup();
    }

    imgui_end();
}

void editor_main_initialize()
{
    int i = 0;

    // resolution
    STRING *temp_resolution = "";
    for (i = 0; i < screen_resolutions_total; i++)
    {
        str_cpy(temp_resolution, str_for_num(NULL, screen_resolution_available_list[SCREEN_RESOLUTION_WIDTH][i]));
        str_cat(temp_resolution, "x");
        str_cat(temp_resolution, str_for_num(NULL, screen_resolution_available_list[SCREEN_RESOLUTION_HEIGHT][i]));

        if (!graphics_resolution_available_list_str[i])
        {
            graphics_resolution_available_list_str[i] = str_create("");
            str_cpy(graphics_resolution_available_list_str[i], temp_resolution);
        }
    }

    // display modes
    for (i = 0; i < DISPLAY_MODES_MAX; i++)
    {
        if (!graphics_display_mode_list_str[i])
        {
            graphics_display_mode_list_str[i] = str_create("");
            switch (i)
            {
            case DISPLAY_MODE_WINDOWED:
                str_cpy(graphics_display_mode_list_str[i], graphics_display_windowed_str);
                break;

            case DISPLAY_MODE_WINDOWED_FULLSCREEN:
                str_cpy(graphics_display_mode_list_str[i], graphics_display_windowed_fullscreen_str);
                break;
            }
        }
    }
    editor_settings_refresh();
}

void editor_main_reset()
{
    is_settings_opened = false;
    is_help_opened = false;

    is_grid_visible = true;
    is_walls_visible = true;
    is_objects_visible = true;
}

void editor_main_update(Episode *e)
{
    if (!e)
    {
        return;
    }

    imgui_start_imode();

    editor_side_bar(e);
    editor_top_bar(e);

    imgui_end_imode();
}