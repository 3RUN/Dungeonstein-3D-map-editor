
void editor_popups_initialize(Episode *episode)
{
    // new episode temp settings
    strcpy(new_filename, "");
    strcpy(new_name, "");
    strcpy(new_start_story, "");
    strcpy(new_end_story, "");
    new_map_count = 1;

    // resolution
    int i = 0;

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

    editor_popups_refresh(episode);
}

void editor_popups_refresh(Episode *episode)
{
    if (!episode)
    {
        return;
    }

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

void editor_popups_destroy()
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

void editor_popup_open(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    imgui_text(_chr(editor_popup_open_str));
    imgui_separator();

    int editor_popup_open_child_flags = ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
    imgui_begin_child(editor_popup_episode_browser_id, vector(EDITOR_POPUP_OPEN_WIDTH, EDITOR_POPUP_OPEN_HEIGHT - 60, 0), 1, editor_popup_open_child_flags);

    if (found_episodes_total <= 0)
    {
        imgui_text(_chr(editor_popup_open_empty_folder_str));
    }
    else
    {
        imgui_push_item_width(-1);
        if (imgui_list_box(editor_popup_episode_listbox_id, &found_episode_index, found_episodes_listbox, found_episodes_total, found_episodes_total))
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

    var width = EDITOR_POPUP_OPEN_WIDTH / 3;

    if (imgui_button_withsize(_chr(editor_refresh_str), width, EDITOR_POPUP_BUTTON_HEIGHT))
    {
        is_episode_open_failed = false;
        editor_episode_list_refresh();
    }

    imgui_same_line();
    if (imgui_button_withsize(_chr(editor_load_str), width, EDITOR_POPUP_BUTTON_HEIGHT))
    {
        if (found_episode_index >= 0)
        {
            is_episode_open_failed = false;
            is_popup_opened = false;
            imgui_close_current_popup();
            editor_switch_state_to(EDITOR_STATE_OPEN);
        }
        else
        {
            is_episode_open_failed = true;
        }
    }

    imgui_same_line();
    if (imgui_button_withsize(_chr(editor_cancel_str), width, EDITOR_POPUP_BUTTON_HEIGHT) || key_esc)
    {
        found_episode_index = -1;
        is_episode_open_failed = false;
        is_popup_opened = false;
        imgui_close_current_popup();
    }

    if (is_episode_open_failed == true)
    {
        imgui_push_style_color(ImGuiCol_TextDisabled, color4_red);
        imgui_text_disabled("      Select an episode from the list to load it!");
        imgui_pop_style_color(1);
    }
}

void editor_popup_open_sure()
{
    imgui_text(_chr(editor_popup_open_sure_str));
    imgui_separator();

    var width = EDITOR_POPUP_OPEN_SURE_WIDTH / 2;

    if (imgui_button_withsize(_chr(editor_yes_str), width, EDITOR_POPUP_BUTTON_HEIGHT))
    {
        // we first need to close old popup
        // because new one's positions won't be centered correctly !
        is_popup_opened = false;
        imgui_close_current_popup();

        // now move to the open state !
        editor_map_popup_state_change_to(MAP_POPUP_OPEN);
    }

    imgui_same_line();
    if (imgui_button_withsize(_chr(editor_no_str), width, EDITOR_POPUP_BUTTON_HEIGHT) || key_esc)
    {
        is_popup_opened = false;
        imgui_close_current_popup();
    }
}

void editor_popup_new(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    imgui_text(_chr(editor_popup_new_filename_str));
    imgui_same_line();
    editor_help_maker(_chr(str_printf(NULL, editor_popup_new_filename_tooltip_str, (long)EPISODE_FILENAME_LENGTH)));
    imgui_push_item_width(-1);
    imgui_input_text(editor_popup_new_filename_input_id, new_filename, EPISODE_FILENAME_LENGTH, NULL);
    imgui_pop_item_width();

    imgui_text(_chr(editor_popup_new_episode_name_str));
    imgui_same_line();
    editor_help_maker(_chr(str_printf(NULL, editor_popup_new_episode_name_tooltip_str, (long)EPISODE_NAME_LENGTH)));
    imgui_push_item_width(-1);
    imgui_input_text(editor_popup_new_episode_name_id, new_name, EPISODE_NAME_LENGTH, NULL);
    imgui_pop_item_width();

    imgui_text(_chr(editor_popup_new_episode_start_story_str));
    imgui_same_line();
    editor_help_maker(_chr(str_printf(NULL, editor_popup_new_episode_start_story_tooltip_str, (long)EPISODE_START_STORY_LENGTH)));
    imgui_input_text_multiline(editor_popup_new_episode_start_story_id, new_start_story, EPISODE_START_STORY_LENGTH, -1, 128, NULL);

    imgui_text(_chr(editor_popup_new_episode_end_story_str));
    imgui_same_line();
    editor_help_maker(_chr(str_printf(NULL, editor_popup_new_episode_end_story_tooltip_str, (long)EPISODE_END_STORY_LENGTH)));
    imgui_input_text_multiline(editor_popup_new_episode_end_story_id, new_end_story, EPISODE_END_STORY_LENGTH, -1, 128, NULL);

    imgui_text(_chr(editor_popup_new_episode_map_count_str));
    imgui_same_line();
    editor_help_maker(_chr(str_printf(NULL, editor_popup_new_episode_map_count_tooltip_str, (long)MAX_MAPS_PER_EPISODE)));
    imgui_push_item_width(-1);
    imgui_slider_int(editor_popup_new_episode_map_slider_id, &new_map_count, 1, MAX_MAPS_PER_EPISODE);
    imgui_pop_item_width();

    var width = EDITOR_POPUP_NEW_WIDTH / 2;

    if (imgui_button_withsize(_chr(editor_popup_new_create_str), width, EDITOR_POPUP_BUTTON_HEIGHT))
    {
        if (strlen(new_filename) > 0 && strlen(new_name) > 0 && strlen(new_start_story) > 0 && strlen(new_end_story) > 0)
        {
            is_episode_creation_failed = false;
            is_popup_opened = false;
            imgui_close_current_popup();
            editor_switch_state_to(EDITOR_STATE_NEW);
        }
        else
        {
            is_episode_creation_failed = true;
        }
    }

    imgui_same_line();
    if (imgui_button_withsize(_chr(editor_back_str), width, EDITOR_POPUP_BUTTON_HEIGHT) || key_esc)
    {
        strcpy(new_filename, "");
        strcpy(new_name, "");
        strcpy(new_start_story, "");
        strcpy(new_end_story, "");
        new_map_count = 1;

        is_episode_creation_failed = false;
        is_popup_opened = false;
        imgui_close_current_popup();
    }

    if (is_episode_creation_failed == true)
    {
        imgui_push_style_color(ImGuiCol_TextDisabled, color4_red);
        imgui_text_disabled(_chr(editor_popup_new_creation_failed_str));
        imgui_pop_style_color(1);
    }

    STRING *check_name = "";
    str_cpy(check_name, episode_save_folder_str);
    str_cat(check_name, new_filename);
    str_cat(check_name, episode_extension_str);
    path_make_absolute(check_name);

    if (file_exists(check_name))
    {
        str_cpy(editor_popup_new_create_str, editor_overwrite_str);
        imgui_push_style_color(ImGuiCol_TextDisabled, color4_red);
        imgui_text_disabled(_chr(editor_popup_new_file_exist_str));
        imgui_pop_style_color(1);
    }
    else
    {
        str_cpy(editor_popup_new_create_str, editor_save_str);
    }
}

void editor_popup_new_sure()
{
    imgui_text(_chr(editor_popup_new_sure_str));
    imgui_separator();

    var width = EDITOR_POPUP_NEW_SURE_WIDTH / 2;

    if (imgui_button_withsize(_chr(editor_yes_str), width, EDITOR_POPUP_BUTTON_HEIGHT))
    {
        // we first need to close old popup
        // because new one's positions won't be centered correctly !
        is_popup_opened = false;
        imgui_close_current_popup();

        // now move to the open state !
        editor_map_popup_state_change_to(MAP_POPUP_NEW);
    }

    imgui_same_line();
    if (imgui_button_withsize(_chr(editor_no_str), width, EDITOR_POPUP_BUTTON_HEIGHT) || key_esc)
    {
        is_popup_opened = false;
        imgui_close_current_popup();
    }
}

void editor_popup_save_as(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    imgui_text(_chr(editor_popup_save_as_str));
    imgui_separator();

    imgui_text(_chr(editor_filename_str));
    imgui_same_line();
    imgui_push_item_width(-1);
    imgui_input_text_with_hint(editor_popup_save_as_input_id, _chr(editor_save_as_hint_str), save_as_filename, EPISODE_FILENAME_LENGTH, NULL);
    imgui_pop_item_width();

    var width = EDITOR_POPUP_SAVE_AS_WIDTH / 2;

    if (imgui_button_withsize(_chr(editor_popup_save_as_button_str), width, EDITOR_POPUP_BUTTON_HEIGHT))
    {
        if (strlen(save_as_filename) > 0)
        {
            is_episode_save_as_failed = false;
            is_popup_opened = false;
            imgui_close_current_popup();
            editor_switch_state_to(EDITOR_STATE_SAVE_US);
        }
        else
        {
            is_episode_save_as_failed = true;
        }
    }
    imgui_same_line();
    if (imgui_button_withsize(_chr(editor_cancel_str), width, EDITOR_POPUP_BUTTON_HEIGHT) || key_esc)
    {
        strcpy(save_as_filename, "");
        is_episode_save_as_failed = false;
        is_popup_opened = false;
        imgui_close_current_popup();
    }

    if (is_episode_save_as_failed == true)
    {
        imgui_push_style_color(ImGuiCol_TextDisabled, color4_red);
        imgui_text_disabled(_chr(editor_popup_save_as_failed_str));
        imgui_pop_style_color(1);
    }

    STRING *check_name = "";
    str_cpy(check_name, episode_save_folder_str);
    str_cat(check_name, save_as_filename);
    str_cat(check_name, episode_extension_str);
    path_make_absolute(check_name);

    if (file_exists(check_name))
    {
        str_cpy(editor_popup_save_as_button_str, _chr(editor_overwrite_str));
        imgui_push_style_color(ImGuiCol_TextDisabled, color4_red);
        imgui_text_disabled(_chr(editor_popup_save_as_overwrite_str));
        imgui_pop_style_color(1);
    }
    else
    {
        str_cpy(editor_popup_save_as_button_str, _chr(editor_save_str));
    }
}

void editor_popup_settings(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    imgui_text(_chr(editor_preferences_str));
    imgui_separator();

    // display mode here
    imgui_text(_chr(graphics_display_mode_str));
    imgui_same_line();
    imgui_align_right_with_offset(EDITOR_POPUP_COMBOBOX_WIDTH);
    imgui_push_item_width(EDITOR_POPUP_COMBOBOX_WIDTH - 1);
    if (imgui_begin_combo(editor_popup_settings_display_combo_id, _chr(graphics_display_currently_used_str), ImGuiComboFlags_HeightSmall))
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
        imgui_align_right_with_offset(EDITOR_POPUP_COMBOBOX_WIDTH);
        imgui_push_item_width(EDITOR_POPUP_COMBOBOX_WIDTH - 1);
        if (imgui_begin_combo(editor_popup_settings_resolution_combo_id, _chr(graphics_resolution_currently_used_str), ImGuiComboFlags_HeightSmall))
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
    imgui_text(_chr(editor_popup_settings_hover_cell_tooltip_str));
    imgui_same_line();
    imgui_align_right_with_offset(160);
    imgui_radiobutton(_chr(editor_enabled_str), &config_current.is_cell_tooltip_enabled, true);
    imgui_same_line();
    imgui_radiobutton(_chr(editor_disabled_str), &config_current.is_cell_tooltip_enabled, false);
    imgui_separator();

    // background color
    imgui_text(_chr(editor_popup_settings_background_color_str));
    imgui_same_line();
    var avail_picker_width = imgui_get_content_region_avail_width();
    imgui_push_item_width(avail_picker_width);
    static int misc_flags = ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoDragDrop;
    imgui_color_edit3(editor_popup_settings_bg_color_picker_id, config_current.background_color, misc_flags);
    imgui_pop_item_width();

    // grid color
    imgui_text(_chr(editor_popup_settings_grid_color_str));
    imgui_same_line();
    var avail_picker_width = imgui_get_content_region_avail_width();
    imgui_push_item_width(avail_picker_width);
    static int misc_flags = ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoDragDrop;
    imgui_color_edit3(editor_popup_settings_grid_color_picker_id, config_current.grid_color, misc_flags);
    imgui_pop_item_width();

    // make a little offset
    imgui_text("\r\n");
    imgui_separator();

    var width = EDITOR_POPUP_SETTINGS_WIDTH / 3;

    // reset to defaults button
    if (imgui_button_withsize(_chr(editor_defaults_str), width, EDITOR_POPUP_BUTTON_HEIGHT))
    {
        config_reset_to_default();
        editor_popups_refresh(episode);
    }

    // apply and save
    imgui_same_line();
    if (imgui_button_withsize(_chr(editor_apply_str), width, EDITOR_POPUP_BUTTON_HEIGHT))
    {
        config_save_n_apply();
        editor_popups_refresh(episode);
        is_popup_opened = false;
        imgui_close_current_popup();
    }

    // cancel changes
    imgui_same_line();
    if (imgui_button_withsize(_chr(editor_cancel_str), width, EDITOR_POPUP_BUTTON_HEIGHT) || key_esc)
    {
        config_reset_to_saved();
        editor_popups_refresh(episode);
        is_popup_opened = false;
        imgui_close_current_popup();
    }
}

void editor_popup_about()
{
    imgui_text(_chr(editor_help_str));
    imgui_separator();

    imgui_text_disabled(_chr(editor_popup_controlls_str));
    int editor_popup_about_controlls_child_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
    imgui_begin_child(editor_popup_about_child_id, vector(EDITOR_POPUP_ABOUT_CHILD_WIDTH, EDITOR_POPUP_ABOUT_CHILD_HEIGHT, 0), 1, editor_popup_about_controlls_child_flags);

    imgui_text(_chr(editor_popup_controlls_cmd_0_str));
    imgui_text(_chr(editor_popup_controlls_cmd_1_str));
    imgui_text(_chr(editor_popup_controlls_cmd_2_str));
    imgui_text(_chr(editor_popup_controlls_cmd_3_str));
    imgui_text(_chr(editor_popup_controlls_cmd_4_str));
    imgui_text(_chr(editor_popup_controlls_cmd_5_str));

    imgui_end_child();
    imgui_separator();

    imgui_text_disabled(_chr(editor_popup_episode_saved_at_str));
    imgui_text(_chr(editor_popup_episode_save_path_str));
    imgui_separator();

    imgui_text_disabled(_chr(editor_popup_credit_name_str));
    imgui_same_line();
    imgui_text(_chr(editor_popup_credit_info_0_str));
    imgui_text_disabled(_chr(editor_popup_credit_email_str));
    imgui_same_line();
    imgui_text(_chr(editor_popup_credit_info_1_str));
    imgui_separator();

    if (imgui_button_withsize(_chr(editor_close_str), -1, EDITOR_POPUP_BUTTON_HEIGHT) || key_esc)
    {
        is_popup_opened = false;
        imgui_close_current_popup();
    }
}

void editor_popup_episode_edit(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    imgui_text(_chr(editor_popup_episode_edit_str));
    imgui_separator();

    imgui_text(_chr(editor_popup_new_episode_name_str));
    imgui_same_line();
    editor_help_maker(_chr(str_printf(NULL, editor_popup_new_episode_name_tooltip_str, (long)EPISODE_NAME_LENGTH)));
    imgui_push_item_width(-1);
    imgui_input_text(editor_popup_episode_edit_name_id, episode_edit_name, EPISODE_NAME_LENGTH, NULL);
    imgui_pop_item_width();

    imgui_text(_chr(editor_popup_new_episode_start_story_str));
    imgui_same_line();
    editor_help_maker(_chr(str_printf(NULL, editor_popup_new_episode_start_story_tooltip_str, (long)EPISODE_START_STORY_LENGTH)));
    imgui_input_text_multiline(editor_popup_episode_edit_start_story_id, episode_edit_start_story, EPISODE_START_STORY_LENGTH, -1, 128, NULL);

    imgui_text(_chr(editor_popup_new_episode_end_story_str));
    imgui_same_line();
    editor_help_maker(_chr(str_printf(NULL, editor_popup_new_episode_end_story_tooltip_str, (long)EPISODE_END_STORY_LENGTH)));
    imgui_input_text_multiline(editor_popup_episode_edit_end_story_id, episode_edit_end_story, EPISODE_END_STORY_LENGTH, -1, 128, NULL);

    imgui_text(_chr(editor_popup_new_episode_map_count_str));
    imgui_same_line();
    editor_help_maker(_chr(str_printf(NULL, editor_popup_new_episode_map_count_tooltip_str, (long)MAX_MAPS_PER_EPISODE)));
    imgui_push_item_width(-1);
    imgui_slider_int(editor_popup_episode_edit_map_slider_id, &episode_edit_map_count, 1, MAX_MAPS_PER_EPISODE);
    imgui_pop_item_width();

    var width = EDITOR_POPUP_EPISODE_EDIT_WIDTH / 3;

    if (imgui_button_withsize(_chr(editor_reset_str), width, EDITOR_POPUP_BUTTON_HEIGHT))
    {
        is_episode_edit_failed = false;
        strcpy(episode_edit_name, episode->name);
        strcpy(episode_edit_start_story, episode->start_story);
        strcpy(episode_edit_end_story, episode->end_story);
        episode_edit_map_count = episode->map_count;
    }

    imgui_same_line();
    if (imgui_button_withsize(_chr(editor_apply_str), width, EDITOR_POPUP_BUTTON_HEIGHT))
    {
        if (strlen(episode_edit_name) > 0 && strlen(episode_edit_start_story) > 0 && strlen(episode_edit_end_story) > 0)
        {
            is_episode_edit_failed = false;

            episode->map_count = episode_edit_map_count;
            strcpy(episode->name, episode_edit_name);
            strcpy(episode->start_story, episode_edit_start_story);
            strcpy(episode->end_story, episode_edit_end_story);

            is_popup_opened = false;
            imgui_close_current_popup();
        }
        else
        {
            is_episode_edit_failed = true;
        }
    }

    imgui_same_line();
    if (imgui_button_withsize(_chr(editor_cancel_str), width, EDITOR_POPUP_BUTTON_HEIGHT) || key_esc)
    {
        is_episode_edit_failed = false;
        strcpy(episode_edit_name, episode->name);
        strcpy(episode_edit_start_story, episode->start_story);
        strcpy(episode_edit_end_story, episode->end_story);
        episode_edit_map_count = episode->map_count;

        is_popup_opened = false;
        imgui_close_current_popup();
    }

    if (is_episode_edit_failed == true)
    {
        imgui_push_style_color(ImGuiCol_TextDisabled, color4_red);
        imgui_text_disabled(_chr(editor_popup_episode_edit_failed_str));
        imgui_pop_style_color(1);
    }
}

void editor_popup_reset_map(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    imgui_text(_chr(editor_popup_reset_map_str));
    imgui_separator();

    var width = EDITOR_POPUP_RESET_MAP_WIDTH / 2;

    if (imgui_button_withsize(_chr(editor_yes_str), width, EDITOR_POPUP_BUTTON_HEIGHT))
    {
        is_popup_opened = false;
        imgui_close_current_popup();
        editor_switch_state_to(EDITOR_STATE_RESET_MAP);
    }

    imgui_same_line();
    if (imgui_button_withsize(_chr(editor_no_str), width, EDITOR_POPUP_BUTTON_HEIGHT) || key_esc)
    {
        is_popup_opened = false;
        imgui_close_current_popup();
    }
}

void editor_popup_music_browser(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    imgui_text(_chr(editor_popup_music_browser_str));
    imgui_separator();

    int editor_music_browser_child_flags = ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
    imgui_begin_child(editor_popup_music_browser_child_id, vector(MUSIC_POPUP_MUSIC_BROWSER_WIDTH, MUSIC_POPUP_MUSIC_BROWSER_HEIGHT - 60, 0), 1, editor_music_browser_child_flags);

    if (found_music_total <= 0)
    {
        imgui_text(_chr(editor_popup_music_browser_empty_folder_str));
    }
    else
    {
        imgui_push_item_width(-1);
        if (imgui_list_box(editor_popup_music_browser_listbox_id, &found_music_index, found_music_listbox, found_music_total, found_music_total))
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

    if (strlen(map_settings.music) <= 0)
    {
        str_cpy(editor_popup_currently_used_music_str, editor_popup_music_browser_used_none_str);
        imgui_text(_chr(editor_popup_currently_used_music_str));
    }
    else
    {
        str_cpy(editor_popup_currently_used_music_str, editor_popup_music_browser_used_str);
        str_cat(editor_popup_currently_used_music_str, _str(map_settings.music));
        str_replace(editor_popup_currently_used_music_str, episode_music_folder_str, "");
        imgui_text(_chr(editor_popup_currently_used_music_str));
    }

    if (media_playing(playing_music_handle))
    {
        str_cpy(editor_popup_currently_playing_music_str, editor_popup_music_browser_playing_str);
        str_cat(editor_popup_currently_playing_music_str, _str(found_music_listbox[playing_music_index]));
        imgui_text(_chr(editor_popup_currently_playing_music_str));
    }
    else
    {
        str_cpy(editor_popup_currently_playing_music_str, editor_popup_music_browser_playing_none_str);
        imgui_text(_chr(editor_popup_currently_playing_music_str));
    }

    imgui_text(_chr(editor_volume_str));
    imgui_same_line();
    imgui_push_item_width(-1);
    imgui_slider_var(editor_popup_music_browser_volume_slider_id, &playing_music_volume, 0, 100);
    imgui_pop_item_width();

    imgui_separator();

    var width = MUSIC_POPUP_MUSIC_BROWSER_WIDTH / 4;

    if (imgui_button_withsize(_chr(editor_refresh_str), width, EDITOR_POPUP_BUTTON_HEIGHT))
    {
        is_music_playing_failed = false;
        editor_music_browser_refresh_list();
    }

    imgui_same_line();
    if (imgui_button_withsize(_chr(editor_play_n_stop_str), width, EDITOR_POPUP_BUTTON_HEIGHT))
    {
        if (found_music_index >= 0)
        {
            is_music_playing_failed = false;

            if (media_playing(playing_music_handle))
            {
                media_stop(playing_music_handle);

                if (playing_music_index != found_music_index)
                {
                    editor_play_browser_music();
                }
            }
            else
            {
                editor_play_browser_music();
            }
        }
        else
        {
            is_music_playing_failed = true;
            media_stop(playing_music_handle);
        }
    }

    imgui_same_line();
    if (imgui_button_withsize(_chr(editor_use_str), width, EDITOR_POPUP_BUTTON_HEIGHT))
    {
        if (found_music_index >= 0)
        {
            master_vol = 100;
            weather_resume_sound();
            media_stop(playing_music_handle);
            is_music_playing_failed = false;
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
            is_music_playing_failed = true;
        }
    }

    imgui_same_line();
    if (imgui_button_withsize(_chr(editor_close_str), width, EDITOR_POPUP_BUTTON_HEIGHT) || key_esc)
    {
        master_vol = 100;
        weather_resume_sound();
        media_stop(playing_music_handle);
        is_music_playing_failed = false;
        found_music_index = -1;

        is_popup_opened = false;
        imgui_close_current_popup();
    }

    if (media_playing(playing_music_handle))
    {
        master_vol = playing_music_volume;
        media_tune(playing_music_handle, playing_music_volume, 0, 0);
    }

    if (is_music_playing_failed == true)
    {
        imgui_push_style_color(ImGuiCol_TextDisabled, color4_red);
        imgui_text_disabled(_chr(editor_popup_music_browser_playing_failed_str));
        imgui_pop_style_color(1);
    }
}

void editor_popup_exit()
{
    imgui_text(_chr(editor_popup_exit_str));
    imgui_separator();

    var width = EDITOR_POPUP_EXIT_WIDTH / 2;

    if (imgui_button_withsize(_chr(editor_yes_str), width, EDITOR_POPUP_BUTTON_HEIGHT))
    {
        is_popup_opened = false;
        imgui_close_current_popup();
        editor_switch_state_to(EDITOR_STATE_EXIT);
    }

    imgui_same_line();
    if (imgui_button_withsize(_chr(editor_no_str), width, EDITOR_POPUP_BUTTON_HEIGHT) || key_esc)
    {
        is_popup_opened = false;
        imgui_close_current_popup();
    }
}