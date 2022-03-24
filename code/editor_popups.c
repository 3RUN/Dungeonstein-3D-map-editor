
void editor_input_overwrite(char *input, STRING *bindkey)
{
    if (strcmp(input, _chr(bindkey)) == 0)
    {
        strcpy(input, _chr(input_none_str));
    }
}

void editor_input_check_overwrite(STRING *bindkey)
{
    // input
    editor_input_overwrite(config_current.input_forward, bindkey);
    editor_input_overwrite(config_current.input_backward, bindkey);
    editor_input_overwrite(config_current.input_strafe_left, bindkey);
    editor_input_overwrite(config_current.input_strafe_right, bindkey);
    editor_input_overwrite(config_current.input_surface, bindkey);
    editor_input_overwrite(config_current.input_dive, bindkey);
    editor_input_overwrite(config_current.input_run, bindkey);
    editor_input_overwrite(config_current.input_draw, bindkey);
    editor_input_overwrite(config_current.input_erase, bindkey);
    editor_input_overwrite(config_current.input_pick, bindkey);
    editor_input_overwrite(config_current.input_rotate, bindkey);

    // shortcuts
    editor_input_overwrite(config_current.short_help, bindkey);
    editor_input_overwrite(config_current.short_new, bindkey);
    editor_input_overwrite(config_current.short_open, bindkey);
    editor_input_overwrite(config_current.short_save, bindkey);
    editor_input_overwrite(config_current.short_ep_reset, bindkey);
    editor_input_overwrite(config_current.short_ep_edit, bindkey);
    editor_input_overwrite(config_current.short_reset_map, bindkey);
    editor_input_overwrite(config_current.short_test_run, bindkey);
    editor_input_overwrite(config_current.short_map_settings, bindkey);
    editor_input_overwrite(config_current.short_screenshot, bindkey);
    editor_input_overwrite(config_current.short_settings, bindkey);
    editor_input_overwrite(config_current.short_prior_map, bindkey);
    editor_input_overwrite(config_current.short_next_map, bindkey);
    editor_input_overwrite(config_current.short_toggle_debug, bindkey);
    editor_input_overwrite(config_current.short_shift_map_west, bindkey);
    editor_input_overwrite(config_current.short_shift_map_east, bindkey);
    editor_input_overwrite(config_current.short_shift_map_south, bindkey);
    editor_input_overwrite(config_current.short_shift_map_north, bindkey);
}

void editor_input_bind_key(char *input, STRING *input_entry, STRING *entry, STRING *bindkey)
{
    if (str_cmp(entry, input_entry))
    {
        strcpy(input, _chr(bindkey));
    }
}

