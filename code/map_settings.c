
void map_settings_copy_from_active(Map *map)
{
    if (!map)
    {
        return;
    }

    map_copy_weather(&map_settings, map);
    map_settings_refresh();
}

void map_settings_copy_to_active(Map *map)
{
    if (!map)
    {
        return;
    }

    map_copy_weather(map, &map_settings);
}

void map_settings_initialize()
{
    // weather
    int i = 0;
    for (i = 0; i < WEATHER_MAX; i++)
    {
        STRING *temp_weather_str = "";
        if (i == WEATHER_CLEAR)
        {
            str_cpy(temp_weather_str, weather_clear_str);
        }
        else if (i == WEATHER_RAIN)
        {
            str_cpy(temp_weather_str, weather_rain_str);
        }
        else if (i == WEATHER_SNOW)
        {
            str_cpy(temp_weather_str, weather_snow_str);
        }

        if (!weather_list_str[i])
        {
            weather_list_str[i] = str_create("");
            str_cpy(weather_list_str[i], temp_weather_str);
        }
    }

    map_settings_refresh();
}

void map_settings_refresh()
{
    int i = 0;
    for (i = 0; i < WEATHER_MAX; i++)
    {
        if (map_settings.weather_id == i)
        {
            str_cpy(weather_currently_used_str, weather_list_str[i]);
            weather_play_sound(i);
        }
    }
}

void map_settings_destory()
{
    int i = 0;
    for (i = 0; i < WEATHER_MAX; i++)
    {
        if (weather_list_str[i])
        {
            ptr_remove(weather_list_str[i]);
        }
    }
}

void map_settings_popup()
{
    if (is_popup_opened)
    {
        imgui_open_popup(map_settings_music_browser_popup_id);
    }

    int editor_map_popup_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;
    if (imgui_begin_popup_modals_params(map_settings_music_browser_popup_id, NULL, editor_map_popup_flags))
    {
        popup_music_browser();
        imgui_end_popup();
    }
}

