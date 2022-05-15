
void input_remove_on_key_binding(var scancode)
{
    if (scancode <= 0)
    {
        return;
    }

    key_set(scancode, NULL);
}

void input_update_on_key_binding(var scancode, void *fnc)
{
    if (scancode <= 0)
    {
        return;
    }

    key_set(scancode, NULL);
    key_set(scancode, fnc);
}

void input_overwrite(char *input, STRING *bindkey)
{
    if (strcmp(input, _chr(bindkey)) == 0)
    {
        strcpy(input, _chr(input_none_str));
    }
}

void input_check_overwrite(STRING *bindkey)
{
    // input
    input_overwrite(config_current.input_forward, bindkey);
    input_overwrite(config_current.input_backward, bindkey);
    input_overwrite(config_current.input_strafe_left, bindkey);
    input_overwrite(config_current.input_strafe_right, bindkey);
    input_overwrite(config_current.input_fly_up, bindkey);
    input_overwrite(config_current.input_fly_down, bindkey);
    input_overwrite(config_current.input_run, bindkey);
    input_overwrite(config_current.input_rotate_camera, bindkey);
    input_overwrite(config_current.input_draw, bindkey);
    input_overwrite(config_current.input_erase, bindkey);
    input_overwrite(config_current.input_pick, bindkey);
    input_overwrite(config_current.input_rotate, bindkey);
    input_overwrite(config_current.input_toggle_assets, bindkey);
    input_overwrite(config_current.input_toggle_lights, bindkey);
    input_overwrite(config_current.input_toggle_draw_mode, bindkey);

    // shortcuts
    input_overwrite(config_current.short_help, bindkey);
    input_overwrite(config_current.short_screenshot, bindkey);
    input_overwrite(config_current.short_new, bindkey);
    input_overwrite(config_current.short_open, bindkey);
    input_overwrite(config_current.short_settings, bindkey);
    input_overwrite(config_current.short_save, bindkey);
    input_overwrite(config_current.short_ep_reset, bindkey);
    input_overwrite(config_current.short_ep_edit, bindkey);
    input_overwrite(config_current.short_map_reset, bindkey);
    input_overwrite(config_current.short_map_settings, bindkey);
    input_overwrite(config_current.short_toggle_debug, bindkey);
    input_overwrite(config_current.short_toggle_hovering, bindkey);
    input_overwrite(config_current.short_map_prior, bindkey);
    input_overwrite(config_current.short_map_next, bindkey);
    input_overwrite(config_current.short_map_shift_west, bindkey);
    input_overwrite(config_current.short_map_shift_east, bindkey);
    input_overwrite(config_current.short_map_shift_south, bindkey);
    input_overwrite(config_current.short_map_shift_north, bindkey);
}

void input_bind_key(char *input, STRING *input_entry, STRING *entry, STRING *bindkey)
{
    if (str_cmp(entry, input_entry))
    {
        strcpy(input, _chr(bindkey));
    }
}

void input_bind_new_key(STRING *entry, STRING *bindkey)
{
    // check if given key is already in use, and if yes
    // then remove it !
    input_check_overwrite(bindkey);
    wait_for(input_check_overwrite);

    // assign the key
    input_bind_key(config_current.input_forward, input_forward_entry_str, entry, bindkey); // input
    input_bind_key(config_current.input_backward, input_backward_entry_str, entry, bindkey);
    input_bind_key(config_current.input_strafe_left, input_strafe_left_entry_str, entry, bindkey);
    input_bind_key(config_current.input_strafe_right, input_strafe_right_entry_str, entry, bindkey);
    input_bind_key(config_current.input_fly_up, input_fly_up_entry_str, entry, bindkey);
    input_bind_key(config_current.input_fly_down, input_fly_down_entry_str, entry, bindkey);
    input_bind_key(config_current.input_run, input_run_entry_str, entry, bindkey);
    input_bind_key(config_current.input_rotate_camera, input_rotate_cam_entry_str, entry, bindkey);
    input_bind_key(config_current.input_draw, input_draw_entry_str, entry, bindkey);
    input_bind_key(config_current.input_erase, input_erase_entry_str, entry, bindkey);
    input_bind_key(config_current.input_pick, input_pick_entry_str, entry, bindkey);
    input_bind_key(config_current.input_rotate, input_rotate_entry_str, entry, bindkey);
    input_bind_key(config_current.input_toggle_assets, input_toggle_assets_entry_str, entry, bindkey);
    input_bind_key(config_current.input_toggle_lights, input_toggle_lights_entry_str, entry, bindkey);
    input_bind_key(config_current.input_toggle_draw_mode, input_toggle_draw_mode_entry_str, entry, bindkey);

    input_bind_key(config_current.short_help, short_help_entry_str, entry, bindkey); // shortcuts
    input_bind_key(config_current.short_screenshot, short_screenshot_entry_str, entry, bindkey);
    input_bind_key(config_current.short_new, short_new_entry_str, entry, bindkey);
    input_bind_key(config_current.short_open, short_open_entry_str, entry, bindkey);
    input_bind_key(config_current.short_settings, short_settings_entry_str, entry, bindkey);
    input_bind_key(config_current.short_save, short_save_entry_str, entry, bindkey);
    input_bind_key(config_current.short_ep_reset, short_ep_reset_entry_str, entry, bindkey);
    input_bind_key(config_current.short_ep_edit, short_ep_edit_entry_str, entry, bindkey);
    input_bind_key(config_current.short_map_reset, short_map_reset_entry_str, entry, bindkey);
    input_bind_key(config_current.short_map_settings, short_map_settings_entry_str, entry, bindkey);
    input_bind_key(config_current.short_toggle_debug, short_toggle_hovering_entry_str, entry, bindkey);
    input_bind_key(config_current.short_toggle_hovering, short_toggle_debug_entry_str, entry, bindkey);
    input_bind_key(config_current.short_map_prior, short_map_prior_entry_str, entry, bindkey);
    input_bind_key(config_current.short_map_next, short_map_next_entry_str, entry, bindkey);
    input_bind_key(config_current.short_map_shift_west, short_map_shift_west_entry_str, entry, bindkey);
    input_bind_key(config_current.short_map_shift_east, short_map_shift_east_entry_str, entry, bindkey);
    input_bind_key(config_current.short_map_shift_south, short_map_shift_south_entry_str, entry, bindkey);
    input_bind_key(config_current.short_map_shift_north, short_map_shift_north_entry_str, entry, bindkey);
}

