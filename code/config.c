
void config_initialize(STRING *config_file)
{
    // default input
    strcpy(config_default.input_forward, _chr(input_def_forward_str));
    strcpy(config_default.input_backward, _chr(input_def_backward_str));
    strcpy(config_default.input_strafe_left, _chr(input_def_strafe_left_str));
    strcpy(config_default.input_strafe_right, _chr(input_def_strafe_right_str));
    strcpy(config_default.input_interact, _chr(input_def_interact_str));
    strcpy(config_default.input_run, _chr(input_def_run_str));
    strcpy(config_default.input_drag_map, _chr(input_def_drag_map_str));
    strcpy(config_default.input_draw, _chr(input_def_draw_str));
    strcpy(config_default.input_erase, _chr(input_def_erase_str));
    strcpy(config_default.input_pick, _chr(input_def_pick_str));
    strcpy(config_default.input_rotate, _chr(input_def_rotate_str));

    // default shortcut
    strcpy(config_default.short_help, _chr(short_def_help_str));
    strcpy(config_default.short_new, _chr(short_def_new_str));
    strcpy(config_default.short_open, _chr(short_def_open_str));
    strcpy(config_default.short_save, _chr(short_def_save_str));
    strcpy(config_default.short_ep_reset, _chr(short_def_ep_reset_str));
    strcpy(config_default.short_ep_edit, _chr(short_def_ep_edit_str));
    strcpy(config_default.short_reset_map, _chr(short_def_reset_map_str));
    strcpy(config_default.short_test_run, _chr(short_def_test_run_str));
    strcpy(config_default.short_map_settings, _chr(short_def_map_settings_str));
    strcpy(config_default.short_screenshot, _chr(short_def_screenshot_str));
    strcpy(config_default.short_settings, _chr(short_def_settings_str));
    strcpy(config_default.short_toggle_debug, _chr(short_def_toggle_debug_str));
    strcpy(config_default.short_prior_map, _chr(short_def_prior_map_str));
    strcpy(config_default.short_next_map, _chr(short_def_next_map_str));
    strcpy(config_default.short_shift_map_west, _chr(short_def_shift_map_west_str));
    strcpy(config_default.short_shift_map_east, _chr(short_def_shift_map_east_str));
    strcpy(config_default.short_shift_map_south, _chr(short_def_shift_map_south_str));
    strcpy(config_default.short_shift_map_north, _chr(short_def_shift_map_north_str));

    // mouse
    config_default.mouse_sensitivity = mouse_def_sensitivity;

    // audio
    config_default.master_volume = master_def_volume;

    // others
    config_default.font_scale = font_def_scale;
    config_default.is_cell_tooltip_enabled = is_cell_tooltip_def_enabled;
    background_def_color[0] = get_hsv_from_color(152);
    background_def_color[1] = get_hsv_from_color(0);
    background_def_color[2] = get_hsv_from_color(136);
    grid_def_color[0] = get_hsv_from_color(128);
    grid_def_color[1] = get_hsv_from_color(128);
    grid_def_color[2] = get_hsv_from_color(128);

    int i = 0;
    for (i = 0; i < 3; i++)
    {
        config_default.background_color[i] = background_def_color[i];
        config_default.grid_color[i] = grid_def_color[i];
    }

    // graphics
    config_default.graphics_video_res_id = graphics_video_res_def_id;
    config_default.graphics_display_mode = graphics_display_def_mode;

    // load/write config
    config_load_from_file(config_file);
}

void config_save()
{
    // set proper path to the config file
    STRING *temp_str = "#256";
    str_cpy(temp_str, editor_config_file_str);
    path_make_absolute(temp_str);  // add 'save_dir' full path (in documents folder)
    config_save_to_file(temp_str); // save all settings back to the config file

    memcpy(&config_saved, &config_current, sizeof(CONFIG));
}

void config_apply()
{
    imgui_set_global_fontscale(config_current.font_scale);
    shortcuts_update_from_config(&config_current);
    tools_update_input_from_config(&config_current);
    camera_update_input_from_config(&config_current);
    // player_update_input_from_config(&config_current);
    engine_apply_video_settings();
}

