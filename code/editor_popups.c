
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

void popup_open(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    imgui_text_centered("Open episode");
    imgui_separator();

    int popup_open_child_flags = ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
    imgui_begin_child(popup_episode_browser_id, vector(-1, (POPUP_OPEN_HEIGHT * config_saved.font_scale) - (60 * config_saved.font_scale), 0), 1, popup_open_child_flags);

    if (found_episodes_total <= 0)
    {
        imgui_text("'Documents\\MapEditor\\episodes' - folder is empty.");
    }
    else
    {
        imgui_push_item_width(-1);
        if (imgui_list_box(popup_episode_listbox_id, &found_episode_index, found_episodes_listbox, found_episodes_total, found_episodes_total))
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

    var width = (POPUP_OPEN_WIDTH * config_saved.font_scale) / 4;
    if (imgui_button_withsize("Refresh", width, POPUP_BUTTON_HEIGHT * config_saved.font_scale))
    {
        is_popup_check_failed = false;
        episode_list_refresh();
    }

    imgui_same_line();
    if (imgui_button_withsize("Delete", width, POPUP_BUTTON_HEIGHT * config_saved.font_scale))
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
    if (imgui_button_withsize("Load", width, POPUP_BUTTON_HEIGHT * config_saved.font_scale) || key_enter)
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
    if (imgui_button_withsize("Cancel", width, POPUP_BUTTON_HEIGHT * config_saved.font_scale) || key_esc && is_esc_popup_allowed == true)
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

void popup_open_sure()
{
    imgui_text_centered("Are you sure you want to open different episode?");
    imgui_text_centered("All unsaved data will be lost!");
    imgui_separator();

    var width = (POPUP_OPEN_SURE_WIDTH * config_saved.font_scale) / 2;
    if (imgui_button_withsize("Yes", width, POPUP_BUTTON_HEIGHT * config_saved.font_scale) || key_y)
    {
        // we first need to close old popup
        // because new one's positions won't be centered correctly !
        is_popup_opened = false;
        imgui_close_current_popup();

        // now move to the open state !
        editor_switch_popup_to(MAIN_POPUP_OPEN);
    }

    imgui_same_line();
    if (imgui_button_withsize("No", width, POPUP_BUTTON_HEIGHT * config_saved.font_scale) || key_esc && is_esc_popup_allowed == true || key_n)
    {
        is_popup_opened = false;
        imgui_close_current_popup();
    }
}

void popup_new_reset()
{
    strcpy(new_episode_filename, "");
    strcpy(new_episode_name, "");
    strcpy(new_episode_story_start, "");
    strcpy(new_episode_story_end, "");
    new_episode_map_count = 1;
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
    editor_help_maker(_chr(str_printf(NULL, "The file name to save episode as. Character limit %d.", (long)EPISODE_FILENAME_LENGTH)));
    imgui_push_item_width(-1);
    imgui_input_text(popup_new_filename_input_id, new_episode_filename, EPISODE_FILENAME_LENGTH, NULL);
    imgui_pop_item_width();

    imgui_text("Episode name");
    imgui_same_line();
    editor_help_maker(_chr(str_printf(NULL, "The name of the episode. Character limit %d.", (long)EPISODE_NAME_LENGTH)));
    imgui_push_item_width(-1);
    imgui_input_text(popup_new_episode_name_input_id, new_episode_name, EPISODE_NAME_LENGTH, NULL);
    imgui_pop_item_width();

    imgui_text("Story beginning");
    imgui_same_line();
    editor_help_maker(_chr(str_printf(NULL, "Short story showed at the beginning of the episode. Character limit %d.", (long)EPISODE_STORY_START_LENGTH)));
    imgui_input_text_multiline(popup_new_episode_story_start_input_id, new_episode_story_start, EPISODE_STORY_START_LENGTH, -1, 128, NULL);

    imgui_text("Story ending");
    imgui_same_line();
    editor_help_maker(_chr(str_printf(NULL, "Short story showed when episode is finished. Character limit %d.", (long)EPISODE_STORY_END_LENGTH)));
    imgui_input_text_multiline(popup_new_episode_story_end_id, new_episode_story_end, EPISODE_STORY_END_LENGTH, -1, 128, NULL);

    imgui_text("Map count");
    imgui_same_line();
    editor_help_maker(_chr(str_printf(NULL, "Amount of maps in the episode. Max %d.", (long)MAX_MAPS_PER_EPISODE)));
    imgui_push_item_width(-1);
    imgui_slider_int(popup_new_episode_map_slider_id, &new_episode_map_count, 1, MAX_MAPS_PER_EPISODE);
    imgui_pop_item_width();

    var width = (POPUP_NEW_WIDTH * config_saved.font_scale) / 2;
    if (imgui_button_withsize(_chr(popup_new_button_str), width, POPUP_BUTTON_HEIGHT * config_saved.font_scale) || key_enter)
    {
        if (strlen(new_episode_filename) > 0 && strlen(new_episode_name) > 0 && strlen(new_episode_story_start) > 0 && strlen(new_episode_story_end) > 0)
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
    if (imgui_button_withsize("Back", width, POPUP_BUTTON_HEIGHT * config_saved.font_scale) || key_esc && is_esc_popup_allowed == true)
    {
        popup_new_reset();
        is_popup_check_failed = false;

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

void popup_new_sure()
{
    imgui_text_centered("Are you sure you want to create a new episode?");
    imgui_text_centered("All unsaved data will be lost!");
    imgui_separator();

    var width = (POPUP_NEW_SURE_WIDTH * config_saved.font_scale) / 2;
    if (imgui_button_withsize("Yes", width, POPUP_BUTTON_HEIGHT * config_saved.font_scale) || key_y)
    {
        // we first need to close old popup
        // because new one's positions won't be centered correctly !
        is_popup_opened = false;
        imgui_close_current_popup();

        // now move to the open state !
        editor_switch_popup_to(MAIN_POPUP_NEW);
    }

    imgui_same_line();
    if (imgui_button_withsize("No", width, POPUP_BUTTON_HEIGHT * config_saved.font_scale) || key_esc && is_esc_popup_allowed == true || key_n)
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

    imgui_text_centered("Save episode as");
    imgui_separator();

    imgui_text("Filename:");
    imgui_same_line();
    imgui_push_item_width(-1);
    imgui_input_text_with_hint(popup_save_as_input_id, "name", save_as_filename, EPISODE_FILENAME_LENGTH, NULL);
    imgui_pop_item_width();

    var width = (POPUP_SAVE_AS_WIDTH * config_saved.font_scale) / 2;
    if (imgui_button_withsize(_chr(popup_save_as_button_str), width, POPUP_BUTTON_HEIGHT * config_saved.font_scale) || key_enter)
    {
        if (strlen(save_as_filename) > 0)
        {
            is_popup_check_failed = false;
            is_popup_opened = false;
            imgui_close_current_popup();

            episode_save_name_udpate_to(_str(save_as_filename));
            episode_save(ep_save_name, episode);
        }
        else
        {
            is_popup_check_failed = true;
        }
    }
    imgui_same_line();
    if (imgui_button_withsize("Cancel", width, POPUP_BUTTON_HEIGHT * config_saved.font_scale) || key_esc && is_esc_popup_allowed == true)
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

void popup_settings_general()
{
    int general_child_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
    imgui_begin_child(popup_settings_input_child_id, vector(-1, POPUP_SETTINGS_CHILD_HEIGHT * config_saved.font_scale, 0), 0, general_child_flags);

    imgui_text_disabled_centered("AUDIO");

    imgui_text("Master volume:");
    imgui_same_line();
    imgui_align_right_with_offset(POPUP_COMBOBOX_WIDTH * config_saved.font_scale);
    imgui_push_item_width((POPUP_COMBOBOX_WIDTH * config_saved.font_scale) - 1);
    imgui_slider_float(popup_settings_general_master_volume_slider_id, &config_current.master_volume, SND_VOLUME_MIN, SND_VOLUME_MAX, "%.1f", 1);
    imgui_pop_item_width();

    master_vol = config_current.master_volume;

    imgui_separator();
    imgui_text_disabled_centered("UI");

    // font scale
    imgui_text("Font scale:");
    imgui_same_line();
    imgui_align_right_with_offset(POPUP_COMBOBOX_WIDTH * config_saved.font_scale);
    imgui_push_item_width((POPUP_COMBOBOX_WIDTH * config_saved.font_scale) - 1);
    imgui_slider_float(popup_settings_general_font_scale_slider_id, &config_current.font_scale, FONT_SCALE_MIN, FONT_SCALE_MAX, "%.1f", 1);
    imgui_pop_item_width();

    // tooltip
    imgui_text("Selected cell tooltip:");
    imgui_same_line();
    imgui_align_right_with_offset(152 * config_saved.font_scale);
    imgui_radiobutton("enabled", &config_current.is_cell_tooltip_enabled, true);
    imgui_same_line();
    imgui_radiobutton("disabled", &config_current.is_cell_tooltip_enabled, false);

    // background color
    imgui_text("Background color:");
    imgui_same_line();
    imgui_align_right_with_offset(POPUP_COMBOBOX_WIDTH * config_saved.font_scale);
    imgui_push_item_width((POPUP_COMBOBOX_WIDTH * config_saved.font_scale) - 1);
    static int misc_flags = ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoDragDrop;
    imgui_color_edit3(popup_settings_bg_color_picker_id, config_current.background_color, misc_flags);
    imgui_pop_item_width();

    // grid color
    imgui_text("Grid color:");
    imgui_same_line();
    imgui_align_right_with_offset(POPUP_COMBOBOX_WIDTH * config_saved.font_scale);
    imgui_push_item_width((POPUP_COMBOBOX_WIDTH * config_saved.font_scale) - 1);
    static int misc_flags = ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoDragDrop;
    imgui_color_edit3(popup_settings_grid_color_picker_id, config_current.grid_color, misc_flags);
    imgui_pop_item_width();

    imgui_separator();
    imgui_text_disabled_centered("GRAPHICS");

    // display mode here
    imgui_text(_chr(graphics_display_mode_str));
    imgui_same_line();
    imgui_align_right_with_offset(POPUP_COMBOBOX_WIDTH * config_saved.font_scale);
    imgui_push_item_width((POPUP_COMBOBOX_WIDTH * config_saved.font_scale) - 1);
    if (imgui_begin_combo(popup_settings_display_combo_id, _chr(graphics_display_currently_used_str), ImGuiComboFlags_HeightSmall))
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
        imgui_align_right_with_offset(POPUP_COMBOBOX_WIDTH * config_saved.font_scale);
        imgui_push_item_width((POPUP_COMBOBOX_WIDTH * config_saved.font_scale) - 1);
        if (imgui_begin_combo(popup_settings_resolution_combo_id, _chr(graphics_resolution_currently_used_str), ImGuiComboFlags_HeightSmall))
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
    imgui_begin_child(popup_settings_input_child_id, vector(-1, POPUP_SETTINGS_CHILD_HEIGHT * config_saved.font_scale, 0), 0, input_main_child_flags);

    imgui_text_disabled_centered("MOUSE");

    imgui_text("Mouse sensitivity:");
    imgui_same_line();
    imgui_align_right_with_offset(POPUP_COMBOBOX_WIDTH * config_saved.font_scale);
    imgui_push_item_width((POPUP_COMBOBOX_WIDTH * config_saved.font_scale) - 1);
    imgui_slider_float(popup_settings_input_mouse_slider_id, &config_current.mouse_sensitivity, MOUSE_SENSE_MIN, MOUSE_SENSE_MAX, "%.1f", 1);
    imgui_pop_item_width();

    imgui_separator();
    imgui_text_disabled_centered("KEYBOARD");

    int input_child_flags = ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
    imgui_begin_child(popup_settings_input_buttons_child_id, vector(-1, -1, 0), 1, input_child_flags);

    imgui_text_disabled_centered("INPUT");
    imgui_separator();

    editor_input_add_keybinding(input_forward_entry_str, config_current.input_forward);
    editor_input_add_keybinding(input_backward_entry_str, config_current.input_backward);
    editor_input_add_keybinding(input_strafe_left_entry_str, config_current.input_strafe_left);
    editor_input_add_keybinding(input_strafe_right_entry_str, config_current.input_strafe_right);
    editor_input_add_keybinding(input_interact_entry_str, config_current.input_interact);
    editor_input_add_keybinding(input_run_entry_str, config_current.input_run);
    editor_input_add_keybinding(input_drag_map_entry_str, config_current.input_drag_map);
    editor_input_add_keybinding(input_draw_entry_str, config_current.input_draw);
    editor_input_add_keybinding(input_erase_entry_str, config_current.input_erase);
    editor_input_add_keybinding(input_pick_entry_str, config_current.input_pick);
    editor_input_add_keybinding(input_rotate_entry_str, config_current.input_rotate);

    imgui_text_disabled_centered("SHORTCUTS");
    imgui_separator();

    editor_shortcut_add_keybinding(short_help_entry_str, "", config_current.short_help);
    editor_shortcut_add_keybinding(short_new_entry_str, "", config_current.short_new);
    editor_shortcut_add_keybinding(short_open_entry_str, "", config_current.short_open);
    editor_shortcut_add_keybinding(short_save_entry_str, "", config_current.short_save);
    editor_shortcut_add_keybinding(short_ep_reset_entry_str, "", config_current.short_ep_reset);
    editor_shortcut_add_keybinding(short_ep_edit_entry_str, "", config_current.short_ep_edit);
    editor_shortcut_add_keybinding(short_reset_map_entry_str, "", config_current.short_reset_map);
    editor_shortcut_add_keybinding(short_test_run_entry_str, "", config_current.short_test_run);
    editor_shortcut_add_keybinding(short_map_settings_entry_str, "", config_current.short_map_settings);
    editor_shortcut_add_keybinding(short_screenshot_entry_str, "", config_current.short_screenshot);
    editor_shortcut_add_keybinding(short_settings_entry_str, "", config_current.short_settings);
    editor_shortcut_add_keybinding(short_toggle_debug_entry_str, "", config_current.short_toggle_debug);
    editor_shortcut_add_keybinding(short_prior_map_entry_str, "", config_current.short_prior_map);
    editor_shortcut_add_keybinding(short_next_map_entry_str, "", config_current.short_next_map);
    editor_shortcut_add_keybinding(short_shift_map_west_entry_str, "shift +", config_current.short_shift_map_west);
    editor_shortcut_add_keybinding(short_shift_map_east_entry_str, "shift +", config_current.short_shift_map_east);
    editor_shortcut_add_keybinding(short_shift_map_south_entry_str, "shift +", config_current.short_shift_map_south);
    editor_shortcut_add_keybinding(short_shift_map_north_entry_str, "shift +", config_current.short_shift_map_north);

    imgui_end_child();
    imgui_end_child();
}

void popup_settings()
{
    imgui_text_centered("Settings");
    imgui_separator();

    int settings_tab_bar_flags = ImGuiTabBarFlags_NoTooltip | ImGuiTabBarFlags_TabListPopupButton | ImGuiTabBarFlags_FittingPolicyDefault_;
    if (imgui_begin_tabbar(popup_settings_tabs_id, settings_tab_bar_flags))
    {
        int settings_tab_item_falgs = ImGuiTabItemFlags_NoCloseWithMiddleMouseButton;
        if (imgui_begin_tabitem("General", NULL, settings_tab_item_falgs))
        {
            settings_tab_id = SETTINGS_TAB_GENERIC;
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

    var width = (POPUP_SETTINGS_WIDTH * config_saved.font_scale) / 3;
    if (imgui_button_withsize("Defaults", width, POPUP_BUTTON_HEIGHT * config_saved.font_scale)) // reset to defaults button
    {
        config_reset_to_default(settings_tab_id);
        popups_refresh();
    }

    // apply and save
    imgui_same_line();
    if (imgui_button_withsize("Ok", width, POPUP_BUTTON_HEIGHT * config_saved.font_scale) || key_enter)
    {
        config_save();
        config_apply();
        popups_refresh();
        is_popup_opened = false;
        imgui_close_current_popup();
    }

    // cancel changes
    imgui_same_line();
    if (imgui_button_withsize("Back", width, POPUP_BUTTON_HEIGHT * config_saved.font_scale) || key_esc && is_esc_popup_allowed == true)
    {
        config_reset_to_saved();
        popups_refresh();
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
    if (imgui_button_withsize("Yes", width, POPUP_BUTTON_HEIGHT * config_saved.font_scale) || key_y)
    {
        is_popup_opened = false;
        imgui_close_current_popup();
        editor_switch_state_to(EDITOR_STATE_EXIT);
    }

    imgui_same_line();
    if (imgui_button_withsize("No", width, POPUP_BUTTON_HEIGHT * config_saved.font_scale) || key_esc && is_esc_popup_allowed == true || key_n)
    {
        is_popup_opened = false;
        imgui_close_current_popup();
    }
}

void popup_ep_reset(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    Map *active_map = map_get_active(episode);
    if (!active_map)
    {
        return;
    }

    imgui_text_centered("Are you sure you want to reset the whole episode?");
    imgui_separator();

    var width = (POPUP_EPISODE_RESET_WIDTH * config_saved.font_scale) / 2;
    if (imgui_button_withsize("Yes", width, POPUP_BUTTON_HEIGHT * config_saved.font_scale) || key_y)
    {
        is_popup_opened = false;
        imgui_close_current_popup();
        editor_switch_state_to(EDITOR_STATE_RESET_EPISODE);
    }

    imgui_same_line();
    if (imgui_button_withsize("No", width, POPUP_BUTTON_HEIGHT * config_saved.font_scale) || key_esc && is_esc_popup_allowed == true || key_n)
    {
        is_popup_opened = false;
        imgui_close_current_popup();
    }
}

void popup_ep_edit_reset(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    strcpy(episode_edit_name, episode->name);
    strcpy(episode_edit_story_start, episode->story_start);
    strcpy(episode_edit_story_end, episode->story_end);
    episode_edit_map_count = episode->map_count;
}

void popup_ep_edit(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    if (is_game_episode_loaded() == true)
    {
        imgui_text_centered(_chr(str_printf(NULL, "Edit: %s", episode->name)));
    }
    else
    {
        imgui_text_centered("Edit episode");
    }
    imgui_separator();

    imgui_text("Episode name");
    imgui_same_line();
    imgui_help_maker(_chr(str_printf(NULL, "The name of the episode. Character limit %d.", (long)EPISODE_NAME_LENGTH)));
    imgui_push_item_width(-1);
    imgui_input_text(popup_episode_edit_name_id, episode_edit_name, EPISODE_NAME_LENGTH, NULL);
    imgui_pop_item_width();

    imgui_text("Story beginning");
    imgui_same_line();
    imgui_help_maker(_chr(str_printf(NULL, "Short story showed at the beginning of the episode. Character limit %d.", (long)EPISODE_STORY_START_LENGTH)));
    imgui_input_text_multiline(popup_episode_edit_story_start_id, episode_edit_story_start, EPISODE_STORY_START_LENGTH, -1, 128, NULL);

    imgui_text("Story ending");
    imgui_same_line();
    imgui_help_maker(_chr(str_printf(NULL, "Short story showed at the ending of the episode. Character limit %d.", (long)EPISODE_STORY_END_LENGTH)));
    imgui_input_text_multiline(popup_episode_edit_story_end_id, episode_edit_story_end, EPISODE_STORY_END_LENGTH, -1, 128, NULL);

    imgui_text("Map count");
    imgui_same_line();
    imgui_help_maker(_chr(str_printf(NULL, "Amount of maps in the episode. Max %d.", (long)MAX_MAPS_PER_EPISODE)));
    imgui_push_item_width(-1);
    imgui_slider_int(popup_episode_edit_map_count_slider_id, &episode_edit_map_count, 1, MAX_MAPS_PER_EPISODE);
    imgui_pop_item_width();

    var width = (POPUP_EPISODE_EDIT_WIDTH * config_saved.font_scale) / 3;
    if (imgui_button_withsize("Reset", width, POPUP_BUTTON_HEIGHT * config_saved.font_scale))
    {
        is_popup_check_failed = false;
        popup_ep_edit_reset(episode);
    }

    imgui_same_line();
    if (imgui_button_withsize("Save", width, POPUP_BUTTON_HEIGHT * config_saved.font_scale) || key_enter)
    {
        if (strlen(episode_edit_name) > 0 && strlen(episode_edit_story_start) > 0 && strlen(episode_edit_story_end) > 0)
        {
            is_popup_check_failed = false;
            episode_change_info(episode, episode_edit_name, episode_edit_story_start, episode_edit_story_end, episode_edit_map_count);
            is_popup_opened = false;
            imgui_close_current_popup();
        }
        else
        {
            is_popup_check_failed = true;
        }
    }

    imgui_same_line();
    if (imgui_button_withsize("Cancel", width, POPUP_BUTTON_HEIGHT * config_saved.font_scale) || key_esc && is_esc_popup_allowed == true)
    {
        is_popup_check_failed = false;
        popup_ep_edit_reset(episode);

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

void popup_map_reset(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    Map *active_map = map_get_active(episode);
    if (!active_map)
    {
        return;
    }

    imgui_text_centered("Are you sure you want to reset current map?");
    imgui_separator();

    var width = (POPUP_RESET_MAP_WIDTH * config_saved.font_scale) / 2;
    if (imgui_button_withsize("Yes", width, POPUP_BUTTON_HEIGHT * config_saved.font_scale) || key_y)
    {
        is_popup_opened = false;
        imgui_close_current_popup();
        editor_switch_state_to(EDITOR_STATE_RESET_MAP);
    }

    imgui_same_line();
    if (imgui_button_withsize("No", width, POPUP_BUTTON_HEIGHT * config_saved.font_scale) || key_esc && is_esc_popup_allowed == true || key_n)
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
    imgui_begin_child(popup_help_child_id, vector(-1, POPUP_HELP_CHILD_HEIGHT * config_saved.font_scale, 0), 1, popup_help_controlls_child_flags);

    imgui_columns(2, popup_help_columns_id, true);
    var column_width = ((POPUP_HELP_WIDTH * config_saved.font_scale) / 2) - engine_theme_win_bordersize * 2;

    imgui_set_column_width(0, column_width);
    imgui_set_column_width(1, column_width);

    {
        imgui_text_disabled("Shortcuts");
        imgui_text(_chr(str_printf(NULL, "Help: %s", config_current.short_help)));
        imgui_text(_chr(str_printf(NULL, "New episode: %s", config_current.short_new)));
        imgui_text(_chr(str_printf(NULL, "Open episode: %s", config_current.short_open)));
        imgui_text(_chr(str_printf(NULL, "Save: %s", config_current.short_save)));
        imgui_text(_chr(str_printf(NULL, "Save as: ctrl + %s", config_current.short_save)));
        imgui_text(_chr(str_printf(NULL, "Episode reset: %s", config_current.short_ep_reset)));
        imgui_text(_chr(str_printf(NULL, "Episode edit: %s", config_current.short_ep_edit)));
        imgui_text(_chr(str_printf(NULL, "Reset active map: %s", config_current.short_reset_map)));
        imgui_text(_chr(str_printf(NULL, "Test run active map: %s", config_current.short_test_run)));
        imgui_text(_chr(str_printf(NULL, "Active map settings: %s", config_current.short_map_settings)));
        imgui_text(_chr(str_printf(NULL, "Take screenshot: %s", config_current.short_screenshot)));
        imgui_text(_chr(str_printf(NULL, "Settings: %s", config_current.short_settings)));
        imgui_text(_chr(str_printf(NULL, "Debug mode ON/OFF: %s", config_current.short_toggle_debug)));
        imgui_text(_chr(str_printf(NULL, "Prior map: %s", config_current.short_prior_map)));
        imgui_text(_chr(str_printf(NULL, "Next map: %s", config_current.short_next_map)));
        imgui_text(_chr(str_printf(NULL, "Shift map to the West: ctrl + %s", config_current.short_shift_map_west)));
        imgui_text(_chr(str_printf(NULL, "Shift map to the East: ctrl + %s", config_current.short_shift_map_east)));
        imgui_text(_chr(str_printf(NULL, "Shift map to the South: ctrl + %s", config_current.short_shift_map_south)));
        imgui_text(_chr(str_printf(NULL, "Shift map to the North: ctrl + %s", config_current.short_shift_map_north)));
    }
    imgui_next_column();
    {
        imgui_text_disabled("Input");
        imgui_text(_chr(str_printf(NULL, "Move forward: %s", config_current.input_forward)));
        imgui_text(_chr(str_printf(NULL, "Move backward: %s", config_current.input_backward)));
        imgui_text(_chr(str_printf(NULL, "Move left (strafe): %s", config_current.input_strafe_left)));
        imgui_text(_chr(str_printf(NULL, "Move right (strafe): %s", config_current.input_strafe_right)));
        imgui_text(_chr(str_printf(NULL, "Interact/Use: %s", config_current.input_interact)));
        imgui_text(_chr(str_printf(NULL, "Run (hold): %s", config_current.input_run)));
        imgui_text(_chr(str_printf(NULL, "Drag map (hold): %s", config_current.input_drag_map)));
        imgui_text(_chr(str_printf(NULL, "Draw cell: %s", config_current.input_draw)));
        imgui_text(_chr(str_printf(NULL, "Erase cell: %s", config_current.input_erase)));
        imgui_text(_chr(str_printf(NULL, "Pick cell (hold + draw): %s", config_current.input_pick)));
        imgui_text(_chr(str_printf(NULL, "Rotate cell: %s", config_current.input_rotate)));
        imgui_text(_chr(str_printf(NULL, "Rapid mode (hold): %s", config_current.input_run)));
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
    if (imgui_button_withsize("Close", width, POPUP_BUTTON_HEIGHT * config_saved.font_scale) || key_esc && is_esc_popup_allowed == true)
    {
        is_popup_opened = false;
        imgui_close_current_popup();
    }
}

void popup_wait_for_input()
{
    imgui_text_centered("Press anykey to bind it to selected command!");

    if (is_popup_opened == false)
    {
        imgui_close_current_popup();
    }
}