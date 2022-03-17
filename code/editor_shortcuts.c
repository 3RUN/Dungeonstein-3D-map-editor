
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

void shortcut_remove_binding(var scancode)
{
    if (scancode <= 0)
    {
        return;
    }

    key_set(scancode, NULL);
}

void shortcut_update_binding(var scancode, void *fnc)
{
    if (scancode <= 0)
    {
        return;
    }

    key_set(scancode, NULL);
    key_set(scancode, fnc);
}

void shortcuts_update_from_config(CONFIG *config)
{
    shortcut_remove_binding(scancode_help);
    shortcut_remove_binding(scancode_new);
    shortcut_remove_binding(scancode_open);
    shortcut_remove_binding(scancode_save);
    shortcut_remove_binding(scancode_ep_reset);
    shortcut_remove_binding(scancode_ep_edit);
    shortcut_remove_binding(scancode_reset_map);
    shortcut_remove_binding(scancode_map_settings);
    shortcut_remove_binding(scancode_screenshot);
    shortcut_remove_binding(scancode_settings);
    shortcut_remove_binding(scancode_prior_map);
    shortcut_remove_binding(scancode_next_map);
    shortcut_remove_binding(scancode_shift_map_west);
    shortcut_remove_binding(scancode_shift_map_east);
    shortcut_remove_binding(scancode_shift_map_south);
    shortcut_remove_binding(scancode_shift_map_north);

    scancode_help = engine_key_return_scancode_from_letter(config->short_help);
    scancode_new = engine_key_return_scancode_from_letter(config->short_new);
    scancode_open = engine_key_return_scancode_from_letter(config->short_open);
    scancode_save = engine_key_return_scancode_from_letter(config->short_save);
    scancode_ep_reset = engine_key_return_scancode_from_letter(config->short_ep_reset);
    scancode_ep_edit = engine_key_return_scancode_from_letter(config->short_ep_edit);
    scancode_reset_map = engine_key_return_scancode_from_letter(config->short_reset_map);
    scancode_map_settings = engine_key_return_scancode_from_letter(config->short_map_settings);
    scancode_screenshot = engine_key_return_scancode_from_letter(config->short_screenshot);
    scancode_settings = engine_key_return_scancode_from_letter(config->short_settings);
    scancode_prior_map = engine_key_return_scancode_from_letter(config->short_prior_map);
    scancode_next_map = engine_key_return_scancode_from_letter(config->short_next_map);
    scancode_shift_map_west = engine_key_return_scancode_from_letter(config->short_shift_map_west);
    scancode_shift_map_east = engine_key_return_scancode_from_letter(config->short_shift_map_east);
    scancode_shift_map_south = engine_key_return_scancode_from_letter(config->short_shift_map_south);
    scancode_shift_map_north = engine_key_return_scancode_from_letter(config->short_shift_map_north);

    shortcut_update_binding(scancode_help, shortcut_help);
    shortcut_update_binding(scancode_new, shortcut_new);
    shortcut_update_binding(scancode_open, shortcut_open);
    shortcut_update_binding(scancode_save, shortcut_save);
    shortcut_update_binding(scancode_ep_reset, shortcut_ep_reset);
    shortcut_update_binding(scancode_ep_edit, shortcut_ep_edit);
    shortcut_update_binding(scancode_reset_map, shortcut_reset_map);
    shortcut_update_binding(scancode_map_settings, shortcut_map_settings);
    shortcut_update_binding(scancode_screenshot, shortcut_screenshot);
    shortcut_update_binding(scancode_settings, shortcut_settings);
    shortcut_update_binding(scancode_prior_map, shortcut_prior_map);
    shortcut_update_binding(scancode_next_map, shortcut_next_map);
    shortcut_update_binding(scancode_shift_map_west, shortcut_shift_map_west);
    shortcut_update_binding(scancode_shift_map_east, shortcut_shift_map_east);
    shortcut_update_binding(scancode_shift_map_south, shortcut_shift_map_south);
    shortcut_update_binding(scancode_shift_map_north, shortcut_shift_map_north);
}

void shortcut_help()
{
    cprintf0("\nhelp");
}

void shortcut_new()
{
    cprintf0("\nnew");
}

void shortcut_open()
{
    cprintf0("\nopen");
}

void shortcut_save()
{
    cprintf0("\nsave");
}

void shortcut_ep_reset()
{
    cprintf0("\nepisode reset");
}

void shortcut_ep_edit()
{
    cprintf0("\nepisode edit");
}

void shortcut_reset_map()
{
    cprintf0("\nreset map");
}

void shortcut_map_settings()
{
    cprintf0("\nmap settings");
}

void shortcut_screenshot()
{
    cprintf0("\nscreenshot");

    beep();

    file_for_screen(str_printf(NULL, "shot_%d_%d_%d_", (long)sys_day, (long)sys_month, (long)sys_year), screenshot_num);
    screenshot_num++;
}

void shortcut_settings()
{
    cprintf0("\nsettings");
}

void shortcut_prior_map()
{
    cprintf0("\nprior map");
}

void shortcut_next_map()
{
    cprintf0("\nnext map");
}

void shortcut_shift_map_west()
{
    cprintf0("\nshift west");
}

void shortcut_shift_map_east()
{
    cprintf0("\nshift east");
}

void shortcut_shift_map_south()
{
    cprintf0("\nshift south");
}

void shortcut_shift_map_north()
{
    cprintf0("\nshift north");
}