void config_reset_to_default(var tab)
{
    if (tab == SETTINGS_TAB_INPUT)
    {
        // input
        strcpy(config_current.input_forward, config_default.input_forward);
        strcpy(config_current.input_backward, config_default.input_backward);
        strcpy(config_current.input_strafe_left, config_default.input_strafe_left);
        strcpy(config_current.input_strafe_right, config_default.input_strafe_right);
        strcpy(config_current.input_interact, config_default.input_interact);
        strcpy(config_current.input_run, config_default.input_run);
        strcpy(config_current.input_drag_map, config_default.input_drag_map);
        strcpy(config_current.input_draw, config_default.input_draw);
        strcpy(config_current.input_erase, config_default.input_erase);
        strcpy(config_current.input_pick, config_default.input_pick);
        strcpy(config_current.input_rotate, config_default.input_rotate);

        // shortcuts
        strcpy(config_current.short_help, config_default.short_help);
        strcpy(config_current.short_new, config_default.short_new);
        strcpy(config_current.short_open, config_default.short_open);
        strcpy(config_current.short_save, config_default.short_save);
        strcpy(config_current.short_ep_reset, config_default.short_ep_reset);
        strcpy(config_current.short_ep_edit, config_default.short_ep_edit);
        strcpy(config_current.short_reset_map, config_default.short_reset_map);
        strcpy(config_current.short_test_run, config_default.short_test_run);
        strcpy(config_current.short_map_settings, config_default.short_map_settings);
        strcpy(config_current.short_screenshot, config_default.short_screenshot);
        strcpy(config_current.short_settings, config_default.short_settings);
        strcpy(config_current.short_toggle_debug, config_default.short_toggle_debug);
        strcpy(config_current.short_prior_map, config_default.short_prior_map);
        strcpy(config_current.short_next_map, config_default.short_next_map);
        strcpy(config_current.short_shift_map_west, config_default.short_shift_map_west);
        strcpy(config_current.short_shift_map_east, config_default.short_shift_map_east);
        strcpy(config_current.short_shift_map_south, config_default.short_shift_map_south);
        strcpy(config_current.short_shift_map_north, config_default.short_shift_map_north);

        // mouse
        config_current.mouse_sensitivity = config_default.mouse_sensitivity;
    }
    else if (tab == SETTINGS_TAB_GENERIC)
    {
        // audio
        config_current.master_volume = config_default.master_volume;

        // other settings
        config_current.font_scale = config_default.font_scale;
        config_current.is_cell_tooltip_enabled = config_default.is_cell_tooltip_enabled;
        config_current.background_color[0] = config_default.background_color[0];
        config_current.background_color[1] = config_default.background_color[1];
        config_current.background_color[2] = config_default.background_color[2];
        config_current.grid_color[0] = config_default.grid_color[0];
        config_current.grid_color[1] = config_default.grid_color[1];
        config_current.grid_color[2] = config_default.grid_color[2];

        // graphics
        config_current.graphics_video_res_id = config_default.graphics_video_res_id;
        config_current.graphics_display_mode = config_default.graphics_display_mode;
    }
}

