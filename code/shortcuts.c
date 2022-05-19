
int is_shortcut_allowed()
{
    if (is_popup_opened == true)
    {
        return false;
    }

    if (editor_state != EDITOR_STATE_EDIT)
    {
        return false;
    }

    return true;
}

void shortcuts_load_config(Config *config)
{
    input_remove_on_key_binding(scancode_help);
    input_remove_on_key_binding(scancode_screenshot);
    input_remove_on_key_binding(scancode_new);
    input_remove_on_key_binding(scancode_open);
    input_remove_on_key_binding(scancode_settings);
    input_remove_on_key_binding(scancode_save);
    input_remove_on_key_binding(scancode_ep_reset);
    input_remove_on_key_binding(scancode_ep_edit);
    input_remove_on_key_binding(scancode_map_reset);
    input_remove_on_key_binding(scancode_map_settings);
    input_remove_on_key_binding(scancode_toggle_hovering_info);
    input_remove_on_key_binding(scancode_toggle_debug_panel);
    input_remove_on_key_binding(scancode_map_prior);
    input_remove_on_key_binding(scancode_map_next);
    input_remove_on_key_binding(scancode_map_shift_west);
    input_remove_on_key_binding(scancode_map_shift_east);
    input_remove_on_key_binding(scancode_map_shift_south);
    input_remove_on_key_binding(scancode_map_shift_north);

    scancode_help = engine_key_return_scancode_from_letter(config->short_help);
    scancode_screenshot = engine_key_return_scancode_from_letter(config->short_screenshot);
    scancode_new = engine_key_return_scancode_from_letter(config->short_new);
    scancode_open = engine_key_return_scancode_from_letter(config->short_open);
    scancode_settings = engine_key_return_scancode_from_letter(config->short_settings);
    scancode_save = engine_key_return_scancode_from_letter(config->short_save);
    scancode_ep_reset = engine_key_return_scancode_from_letter(config->short_ep_reset);
    scancode_ep_edit = engine_key_return_scancode_from_letter(config->short_ep_edit);
    scancode_map_reset = engine_key_return_scancode_from_letter(config->short_map_reset);
    scancode_map_settings = engine_key_return_scancode_from_letter(config->short_map_settings);
    scancode_toggle_hovering_info = engine_key_return_scancode_from_letter(config->short_toggle_debug);
    scancode_toggle_debug_panel = engine_key_return_scancode_from_letter(config->short_toggle_hovering);
    scancode_map_prior = engine_key_return_scancode_from_letter(config->short_map_prior);
    scancode_map_next = engine_key_return_scancode_from_letter(config->short_map_next);
    scancode_map_shift_west = engine_key_return_scancode_from_letter(config->short_map_shift_west);
    scancode_map_shift_east = engine_key_return_scancode_from_letter(config->short_map_shift_east);
    scancode_map_shift_south = engine_key_return_scancode_from_letter(config->short_map_shift_south);
    scancode_map_shift_north = engine_key_return_scancode_from_letter(config->short_map_shift_north);

    input_update_on_key_binding(scancode_help, shortcut_help);
    input_update_on_key_binding(scancode_screenshot, shortcut_screenshot);
    input_update_on_key_binding(scancode_new, shortcut_new);
    input_update_on_key_binding(scancode_open, shortcut_open);
    input_update_on_key_binding(scancode_settings, shortcut_settings);
    input_update_on_key_binding(scancode_save, shortcut_save);
    input_update_on_key_binding(scancode_ep_reset, shortcut_ep_reset);
    input_update_on_key_binding(scancode_ep_edit, shortcut_ep_edit);
    input_update_on_key_binding(scancode_map_reset, shortcut_map_reset);
    input_update_on_key_binding(scancode_map_settings, shortcut_map_settings);
    input_update_on_key_binding(scancode_toggle_hovering_info, shortcut_toggle_hovering_info);
    input_update_on_key_binding(scancode_toggle_debug_panel, shortcut_toggle_debug_panel);
    input_update_on_key_binding(scancode_map_prior, shortcut_map_prior);
    input_update_on_key_binding(scancode_map_next, shortcut_map_next);
    input_update_on_key_binding(scancode_map_shift_west, shortcut_map_shift_west);
    input_update_on_key_binding(scancode_map_shift_east, shortcut_map_shift_east);
    input_update_on_key_binding(scancode_map_shift_south, shortcut_map_shift_south);
    input_update_on_key_binding(scancode_map_shift_north, shortcut_map_shift_north);
}

