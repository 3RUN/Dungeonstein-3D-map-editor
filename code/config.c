
// initialize config into the given file
void config_initialize(STRING *config_file)
{
    config_default.graphics_video_res_id = graphics_video_res_def_id;
    config_default.graphics_display_mode = graphics_display_def_mode;

    config_default.is_cell_tooltip_enabled = is_cell_tooltip_def_enabled;

    // load/write config
    config_load_from_file(config_file);
}

// save and apply config
void config_save_n_apply()
{
    memcpy(&config_saved, &config_current, sizeof(CONFIG));

    // set proper path to the config file
    STRING *temp_str = "#256";
    str_cpy(temp_str, config_file_str);
    path_make_absolute(temp_str);  // add 'save_dir' full path (in documents folder)
    config_save_to_file(temp_str); // save all settings back to the config file

    engine_apply_settings();
}

// reset config to defaults
void config_reset_to_default()
{
    config_current.graphics_video_res_id = config_default.graphics_video_res_id;
    config_current.graphics_display_mode = config_default.graphics_display_mode;

    config_current.is_cell_tooltip_enabled = config_default.is_cell_tooltip_enabled;
}

// reset config to saved
void config_reset_to_saved()
{
    config_current.graphics_video_res_id = config_saved.graphics_video_res_id;
    config_current.graphics_display_mode = config_saved.graphics_display_mode;

    config_current.is_cell_tooltip_enabled = config_saved.is_cell_tooltip_enabled;
}

// load config from the file
void config_load_from_file(STRING *config_file)
{
    ini_read_write_int(&config_current.graphics_video_res_id, config_file, config_graphics_section_str, graphics_video_res_id_entry_str, config_default.graphics_video_res_id);
    ini_read_write_int(&config_current.graphics_display_mode, config_file, config_graphics_section_str, graphics_display_mode_entry_str, config_default.graphics_display_mode);

    ini_read_write_int(&config_current.is_cell_tooltip_enabled, config_file, config_other_section_str, other_cell_tooltip_str, config_default.is_cell_tooltip_enabled);

    memcpy(&config_saved, &config_current, sizeof(CONFIG));
}

// save config into the given file
void config_save_to_file(STRING *config_file)
{
    ini_write_int(config_file, config_graphics_section_str, graphics_video_res_id_entry_str, config_current.graphics_video_res_id);
    ini_write_int(config_file, config_graphics_section_str, graphics_display_mode_entry_str, config_current.graphics_display_mode);

    ini_write_int(config_file, config_other_section_str, other_cell_tooltip_str, config_current.is_cell_tooltip_enabled);
}