void input_remove_bind_key(STRING *entry)
{
    // assign the key
    input_bind_key(config_current.input_forward, input_forward_entry_str, entry, input_none_str); // input
    input_bind_key(config_current.input_backward, input_backward_entry_str, entry, input_none_str);
    input_bind_key(config_current.input_strafe_left, input_strafe_left_entry_str, entry, input_none_str);
    input_bind_key(config_current.input_strafe_right, input_strafe_right_entry_str, entry, input_none_str);
    input_bind_key(config_current.input_fly_up, input_fly_up_entry_str, entry, input_none_str);
    input_bind_key(config_current.input_fly_down, input_fly_down_entry_str, entry, input_none_str);
    input_bind_key(config_current.input_run, input_run_entry_str, entry, input_none_str);
    input_bind_key(config_current.input_rotate_camera, input_rotate_cam_entry_str, entry, input_none_str);
    input_bind_key(config_current.input_draw, input_draw_entry_str, entry, input_none_str);
    input_bind_key(config_current.input_erase, input_erase_entry_str, entry, input_none_str);
    input_bind_key(config_current.input_pick, input_pick_entry_str, entry, input_none_str);
    input_bind_key(config_current.input_rotate, input_rotate_entry_str, entry, input_none_str);
    input_bind_key(config_current.input_toggle_assets, input_toggle_assets_entry_str, entry, input_none_str);
    input_bind_key(config_current.input_toggle_lights, input_toggle_lights_entry_str, entry, input_none_str);
    input_bind_key(config_current.input_toggle_draw_mode, input_toggle_draw_mode_entry_str, entry, input_none_str);

    input_bind_key(config_current.short_help, short_help_entry_str, entry, input_none_str); // shortcuts
    input_bind_key(config_current.short_screenshot, short_screenshot_entry_str, entry, input_none_str);
    input_bind_key(config_current.short_new, short_new_entry_str, entry, input_none_str);
    input_bind_key(config_current.short_open, short_open_entry_str, entry, input_none_str);
    input_bind_key(config_current.short_settings, short_settings_entry_str, entry, input_none_str);
    input_bind_key(config_current.short_save, short_save_entry_str, entry, input_none_str);
    input_bind_key(config_current.short_ep_reset, short_ep_reset_entry_str, entry, input_none_str);
    input_bind_key(config_current.short_ep_edit, short_ep_edit_entry_str, entry, input_none_str);
    input_bind_key(config_current.short_map_reset, short_map_reset_entry_str, entry, input_none_str);
    input_bind_key(config_current.short_map_settings, short_map_settings_entry_str, entry, input_none_str);
    input_bind_key(config_current.short_toggle_debug, short_toggle_hovering_entry_str, entry, input_none_str);
    input_bind_key(config_current.short_toggle_hovering, short_toggle_debug_entry_str, entry, input_none_str);
    input_bind_key(config_current.short_map_prior, short_map_prior_entry_str, entry, input_none_str);
    input_bind_key(config_current.short_map_next, short_map_next_entry_str, entry, input_none_str);
    input_bind_key(config_current.short_map_shift_west, short_map_shift_west_entry_str, entry, input_none_str);
    input_bind_key(config_current.short_map_shift_east, short_map_shift_east_entry_str, entry, input_none_str);
    input_bind_key(config_current.short_map_shift_south, short_map_shift_south_entry_str, entry, input_none_str);
    input_bind_key(config_current.short_map_shift_north, short_map_shift_north_entry_str, entry, input_none_str);
}

void input_wait_for_binding(STRING *entry)
{
    is_popup_opened = false;
    imgui_close_current_popup();
    editor_switch_popup_to(EDITOR_POPUP_STATE_WAIT_FOR_INPUT);

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
            input_remove_bind_key(entry);
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
                input_bind_new_key(entry, bindkey);
                wait_for_input = false;
            }
        }

        wait(1);
    }

    is_popup_opened = false;

    wait(1);

    editor_switch_popup_to(editor_popup_previous_state);
}

void input_add_keybinding(STRING *entry, STRING *input)
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
        input_wait_for_binding(entry);
    }
    imgui_separator();
}

void shortcut_add_keybinding(STRING *entry, STRING *base_key, STRING *input)
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
        input_wait_for_binding(entry);
    }
    imgui_separator();
}