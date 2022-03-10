
void editor_shortcuts_initialize()
{
    shortcut_info_pan = pan_create(NULL, SHORTCUT_PANEL_LAYER);
    layer_sort(shortcut_info_pan, SHORTCUT_PANEL_LAYER);
    set(shortcut_info_pan, TRANSLUCENT | SHOW);
    shortcut_info_pan->alpha = 0;

    pan_setstring(shortcut_info_pan, 0, 0, 0, shortcut_ackfont, shortcut_screenshot_saved_str);
}

void editor_shortcuts_destroy()
{
    safe_remove(shortcut_info_pan);
}

void shortcut_show_info(STRING *msg)
{
    if (beep_once == true)
    {
        beep_once = false;
    }

    if (snd_playing(beep_handle))
    {
        snd_stop(beep_handle);
    }
    beep_handle = snd_play(beep_ogg, beep_volume, 0);
    pan_setstring(shortcut_info_pan, 1, 0, 0, shortcut_ackfont, msg);

    wait(1);
    beep_once = true;

    shortcut_info_pan->alpha = SHORTCUT_INFO_PANEL_ALPHA;
    while (shortcut_info_pan->alpha > 0)
    {
        if (beep_once == false)
        {
            return;
        }

        shortcut_info_pan->alpha -= 2.5 * time_step;
        wait(1);
    }
    shortcut_info_pan->alpha = 0;
}

void editor_shortcuts_update()
{
    if (shortcut_info_pan)
    {
        shortcut_info_pan->pos_x = 10;
        shortcut_info_pan->pos_y = camera->pos_y + 10;
    }
}

int is_edit_shortcuts_allowed()
{
    if (is_popup_opened == true)
    {
        return false;
    }

    if (editor_state != EDITOR_STATE_EDIT_MAP)
    {
        return false;
    }

    if (is_game_episode_loaded() == false)
    {
        return false;
    }

    return true;
}

int is_empty_shortcuts_allowed()
{
    if (is_popup_opened == true)
    {
        return false;
    }

    if (editor_state != EDITOR_STATE_EMPTY)
    {
        return false;
    }

    if (is_game_episode_loaded() == true)
    {
        return false;
    }

    return true;
}

void shortcut_exit()
{
    if (!key_f4 || key_alt)
    {
        sys_exit(NULL);
    }
}

void shortcut_screenshot()
{
    shortcut_show_info(shortcut_screenshot_saved_str);
    file_for_screen("shot_", screenshot_num);
    screenshot_num++;
}

void shortcut_help()
{
    if (is_empty_shortcuts_allowed() == true)
    {
        empty_popup_state = EMPTY_POPUP_ABOUT;
        is_popup_opened = true;
    }
    else if (is_edit_shortcuts_allowed() == true)
    {
        editor_map_popup_state_change_to(MAP_POPUP_ABOUT);
    }
}

void shortcut_settings()
{
    if (is_empty_shortcuts_allowed() == true)
    {
        empty_popup_state = EMPTY_POPUP_SETTINGS;
        is_popup_opened = true;
    }
    else if (is_edit_shortcuts_allowed() == true)
    {
        editor_map_popup_state_change_to(MAP_POPUP_SETTINGS);
    }
}

void shortcut_save()
{
    if (is_edit_shortcuts_allowed() == false)
    {
        return;
    }

    if (!key_s || key_ctrl && !key_alt) // normal save
    {
        shortcut_show_info(shortcut_episode_saved_str);
        episode_save(episode_save_name, &def_episode);
    }
    else if (!key_s || key_ctrl && key_alt) // save as
    {
        shortcut_show_info(shortcut_episode_saved_str);
        strcpy(save_as_filename, episode_save_name);
        editor_map_popup_state_change_to(MAP_POPUP_SAVE_AS);
    }
}

void shortcut_open()
{
    if (!key_o || key_ctrl)
    {
        if (is_empty_shortcuts_allowed() == true)
        {
            empty_popup_state = EMPTY_POPUP_OPEN;
            is_popup_opened = true;
        }
        else if (is_edit_shortcuts_allowed() == true)
        {
            editor_map_popup_state_change_to(MAP_POPUP_OPEN_SURE);
        }
    }
}

void shortcut_new()
{
    if (!key_n || key_ctrl)
    {
        if (is_empty_shortcuts_allowed() == true)
        {
            empty_popup_state = EMPTY_POPUP_NEW;
            is_popup_opened = true;
        }
        else if (is_edit_shortcuts_allowed() == true)
        {
            editor_map_popup_state_change_to(MAP_POPUP_NEW_SURE);
        }
    }
}

void shortcut_episode_edit()
{
    if (is_edit_shortcuts_allowed() == false)
    {
        return;
    }

    if (!key_e || key_ctrl)
    {
        strcpy(episode_edit_name, def_episode.name);
        strcpy(episode_edit_start_story, def_episode.start_story);
        strcpy(episode_edit_end_story, def_episode.end_story);
        episode_edit_map_count = def_episode.map_count;
        editor_map_popup_state_change_to(MAP_POPUP_EPISODE_EDIT);
    }
}

void shortcut_shift_map()
{
    if (is_edit_shortcuts_allowed() == true)
    {
        if (!key_cuu || key_shift && !key_cud && !key_cur && !key_cul) // up
        {
            shortcut_show_info(shortcut_map_shifted_up_str);
        }
        else if (!key_cud || key_shift && !key_cuu && !key_cur && !key_cul) // down
        {
            shortcut_show_info(shortcut_map_shifted_down_str);
        }
        else if (!key_cur || key_shift && !key_cud && !key_cuu && !key_cul) // right
        {
            shortcut_show_info(shortcut_map_shifted_right_str);
        }
        else if (!key_cul || key_shift && !key_cud && !key_cur && !key_cuu) // left
        {
            shortcut_show_info(shortcut_map_shifted_left_str);
        }
    }
}

void shortcut_prior_map()
{
    if (is_edit_shortcuts_allowed() == false)
    {
        return;
    }

    if (!key_pgdn || key_ctrl)
    {
        shortcut_show_info(shortcut_prior_map_loaded_str);
        current_map_id--;
        current_map_id = clamp(current_map_id, 0, def_episode.map_count - 1);
        editor_grid_sprites_refresh(&def_episode);
    }
}

void shortcut_next_map()
{
    if (is_edit_shortcuts_allowed() == false)
    {
        return;
    }

    if (!key_pgup || key_ctrl)
    {
        shortcut_show_info(shortcut_next_map_loaded_str);
        current_map_id++;
        current_map_id = clamp(current_map_id, 0, def_episode.map_count - 1);
        editor_grid_sprites_refresh(&def_episode);
    }
}

void shortcut_reset_map()
{
    if (is_edit_shortcuts_allowed() == false)
    {
        return;
    }

    if (!key_r || key_ctrl)
    {
        editor_map_popup_state_change_to(MAP_POPUP_RESET_MAP);
    }
}

void shortcut_map_settings()
{
    if (is_edit_shortcuts_allowed() == false)
    {
        return;
    }

    if (!key_m || key_ctrl)
    {
        is_popup_opened = false;
        imgui_close_current_popup();
        editor_switch_state_to(EDITOR_STATE_TO_MAP_SETTINGS);
    }
}

void shortcut_test_build()
{
    if (is_edit_shortcuts_allowed() == false)
    {
        return;
    }

    if (!key_t || key_ctrl)
    {
        is_popup_opened = false;
        imgui_close_current_popup();
        editor_switch_state_to(EDITOR_STATE_TO_TEST_BUILD);
    }
}