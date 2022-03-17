
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
    editor_input_overwrite(config_current.input_interact, bindkey);
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
    editor_input_bind_key(config_current.input_interact, input_interact_entry_str, entry, bindkey);
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
    editor_input_bind_key(config_current.input_interact, input_interact_entry_str, entry, input_none_str);
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
    editor_switch_popup_to(MAIN_POPUP_WAIT_FOR_INPUT);

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
                editor_input_bind_new_key(entry, engine_key_return_letter_from_scancode(key_lastpressed));
                wait_for_input = false;
            }
        }

        wait(1);
    }

    is_popup_opened = false;

    wait(1);

    editor_switch_popup_to(main_popup_old_state);
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