void editor_input_bind_new_key(STRING *entry, STRING *bindkey)
{
    // check if given key is already in use, and if yes
    // then remove it !
    editor_input_check_overwrite(bindkey);
    wait_for(editor_input_check_overwrite);

    // assign the key
    editor_input_bind_key(config_current.input_forward, input_forward_entry_str, entry, bindkey); // input
    editor_input_bind_key(config_current.input_backward, input_backward_entry_str, entry, bindkey);
    editor_input_bind_key(config_current.input_strafe_left, input_strafe_left_entry_str, entry, bindkey);
    editor_input_bind_key(config_current.input_strafe_right, input_strafe_right_entry_str, entry, bindkey);
    editor_input_bind_key(config_current.input_surface, input_surface_entry_str, entry, bindkey);
    editor_input_bind_key(config_current.input_dive, input_dive_entry_str, entry, bindkey);
    editor_input_bind_key(config_current.input_run, input_run_entry_str, entry, bindkey);
    editor_input_bind_key(config_current.input_draw, input_draw_entry_str, entry, bindkey);
    editor_input_bind_key(config_current.input_erase, input_erase_entry_str, entry, bindkey);
    editor_input_bind_key(config_current.input_pick, input_pick_entry_str, entry, bindkey);
    editor_input_bind_key(config_current.input_rotate, input_rotate_entry_str, entry, bindkey);

    editor_input_bind_key(config_current.short_help, short_help_entry_str, entry, bindkey); // shortcuts
    editor_input_bind_key(config_current.short_new, short_new_entry_str, entry, bindkey);
    editor_input_bind_key(config_current.short_open, short_open_entry_str, entry, bindkey);
    editor_input_bind_key(config_current.short_save, short_save_entry_str, entry, bindkey);
    editor_input_bind_key(config_current.short_ep_reset, short_ep_reset_entry_str, entry, bindkey);
    editor_input_bind_key(config_current.short_ep_edit, short_ep_edit_entry_str, entry, bindkey);
    editor_input_bind_key(config_current.short_reset_map, short_reset_map_entry_str, entry, bindkey);
    editor_input_bind_key(config_current.short_test_run, short_test_run_entry_str, entry, bindkey);
    editor_input_bind_key(config_current.short_map_settings, short_map_settings_entry_str, entry, bindkey);
    editor_input_bind_key(config_current.short_screenshot, short_screenshot_entry_str, entry, bindkey);
    editor_input_bind_key(config_current.short_settings, short_settings_entry_str, entry, bindkey);
    editor_input_bind_key(config_current.short_prior_map, short_prior_map_entry_str, entry, bindkey);
    editor_input_bind_key(config_current.short_next_map, short_next_map_entry_str, entry, bindkey);
    editor_input_bind_key(config_current.short_toggle_debug, short_toggle_debug_entry_str, entry, bindkey);
    editor_input_bind_key(config_current.short_shift_map_west, short_shift_map_west_entry_str, entry, bindkey);
    editor_input_bind_key(config_current.short_shift_map_east, short_shift_map_east_entry_str, entry, bindkey);
    editor_input_bind_key(config_current.short_shift_map_south, short_shift_map_south_entry_str, entry, bindkey);
    editor_input_bind_key(config_current.short_shift_map_north, short_shift_map_north_entry_str, entry, bindkey);
}

void editor_input_remove_bind_key(STRING *entry)
{
    // assign the key
    editor_input_bind_key(config_current.input_forward, input_forward_entry_str, entry, input_none_str); // input
    editor_input_bind_key(config_current.input_backward, input_backward_entry_str, entry, input_none_str);
    editor_input_bind_key(config_current.input_strafe_left, input_strafe_left_entry_str, entry, input_none_str);
    editor_input_bind_key(config_current.input_strafe_right, input_strafe_right_entry_str, entry, input_none_str);
    editor_input_bind_key(config_current.input_surface, input_surface_entry_str, entry, input_none_str);
    editor_input_bind_key(config_current.input_dive, input_dive_entry_str, entry, input_none_str);
    editor_input_bind_key(config_current.input_run, input_run_entry_str, entry, input_none_str);
    editor_input_bind_key(config_current.input_draw, input_draw_entry_str, entry, input_none_str);
    editor_input_bind_key(config_current.input_erase, input_erase_entry_str, entry, input_none_str);
    editor_input_bind_key(config_current.input_pick, input_pick_entry_str, entry, input_none_str);
    editor_input_bind_key(config_current.input_rotate, input_rotate_entry_str, entry, input_none_str);

    editor_input_bind_key(config_current.short_help, short_help_entry_str, entry, input_none_str); // shortcuts
    editor_input_bind_key(config_current.short_new, short_new_entry_str, entry, input_none_str);
    editor_input_bind_key(config_current.short_open, short_open_entry_str, entry, input_none_str);
    editor_input_bind_key(config_current.short_save, short_save_entry_str, entry, input_none_str);
    editor_input_bind_key(config_current.short_ep_reset, short_ep_reset_entry_str, entry, input_none_str);
    editor_input_bind_key(config_current.short_ep_edit, short_ep_edit_entry_str, entry, input_none_str);
    editor_input_bind_key(config_current.short_reset_map, short_reset_map_entry_str, entry, input_none_str);
    editor_input_bind_key(config_current.short_test_run, short_test_run_entry_str, entry, input_none_str);
    editor_input_bind_key(config_current.short_map_settings, short_map_settings_entry_str, entry, input_none_str);
    editor_input_bind_key(config_current.short_screenshot, short_screenshot_entry_str, entry, input_none_str);
    editor_input_bind_key(config_current.short_settings, short_settings_entry_str, entry, input_none_str);
    editor_input_bind_key(config_current.short_prior_map, short_prior_map_entry_str, entry, input_none_str);
    editor_input_bind_key(config_current.short_next_map, short_next_map_entry_str, entry, input_none_str);
    editor_input_bind_key(config_current.short_toggle_debug, short_toggle_debug_entry_str, entry, input_none_str);
    editor_input_bind_key(config_current.short_shift_map_west, short_shift_map_west_entry_str, entry, input_none_str);
    editor_input_bind_key(config_current.short_shift_map_east, short_shift_map_east_entry_str, entry, input_none_str);
    editor_input_bind_key(config_current.short_shift_map_south, short_shift_map_south_entry_str, entry, input_none_str);
    editor_input_bind_key(config_current.short_shift_map_north, short_shift_map_north_entry_str, entry, input_none_str);
}