void config_reset_to_saved()
{
    // input
    strcpy(config_current.input_forward, config_saved.input_forward);
    strcpy(config_current.input_backward, config_saved.input_backward);
    strcpy(config_current.input_strafe_left, config_saved.input_strafe_left);
    strcpy(config_current.input_strafe_right, config_saved.input_strafe_right);
    strcpy(config_current.input_interact, config_saved.input_interact);
    strcpy(config_current.input_run, config_saved.input_run);
    strcpy(config_current.input_drag_map, config_saved.input_drag_map);
    strcpy(config_current.input_draw, config_saved.input_draw);
    strcpy(config_current.input_erase, config_saved.input_erase);
    strcpy(config_current.input_pick, config_saved.input_pick);
    strcpy(config_current.input_rotate, config_saved.input_rotate);

    // shortcuts
    strcpy(config_current.short_help, config_saved.short_help);
    strcpy(config_current.short_new, config_saved.short_new);
    strcpy(config_current.short_open, config_saved.short_open);
    strcpy(config_current.short_save, config_saved.short_save);
    strcpy(config_current.short_ep_reset, config_saved.short_ep_reset);
    strcpy(config_current.short_ep_edit, config_saved.short_ep_edit);
    strcpy(config_current.short_reset_map, config_saved.short_reset_map);
    strcpy(config_current.short_test_run, config_saved.short_test_run);
    strcpy(config_current.short_map_settings, config_saved.short_map_settings);
    strcpy(config_current.short_screenshot, config_saved.short_screenshot);
    strcpy(config_current.short_settings, config_saved.short_settings);
    strcpy(config_current.short_toggle_debug, config_saved.short_toggle_debug);
    strcpy(config_current.short_prior_map, config_saved.short_prior_map);
    strcpy(config_current.short_next_map, config_saved.short_next_map);
    strcpy(config_current.short_shift_map_west, config_saved.short_shift_map_west);
    strcpy(config_current.short_shift_map_east, config_saved.short_shift_map_east);
    strcpy(config_current.short_shift_map_south, config_saved.short_shift_map_south);
    strcpy(config_current.short_shift_map_north, config_saved.short_shift_map_north);

    // mouse
    config_current.mouse_sensitivity = config_saved.mouse_sensitivity;

    // audio
    config_current.master_volume = config_saved.master_volume;

    // other settings
    config_current.font_scale = config_saved.font_scale;
    config_current.is_cell_tooltip_enabled = config_saved.is_cell_tooltip_enabled;
    config_current.background_color[0] = config_saved.background_color[0];
    config_current.background_color[1] = config_saved.background_color[1];
    config_current.background_color[2] = config_saved.background_color[2];
    config_current.grid_color[0] = config_saved.grid_color[0];
    config_current.grid_color[1] = config_saved.grid_color[1];
    config_current.grid_color[2] = config_saved.grid_color[2];

    // graphics
    config_current.graphics_video_res_id = config_saved.graphics_video_res_id;
    config_current.graphics_display_mode = config_saved.graphics_display_mode;
}

