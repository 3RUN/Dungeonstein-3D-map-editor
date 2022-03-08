
void editor_map_fnc()
{
    set(my, INVISIBLE | PASSABLE | LIGHT | NOFILTER | UNLIT | DECAL);
    my->material = mtl_solid;
}

void editor_map_settings_initialize()
{
    // create visible entities
    map_settings_ceiling_ent = ent_create(map_settings_ceiling_mdl, nullvector, editor_map_fnc);
    map_settings_walls_ent = ent_create(map_settings_map_wmb, nullvector, editor_map_fnc);
    map_settings_floor_ent = ent_create(map_settings_floor_mdl, nullvector, editor_map_fnc);

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

    editor_map_settings_refresh();
}

void editor_map_settings_refresh()
{
    // weather
    int i = 0;
    for (i = 0; i < WEATHER_MAX; i++)
    {
        if (map_settings.weather_id == i)
        {
            str_cpy(weather_currently_used_str, weather_list_str[i]);
            weather_play_sound(map_settings.weather_id);
        }
    }
}

void editor_map_settings_destroy()
{
    if (map_settings_ceiling_ent)
    {
        safe_remove(map_settings_ceiling_ent);
    }

    if (map_settings_walls_ent)
    {
        safe_remove(map_settings_walls_ent);
    }

    if (map_settings_floor_ent)
    {
        safe_remove(map_settings_floor_ent);
    }

    int i = 0;
    for (i = 0; i < WEATHER_MAX; i++)
    {
        if (weather_list_str[i])
        {
            ptr_remove(weather_list_str[i]);
        }
    }
}

void editor_map_settings_show(Map *map)
{
    if (!map)
    {
        return;
    }

    reset(map_settings_ceiling_ent, INVISIBLE);
    reset(map_settings_walls_ent, INVISIBLE);
    reset(map_settings_floor_ent, INVISIBLE);

    if (map->weather_id > WEATHER_CLEAR)
    {
        set(map_settings_ceiling_ent, INVISIBLE);
    }

    map_copy_weather(&map_settings, map);
    editor_map_settings_refresh();
}

void editor_map_settings_hide()
{
    set(map_settings_ceiling_ent, INVISIBLE);
    set(map_settings_walls_ent, INVISIBLE);
    set(map_settings_floor_ent, INVISIBLE);
}

void editor_map_settings_popup(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    if (is_popup_opened)
    {
        imgui_open_popup(map_settings_music_browser_popup_id);
    }

    int editor_map_popup_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;
    if (imgui_begin_popup_modals_params(map_settings_music_browser_popup_id, NULL, editor_map_popup_flags))
    {
        editor_popup_music_browser(episode);
        imgui_end_popup();
    }
}

