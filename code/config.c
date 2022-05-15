
void config_initialize(STRING *config_file)
{
    // default input
    strcpy(config_default.input_forward, _chr(input_def_forward_str));
    strcpy(config_default.input_backward, _chr(input_def_backward_str));
    strcpy(config_default.input_strafe_left, _chr(input_def_strafe_left_str));
    strcpy(config_default.input_strafe_right, _chr(input_def_strafe_right_str));
    strcpy(config_default.input_fly_up, _chr(input_def_fly_up_str));
    strcpy(config_default.input_fly_down, _chr(input_def_fly_down_str));
    strcpy(config_default.input_run, _chr(input_def_run_str));
    strcpy(config_default.input_rotate_camera, _chr(input_def_rotate_camera_str));
    strcpy(config_default.input_draw, _chr(input_def_draw_str));
    strcpy(config_default.input_erase, _chr(input_def_erase_str));
    strcpy(config_default.input_pick, _chr(input_def_pick_str));
    strcpy(config_default.input_rotate, _chr(input_def_rotate_str));
    strcpy(config_default.input_toggle_assets, _chr(input_def_toggle_assets_str));
    strcpy(config_default.input_toggle_lights, _chr(input_def_toggle_lights_str));
    strcpy(config_default.input_toggle_draw_mode, _chr(input_def_toggle_draw_mode_str));

    // default shortcut
    strcpy(config_default.short_help, _chr(short_def_help_str));
    strcpy(config_default.short_screenshot, _chr(short_def_screenshot_str));
    strcpy(config_default.short_new, _chr(short_def_new_str));
    strcpy(config_default.short_open, _chr(short_def_open_str));
    strcpy(config_default.short_settings, _chr(short_def_settings_str));
    strcpy(config_default.short_save, _chr(short_def_save_str));
    strcpy(config_default.short_ep_reset, _chr(short_def_ep_reset_str));
    strcpy(config_default.short_ep_edit, _chr(short_def_ep_edit_str));
    strcpy(config_default.short_map_reset, _chr(short_def_map_reset_str));
    strcpy(config_default.short_map_settings, _chr(short_def_map_settings_str));
    strcpy(config_default.short_toggle_debug, _chr(short_def_toggle_hovering_str));
    strcpy(config_default.short_toggle_hovering, _chr(short_def_toggle_debug_str));
    strcpy(config_default.short_map_prior, _chr(short_def_map_prior_str));
    strcpy(config_default.short_map_next, _chr(short_def_map_next_str));
    strcpy(config_default.short_map_shift_west, _chr(short_def_map_shift_west_str));
    strcpy(config_default.short_map_shift_east, _chr(short_def_map_shift_east_str));
    strcpy(config_default.short_map_shift_south, _chr(short_def_map_shift_south_str));
    strcpy(config_default.short_map_shift_north, _chr(short_def_map_shift_north_str));

    // mouse
    config_default.mouse_sensitivity = mouse_def_sensitivity;

    // audio
    config_default.master_volume = master_def_volume;

    // others
    config_default.font_scale = font_def_scale;
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

    memcpy(&config_saved, &config_current, sizeof(Config));
}

void config_apply()
{
    camera_load_config(&config_current);
    editor_load_config(&config_current);
    shortcuts_load_config(&config_current);
    map_draw_load_config(&config_current);

    imgui_set_global_fontscale(config_current.font_scale);
    draw_textmode("Courier", 1, 12 * config_saved.font_scale, 100);
    master_vol = config_saved.master_volume;

    engine_apply_video_settings();
}