void editor_input_wait_for_binding(STRING *entry)
{
    is_popup_opened = false;
    imgui_close_current_popup();
    editor_switch_popup_to(EDITOR_POPUP_WAIT_FOR_INPUT);

    while (key_any) // wait untill we 'unpress' all keys
    {
        wait(1);
    }

    var cooldown_time = 0.1;
    while (cooldown_time > 0)
    {
        cooldown_time -= time_frame / 16;
        wait(1);
    }

    int wait_for_input = true;
    while (wait_for_input == true)
    {
        if (key_lastpressed == SCANCODE_ESC || key_lastpressed == SCANCODE_ENTER)
        {
            wait_for_input = false;
        }

        if (key_lastpressed == SCANCODE_DELETE)
        {
            editor_input_remove_bind_key(entry);
            wait_for_input = false;
        }

        if (key_any == true)
        {
            // check for the key's not being esc, enter or delete
            // also (sorry...) we don't support joystick buttons...
            if (key_lastpressed != SCANCODE_ESC && key_lastpressed != SCANCODE_ENTER && key_lastpressed != SCANCODE_DELETE && key_lastpressed < 256 || key_lastpressed != SCANCODE_ESC && key_lastpressed != SCANCODE_ENTER && key_lastpressed != SCANCODE_DELETE && key_lastpressed > 279)
            {
                STRING *bindkey = "";
                engine_key_return_letter_from_scancode(&bindkey, key_lastpressed);
                editor_input_bind_new_key(entry, bindkey);
                wait_for_input = false;
            }
        }

        wait(1);
    }

    is_popup_opened = false;

    wait(1);

    editor_switch_popup_to(editor_old_popup_state);
}

void editor_input_add_keybinding(STRING *entry, STRING *input)
{
    imgui_text(_chr(entry));
    imgui_same_line();
    imgui_align_right_with_offset(INPUT_BOTTON_WIDTH * config_saved.font_scale);

    // fixed button label (id)
    STRING *id_str = "";
    str_cpy(id_str, input);
    str_cat(id_str, "##");
    str_cat(id_str, entry);

    if (imgui_button_withsize(_chr(id_str), INPUT_BOTTON_WIDTH * config_saved.font_scale, INPUT_BUTTON_HEIGHT * config_saved.font_scale))
    {
        editor_input_wait_for_binding(entry);
    }
    imgui_separator();
}

void editor_shortcut_add_keybinding(STRING *entry, STRING *base_key, STRING *input)
{
    imgui_text(_chr(entry));
    imgui_same_line();

    VECTOR pos;
    vec_set(&pos, imgui_get_cursor_screen_pos());
    var width = imgui_get_content_region_avail_width() - (INPUT_BOTTON_WIDTH * config_saved.font_scale) - (imgui_get_text_width(_chr(base_key))) - ((engine_theme_win_padding[0] * 1.5) * config_saved.font_scale);
    imgui_set_cursor_screen_pos(vector(pos.x + width, pos.y, pos.z));
    imgui_text_disabled(_chr(base_key));
    imgui_same_line();
    imgui_align_right_with_offset(INPUT_BOTTON_WIDTH * config_saved.font_scale);

    // fixed button label (id)
    STRING *id_str = "";
    str_cpy(id_str, input);
    str_cat(id_str, "##");
    str_cat(id_str, entry);

    if (imgui_button_withsize(_chr(id_str), INPUT_BOTTON_WIDTH * config_saved.font_scale, INPUT_BUTTON_HEIGHT * config_saved.font_scale))
    {
        editor_input_wait_for_binding(entry);
    }
    imgui_separator();
}