void editor_map_settings_update(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    imgui_start_imode();
    imgui_set_next_window_pos(screen_size.x - EDITOR_MAP_SETTINGS_WINDOW_WIDTH - 8, screen_size.y - EDITOR_MAP_SETTINGS_WINDOW_HEIGHT - 8, ImGuiCond_Appearing);
    imgui_set_next_window_size(EDITOR_MAP_SETTINGS_WINDOW_WIDTH, EDITOR_MAP_SETTINGS_WINDOW_HEIGHT, ImGuiCond_Appearing);
    int settings_window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoSavedSettings;
    imgui_begin(map_settings_window_id, NULL, settings_window_flags);

    imgui_separator();
    imgui_text(_chr(map_settings_opened_map_id_str));
    imgui_same_line();
    imgui_align_right_with_offset(80);
    if (imgui_arrow_button(_chr(editor_decrease_str), ImGuiDir_Left))
    {
        current_map_id--;
        current_map_id = clamp(current_map_id, 0, episode->map_count - 1);

        editor_grid_sprites_refresh(episode);
        Map *current_map = map_get_active(episode);
        editor_map_settings_show(current_map);
    }
    imgui_same_line();
    imgui_text(_chr(str_printf(NULL, "%d / %d", (long)(current_map_id + 1), (long)episode->map_count)));
    imgui_same_line();
    if (imgui_arrow_button(_chr(editor_increase_str), ImGuiDir_Right))
    {
        current_map_id++;
        current_map_id = clamp(current_map_id, 0, episode->map_count - 1);

        editor_grid_sprites_refresh(episode);
        Map *current_map = map_get_active(episode);
        editor_map_settings_show(current_map);
    }
    current_map_id = clamp(current_map_id, 0, episode->map_count - 1);
    imgui_separator();

    // weather
    imgui_text(_chr(map_settings_weather_str));
    imgui_same_line();
    var avail_combobox_width = imgui_get_content_region_avail_width();
    imgui_push_item_width(avail_combobox_width);
    if (imgui_begin_combo(map_settings_weather_combobox_id, _chr(weather_currently_used_str), ImGuiComboFlags_HeightSmall))
    {
        int i = 0;
        for (i = 0; i < WEATHER_MAX; i++)
        {
            int is_selected = str_cmp(weather_currently_used_str, weather_list_str[i]);
            if (imgui_selectable(_chr(weather_list_str[i]), &is_selected, 0))
            {
                map_settings.weather_id = i;
                str_cpy(weather_currently_used_str, weather_list_str[i]);
                editor_map_settings_refresh();

                if (map_settings_ceiling_ent)
                {
                    if (map_settings.weather_id > WEATHER_CLEAR)
                    {
                        set(map_settings_ceiling_ent, INVISIBLE);
                    }
                    else
                    {
                        reset(map_settings_ceiling_ent, INVISIBLE);
                    }
                }
            }
        }
        imgui_end_combo();
    }
    imgui_pop_item_width();

    // fog settings
    imgui_text(_chr(map_settings_fog_start_str));
    imgui_same_line();
    var avail_slider_width = imgui_get_content_region_avail_width();
    imgui_push_item_width(avail_slider_width);
    imgui_slider_var(map_settings_fog_start_slider_id, &map_settings.fog_start, 0, map_settings.fog_end);
    map_settings.fog_start = clamp(map_settings.fog_start, 0, map_settings.fog_end);
    editor_create_tooltip(_chr(map_settings_fog_start_tooltip_str));

    imgui_text(_chr(map_settings_fog_end_str));
    imgui_same_line();
    imgui_slider_var(map_settings_fog_end_slider_id, &map_settings.fog_end, maxv(map_settings.fog_start, 32), FOG_MAX_END);
    map_settings.fog_end = clamp(map_settings.fog_end, maxv(map_settings.fog_start, 32), FOG_MAX_END);
    editor_create_tooltip(_chr(map_settings_fog_end_tooltip_str));
    imgui_pop_item_width();

    imgui_text(_chr(map_settings_fog_color_str));
    imgui_same_line();
    var avail_picker_width = imgui_get_content_region_avail_width();
    imgui_push_item_width(avail_picker_width);
    static int fog_color_misc_flags = ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoDragDrop;
    imgui_color_edit3(map_settings_fog_color_picker_id, map_settings.fog_color, fog_color_misc_flags);
    imgui_pop_item_width();
    imgui_separator();

    // ceiling color
    if (map_settings.weather_id <= WEATHER_CLEAR)
    {
        str_cpy(map_settings_ceiling_color_str, map_settings_change_ceiling_color_str);
    }
    else
    {
        str_cpy(map_settings_ceiling_color_str, map_settings_change_sky_color_str);
    }
    imgui_text(_chr(map_settings_ceiling_color_str));
    imgui_same_line();
    var avail_picker_width = imgui_get_content_region_avail_width();
    imgui_push_item_width(avail_picker_width);
    static int sky_color_misc_flags = ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoDragDrop;
    imgui_color_edit3(map_settings_sky_color_picker_id, map_settings.ceiling_color, sky_color_misc_flags);
    imgui_pop_item_width();

    // floor color
    imgui_text(_chr(map_settings_floor_color_str));
    imgui_same_line();
    var avail_picker_width = imgui_get_content_region_avail_width();
    imgui_push_item_width(avail_picker_width);
    static int misc_flags = ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoDragDrop;
    imgui_color_edit3(map_settings_floor_color_picker_id, map_settings.floor_color, misc_flags);
    imgui_pop_item_width();
    imgui_separator();

    // music
    imgui_text(_chr(map_settings_music_str));
    imgui_same_line();
    int len = strlen(map_settings.music);
    imgui_push_item_width(EDITOR_MAP_SETTINGS_MUSIC_NAME_INPUT_WIDTH);
    imgui_input_text(map_settings_music_input_id, map_settings.music, len, ImGuiInputTextFlags_ReadOnly | ImGuiInputTextFlags_AutoSelectAll);
    imgui_pop_item_width();
    imgui_same_line();
    if (imgui_button_withsize(_chr(editor_browse_str), -1, EDITOR_MAP_SETTINGS_MUSIC_BROWSE_BUTTON_HEIGHT))
    {
        is_popup_opened = true;
    }
    imgui_separator();

    var width = ((EDITOR_MAP_SETTINGS_WINDOW_WIDTH - (engine_theme_win_padding[0] * 2)) / 4) - 3;

    // reset current level settings
    if (imgui_button_withsize(_chr(editor_defaults_str), width, EDITOR_POPUP_BUTTON_HEIGHT))
    {
        map_copy_weather(&map_settings, NULL);
        editor_map_settings_refresh();
        editor_map_settings_show(&map_settings);
    }

    // reset to previous ones
    imgui_same_line();
    if (imgui_button_withsize(_chr(editor_reset_str), width, EDITOR_POPUP_BUTTON_HEIGHT))
    {
        Map *current_map = map_get_active(episode);
        map_copy_weather(&map_settings, current_map);
        editor_map_settings_show(&map_settings);
    }

    // apply and return back to the editor mode
    imgui_same_line();
    if (imgui_button_withsize(_chr(editor_ok_str), width, EDITOR_POPUP_BUTTON_HEIGHT))
    {
        Map *current_map = map_get_active(episode);
        map_copy_weather(current_map, &map_settings);
        editor_switch_state_to(EDITOR_STATE_FROM_MAP_SETTINGS);
    }

    // reset to previous ones and close
    imgui_same_line();
    if (imgui_button_withsize(_chr(editor_cancel_str), width, EDITOR_POPUP_BUTTON_HEIGHT))
    {
        Map *current_map = map_get_active(episode);
        map_copy_weather(&map_settings, current_map);
        editor_switch_state_to(EDITOR_STATE_FROM_MAP_SETTINGS);
    }

    imgui_end();
    editor_map_settings_popup(episode);
    imgui_end_imode();

    // apply all the settings at the test level
    // so user can see the changes instantly
    // camera and fog settings
    game_build_weather_settings(&map_settings);

    // ceiling and floor
    if (map_settings_ceiling_ent)
    {
        change_color_from_hsv(&map_settings_ceiling_ent->blue, map_settings.ceiling_color[0], map_settings.ceiling_color[1], map_settings.ceiling_color[2]);
    }

    if (map_settings_floor_ent)
    {
        change_color_from_hsv(&map_settings_floor_ent->blue, map_settings.floor_color[0], map_settings.floor_color[1], map_settings.floor_color[2]);
    }

    // update shaders
    mtl_solid->skill1 = floatv(shader_level_ambient);
    mtl_solid->skill2 = floatv(shader_angle_surface_darken);

    mtl_two_sided->skill1 = floatv(shader_level_ambient);
    mtl_two_sided->skill2 = floatv(shader_angle_surface_darken);
}