void config_load_from_file(STRING *config_file)
{
    // input
    ini_read_write_char(config_current.input_forward, config_file, config_input_section_str, input_forward_entry_str, config_default.input_forward);
    ini_read_write_char(config_current.input_backward, config_file, config_input_section_str, input_backward_entry_str, config_default.input_backward);
    ini_read_write_char(config_current.input_strafe_left, config_file, config_input_section_str, input_strafe_left_entry_str, config_default.input_strafe_left);
    ini_read_write_char(config_current.input_strafe_right, config_file, config_input_section_str, input_strafe_right_entry_str, config_default.input_strafe_right);
    ini_read_write_char(config_current.input_interact, config_file, config_input_section_str, input_interact_entry_str, config_default.input_interact);
    ini_read_write_char(config_current.input_run, config_file, config_input_section_str, input_run_entry_str, config_default.input_run);
    ini_read_write_char(config_current.input_drag_map, config_file, config_input_section_str, input_drag_map_entry_str, config_default.input_drag_map);
    ini_read_write_char(config_current.input_draw, config_file, config_input_section_str, input_draw_entry_str, config_default.input_draw);
    ini_read_write_char(config_current.input_erase, config_file, config_input_section_str, input_erase_entry_str, config_default.input_erase);
    ini_read_write_char(config_current.input_pick, config_file, config_input_section_str, input_pick_entry_str, config_default.input_pick);
    ini_read_write_char(config_current.input_rotate, config_file, config_input_section_str, input_rotate_entry_str, config_default.input_rotate);

    // shortcuts
    ini_read_write_char(config_current.short_help, config_file, config_shortcuts_section_str, short_help_entry_str, config_default.short_help);
    ini_read_write_char(config_current.short_new, config_file, config_shortcuts_section_str, short_new_entry_str, config_default.short_new);
    ini_read_write_char(config_current.short_open, config_file, config_shortcuts_section_str, short_open_entry_str, config_default.short_open);
    ini_read_write_char(config_current.short_save, config_file, config_shortcuts_section_str, short_save_entry_str, config_default.short_save);
    ini_read_write_char(config_current.short_ep_reset, config_file, config_shortcuts_section_str, short_ep_reset_entry_str, config_default.short_ep_reset);
    ini_read_write_char(config_current.short_ep_edit, config_file, config_shortcuts_section_str, short_ep_edit_entry_str, config_default.short_ep_edit);
    ini_read_write_char(config_current.short_reset_map, config_file, config_shortcuts_section_str, short_reset_map_entry_str, config_default.short_reset_map);
    ini_read_write_char(config_current.short_test_run, config_file, config_shortcuts_section_str, short_test_run_entry_str, config_default.short_test_run);
    ini_read_write_char(config_current.short_map_settings, config_file, config_shortcuts_section_str, short_map_settings_entry_str, config_default.short_map_settings);
    ini_read_write_char(config_current.short_screenshot, config_file, config_shortcuts_section_str, short_screenshot_entry_str, config_default.short_screenshot);
    ini_read_write_char(config_current.short_settings, config_file, config_shortcuts_section_str, short_settings_entry_str, config_default.short_settings);
    ini_read_write_char(config_current.short_toggle_debug, config_file, config_shortcuts_section_str, short_toggle_debug_entry_str, config_default.short_toggle_debug);
    ini_read_write_char(config_current.short_prior_map, config_file, config_shortcuts_section_str, short_prior_map_entry_str, config_default.short_prior_map);
    ini_read_write_char(config_current.short_next_map, config_file, config_shortcuts_section_str, short_next_map_entry_str, config_default.short_next_map);
    ini_read_write_char(config_current.short_shift_map_west, config_file, config_shortcuts_section_str, short_shift_map_west_entry_str, config_default.short_shift_map_west);
    ini_read_write_char(config_current.short_shift_map_east, config_file, config_shortcuts_section_str, short_shift_map_east_entry_str, config_default.short_shift_map_east);
    ini_read_write_char(config_current.short_shift_map_south, config_file, config_shortcuts_section_str, short_shift_map_south_entry_str, config_default.short_shift_map_south);
    ini_read_write_char(config_current.short_shift_map_north, config_file, config_shortcuts_section_str, short_shift_map_north_entry_str, config_default.short_shift_map_north);

    // mouse
    ini_read_write_float(&config_current.mouse_sensitivity, config_file, config_input_section_str, mouse_sensitivity_entry_str, config_default.mouse_sensitivity);

    // audio
    ini_read_write_float(&config_current.master_volume, config_file, config_other_section_str, other_master_volume_entry_str, config_default.master_volume);

    // other settings
    ini_read_write_float(&config_current.font_scale, config_file, config_other_section_str, other_font_scale_entry_str, config_default.font_scale);
    ini_read_write_int(&config_current.is_cell_tooltip_enabled, config_file, config_other_section_str, other_cell_tooltip_entry_str, config_default.is_cell_tooltip_enabled);
    ini_read_write_float(&config_current.background_color[0], config_file, config_other_section_str, other_background_color_red_entry_str, config_default.background_color[0]);
    ini_read_write_float(&config_current.background_color[1], config_file, config_other_section_str, other_background_color_green_entry_str, config_default.background_color[1]);
    ini_read_write_float(&config_current.background_color[2], config_file, config_other_section_str, other_background_color_blue_entry_str, config_default.background_color[2]);
    ini_read_write_float(&config_current.grid_color[0], config_file, config_other_section_str, other_grid_color_red_entry_str, config_default.grid_color[0]);
    ini_read_write_float(&config_current.grid_color[1], config_file, config_other_section_str, other_grid_color_green_entry_str, config_default.grid_color[1]);
    ini_read_write_float(&config_current.grid_color[2], config_file, config_other_section_str, other_grid_color_blue_entry_str, config_default.grid_color[2]);

    // graphics
    ini_read_write_int(&config_current.graphics_video_res_id, config_file, config_graphics_section_str, graphics_video_res_id_entry_str, config_default.graphics_video_res_id);
    ini_read_write_int(&config_current.graphics_display_mode, config_file, config_graphics_section_str, graphics_display_mode_entry_str, config_default.graphics_display_mode);

    config_save();
    config_apply();
}