void editor_popups_initialize()
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

    editor_popups_refresh();
}

void editor_popups_refresh()
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

    if (imgui_button_withsize("Refresh", -1, POPUP_BUTTON_HEIGHT * config_saved.font_scale))
    {
        is_popup_check_failed = false;
        episode_list_refresh();
    }

    var width = (POPUP_OPEN_WIDTH * config_saved.font_scale) / 3;
    imgui_push_id(POPUP_DELETE_BUTTON_ID);
    imgui_push_style_color_hsv(ImGuiCol_Button, 0, 0.7, 0.7, 1.0);
    imgui_push_style_color_hsv(ImGuiCol_ButtonHovered, 0, 0.8, 0.8, 1.0);
    imgui_push_style_color_hsv(ImGuiCol_ButtonActive, 0, 0.9, 0.9, 1.0);
    var delete_button = imgui_button_withsize("Delete", width, POPUP_BUTTON_HEIGHT * config_saved.font_scale);
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

void editor_popup_open_sure()
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
        editor_switch_popup_to(EDITOR_POPUP_OPEN);
    }

    imgui_same_line();
    if (imgui_button_withsize("No", width, POPUP_BUTTON_HEIGHT * config_saved.font_scale) || key_esc && is_esc_popup_allowed == true || key_n)
    {
        is_popup_opened = false;
        imgui_close_current_popup();
    }
}

void editor_popup_new_reset()
{
    strcpy(new_episode_filename, "");
    strcpy(new_episode_name, "");
    strcpy(new_episode_story_start, "");
    strcpy(new_episode_story_end, "");
    new_episode_map_count = 1;
}

void editor_popup_new(Episode *episode)
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
        editor_popup_new_reset();
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

void editor_popup_new_sure()
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
        editor_switch_popup_to(EDITOR_POPUP_NEW);
    }

    imgui_same_line();
    if (imgui_button_withsize("No", width, POPUP_BUTTON_HEIGHT * config_saved.font_scale) || key_esc && is_esc_popup_allowed == true || key_n)
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

            STRING *temp_ep_name_str = "";
            str_cpy(temp_ep_name_str, _str(save_as_filename));
            str_cat(temp_ep_name_str, " saved.");
            message_add(temp_ep_name_str);

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

void editor_popup_settings_general()
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

void editor_popup_settings_input()
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
    editor_input_add_keybinding(input_surface_entry_str, config_current.input_surface);
    editor_input_add_keybinding(input_dive_entry_str, config_current.input_dive);
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

void editor_popup_settings()
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
            editor_popup_settings_general();
            imgui_end_tabitem();
        }

        if (imgui_begin_tabitem("Input", NULL, settings_tab_item_falgs))
        {
            settings_tab_id = SETTINGS_TAB_INPUT;
            editor_popup_settings_input();
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
        editor_popups_refresh();
    }

    // apply and save
    imgui_same_line();
    if (imgui_button_withsize("Ok", width, POPUP_BUTTON_HEIGHT * config_saved.font_scale) || key_enter)
    {
        config_save();
        config_apply();
        editor_popups_refresh();
        is_popup_opened = false;
        imgui_close_current_popup();
    }

    // cancel changes
    imgui_same_line();
    if (imgui_button_withsize("Back", width, POPUP_BUTTON_HEIGHT * config_saved.font_scale) || key_esc && is_esc_popup_allowed == true)
    {
        config_reset_to_saved();
        editor_popups_refresh();
        is_popup_opened = false;
        imgui_close_current_popup();
    }
}

void editor_popup_exit()
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