void shortcut_help()
{
    if (is_popup_opened == true)
    {
        return false;
    }

    editor_switch_popup_to(EDITOR_POPUP_STATE_HELP);
}

void shortcut_screenshot()
{
    STRING *screenshot_str = "";
    str_printf(screenshot_str, "shot_%d_%d_%d_", (long)sys_day, (long)sys_month, (long)sys_year);

    STRING *temp_message_str = "";
    str_cpy(temp_message_str, screenshot_str);
    str_cat(temp_message_str, str_for_num(NULL, screenshot_num));
    str_cat(temp_message_str, " was saved.");
    message_add(temp_message_str);

    file_for_screen(screenshot_str, screenshot_num);
    screenshot_num++;
}

void shortcut_new()
{
    if (is_popup_opened == true)
    {
        return;
    }

    if (editor_state == EDITOR_STATE_START)
    {
        editor_switch_popup_to(EDITOR_POPUP_STATE_NEW);
        return;
    }

    editor_switch_popup_to(EDITOR_POPUP_STATE_CONFIRM_NEW);
}

void shortcut_open()
{
    if (is_popup_opened == true)
    {
        return;
    }

    if (editor_state == EDITOR_STATE_START)
    {
        editor_switch_popup_to(EDITOR_POPUP_STATE_OPEN);
        return;
    }

    editor_switch_popup_to(EDITOR_POPUP_STATE_CONFIRM_OPEN);
}

void shortcut_settings()
{
    if (is_popup_opened == true)
    {
        return;
    }

    editor_switch_popup_to(EDITOR_POPUP_STATE_SETTINGS);
}

void shortcut_save()
{
    if (is_shortcut_allowed() == false)
    {
        return;
    }

    if (key_ctrl)
    {
        strcpy(save_as_filename, ep_filename);
        editor_switch_popup_to(EDITOR_POPUP_STATE_SAVE_AS);
        return;
    }

    STRING *temp_ep_name_str = "";
    str_cpy(temp_ep_name_str, ep_filename);
    str_cat(temp_ep_name_str, " saved.");
    message_add(temp_ep_name_str);

    episode_save(ep_filename, &def_episode);
}

void shortcut_ep_reset()
{
    if (is_shortcut_allowed() == false)
    {
        return;
    }

    editor_switch_popup_to(EDITOR_POPUP_STATE_EP_RESET);
}

void shortcut_ep_edit()
{
    if (is_shortcut_allowed() == false)
    {
        return;
    }

    strcpy(episode_edit_name, def_episode.name);
    episode_edit_map_count = def_episode.map_count;
    editor_switch_popup_to(EDITOR_POPUP_STATE_EP_EDIT);
}

void shortcut_map_reset()
{
    if (is_shortcut_allowed() == false)
    {
        return;
    }

    editor_switch_popup_to(EDITOR_POPUP_STATE_MAP_RESET);
}

void shortcut_map_settings()
{
    if (is_shortcut_allowed() == false)
    {
        return;
    }

    Map *active_map = map_get_active(&def_episode);
    map_copy(&map_settings, active_map);

    is_map_settings_visible = 1 - is_map_settings_visible;
}

void shortcut_toggle_hovering_info()
{
    if (is_shortcut_allowed() == false)
    {
        return;
    }

    is_selected_cell_visible = 1 - is_selected_cell_visible;
}

void shortcut_toggle_debug_panel()
{
    if (is_shortcut_allowed() == false)
    {
        return;
    }

    is_debug_panel_visible = 1 - is_debug_panel_visible;
}

void shortcut_map_prior()
{
    if (is_shortcut_allowed() == false)
    {
        return;
    }

    if (!key_ctrl)
    {
        return;
    }

    map_prior();
}

void shortcut_map_next()
{
    if (is_shortcut_allowed() == false)
    {
        return;
    }

    if (!key_ctrl)
    {
        return;
    }

    map_next();
}

void shortcut_map_shift_west()
{
    if (is_shortcut_allowed() == false)
    {
        return;
    }

    if (!key_shift)
    {
        return;
    }

    map_shift_west();
}

void shortcut_map_shift_east()
{
    if (is_shortcut_allowed() == false)
    {
        return;
    }

    if (!key_shift)
    {
        return;
    }

    map_shift_east();
}

void shortcut_map_shift_south()
{
    if (is_shortcut_allowed() == false)
    {
        return;
    }

    if (!key_shift)
    {
        return;
    }

    map_shift_south();
}

void shortcut_map_shift_north()
{
    if (is_shortcut_allowed() == false)
    {
        return;
    }

    if (!key_shift)
    {
        return;
    }

    map_shift_north();
}