void config_reset_to_default(int tab)
{
    if (tab == SETTINGS_TAB_INPUT)
    {
        // input
        strcpy(config_current.input_forward, config_default.input_forward);
        strcpy(config_current.input_backward, config_default.input_backward);
        strcpy(config_current.input_strafe_left, config_default.input_strafe_left);
        strcpy(config_current.input_strafe_right, config_default.input_strafe_right);
        strcpy(config_current.input_fly_up, config_default.input_fly_up);
        strcpy(config_current.input_fly_down, config_default.input_fly_down);
        strcpy(config_current.input_run, config_default.input_run);
        strcpy(config_current.input_rotate_camera, config_default.input_rotate_camera);
        strcpy(config_current.input_draw, config_default.input_draw);
        strcpy(config_current.input_erase, config_default.input_erase);
        strcpy(config_current.input_pick, config_default.input_pick);
        strcpy(config_current.input_rotate, config_default.input_rotate);
        strcpy(config_current.input_toggle_assets, config_default.input_toggle_assets);
        strcpy(config_current.input_toggle_lights, config_default.input_toggle_lights);
        strcpy(config_current.input_toggle_draw_mode, config_default.input_toggle_draw_mode);

        // shortcuts
        strcpy(config_current.short_help, config_default.short_help);
        strcpy(config_current.short_screenshot, config_default.short_screenshot);
        strcpy(config_current.short_new, config_default.short_new);
        strcpy(config_current.short_open, config_default.short_open);
        strcpy(config_current.short_settings, config_default.short_settings);
        strcpy(config_current.short_save, config_default.short_save);
        strcpy(config_current.short_ep_reset, config_default.short_ep_reset);
        strcpy(config_current.short_ep_edit, config_default.short_ep_edit);
        strcpy(config_current.short_map_reset, config_default.short_map_reset);
        strcpy(config_current.short_map_settings, config_default.short_map_settings);
        strcpy(config_current.short_toggle_debug, config_default.short_toggle_debug);
        strcpy(config_current.short_toggle_hovering, config_default.short_toggle_hovering);
        strcpy(config_current.short_map_prior, config_default.short_map_prior);
        strcpy(config_current.short_map_next, config_default.short_map_next);
        strcpy(config_current.short_map_shift_west, config_default.short_map_shift_west);
        strcpy(config_current.short_map_shift_east, config_default.short_map_shift_east);
        strcpy(config_current.short_map_shift_south, config_default.short_map_shift_south);
        strcpy(config_current.short_map_shift_north, config_default.short_map_shift_north);

        // mouse
        config_current.mouse_sensitivity = config_default.mouse_sensitivity;
    }
    else if (tab == SETTINGS_TAB_GENERIC)
    {
        // audio
        config_current.master_volume = config_default.master_volume;

        // other settings
        config_current.font_scale = config_default.font_scale;
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
    strcpy(config_current.input_fly_up, config_saved.input_fly_up);
    strcpy(config_current.input_fly_down, config_saved.input_fly_down);
    strcpy(config_current.input_run, config_saved.input_run);
    strcpy(config_current.input_rotate_camera, config_saved.input_rotate_camera);
    strcpy(config_current.input_draw, config_saved.input_draw);
    strcpy(config_current.input_erase, config_saved.input_erase);
    strcpy(config_current.input_pick, config_saved.input_pick);
    strcpy(config_current.input_rotate, config_saved.input_rotate);
    strcpy(config_current.input_toggle_assets, config_saved.input_toggle_assets);
    strcpy(config_current.input_toggle_lights, config_saved.input_toggle_lights);
    strcpy(config_current.input_toggle_draw_mode, config_saved.input_toggle_draw_mode);

    // shortcuts
    strcpy(config_current.short_help, config_saved.short_help);
    strcpy(config_current.short_screenshot, config_saved.short_screenshot);
    strcpy(config_current.short_new, config_saved.short_new);
    strcpy(config_current.short_open, config_saved.short_open);
    strcpy(config_current.short_settings, config_saved.short_settings);
    strcpy(config_current.short_save, config_saved.short_save);
    strcpy(config_current.short_ep_reset, config_saved.short_ep_reset);
    strcpy(config_current.short_ep_edit, config_saved.short_ep_edit);
    strcpy(config_current.short_map_reset, config_saved.short_map_reset);
    strcpy(config_current.short_map_settings, config_saved.short_map_settings);
    strcpy(config_current.short_toggle_debug, config_saved.short_toggle_debug);
    strcpy(config_current.short_toggle_hovering, config_saved.short_toggle_hovering);
    strcpy(config_current.short_map_prior, config_saved.short_map_prior);
    strcpy(config_current.short_map_next, config_saved.short_map_next);
    strcpy(config_current.short_map_shift_west, config_saved.short_map_shift_west);
    strcpy(config_current.short_map_shift_east, config_saved.short_map_shift_east);
    strcpy(config_current.short_map_shift_south, config_saved.short_map_shift_south);
    strcpy(config_current.short_map_shift_north, config_saved.short_map_shift_north);

    // mouse
    config_current.mouse_sensitivity = config_saved.mouse_sensitivity;

    // audio
    config_current.master_volume = config_saved.master_volume;

    // other settings
    config_current.font_scale = config_saved.font_scale;
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
    ini_read_write_char(config_current.input_fly_up, config_file, config_input_section_str, input_fly_up_entry_str, config_default.input_fly_up);
    ini_read_write_char(config_current.input_fly_down, config_file, config_input_section_str, input_fly_down_entry_str, config_default.input_fly_down);
    ini_read_write_char(config_current.input_run, config_file, config_input_section_str, input_run_entry_str, config_default.input_run);
    ini_read_write_char(config_current.input_rotate_camera, config_file, config_input_section_str, input_rotate_cam_entry_str, config_default.input_rotate_camera);
    ini_read_write_char(config_current.input_draw, config_file, config_input_section_str, input_draw_entry_str, config_default.input_draw);
    ini_read_write_char(config_current.input_erase, config_file, config_input_section_str, input_erase_entry_str, config_default.input_erase);
    ini_read_write_char(config_current.input_pick, config_file, config_input_section_str, input_pick_entry_str, config_default.input_pick);
    ini_read_write_char(config_current.input_rotate, config_file, config_input_section_str, input_rotate_entry_str, config_default.input_rotate);
    ini_read_write_char(config_current.input_toggle_assets, config_file, config_input_section_str, input_toggle_assets_entry_str, config_default.input_toggle_assets);
    ini_read_write_char(config_current.input_toggle_lights, config_file, config_input_section_str, input_toggle_lights_entry_str, config_default.input_toggle_lights);
    ini_read_write_char(config_current.input_toggle_draw_mode, config_file, config_input_section_str, input_toggle_draw_mode_entry_str, config_default.input_toggle_draw_mode);

    // shortcuts
    ini_read_write_char(config_current.short_help, config_file, config_shortcuts_section_str, short_help_entry_str, config_default.short_help);
    ini_read_write_char(config_current.short_screenshot, config_file, config_shortcuts_section_str, short_screenshot_entry_str, config_default.short_screenshot);
    ini_read_write_char(config_current.short_new, config_file, config_shortcuts_section_str, short_new_entry_str, config_default.short_new);
    ini_read_write_char(config_current.short_open, config_file, config_shortcuts_section_str, short_open_entry_str, config_default.short_open);
    ini_read_write_char(config_current.short_settings, config_file, config_shortcuts_section_str, short_settings_entry_str, config_default.short_settings);
    ini_read_write_char(config_current.short_save, config_file, config_shortcuts_section_str, short_save_entry_str, config_default.short_save);
    ini_read_write_char(config_current.short_ep_reset, config_file, config_shortcuts_section_str, short_ep_reset_entry_str, config_default.short_ep_reset);
    ini_read_write_char(config_current.short_ep_edit, config_file, config_shortcuts_section_str, short_ep_edit_entry_str, config_default.short_ep_edit);
    ini_read_write_char(config_current.short_map_reset, config_file, config_shortcuts_section_str, short_map_reset_entry_str, config_default.short_map_reset);
    ini_read_write_char(config_current.short_map_settings, config_file, config_shortcuts_section_str, short_map_settings_entry_str, config_default.short_map_settings);
    ini_read_write_char(config_current.short_toggle_debug, config_file, config_shortcuts_section_str, short_toggle_hovering_entry_str, config_default.short_toggle_debug);
    ini_read_write_char(config_current.short_toggle_hovering, config_file, config_shortcuts_section_str, short_toggle_debug_entry_str, config_default.short_toggle_hovering);
    ini_read_write_char(config_current.short_map_prior, config_file, config_shortcuts_section_str, short_map_prior_entry_str, config_default.short_map_prior);
    ini_read_write_char(config_current.short_map_next, config_file, config_shortcuts_section_str, short_map_next_entry_str, config_default.short_map_next);
    ini_read_write_char(config_current.short_map_shift_west, config_file, config_shortcuts_section_str, short_map_shift_west_entry_str, config_default.short_map_shift_west);
    ini_read_write_char(config_current.short_map_shift_east, config_file, config_shortcuts_section_str, short_map_shift_east_entry_str, config_default.short_map_shift_east);
    ini_read_write_char(config_current.short_map_shift_south, config_file, config_shortcuts_section_str, short_map_shift_south_entry_str, config_default.short_map_shift_south);
    ini_read_write_char(config_current.short_map_shift_north, config_file, config_shortcuts_section_str, short_map_shift_north_entry_str, config_default.short_map_shift_north);

    // mouse
    ini_read_write_float(&config_current.mouse_sensitivity, config_file, config_input_section_str, mouse_sensitivity_entry_str, config_default.mouse_sensitivity);

    // audio
    ini_read_write_float(&config_current.master_volume, config_file, config_other_section_str, other_master_volume_entry_str, config_default.master_volume);

    // other settings
    ini_read_write_float(&config_current.font_scale, config_file, config_other_section_str, other_font_scale_entry_str, config_default.font_scale);
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
    ini_write(config_file, config_input_section_str, input_fly_up_entry_str, config_current.input_fly_up);
    ini_write(config_file, config_input_section_str, input_fly_down_entry_str, config_current.input_fly_down);
    ini_write(config_file, config_input_section_str, input_run_entry_str, config_current.input_run);
    ini_write(config_file, config_input_section_str, input_rotate_cam_entry_str, config_current.input_rotate_camera);
    ini_write(config_file, config_input_section_str, input_draw_entry_str, config_current.input_draw);
    ini_write(config_file, config_input_section_str, input_erase_entry_str, config_current.input_erase);
    ini_write(config_file, config_input_section_str, input_pick_entry_str, config_current.input_pick);
    ini_write(config_file, config_input_section_str, input_rotate_entry_str, config_current.input_rotate);
    ini_write(config_file, config_input_section_str, input_toggle_assets_entry_str, config_current.input_toggle_assets);
    ini_write(config_file, config_input_section_str, input_toggle_lights_entry_str, config_current.input_toggle_lights);
    ini_write(config_file, config_input_section_str, input_toggle_draw_mode_entry_str, config_current.input_toggle_draw_mode);

    // shortcut
    ini_write(config_file, config_shortcuts_section_str, short_help_entry_str, config_current.short_help);
    ini_write(config_file, config_shortcuts_section_str, short_screenshot_entry_str, config_current.short_screenshot);
    ini_write(config_file, config_shortcuts_section_str, short_new_entry_str, config_current.short_new);
    ini_write(config_file, config_shortcuts_section_str, short_open_entry_str, config_current.short_open);
    ini_write(config_file, config_shortcuts_section_str, short_settings_entry_str, config_current.short_settings);
    ini_write(config_file, config_shortcuts_section_str, short_save_entry_str, config_current.short_save);
    ini_write(config_file, config_shortcuts_section_str, short_ep_reset_entry_str, config_current.short_ep_reset);
    ini_write(config_file, config_shortcuts_section_str, short_ep_edit_entry_str, config_current.short_ep_edit);
    ini_write(config_file, config_shortcuts_section_str, short_map_reset_entry_str, config_current.short_map_reset);
    ini_write(config_file, config_shortcuts_section_str, short_map_settings_entry_str, config_current.short_map_settings);
    ini_write(config_file, config_shortcuts_section_str, short_toggle_hovering_entry_str, config_current.short_toggle_debug);
    ini_write(config_file, config_shortcuts_section_str, short_toggle_debug_entry_str, config_current.short_toggle_hovering);
    ini_write(config_file, config_shortcuts_section_str, short_map_prior_entry_str, config_current.short_map_prior);
    ini_write(config_file, config_shortcuts_section_str, short_map_next_entry_str, config_current.short_map_next);
    ini_write(config_file, config_shortcuts_section_str, short_map_shift_west_entry_str, config_current.short_map_shift_west);
    ini_write(config_file, config_shortcuts_section_str, short_map_shift_east_entry_str, config_current.short_map_shift_east);
    ini_write(config_file, config_shortcuts_section_str, short_map_shift_south_entry_str, config_current.short_map_shift_south);
    ini_write(config_file, config_shortcuts_section_str, short_map_shift_north_entry_str, config_current.short_map_shift_north);

    // mouse
    ini_write_float(config_file, config_input_section_str, mouse_sensitivity_entry_str, config_current.mouse_sensitivity);

    // audio
    ini_write_float(config_file, config_other_section_str, other_master_volume_entry_str, config_current.master_volume);

    // other settings
    ini_write_float(config_file, config_other_section_str, other_font_scale_entry_str, config_current.font_scale);
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