void editor_popup_ep_reset()
{
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

void editor_popup_ep_edit_reset(Episode *episode)
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

void editor_popup_ep_edit(Episode *episode)
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
        editor_popup_ep_edit_reset(episode);
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
        editor_popup_ep_edit_reset(episode);

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

void editor_popup_map_reset()
{
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

void editor_popup_help()
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
        imgui_text(_chr(str_printf(NULL, "Shift map to the West: shift + %s", config_current.short_shift_map_west)));
        imgui_text(_chr(str_printf(NULL, "Shift map to the East: shift + %s", config_current.short_shift_map_east)));
        imgui_text(_chr(str_printf(NULL, "Shift map to the South: shift + %s", config_current.short_shift_map_south)));
        imgui_text(_chr(str_printf(NULL, "Shift map to the North: shift + %s", config_current.short_shift_map_north)));
    }
    imgui_next_column();
    {
        imgui_text_disabled("Input");
        imgui_text(_chr(str_printf(NULL, "Move forward: %s", config_current.input_forward)));
        imgui_text(_chr(str_printf(NULL, "Move backward: %s", config_current.input_backward)));
        imgui_text(_chr(str_printf(NULL, "Move left (strafe): %s", config_current.input_strafe_left)));
        imgui_text(_chr(str_printf(NULL, "Move right (strafe): %s", config_current.input_strafe_right)));
        imgui_text(_chr(str_printf(NULL, "Move up (surface): %s", config_current.input_surface)));
        imgui_text(_chr(str_printf(NULL, "Move down (dive): %s", config_current.input_dive)));
        imgui_text(_chr(str_printf(NULL, "Run (hold): %s", config_current.input_run)));
        imgui_text(_chr(str_printf(NULL, "Drag map (hold): %s", config_current.input_drag_map)));
        imgui_text(_chr(str_printf(NULL, "Draw/Select cell: %s", config_current.input_draw)));
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

void editor_popup_wait_for_input()
{
    imgui_text("Press anykey to bind it to selected command!");

    if (is_popup_opened == false)
    {
        imgui_close_current_popup();
    }
}

void editor_popup_music_browser()
{
    imgui_text_centered("Music browser");
    imgui_separator();

    int editor_music_browser_child_flags = ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
    imgui_begin_child(popup_music_browser_child_id, vector(-1, POPUP_MUSIC_BROWSER_HEIGHT - 60, 0), 1, editor_music_browser_child_flags);

    if (found_music_total <= 0)
    {
        imgui_text("'Music' - folder is empty.");
    }
    else
    {
        imgui_push_item_width(-1);
        if (imgui_list_box(popup_music_browser_listbox_id, &found_music_index, found_music_listbox, found_music_total, found_music_total))
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

    // volume slider
    imgui_text("Volume: ");
    imgui_same_line();
    imgui_push_item_width(-1);
    imgui_slider_var(popup_music_browser_volume_slider_id, &playing_music_volume, 0, 100);
    imgui_pop_item_width();

    imgui_separator();

    var width = (POPUP_MUSIC_BROWSER_WIDTH * config_saved.font_scale) / 4;
    if (imgui_button_withsize("Refresh", width, POPUP_BUTTON_HEIGHT * config_saved.font_scale))
    {
        is_popup_check_failed = false;
        music_list_refresh();
    }

    imgui_same_line();
    if (imgui_button_withsize("Play / Stop", width, POPUP_BUTTON_HEIGHT * config_saved.font_scale))
    {
        if (found_music_index >= 0)
        {
            is_popup_check_failed = false;

            if (media_playing(playing_music_handle))
            {
                stop_playing_music();

                if (playing_music_index != found_music_index)
                {
                    play_selection_from_music_list();
                }
            }
            else
            {
                play_selection_from_music_list();
            }
        }
        else
        {
            is_popup_check_failed = true;
            stop_playing_music();
        }
    }

    imgui_same_line();
    if (imgui_button_withsize("Use", width, POPUP_BUTTON_HEIGHT * config_saved.font_scale))
    {
        if (found_music_index >= 0)
        {
            weather_resume_sound();
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
    if (imgui_button_withsize("Close", width, POPUP_BUTTON_HEIGHT * config_saved.font_scale) || key_esc)
    {
        weather_resume_sound();
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