void config_save_to_file(STRING *config_file)
{
    // input
    ini_write(config_file, config_input_section_str, input_forward_entry_str, config_current.input_forward);
    ini_write(config_file, config_input_section_str, input_backward_entry_str, config_current.input_backward);
    ini_write(config_file, config_input_section_str, input_strafe_left_entry_str, config_current.input_strafe_left);
    ini_write(config_file, config_input_section_str, input_strafe_right_entry_str, config_current.input_strafe_right);
    ini_write(config_file, config_input_section_str, input_interact_entry_str, config_current.input_interact);
    ini_write(config_file, config_input_section_str, input_run_entry_str, config_current.input_run);
    ini_write(config_file, config_input_section_str, input_drag_map_entry_str, config_current.input_drag_map);
    ini_write(config_file, config_input_section_str, input_draw_entry_str, config_current.input_draw);
    ini_write(config_file, config_input_section_str, input_erase_entry_str, config_current.input_erase);
    ini_write(config_file, config_input_section_str, input_pick_entry_str, config_current.input_pick);
    ini_write(config_file, config_input_section_str, input_rotate_entry_str, config_current.input_rotate);

    // shortcut
    ini_write(config_file, config_shortcuts_section_str, short_help_entry_str, config_current.short_help);
    ini_write(config_file, config_shortcuts_section_str, short_new_entry_str, config_current.short_new);
    ini_write(config_file, config_shortcuts_section_str, short_open_entry_str, config_current.short_open);
    ini_write(config_file, config_shortcuts_section_str, short_save_entry_str, config_current.short_save);
    ini_write(config_file, config_shortcuts_section_str, short_ep_reset_entry_str, config_current.short_ep_reset);
    ini_write(config_file, config_shortcuts_section_str, short_ep_edit_entry_str, config_current.short_ep_edit);
    ini_write(config_file, config_shortcuts_section_str, short_reset_map_entry_str, config_current.short_reset_map);
    ini_write(config_file, config_shortcuts_section_str, short_test_run_entry_str, config_current.short_test_run);
    ini_write(config_file, config_shortcuts_section_str, short_map_settings_entry_str, config_current.short_map_settings);
    ini_write(config_file, config_shortcuts_section_str, short_screenshot_entry_str, config_current.short_screenshot);
    ini_write(config_file, config_shortcuts_section_str, short_settings_entry_str, config_current.short_settings);
    ini_write(config_file, config_shortcuts_section_str, short_prior_map_entry_str, config_current.short_prior_map);
    ini_write(config_file, config_shortcuts_section_str, short_next_map_entry_str, config_current.short_next_map);
    ini_write(config_file, config_shortcuts_section_str, short_toggle_debug_entry_str, config_current.short_toggle_debug);
    ini_write(config_file, config_shortcuts_section_str, short_shift_map_west_entry_str, config_current.short_shift_map_west);
    ini_write(config_file, config_shortcuts_section_str, short_shift_map_east_entry_str, config_current.short_shift_map_east);
    ini_write(config_file, config_shortcuts_section_str, short_shift_map_south_entry_str, config_current.short_shift_map_south);
    ini_write(config_file, config_shortcuts_section_str, short_shift_map_north_entry_str, config_current.short_shift_map_north);

    // mouse
    ini_write_float(config_file, config_input_section_str, mouse_sensitivity_entry_str, config_current.mouse_sensitivity);

    // audio
    ini_write_float(config_file, config_other_section_str, other_master_volume_entry_str, config_current.master_volume);

    // other settings
    ini_write_float(config_file, config_other_section_str, other_font_scale_entry_str, config_current.font_scale);
    ini_write_int(config_file, config_other_section_str, other_cell_tooltip_entry_str, config_current.is_cell_tooltip_enabled);
    ini_write_float(config_file, config_other_section_str, other_background_color_red_entry_str, config_current.background_color[0]);
    ini_write_float(config_file, config_other_section_str, other_background_color_green_entry_str, config_current.background_color[1]);
    ini_write_float(config_file, config_other_section_str, other_background_color_blue_entry_str, config_current.background_color[2]);
    ini_write_float(config_file, config_other_section_str, other_grid_color_red_entry_str, config_current.grid_color[0]);
    ini_write_float(config_file, config_other_section_str, other_grid_color_green_entry_str, config_current.grid_color[1]);
    ini_write_float(config_file, config_other_section_str, other_grid_color_blue_entry_str, config_current.grid_color[2]);

    // graphics
    ini_write_int(config_file, config_graphics_section_str, graphics_video_res_id_entry_str, config_current.graphics_video_res_id);
    ini_write_int(config_file, config_graphics_section_str, graphics_display_mode_entry_str, config_current.graphics_display_mode);
}