void map_settings_update(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    Map *active_map = map_get_active(episode);
    if (!active_map)
    {
        return;
    }

    imgui_start_imode();
    imgui_set_next_window_pos(screen_size.x - (MAP_SETTINGS_WINDOW_WIDTH * config_saved.font_scale) - 8, screen_size.y - (MAP_SETTINGS_WINDOW_HEIGHT * config_saved.font_scale) - 8, ImGuiCond_Always);
    imgui_set_next_window_size(MAP_SETTINGS_WINDOW_WIDTH * config_saved.font_scale, MAP_SETTINGS_WINDOW_HEIGHT * config_saved.font_scale, ImGuiCond_Always);
    int settings_window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoSavedSettings;
    imgui_begin(map_settings_window_id, NULL, settings_window_flags);
    imgui_separator();
    imgui_text_disabled_centered(_chr(str_printf(NULL, "Opened map id: %d", (long)active_map_id)));
    imgui_separator();

    // weather
    imgui_text("Weather:      ");
    imgui_same_line();
    var avail_combobox_width = imgui_get_content_region_avail_width();
    imgui_push_item_width(avail_combobox_width);
    if (imgui_begin_combo(map_settings_weather_combo_id, _chr(weather_currently_used_str), ImGuiComboFlags_HeightSmall))
    {
        int i = 0;
        for (i = 0; i < WEATHER_MAX; i++)
        {
            int is_selected = str_cmp(weather_currently_used_str, weather_list_str[i]);
            if (imgui_selectable(_chr(weather_list_str[i]), &is_selected, 0))
            {
                map_settings.weather_id = i;
                str_cpy(weather_currently_used_str, weather_list_str[i]);
                map_settings_refresh();
            }
        }
        imgui_end_combo();
    }
    imgui_pop_item_width();

    // fog settings
    imgui_text("Fog start:    ");
    imgui_same_line();
    var avail_slider_width = imgui_get_content_region_avail_width();
    imgui_push_item_width(avail_slider_width);
    imgui_slider_var(map_settings_fog_start_slider_id, &map_settings.fog_start, 0, map_settings.fog_end);
    map_settings.fog_start = clamp(map_settings.fog_start, 0, map_settings.fog_end);
    editor_create_tooltip("Fog starting distance in quants.\nShould be smaller than 'end'.");

    imgui_text("Fog end:      ");
    imgui_same_line();
    imgui_slider_var(map_settings_fog_end_slider_id, &map_settings.fog_end, maxv(map_settings.fog_start, 32), FOG_MAX_END);
    map_settings.fog_end = clamp(map_settings.fog_end, maxv(map_settings.fog_start, 32), FOG_MAX_END);
    editor_create_tooltip("Fog end distance in quants.\nShould be higher than 'start'.");
    imgui_pop_item_width();

    imgui_text("Fog color:    ");
    imgui_same_line();
    var avail_picker_width = imgui_get_content_region_avail_width();
    imgui_push_item_width(avail_picker_width);
    static int fog_color_misc_flags = ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoDragDrop;
    imgui_color_edit3(map_settings_fog_color_picker_id, map_settings.fog_color, fog_color_misc_flags);
    imgui_pop_item_width();
    imgui_separator();

    // toggle ceiling visibility
    imgui_text("Ceiling is visible:");
    imgui_same_line();
    imgui_align_right_with_offset(110 * config_saved.font_scale);
    imgui_radiobutton("true", &map_settings.is_ceiling_visible, true);
    imgui_same_line();
    imgui_radiobutton("false", &map_settings.is_ceiling_visible, false);

    // ceiling color
    if (map_settings.weather_id <= WEATHER_CLEAR && map_settings.is_ceiling_visible == true)
    {
        str_cpy(map_settings_ceiling_color_str, "Ceiling color:");
    }
    else
    {
        str_cpy(map_settings_ceiling_color_str, "Sky color:    ");
    }
    imgui_text(_chr(map_settings_ceiling_color_str));
    imgui_same_line();
    var avail_picker_width = imgui_get_content_region_avail_width();
    imgui_push_item_width(avail_picker_width);
    static int sky_color_misc_flags = ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoDragDrop;
    imgui_color_edit3(map_settings_sky_color_picker_id, map_settings.ceiling_color, sky_color_misc_flags);
    imgui_pop_item_width();

    // floor color
    imgui_text("Floor color:  ");
    imgui_same_line();
    var avail_picker_width = imgui_get_content_region_avail_width();
    imgui_push_item_width(avail_picker_width);
    static int misc_flags = ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoDragDrop;
    imgui_color_edit3(map_settings_floor_color_picker_id, map_settings.floor_color, misc_flags);
    imgui_pop_item_width();
    imgui_separator();

    // music
    imgui_text("Music:        ");
    imgui_same_line();
    int len = strlen(map_settings.music);
    imgui_push_item_width(MAP_SETTINGS_MUSIC_NAME_INPUT_WIDTH);
    imgui_input_text(map_settings_music_input_id, map_settings.music, len, ImGuiInputTextFlags_ReadOnly | ImGuiInputTextFlags_AutoSelectAll);
    imgui_pop_item_width();
    imgui_same_line();
    if (imgui_button_withsize("Browser", -1, MAP_SETTINGS_MUSIC_BROWSE_BUTTON_HEIGHT))
    {
        weather_pause_sound();
        is_popup_opened = true;
    }
    imgui_separator();

    var width = (((MAP_SETTINGS_WINDOW_WIDTH * config_saved.font_scale) - (engine_theme_win_padding[0] * 2)) / 4) - 3;
    if (imgui_button_withsize("Defaults", width, MAP_SETTINGS_BUTTON_HEIGHT * config_saved.font_scale)) // reset current level settings
    {
        map_copy_weather(&map_settings, NULL);
        map_settings_refresh();
    }

    // reset to previous ones
    imgui_same_line();
    if (imgui_button_withsize("Reset", width, MAP_SETTINGS_BUTTON_HEIGHT * config_saved.font_scale))
    {
        map_settings_copy_from_active(active_map);
    }

    // apply and return back to the editor mode
    imgui_same_line();
    if (imgui_button_withsize("Ok", width, MAP_SETTINGS_BUTTON_HEIGHT * config_saved.font_scale))
    {
        map_settings_copy_to_active(active_map);
        editor_switch_state_to(EDITOR_STATE_FROM_MAP_SETTINGS);
    }

    // reset to previous ones and close
    imgui_same_line();
    if (imgui_button_withsize("Back", width, MAP_SETTINGS_BUTTON_HEIGHT * config_saved.font_scale))
    {
        map_settings_copy_from_active(active_map);
        editor_switch_state_to(EDITOR_STATE_FROM_MAP_SETTINGS);
    }

    imgui_end();
    map_settings_popup();
    imgui_end_imode();

    // update floor and ceiling
    ceiling_update_from_map(&map_settings);
    floor_update_from_map(&map_settings);

    // handle esc without on_esc
    // because on_ engine events are handled after imgui
    // I've also separated esc from popup esc
    if (is_popup_opened == false)
    {
        is_esc_popup_allowed = false;

        if (key_esc)
        {
            if (is_esc_allowed == true)
            {
                editor_switch_state_to(EDITOR_STATE_FROM_MAP_SETTINGS);
                is_esc_allowed = false;
            }
        }
        else
        {
            is_esc_allowed = true;
        }
    }
    else // this part is used in popup functions
    {
        is_esc_allowed = false;

        if (key_esc)
        {
            if (is_esc_popup_allowed == true)
            {
                is_esc_popup_allowed = false;
            }
        }
        else
        {
            is_esc_popup_allowed = true;
        }
    }
}