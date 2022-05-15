
void popups_initialize()
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

    popups_refresh();
}

void popups_refresh()
{
    int i = 0;

    // resolution
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

void popups_destroy()
{
    int i = 0;

    for (i = 0; i < screen_resolutions_total; i++)
    {
        if (graphics_resolution_available_list_str[i])
        {
            ptr_remove(graphics_resolution_available_list_str[i]);
        }
    }

    for (i = 0; i < DISPLAY_MODES_MAX; i++)
    {
        if (graphics_display_mode_list_str[i])
        {
            ptr_remove(graphics_display_mode_list_str[i]);
        }
    }
}

void popup_new(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    imgui_text_centered("Create new episode");
    imgui_separator();

    imgui_text("File name");
    imgui_same_line();
    imgui_text(_chr(str_printf(NULL, "(%d / %d)", (long)strlen(new_episode_filename), (long)(EPISODE_NAME_LENGTH - 1))));
    imgui_push_item_width(-1);
    imgui_input_text("##popup episode new filename id", new_episode_filename, EPISODE_NAME_LENGTH, NULL);
    imgui_pop_item_width();

    imgui_text("Episode name");
    imgui_same_line();
    imgui_text(_chr(str_printf(NULL, "(%d / %d)", (long)strlen(new_episode_name), (long)(EPISODE_NAME_LENGTH - 1))));
    imgui_push_item_width(-1);
    imgui_input_text("##popup episode new name id", new_episode_name, EPISODE_NAME_LENGTH, NULL);
    imgui_pop_item_width();

    imgui_text("Map count");
    imgui_same_line();
    imgui_text(_chr(str_printf(NULL, "(%d / %d)", (long)new_episode_map_count, (long)MAX_MAPS_PER_EPISODE)));
    imgui_push_item_width(-1);
    imgui_slider_int("##popup episode new map cound slider id", &new_episode_map_count, 1, MAX_MAPS_PER_EPISODE);
    imgui_pop_item_width();

    var width = (POPUP_NEW_WIDTH * config_saved.font_scale) / 2;
    if (imgui_button_withsize(_chr(popup_new_button_str), width, EDITOR_BUTTON_HEIGHT * config_saved.font_scale) || key_enter)
    {
        if (strlen(new_episode_filename) > 0 && strlen(new_episode_name) > 0)
        {
            is_popup_check_failed = false;
            is_popup_opened = false;
            imgui_close_current_popup();
            editor_switch_state_to(EDITOR_STATE_NEW);
        }
        else
        {
            is_popup_check_failed = true;
        }
    }

    imgui_same_line();
    if (imgui_button_withsize("Back", width, EDITOR_BUTTON_HEIGHT * config_saved.font_scale) || key_esc && is_esc_popup_allowed == true)
    {
        is_popup_check_failed = false;
        strcpy(new_episode_filename, "");
        strcpy(new_episode_name, "");
        new_episode_map_count = 1;

        is_popup_opened = false;
        imgui_close_current_popup();
    }

    if (is_popup_check_failed == true)
    {
        imgui_push_style_color(ImGuiCol_TextDisabled, color4_red);
        imgui_text_disabled_centered("Make sure to enter filename, name and start/end stories!");
        imgui_pop_style_color(1);
    }

    STRING *check_name = "";
    str_cpy(check_name, episode_save_folder_str);
    str_cat(check_name, new_episode_filename);
    str_cat(check_name, episode_extension_str);
    path_make_absolute(check_name);

    if (file_exists(check_name))
    {
        str_cpy(popup_new_button_str, "Overwrite");
        imgui_push_style_color(ImGuiCol_TextDisabled, color4_red);
        imgui_text_disabled_centered("Episode with this name already exists!");
        imgui_pop_style_color(1);
    }
    else
    {
        str_cpy(popup_new_button_str, "Create");
    }
}

void popup_open(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    imgui_text_centered("Open episode");
    imgui_separator();

    int popup_open_child_flags = ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
    imgui_begin_child("##popup episode open browser child id", vector(-1, (POPUP_OPEN_HEIGHT * config_saved.font_scale) - (60 * config_saved.font_scale), 0), 1, popup_open_child_flags);

    if (found_episodes_total <= 0)
    {
        imgui_text("'Documents\\Dungeonstein3D\\episodes' - folder is empty.");
    }
    else
    {
        imgui_push_item_width(-1);
        if (imgui_list_box("##popup episode open listbox", &found_episode_index, found_episodes_listbox, found_episodes_total, found_episodes_total))
        {
            int i = 0;
            for (i = 0; i < found_episodes_total; i++)
            {
                if (found_episode_index == i)
                {
                    selected_episode = found_episodes_listbox[i];
                }
            }
        }
        imgui_pop_item_width();
    }

    imgui_end_child();

    if (imgui_button_withsize("Refresh", -1, EDITOR_BUTTON_HEIGHT * config_saved.font_scale))
    {
        is_popup_check_failed = false;
        episode_list_refresh();
    }

    var width = (POPUP_OPEN_WIDTH * config_saved.font_scale) / 3;
    imgui_push_id(POPUP_DELETE_BUTTON_ID);
    imgui_push_style_color_hsv(ImGuiCol_Button, 0, 0.7, 0.7, 1.0);
    imgui_push_style_color_hsv(ImGuiCol_ButtonHovered, 0, 0.8, 0.8, 1.0);
    imgui_push_style_color_hsv(ImGuiCol_ButtonActive, 0, 0.9, 0.9, 1.0);
    var delete_button = imgui_button_withsize("Delete", width, EDITOR_BUTTON_HEIGHT * config_saved.font_scale);
    imgui_pop_style_color(3);
    imgui_pop_id();

    if (delete_button == true)
    {
        if (found_episode_index >= 0)
        {
            STRING *delete_name = "";
            str_cpy(delete_name, episode_save_folder_str);
            str_cat(delete_name, selected_episode);
            str_cat(delete_name, episode_extension_str);
            path_make_absolute(delete_name);

            is_popup_check_failed = false;
            file_delete(delete_name);

            episode_list_refresh();
        }
        else
        {
            is_popup_check_failed = true;
        }
    }

    imgui_same_line();
    if (imgui_button_withsize("Open", width, EDITOR_BUTTON_HEIGHT * config_saved.font_scale) || key_enter)
    {
        if (found_episode_index >= 0)
        {
            is_popup_check_failed = false;
            is_popup_opened = false;
            imgui_close_current_popup();
            editor_switch_state_to(EDITOR_STATE_OPEN);
        }
        else
        {
            is_popup_check_failed = true;
        }
    }

    imgui_same_line();
    if (imgui_button_withsize("Cancel", width, EDITOR_BUTTON_HEIGHT * config_saved.font_scale) || key_esc && is_esc_popup_allowed == true)
    {
        found_episode_index = -1;
        is_popup_check_failed = false;
        is_popup_opened = false;
        imgui_close_current_popup();
    }

    if (is_popup_check_failed == true)
    {
        imgui_push_style_color(ImGuiCol_TextDisabled, color4_red);
        imgui_text_disabled_centered("Select an episode from the list!");
        imgui_pop_style_color(1);
    }
}

void popup_settings_general()
{
    int general_child_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
    imgui_begin_child("##popup settings general child window id", vector(-1, POPUP_SETTINGS_CHILD_HEIGHT * config_saved.font_scale, 0), 0, general_child_flags);

    imgui_text_disabled_centered("AUDIO");

    imgui_text("Master volume:");
    imgui_same_line();
    imgui_align_right_with_offset(EDITOR_COMBOBOX_WIDTH * config_saved.font_scale);
    imgui_push_item_width((EDITOR_COMBOBOX_WIDTH * config_saved.font_scale) - 1);
    imgui_slider_float("##popup settings master volume slider id", &config_current.master_volume, SND_VOLUME_MIN, SND_VOLUME_MAX, "%.1f", 1);
    imgui_pop_item_width();

    master_vol = config_current.master_volume;

    imgui_separator();
    imgui_text_disabled_centered("UI");

    // font scale
    imgui_text("Font scale:");
    imgui_same_line();
    imgui_align_right_with_offset(EDITOR_COMBOBOX_WIDTH * config_saved.font_scale);
    imgui_push_item_width((EDITOR_COMBOBOX_WIDTH * config_saved.font_scale) - 1);
    imgui_slider_float("##popup settings font scale slider id", &config_current.font_scale, FONT_SCALE_MIN, FONT_SCALE_MAX, "%.1f", 1);
    imgui_pop_item_width();

    // background color
    imgui_text("Background color:");
    imgui_same_line();
    imgui_align_right_with_offset(EDITOR_COMBOBOX_WIDTH * config_saved.font_scale);
    imgui_push_item_width((EDITOR_COMBOBOX_WIDTH * config_saved.font_scale) - 1);
    static int misc_flags = ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoDragDrop;
    imgui_color_edit3("##popup settings background color picker id", config_current.background_color, misc_flags);
    imgui_pop_item_width();

    // grid color
    imgui_text("Grid color:");
    imgui_same_line();
    imgui_align_right_with_offset(EDITOR_COMBOBOX_WIDTH * config_saved.font_scale);
    imgui_push_item_width((EDITOR_COMBOBOX_WIDTH * config_saved.font_scale) - 1);
    static int misc_flags = ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoDragDrop;
    imgui_color_edit3("##popup settings grid color picker id", config_current.grid_color, misc_flags);
    imgui_pop_item_width();

    imgui_separator();
    imgui_text_disabled_centered("GRAPHICS");

    // display mode here
    imgui_text(_chr(graphics_display_mode_str));
    imgui_same_line();
    imgui_align_right_with_offset(EDITOR_COMBOBOX_WIDTH * config_saved.font_scale);
    imgui_push_item_width((EDITOR_COMBOBOX_WIDTH * config_saved.font_scale) - 1);
    if (imgui_begin_combo("##popup settings display mode combobox id", _chr(graphics_display_currently_used_str), ImGuiComboFlags_HeightSmall))
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
        imgui_align_right_with_offset(EDITOR_COMBOBOX_WIDTH * config_saved.font_scale);
        imgui_push_item_width((EDITOR_COMBOBOX_WIDTH * config_saved.font_scale) - 1);
        if (imgui_begin_combo("##popup settings resolution combobox id", _chr(graphics_resolution_currently_used_str), ImGuiComboFlags_HeightSmall))
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

    imgui_end_child();
}

void popup_settings_input()
{
    int input_main_child_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
    imgui_begin_child("##popup settings input child id", vector(-1, POPUP_SETTINGS_CHILD_HEIGHT * config_saved.font_scale, 0), 0, input_main_child_flags);

    imgui_text_disabled_centered("MOUSE");

    imgui_text("Mouse sensitivity:");
    imgui_same_line();
    imgui_align_right_with_offset(EDITOR_COMBOBOX_WIDTH * config_saved.font_scale);
    imgui_push_item_width((EDITOR_COMBOBOX_WIDTH * config_saved.font_scale) - 1);
    imgui_slider_float("##popup settings mouse sensitivity slider id", &config_current.mouse_sensitivity, MOUSE_SENSE_MIN, MOUSE_SENSE_MAX, "%.1f", 1);
    imgui_pop_item_width();

    imgui_separator();
    imgui_text_disabled_centered("KEYBOARD");

    int input_child_flags = ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
    imgui_begin_child("##popup settings input buttons child id", vector(-1, -1, 0), 1, input_child_flags);

    if (settings_input_reset_scrollbar == true)
    {
        imgui_set_scroll_here_y(0);
        settings_input_reset_scrollbar = false;
    }

    imgui_text_disabled_centered("INPUT");
    imgui_separator();

    input_add_keybinding(input_forward_entry_str, config_current.input_forward);
    input_add_keybinding(input_backward_entry_str, config_current.input_backward);
    input_add_keybinding(input_strafe_left_entry_str, config_current.input_strafe_left);
    input_add_keybinding(input_strafe_right_entry_str, config_current.input_strafe_right);
    input_add_keybinding(input_fly_up_entry_str, config_current.input_fly_up);
    input_add_keybinding(input_fly_down_entry_str, config_current.input_fly_down);
    input_add_keybinding(input_run_entry_str, config_current.input_run);
    input_add_keybinding(input_rotate_cam_entry_str, config_current.input_rotate_camera);
    input_add_keybinding(input_draw_entry_str, config_current.input_draw);
    input_add_keybinding(input_erase_entry_str, config_current.input_erase);
    input_add_keybinding(input_pick_entry_str, config_current.input_pick);
    input_add_keybinding(input_rotate_entry_str, config_current.input_rotate);
    input_add_keybinding(input_toggle_assets_entry_str, config_current.input_toggle_assets);
    input_add_keybinding(input_toggle_lights_entry_str, config_current.input_toggle_lights);
    input_add_keybinding(input_toggle_draw_mode_entry_str, config_current.input_toggle_draw_mode);

    imgui_text_disabled_centered("SHORTCUTS");
    imgui_separator();

    shortcut_add_keybinding(short_help_entry_str, "", config_current.short_help);
    shortcut_add_keybinding(short_screenshot_entry_str, "", config_current.short_screenshot);
    shortcut_add_keybinding(short_new_entry_str, "", config_current.short_new);
    shortcut_add_keybinding(short_open_entry_str, "", config_current.short_open);
    shortcut_add_keybinding(short_settings_entry_str, "", config_current.short_settings);
    shortcut_add_keybinding(short_save_entry_str, "", config_current.short_save);
    shortcut_add_keybinding(short_ep_reset_entry_str, "", config_current.short_ep_reset);
    shortcut_add_keybinding(short_ep_edit_entry_str, "", config_current.short_ep_edit);
    shortcut_add_keybinding(short_map_reset_entry_str, "", config_current.short_map_reset);
    shortcut_add_keybinding(short_map_settings_entry_str, "", config_current.short_map_settings);
    shortcut_add_keybinding(short_toggle_hovering_entry_str, "", config_current.short_toggle_debug);
    shortcut_add_keybinding(short_toggle_debug_entry_str, "", config_current.short_toggle_hovering);
    shortcut_add_keybinding(short_map_prior_entry_str, "", config_current.short_map_prior);
    shortcut_add_keybinding(short_map_next_entry_str, "", config_current.short_map_next);
    shortcut_add_keybinding(short_map_shift_west_entry_str, "", config_current.short_map_shift_west);
    shortcut_add_keybinding(short_map_shift_east_entry_str, "", config_current.short_map_shift_east);
    shortcut_add_keybinding(short_map_shift_south_entry_str, "", config_current.short_map_shift_south);
    shortcut_add_keybinding(short_map_shift_north_entry_str, "", config_current.short_map_shift_north);

    imgui_end_child();
    imgui_end_child();
}

void popup_settings()
{
    imgui_text_centered("Settings");
    imgui_separator();

    int settings_tab_bar_flags = ImGuiTabBarFlags_NoTooltip | ImGuiTabBarFlags_TabListPopupButton | ImGuiTabBarFlags_FittingPolicyDefault_;
    if (imgui_begin_tabbar("##popup settings tabbars", settings_tab_bar_flags))
    {
        int settings_tab_item_falgs = ImGuiTabItemFlags_NoCloseWithMiddleMouseButton;
        if (imgui_begin_tabitem("General", NULL, settings_tab_item_falgs))
        {
            settings_tab_id = SETTINGS_TAB_GENERIC;
            settings_input_reset_scrollbar = true;
            popup_settings_general();
            imgui_end_tabitem();
        }

        if (imgui_begin_tabitem("Input", NULL, settings_tab_item_falgs))
        {
            settings_tab_id = SETTINGS_TAB_INPUT;
            popup_settings_input();
            imgui_end_tabitem();
        }

        imgui_end_tabbar();
    }

    // make a little offset
    imgui_separator();

    var width = (POPUP_SETTINGS_WIDTH * config_saved.font_scale) / 4;
    if (imgui_button_withsize("Defaults", width, EDITOR_BUTTON_HEIGHT * config_saved.font_scale)) // reset to defaults button
    {
        config_reset_to_default(settings_tab_id);
        popups_refresh();
    }

    // apply and save
    imgui_same_line();
    if (imgui_button_withsize("Apply", width, EDITOR_BUTTON_HEIGHT * config_saved.font_scale) || key_enter)
    {
        config_save();
        config_apply();
        popups_refresh();

        is_popup_opened = false;                    // restart popup to make sure
        imgui_close_current_popup();                // that if we've changed a screen resolution
        editor_switch_popup_to(editor_popup_state); // the popup is centered again
    }

    // apply, save and close
    imgui_same_line();
    if (imgui_button_withsize("Ok", width, EDITOR_BUTTON_HEIGHT * config_saved.font_scale))
    {
        config_save();
        config_apply();
        popups_refresh();

        settings_input_reset_scrollbar = true;

        is_popup_opened = false;
        imgui_close_current_popup();
    }

    // cancel changes
    imgui_same_line();
    if (imgui_button_withsize("Back", width, EDITOR_BUTTON_HEIGHT * config_saved.font_scale) || key_esc && is_esc_popup_allowed == true)
    {
        config_reset_to_saved();
        popups_refresh();

        settings_input_reset_scrollbar = true;

        is_popup_opened = false;
        imgui_close_current_popup();
    }
}

void popup_exit()
{
    imgui_text_centered("Are you sure you want to exit?");
    imgui_text_centered("All unsaved data will be lost!");
    imgui_separator();

    var width = (POPUP_EXIT_WIDTH * config_saved.font_scale) / 2;
    if (imgui_button_withsize("Yes", width, EDITOR_BUTTON_HEIGHT * config_saved.font_scale) || key_y || key_enter)
    {
        is_popup_opened = false;
        imgui_close_current_popup();
        editor_switch_state_to(EDITOR_STATE_EXIT);
    }

    imgui_same_line();
    if (imgui_button_withsize("No", width, EDITOR_BUTTON_HEIGHT * config_saved.font_scale) || key_esc && is_esc_popup_allowed == true || key_n)
    {
        is_popup_opened = false;
        imgui_close_current_popup();
    }
}

void popup_wait_for_input()
{
    imgui_text("Press anykey to bind it to selected command!");

    if (is_popup_opened == false)
    {
        imgui_close_current_popup();
    }
}

void popup_confirm_open()
{
    imgui_text_centered("Are you sure you want to open different episode?");
    imgui_text_centered("All unsaved data will be lost!");
    imgui_separator();

    var width = (POPUP_OPEN_CONFIRM_WIDTH * config_saved.font_scale) / 2;
    if (imgui_button_withsize("Yes", width, EDITOR_BUTTON_HEIGHT * config_saved.font_scale) || key_y)
    {
        // we first need to close old popup
        // because new one's positions won't be centered correctly !
        is_popup_opened = false;
        imgui_close_current_popup();

        // now move to the open state !
        editor_switch_popup_to(EDITOR_POPUP_STATE_OPEN);
    }

    imgui_same_line();
    if (imgui_button_withsize("No", width, EDITOR_BUTTON_HEIGHT * config_saved.font_scale) || key_esc && is_esc_popup_allowed == true || key_n)
    {
        is_popup_opened = false;
        imgui_close_current_popup();
    }
}

void popup_confirm_new()
{
    imgui_text_centered("Are you sure you want to create a new episode?");
    imgui_text_centered("All unsaved data will be lost!");
    imgui_separator();

    var width = (POPUP_NEW_CONFIRM_WIDTH * config_saved.font_scale) / 2;
    if (imgui_button_withsize("Yes", width, EDITOR_BUTTON_HEIGHT * config_saved.font_scale) || key_y)
    {
        // we first need to close old popup
        // because new one's positions won't be centered correctly !
        is_popup_opened = false;
        imgui_close_current_popup();

        // now move to the open state !
        editor_switch_popup_to(EDITOR_POPUP_STATE_NEW);
    }

    imgui_same_line();
    if (imgui_button_withsize("No", width, EDITOR_BUTTON_HEIGHT * config_saved.font_scale) || key_esc && is_esc_popup_allowed == true || key_n)
    {
        is_popup_opened = false;
        imgui_close_current_popup();
    }
}

void popup_save_as(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    imgui_text_centered("Save as");
    imgui_separator();

    imgui_text("Filename:");
    imgui_same_line();
    imgui_text(_chr(str_printf(NULL, "(%d / %d)", (long)strlen(save_as_filename), (long)(EPISODE_NAME_LENGTH - 1))));
    imgui_push_item_width(-1);
    imgui_input_text_with_hint("##popup save as id", "name", save_as_filename, EPISODE_NAME_LENGTH, NULL);
    imgui_pop_item_width();

    var width = (POPUP_SAVE_AS_WIDTH * config_saved.font_scale) / 2;
    if (imgui_button_withsize(_chr(popup_save_as_button_str), width, EDITOR_BUTTON_HEIGHT * config_saved.font_scale) || key_enter)
    {
        if (strlen(save_as_filename) > 0)
        {
            is_popup_check_failed = false;
            is_popup_opened = false;
            imgui_close_current_popup();

            STRING *temp_ep_name_str = "";
            str_cpy(temp_ep_name_str, _str(save_as_filename));
            str_cat(temp_ep_name_str, " saved.");
            message_add(temp_ep_name_str);

            episode_set_filename(_str(save_as_filename));
            episode_save(ep_filename, episode);
        }
        else
        {
            is_popup_check_failed = true;
        }
    }
    imgui_same_line();
    if (imgui_button_withsize("Cancel", width, EDITOR_BUTTON_HEIGHT * config_saved.font_scale) || key_esc && is_esc_popup_allowed == true)
    {
        strcpy(save_as_filename, "");
        is_popup_check_failed = false;
        is_popup_opened = false;
        imgui_close_current_popup();
    }

    if (is_popup_check_failed == true)
    {
        imgui_push_style_color(ImGuiCol_TextDisabled, color4_red);
        imgui_text_disabled_centered("You forgot to enter file name!");
        imgui_pop_style_color(1);
    }

    STRING *check_name = "";
    str_cpy(check_name, episode_save_folder_str);
    str_cat(check_name, save_as_filename);
    str_cat(check_name, episode_extension_str);
    path_make_absolute(check_name);

    if (file_exists(check_name))
    {
        str_cpy(popup_save_as_button_str, "Overwrite");
        imgui_push_style_color(ImGuiCol_TextDisabled, color4_red);
        imgui_text_disabled_centered("Episode with this name already exists!");
        imgui_pop_style_color(1);
    }
    else
    {
        str_cpy(popup_save_as_button_str, "Save");
    }
}

void popup_ep_reset(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    imgui_text_centered("Are you sure you want to reset the whole episode?");
    imgui_separator();

    var width = (POPUP_EPISODE_RESET_WIDTH * config_saved.font_scale) / 2;
    if (imgui_button_withsize("Yes", width, EDITOR_BUTTON_HEIGHT * config_saved.font_scale) || key_y)
    {
        STRING *str = "";
        str_cpy(str, "Episode \"");

        if (strlen(episode->name) > 0)
        {
            str_cat(str, _str(episode->name));
        }
        else
        {
            str_cat(str, "UNNAMED");
        }

        str_cat(str, "\" was reset");
        message_add(str);

        is_popup_opened = false;
        imgui_close_current_popup();
        episode_copy(episode, NULL);
        Map *active_map = map_get_active(episode);
        map_load(active_map);
    }

    imgui_same_line();
    if (imgui_button_withsize("No", width, EDITOR_BUTTON_HEIGHT * config_saved.font_scale) || key_esc && is_esc_popup_allowed == true || key_n)
    {
        is_popup_opened = false;
        imgui_close_current_popup();
    }
}

void popup_ep_edit(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    imgui_text_centered(_chr(str_printf(NULL, "Edit: %s", episode->name)));
    imgui_separator();

    imgui_text("Episode name");
    imgui_same_line();
    imgui_text(_chr(str_printf(NULL, "(%d / %d)", (long)strlen(episode_edit_name), (long)(EPISODE_NAME_LENGTH - 1))));
    imgui_push_item_width(-1);
    imgui_input_text("##popup episode edit name", episode_edit_name, EPISODE_NAME_LENGTH, NULL);
    imgui_pop_item_width();

    imgui_text("Map count");
    imgui_same_line();
    imgui_text(_chr(str_printf(NULL, "(%d / %d)", (long)episode_edit_map_count, (long)MAX_MAPS_PER_EPISODE)));
    imgui_push_item_width(-1);
    imgui_slider_int("##popup episode edit map count slider id", &episode_edit_map_count, 1, MAX_MAPS_PER_EPISODE);
    imgui_pop_item_width();

    var width = (POPUP_EPISODE_EDIT_WIDTH * config_saved.font_scale) / 3;
    if (imgui_button_withsize("Reset", width, EDITOR_BUTTON_HEIGHT * config_saved.font_scale))
    {
        is_popup_check_failed = false;
        strcpy(episode_edit_name, episode->name);
        episode_edit_map_count = episode->map_count;
    }

    imgui_same_line();
    if (imgui_button_withsize("Save", width, EDITOR_BUTTON_HEIGHT * config_saved.font_scale) || key_enter)
    {
        if (strlen(episode_edit_name) > 0)
        {
            STRING *temp_ep_name_str = "";
            str_cpy(temp_ep_name_str, "Episode ");
            str_cat(temp_ep_name_str, _str(episode_edit_name));
            str_cat(temp_ep_name_str, " edited.");
            message_add(temp_ep_name_str);

            is_popup_check_failed = false;
            episode_edit_info(episode, episode_edit_name, episode_edit_map_count);

            is_popup_opened = false;
            imgui_close_current_popup();
        }
        else
        {
            is_popup_check_failed = true;
        }
    }

    imgui_same_line();
    if (imgui_button_withsize("Cancel", width, EDITOR_BUTTON_HEIGHT * config_saved.font_scale) || key_esc && is_esc_popup_allowed == true)
    {
        is_popup_check_failed = false;
        strcpy(episode_edit_name, episode->name);
        episode_edit_map_count = episode->map_count;

        is_popup_opened = false;
        imgui_close_current_popup();
    }

    if (is_popup_check_failed == true)
    {
        imgui_push_style_color(ImGuiCol_TextDisabled, color4_red);
        imgui_text_disabled_centered("Make sure to enter episode name and start/end stories!");
        imgui_pop_style_color(1);
    }
}

void popup_map_reset(Map *map)
{
    if (!map)
    {
        return;
    }

    imgui_text_centered("Are you sure you want to reset current map?");
    imgui_separator();

    var width = (POPUP_MAP_RESET_WIDTH * config_saved.font_scale) / 2;
    if (imgui_button_withsize("Yes", width, EDITOR_BUTTON_HEIGHT * config_saved.font_scale) || key_y)
    {
        message_add(str_printf(NULL, "Map %d was reset", (long)active_map_id));

        is_popup_opened = false;
        imgui_close_current_popup();
        map_copy(map, NULL);
        map_load(map);
    }

    imgui_same_line();
    if (imgui_button_withsize("No", width, EDITOR_BUTTON_HEIGHT * config_saved.font_scale) || key_esc && is_esc_popup_allowed == true || key_n)
    {
        is_popup_opened = false;
        imgui_close_current_popup();
    }
}

void popup_help()
{
    imgui_text_centered("Help");
    imgui_separator();

    int popup_help_controlls_child_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
    imgui_begin_child("##popup help child window id", vector(-1, POPUP_HELP_CHILD_HEIGHT * config_saved.font_scale, 0), 1, popup_help_controlls_child_flags);

    imgui_columns(2, "##popup help column id", true);
    var column_width = ((POPUP_HELP_WIDTH * config_saved.font_scale) / 2) - engine_theme_win_bordersize * 2;

    imgui_set_column_width(0, column_width);
    imgui_set_column_width(1, column_width);

    {
        imgui_text_disabled("Shortcuts");
        imgui_text(_chr(str_printf(NULL, "Help: %s", config_current.short_help)));
        imgui_text(_chr(str_printf(NULL, "Take screenshot: %s", config_current.short_screenshot)));

        imgui_text(_chr(str_printf(NULL, "New episode: %s", config_current.short_new)));
        imgui_text(_chr(str_printf(NULL, "Open episode: %s", config_current.short_open)));
        imgui_text(_chr(str_printf(NULL, "Settings: %s", config_current.short_settings)));
        imgui_text(_chr(str_printf(NULL, "Save episode: %s", config_current.short_save)));
        imgui_text(_chr(str_printf(NULL, "Save episode as: CTRL + %s", config_current.short_save)));
        imgui_text(_chr(str_printf(NULL, "Episode reset: %s", config_current.short_ep_reset)));
        imgui_text(_chr(str_printf(NULL, "Episode edit: %s", config_current.short_ep_edit)));
        imgui_text(_chr(str_printf(NULL, "Map reset: %s", config_current.short_map_reset)));
        imgui_text(_chr(str_printf(NULL, "Map settings: %s", config_current.short_map_settings)));
        imgui_text(_chr(str_printf(NULL, "Hovering obj info ON/OFF: %s", config_current.short_toggle_debug)));
        imgui_text(_chr(str_printf(NULL, "Debug panel ON/OFF: %s", config_current.short_toggle_hovering)));
        imgui_text(_chr(str_printf(NULL, "Map prior: CTRL + %s", config_current.short_map_prior)));
        imgui_text(_chr(str_printf(NULL, "Map next: CTRL + %s", config_current.short_map_next)));
        imgui_text(_chr(str_printf(NULL, "Map shift to West: SHIFT + %s", config_current.short_map_shift_west)));
        imgui_text(_chr(str_printf(NULL, "Map shift to East: SHIFT + %s", config_current.short_map_shift_east)));
        imgui_text(_chr(str_printf(NULL, "Map shift to South: SHIFT + %s", config_current.short_map_shift_south)));
        imgui_text(_chr(str_printf(NULL, "Map shift to North: SHIFT + %s", config_current.short_map_shift_north)));
    }
    imgui_next_column();
    {
        imgui_text_disabled("Input");
        imgui_text(_chr(str_printf(NULL, "Move forward: %s", config_current.input_forward)));
        imgui_text(_chr(str_printf(NULL, "Move backward: %s", config_current.input_backward)));
        imgui_text(_chr(str_printf(NULL, "Move left (strafe): %s", config_current.input_strafe_left)));
        imgui_text(_chr(str_printf(NULL, "Move right (strafe): %s", config_current.input_strafe_right)));
        imgui_text(_chr(str_printf(NULL, "Move up: %s", config_current.input_fly_up)));
        imgui_text(_chr(str_printf(NULL, "Move down: %s", config_current.input_fly_down)));
        imgui_text(_chr(str_printf(NULL, "Run (hold): %s", config_current.input_run)));
        imgui_text(_chr(str_printf(NULL, "Rotate camera (hold): %s", config_current.input_rotate_camera)));
        imgui_text(_chr(str_printf(NULL, "Draw cell: %s", config_current.input_draw)));
        imgui_text(_chr(str_printf(NULL, "Erase cell (hold + draw): %s", config_current.input_erase)));
        imgui_text(_chr(str_printf(NULL, "Pick cell (hold + draw): %s", config_current.input_pick)));
        imgui_text(_chr(str_printf(NULL, "Rotate object (if possible): %s", config_current.input_rotate)));
        imgui_text(_chr(str_printf(NULL, "Toggle assets on/off: %s", config_current.input_toggle_assets)));
        imgui_text(_chr(str_printf(NULL, "Toggle in-game mode on/off: %s", config_current.input_toggle_lights)));
        imgui_text(_chr(str_printf(NULL, "Toggle drawing mode on/off: %s", config_current.input_toggle_draw_mode)));
    }

    imgui_end_child();

    imgui_separator();

    imgui_text_disabled_centered("Episodes saved at:");
    imgui_text_centered("username\\Documents\\MapEditor\\episodes");
    imgui_separator();

    imgui_text_disabled_centered("Created by:");
    imgui_text_centered("Magomet Kochkarov aka 3RUN (parkour09@mail.ru)");
    imgui_separator();

    var width = (POPUP_HELP_WIDTH * config_saved.font_scale);
    if (imgui_button_withsize("Close", width, EDITOR_BUTTON_HEIGHT * config_saved.font_scale) || key_esc && is_esc_popup_allowed == true)
    {
        is_popup_opened = false;
        imgui_close_current_popup();
    }
}

void popup_asset_list_object_info(STRING *str_out, int type, int index)
{
    if (type == ASSET_EVENTS)
    {
        if (index == EVENTS_PLAYER)
        {
            str_cpy(str_out, "Player start");
        }
        else if (index == EVENTS_LEVEL_FINISH)
        {
            str_cpy(str_out, "Level finish switch");
        }
        else if (index == EVENTS_TRIGGER_ZONE)
        {
            str_cpy(str_out, "Trigger zone");
        }
        else if (index == EVENTS_OBJECT_SPAWN_POINT)
        {
            str_cpy(str_out, "Object spawn point");
        }
        else if (index == EVENTS_SECRET_WALL)
        {
            str_cpy(str_out, "Secret wall");
        }
        else if (index == EVENTS_TELEPORT_IN)
        {
            str_cpy(str_out, "Teleport IN");
        }
        else if (index == EVENTS_TELEPORT_OUT)
        {
            str_cpy(str_out, "Teleport OUT");
        }
    }
    else if (type == ASSET_PROPS)
    {
        if (index == PROPS_LIGHT)
        {
            str_cpy(str_out, "Light");
        }
        else if (index == PROPS_COLUMN)
        {
            str_cpy(str_out, "Column");
        }
        else if (index == PROPS_BARREL)
        {
            str_cpy(str_out, "Barrel");
        }
        else if (index == PROPS_TABLE)
        {
            str_cpy(str_out, "Table");
        }
        else if (index == PROPS_VASE)
        {
            str_cpy(str_out, "Vase");
        }
        else if (index == PROPS_DOOR)
        {
            str_cpy(str_out, "Door");
        }
        else if (index == PROPS_GATE)
        {
            str_cpy(str_out, "Gate");
        }
        else if (index == PROPS_CEILING_SUPPORT)
        {
            str_cpy(str_out, "Ceiling support");
        }
        else if (index == PROPS_WINDOW_BLOCK)
        {
            str_cpy(str_out, "Window wall block");
        }
        else if (index == PROPS_WINDOW_BRICK_BLUE)
        {
            str_cpy(str_out, "Window wall brick blue");
        }
        else if (index == PROPS_WINDOW_BRICK_RED)
        {
            str_cpy(str_out, "Window wall brick red");
        }
        else if (index == PROPS_WINDOW_BRICK_GREY)
        {
            str_cpy(str_out, "Window wall brick grey");
        }
        else if (index == PROPS_WINDOW_DIRT)
        {
            str_cpy(str_out, "Window wall dirt");
        }
        else if (index == PROPS_WINDOW_METAL)
        {
            str_cpy(str_out, "Window wall metal");
        }
        else if (index == PROPS_DECOR_ON_WALL)
        {
            str_cpy(str_out, "Decor on wall");
        }
        else if (index == PROPS_SWITCH)
        {
            str_cpy(str_out, "Switch");
        }
    }
    else if (type == ASSET_ITEMS)
    {
        if (index == ITEMS_KEY_BLUE)
        {
            str_cpy(str_out, "Key blue");
        }
        else if (index == ITEMS_KEY_RED)
        {
            str_cpy(str_out, "Key red");
        }
        else if (index == ITEMS_KEY_YELLOW)
        {
            str_cpy(str_out, "Key yellow");
        }
        else if (index == ITEMS_HEALTH_BONUS)
        {
            str_cpy(str_out, "Health bonus");
        }
        else if (index == ITEMS_MEDKIT_SMALL)
        {
            str_cpy(str_out, "Medkit small");
        }
        else if (index == ITEMS_MEDKIT_BIG)
        {
            str_cpy(str_out, "Medkit big");
        }
        else if (index == ITEMS_AMMO_BULLETS_SMALL)
        {
            str_cpy(str_out, "Ammo bullets small");
        }
        else if (index == ITEMS_AMMO_BULLETS_BIG)
        {
            str_cpy(str_out, "Ammo bullets big");
        }
        else if (index == ITEMS_AMMO_SHELLS_SMALL)
        {
            str_cpy(str_out, "Ammo shells small");
        }
        else if (index == ITEMS_AMMO_SHELLS_BIG)
        {
            str_cpy(str_out, "Ammo shells big");
        }
        else if (index == ITEMS_AMMO_ROCKETS_SMALL)
        {
            str_cpy(str_out, "Ammo rockets small");
        }
        else if (index == ITEMS_AMMO_ROCKETS_BIG)
        {
            str_cpy(str_out, "Ammo rockets big");
        }
        else if (index == ITEMS_TREASURE)
        {
            str_cpy(str_out, "Treasures");
        }
        else if (index == ITEMS_POWERUP_MAP)
        {
            str_cpy(str_out, "Powerup map");
        }
        else if (index == ITEMS_POWERUP_SUIT)
        {
            str_cpy(str_out, "Powerup suit");
        }
        else if (index == ITEMS_POWERUP_CHICKEN)
        {
            str_cpy(str_out, "Powerup chicken");
        }
        else if (index == ITEMS_POWERUP_LANTERN)
        {
            str_cpy(str_out, "Powerup lantern");
        }
        else if (index == ITEMS_POWERUP_MUSHROOM)
        {
            str_cpy(str_out, "Powerup mushroom");
        }
        else if (index == ITEMS_WEAPON_PISTOL)
        {
            str_cpy(str_out, "Weapon pistol");
        }
        else if (index == ITEMS_WEAPON_SHOTGUN)
        {
            str_cpy(str_out, "Weapon shotgun");
        }
        else if (index == ITEMS_WEAPON_CHAINGUN)
        {
            str_cpy(str_out, "Weapon chaingun");
        }
        else if (index == ITEMS_WEAPON_ROCKETLAUNCHER)
        {
            str_cpy(str_out, "Weapon rocketlauncher");
        }
    }
    else if (type == ASSET_ENEMIES)
    {
        if (index == ASSET_ENEMY_BAT)
        {
            str_cpy(str_out, "Enemy bat");
        }
        else if (index == ASSET_ENEMY_BOXER)
        {
            str_cpy(str_out, "Enemy boxer");
        }
        else if (index == ASSET_ENEMY_BUM)
        {
            str_cpy(str_out, "Enemy bum");
        }
        else if (index == ASSET_ENEMY_MAGE)
        {
            str_cpy(str_out, "Enemy mage");
        }
        else if (index == ASSET_ENEMY_HUMAN_PISTOL)
        {
            str_cpy(str_out, "Enemy human pistol");
        }
        else if (index == ASSET_ENEMY_HUMAN_SHOTGUN)
        {
            str_cpy(str_out, "Enemy human shotgun");
        }
        else if (index == ASSET_ENEMY_SKELETON)
        {
            str_cpy(str_out, "Enemy skeleton");
        }
        else if (index == ASSET_ENEMY_SLIME_FIRE)
        {
            str_cpy(str_out, "Enemy slime fire");
        }
        else if (index == ASSET_ENEMY_SLIME_ICE)
        {
            str_cpy(str_out, "Enemy slime ice");
        }
        else if (index == ASSET_ENEMY_ZOMBIE)
        {
            str_cpy(str_out, "Enemy zombie");
        }
    }
    else if (type == ASSET_BOSSES)
    {
        if (index == ASSET_BOSS_HUMAN_CHAINGUN)
        {
            str_cpy(str_out, "Boss human chaingun");
        }
        else if (index == ASSET_BOSS_HUMAN_ROCKETLAUNCHER)
        {
            str_cpy(str_out, "Boss human rocketlauncher");
        }
        else if (index == ASSET_BOSS_SLIME_TOXIC)
        {
            str_cpy(str_out, "Boss slime toxic");
        }
        else if (index == ASSET_BOSS_MEGAEYE)
        {
            str_cpy(str_out, "Boss megaeye");
        }
    }
}

void popup_assets_list_item(void *draw_list, BMAP *texture, int *selection, int type, int index)
{
    if (!draw_list)
    {
        return;
    }

    VECTOR cursor_screen_pos;
    vec_set(&cursor_screen_pos, imgui_get_cursor_screen_pos());

    int is_temp_boolean = false;
    if (type <= ASSET_FLOORS)
    {
        if (*selection == index)
        {
            is_temp_boolean = true;
        }
    }
    else
    {
        if (preview_cell.object.type == type && preview_cell.object.index == index)
        {
            is_temp_boolean = true;
        }
    }

    STRING *selectable_id_str = "";
    str_cpy(selectable_id_str, "##index");
    str_cat(selectable_id_str, str_for_num(NULL, index));
    if (imgui_selectable_size(_chr(selectable_id_str), &is_temp_boolean, ImGuiSelectableFlags_None, vector(ASSET_PREVIEW_TEXTURE_WIDTH * config_saved.font_scale, ASSET_PREVIEW_TEXTURE_HEIGHT * config_saved.font_scale, 0)))
    {
        *selection = index;
        object_params_reset(&preview_cell.object);
        cell_update_preview(category_button_id, type, index);
        if (drawing_mode == DRAWING_MODE_MAP)
        {
            is_asset_list_visible = false;
            is_popup_opened = false;
        }
    }

    if (imgui_is_item_hovered())
    {
        if (drawing_mode == DRAWING_MODE_MAP)
        {
            if (category_button_id == ASSET_LIST_BUTTON_ID_CEILING || category_button_id == ASSET_LIST_BUTTON_ID_FLOOR)
            {
                if (index == FLOORS_NONE)
                {
                    imgui_create_tooltip("None (sky)");
                }
                else if (index == FLOORS_TOXIC_WASTE)
                {
                    imgui_create_tooltip("Toxic waste (animated + light)");
                }
            }
        }
        else if (drawing_mode == DRAWING_MODE_OBJECT)
        {
            popup_asset_list_object_info(popup_asset_list_object_tooltip_str, type, index);
            imgui_create_tooltip(_chr(popup_asset_list_object_tooltip_str));
        }
    }

    var image_start_x = cursor_screen_pos.x;
    var image_start_y = cursor_screen_pos.y;
    var image_end_x = image_start_x + (ASSET_PREVIEW_TEXTURE_WIDTH * config_saved.font_scale);
    var image_end_y = image_start_y + (ASSET_PREVIEW_TEXTURE_HEIGHT * config_saved.font_scale);
    imgui_drawlist_add_image(draw_list, texture, vector(image_start_x, image_start_y, 0), vector(image_end_x, image_end_y, 0), vector(0, 0, 0), vector(1, 1, 0), color4_image, 1);
}

void popup_asset_list()
{
    if (drawing_mode == DRAWING_MODE_MAP)
    {
        if (category_button_id == ASSET_LIST_BUTTON_ID_WALL)
        {
            imgui_text_centered("Wall Textures");

            int texture_browser_child_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
            imgui_begin_child("##asset texture browser child id", vector(-1, POPUP_ASSET_TEXTURE_LIST_HEIGHT * config_saved.font_scale, 0), 1, texture_browser_child_flags);

            int i = 0, counter = 0;
            while (counter < wall_asset_count)
            {
                for (i = 0; i < ASSETS_IN_THE_ROW; i++)
                {
                    if (counter >= wall_asset_count)
                    {
                        break;
                    }

                    if (i != 0)
                    {
                        imgui_same_line();
                    }

                    int type = ASSET_WALLS;
                    int index = counter;

                    asset_list_popup_draw = imgui_get_window_draw_list();
                    popup_assets_list_item(asset_list_popup_draw, asset_get_texture(type, index), &preview_cell.wall_index, type, index);
                    counter++;
                }
            }

            imgui_end_child();
        }
        else if (category_button_id == ASSET_LIST_BUTTON_ID_CEILING)
        {
            imgui_text_centered("Ceiling Textures");

            int texture_browser_child_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
            imgui_begin_child("##asset texture browser child id", vector(-1, POPUP_ASSET_TEXTURE_LIST_HEIGHT * config_saved.font_scale, 0), 1, texture_browser_child_flags);

            int i = 0, counter = 0;
            while (counter < floor_asset_count)
            {
                for (i = 0; i < ASSETS_IN_THE_ROW; i++)
                {
                    if (counter >= floor_asset_count)
                    {
                        break;
                    }

                    if (i != 0)
                    {
                        imgui_same_line();
                    }

                    int type = ASSET_FLOORS;
                    int index = counter;

                    asset_list_popup_draw = imgui_get_window_draw_list();
                    popup_assets_list_item(asset_list_popup_draw, asset_get_texture(type, index), &preview_cell.ceiling_index, type, index);
                    counter++;
                }
            }

            imgui_end_child();
        }
        else if (category_button_id == ASSET_LIST_BUTTON_ID_FLOOR)
        {
            imgui_text_centered("Floor Textures");

            int texture_browser_child_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
            imgui_begin_child("##asset texture browser child id", vector(-1, POPUP_ASSET_TEXTURE_LIST_HEIGHT * config_saved.font_scale, 0), 1, texture_browser_child_flags);

            int i = 0, counter = 0;
            while (counter < floor_asset_count)
            {
                for (i = 0; i < ASSETS_IN_THE_ROW; i++)
                {
                    if (counter >= floor_asset_count)
                    {
                        break;
                    }

                    if (i != 0)
                    {
                        imgui_same_line();
                    }

                    int type = ASSET_FLOORS;
                    int index = counter;

                    asset_list_popup_draw = imgui_get_window_draw_list();
                    popup_assets_list_item(asset_list_popup_draw, asset_get_texture(type, index), &preview_cell.floor_index, type, index);
                    counter++;
                }
            }

            imgui_end_child();
        }
    }
    else if (drawing_mode == DRAWING_MODE_OBJECT)
    {
        imgui_text_centered("Objects");
        imgui_separator();

        int marker_params_child_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
        imgui_begin_child("##asset marker params child id", vector(-1, POPUP_ASSET_OBJECT_PARAM_HEIGHT * config_saved.font_scale, 0), 1, marker_params_child_flags);

        popup_asset_list_object_info(popup_asset_selected_object_name_str, preview_cell.object.type, preview_cell.object.index);
        imgui_text("Selected marker: ");
        imgui_same_line();
        imgui_text(_chr(popup_asset_selected_object_name_str));
        imgui_separator();

        object_params_gui(preview_cell.object.type, preview_cell.object.index);

        imgui_end_child();
        imgui_separator();

        int objects_tab_bar_flags = ImGuiTabBarFlags_NoTooltip | ImGuiTabBarFlags_TabListPopupButton | ImGuiTabBarFlags_FittingPolicyDefault_;
        if (imgui_begin_tabbar("##popup objects asset list tabbars", objects_tab_bar_flags))
        {
            int objects_tab_item_falgs = ImGuiTabItemFlags_NoCloseWithMiddleMouseButton;
            if (imgui_begin_tabitem("Events", NULL, objects_tab_item_falgs))
            {
                category_object_tab = ASSET_LIST_CATEGORY_EVENTS;

                int object_browser_child_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
                imgui_begin_child("##asset events browser child id", vector(-1, POPUP_ASSET_OBJECT_LIST_HEIGHT * config_saved.font_scale, 0), 1, object_browser_child_flags);

                int i = 0, counter = 0;
                while (counter < event_asset_count)
                {
                    for (i = 0; i < ASSETS_IN_THE_ROW; i++)
                    {
                        if (counter >= event_asset_count)
                        {
                            break;
                        }

                        if (i != 0)
                        {
                            imgui_same_line();
                        }

                        int type = ASSET_EVENTS;
                        int index = counter;

                        asset_list_popup_draw = imgui_get_window_draw_list();
                        popup_assets_list_item(asset_list_popup_draw, asset_get_texture(type, index), &preview_cell.object.index, type, index);
                        counter++;
                    }
                }

                imgui_end_child();
                imgui_end_tabitem();
            }

            if (imgui_begin_tabitem("Props", NULL, objects_tab_item_falgs))
            {
                category_object_tab = ASSET_LIST_CATEGORY_PROPS;

                int object_browser_child_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
                imgui_begin_child("##asset props browser child id", vector(-1, POPUP_ASSET_OBJECT_LIST_HEIGHT * config_saved.font_scale, 0), 1, object_browser_child_flags);

                int i = 0, counter = 0;
                while (counter < props_asset_count)
                {
                    for (i = 0; i < ASSETS_IN_THE_ROW; i++)
                    {
                        if (counter >= props_asset_count)
                        {
                            break;
                        }

                        if (i != 0)
                        {
                            imgui_same_line();
                        }

                        int type = ASSET_PROPS;
                        int index = counter;

                        asset_list_popup_draw = imgui_get_window_draw_list();
                        popup_assets_list_item(asset_list_popup_draw, asset_get_texture(type, index), &preview_cell.object.index, type, index);
                        counter++;
                    }
                }

                imgui_end_child();
                imgui_end_tabitem();
            }

            if (imgui_begin_tabitem("Items", NULL, objects_tab_item_falgs))
            {
                category_object_tab = ASSET_LIST_CATEGORY_ITEMS;

                int object_browser_child_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
                imgui_begin_child("##asset item browser child id", vector(-1, POPUP_ASSET_OBJECT_LIST_HEIGHT * config_saved.font_scale, 0), 1, object_browser_child_flags);

                int i = 0, counter = 0;
                while (counter < item_asset_count)
                {
                    for (i = 0; i < ASSETS_IN_THE_ROW; i++)
                    {
                        if (counter >= item_asset_count)
                        {
                            break;
                        }

                        if (i != 0)
                        {
                            imgui_same_line();
                        }

                        int type = ASSET_ITEMS;
                        int index = counter;

                        asset_list_popup_draw = imgui_get_window_draw_list();
                        popup_assets_list_item(asset_list_popup_draw, asset_get_texture(type, index), &preview_cell.object.index, type, index);
                        counter++;
                    }
                }

                imgui_end_child();
                imgui_end_tabitem();
            }

            if (imgui_begin_tabitem("Enemies", NULL, objects_tab_item_falgs))
            {
                category_object_tab = ASSET_LIST_CATEGORY_ENEMIES;

                int object_browser_child_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
                imgui_begin_child("##asset enemies browser child id", vector(-1, POPUP_ASSET_OBJECT_LIST_HEIGHT * config_saved.font_scale, 0), 1, object_browser_child_flags);

                int i = 0, counter = 0;
                while (counter < enemy_asset_count)
                {
                    for (i = 0; i < ASSETS_IN_THE_ROW; i++)
                    {
                        if (counter >= enemy_asset_count)
                        {
                            break;
                        }

                        if (i != 0)
                        {
                            imgui_same_line();
                        }

                        int type = ASSET_ENEMIES;
                        int index = counter;

                        asset_list_popup_draw = imgui_get_window_draw_list();
                        popup_assets_list_item(asset_list_popup_draw, asset_get_texture(type, index), &preview_cell.object.index, type, index);
                        counter++;
                    }
                }

                imgui_end_child();
                imgui_end_tabitem();
            }

            if (imgui_begin_tabitem("Bosses", NULL, objects_tab_item_falgs))
            {
                category_object_tab = ASSET_LIST_CATEGORY_BOSSES;

                int object_browser_child_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
                imgui_begin_child("##asset bosses browser child id", vector(-1, POPUP_ASSET_OBJECT_LIST_HEIGHT * config_saved.font_scale, 0), 1, object_browser_child_flags);

                int i = 0, counter = 0;
                while (counter < boss_asset_count)
                {
                    for (i = 0; i < ASSETS_IN_THE_ROW; i++)
                    {
                        if (counter >= boss_asset_count)
                        {
                            break;
                        }

                        if (i != 0)
                        {
                            imgui_same_line();
                        }

                        int type = ASSET_BOSSES;
                        int index = counter;

                        asset_list_popup_draw = imgui_get_window_draw_list();
                        popup_assets_list_item(asset_list_popup_draw, asset_get_texture(type, index), &preview_cell.object.index, type, index);
                        counter++;
                    }
                }

                imgui_end_child();
                imgui_end_tabitem();
            }

            imgui_end_tabbar();
        }
    }

    var width = (POPUP_ASSET_LIST_WIDTH * config_saved.font_scale);
    if (imgui_button_withsize("Back", width, EDITOR_BUTTON_HEIGHT * config_saved.font_scale) || key_esc && is_esc_popup_allowed == true)
    {
        is_asset_list_visible = false;
        is_popup_opened = false;
    }

    if (is_popup_opened == false)
    {
        imgui_close_current_popup();
    }
}

void stop_playing_music()
{
    media_stop(playing_music_handle);
}

void play_selection()
{
    STRING *music_to_play_str = "";
    str_cpy(music_to_play_str, episode_music_folder_str);
    str_cat(music_to_play_str, selected_music);
    playing_music_handle = media_loop(music_to_play_str, NULL, playing_music_volume);
    playing_music_index = found_music_index;
}

void popup_music_browser()
{
    imgui_text_centered("Music browser");
    imgui_separator();

    int editor_music_browser_child_flags = ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
    imgui_begin_child("##popup music browser child id", vector(-1, POPUP_MUSIC_BROWSER_HEIGHT - 60, 0), 1, editor_music_browser_child_flags);

    if (found_music_total <= 0)
    {
        imgui_text("'Music' - folder is empty.");
    }
    else
    {
        imgui_push_item_width(-1);
        if (imgui_list_box("##popup music browser listbox id", &found_music_index, found_music_listbox, found_music_total, found_music_total))
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

    // currently used music name
    if (strlen(map_settings.music) <= 0)
    {
        str_cpy(popup_currently_used_music_str, "Currently used: none");
        imgui_text(_chr(popup_currently_used_music_str));
    }
    else
    {
        str_cpy(popup_currently_used_music_str, "Currently used: ");
        str_cat(popup_currently_used_music_str, _str(map_settings.music));
        str_replace(popup_currently_used_music_str, episode_music_folder_str, "");
        imgui_text(_chr(popup_currently_used_music_str));
    }

    // currently playing music name
    if (media_playing(playing_music_handle))
    {
        str_cpy(popup_currently_playing_music_str, "Currently playing: ");
        str_cat(popup_currently_playing_music_str, _str(found_music_listbox[playing_music_index]));
        imgui_text(_chr(popup_currently_playing_music_str));
    }
    else
    {
        str_cpy(popup_currently_playing_music_str, "Currently playing: none");
        imgui_text(_chr(popup_currently_playing_music_str));
    }

    imgui_separator();

    // volume slider
    imgui_text("Volume: ");
    imgui_same_line();
    imgui_push_item_width(-1);
    imgui_slider_var("##popup music volume slider id", &playing_music_volume, 0, 100);
    imgui_pop_item_width();

    imgui_separator();

    var width = (POPUP_MUSIC_BROWSER_WIDTH * config_saved.font_scale) / 4;
    if (imgui_button_withsize("Refresh", width, EDITOR_BUTTON_HEIGHT * config_saved.font_scale))
    {
        is_popup_check_failed = false;
        music_list_refresh();
    }

    imgui_same_line();
    if (imgui_button_withsize("Play / Stop", width, EDITOR_BUTTON_HEIGHT * config_saved.font_scale))
    {
        if (found_music_index >= 0)
        {
            is_popup_check_failed = false;

            if (media_playing(playing_music_handle))
            {
                stop_playing_music();

                if (playing_music_index != found_music_index)
                {
                    play_selection();
                }
            }
            else
            {
                play_selection();
            }
        }
        else
        {
            if (media_playing(playing_music_handle))
            {
                stop_playing_music();
            }
            else
            {
                is_popup_check_failed = true;
            }
        }
    }

    imgui_same_line();
    if (imgui_button_withsize("Use", width, EDITOR_BUTTON_HEIGHT * config_saved.font_scale))
    {
        if (found_music_index >= 0)
        {
            stop_playing_music();
            is_popup_check_failed = false;
            found_music_index = -1;

            is_popup_opened = false;
            imgui_close_current_popup();

            STRING *music_to_use_str = "";
            str_cpy(music_to_use_str, episode_music_folder_str);
            str_cat(music_to_use_str, selected_music);

            strcpy(map_settings.music, _chr(music_to_use_str));
        }
        else
        {
            is_popup_check_failed = true;
        }
    }

    imgui_same_line();
    if (imgui_button_withsize("Close", width, EDITOR_BUTTON_HEIGHT * config_saved.font_scale) || key_esc)
    {
        stop_playing_music();
        is_popup_check_failed = false;
        found_music_index = -1;

        is_popup_opened = false;
        imgui_close_current_popup();
    }

    if (media_playing(playing_music_handle))
    {
        media_tune(playing_music_handle, playing_music_volume, 0, 0);
    }

    if (is_popup_check_failed == true)
    {
        imgui_push_style_color(ImGuiCol_TextDisabled, color4_red);
        imgui_text_disabled_centered("Please, select music file from the list.");
        imgui_pop_style_color(1);
    }
}