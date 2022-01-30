
// imgui handles color range from 0...1
// so I do this dumb trick to get 0...255 value
float get_hsv_from_color(float value)
{
    return value / 255;
}

float get_color_from_hsv(float value)
{
    return value * 255;
}

void editor_camera_resize(int is_shrinked)
{
    if (is_shrinked == true)
    {
        camera->pos_x = 0;
        camera->pos_y = EDITOR_TOP_BAR_HEIGHT;
        camera->size_x = screen_size.x - EDITOR_SIDE_BAR_WIDTH;
        camera->size_y = screen_size.y - EDITOR_TOP_BAR_HEIGHT;
    }
    else
    {
        camera->pos_x = 0;
        camera->pos_y = 0;
        camera->size_x = screen_size.x;
        camera->size_y = screen_size.y;
    }
}

void editor_main_initialize(Episode *e)
{
    if (!e)
    {
        return;
    }

    // weather
    int i = 0;
    for (i = 0; i < WEATHER_MAX; i++)
    {
        STRING *temp_weather_str = "";

        if (i == WEATHER_CLEAR)
        {
            str_cpy(temp_weather_str, weather_clear_str);
        }
        else if (i == WEATHER_CLOUDY)
        {
            str_cpy(temp_weather_str, weather_cloudy_str);
        }
        else if (i == WEATHER_RAINY)
        {
            str_cpy(temp_weather_str, weather_rain_str);
        }

        if (!weather_list_str[i])
        {
            weather_list_str[i] = str_create("");
            str_cpy(weather_list_str[i], temp_weather_str);
        }
    }
    editor_weather_refresh(e);

    // sky
    for (i = 0; i < SKY_MAX; i++)
    {
        STRING *temp_sky_str = "";

        if (i == SKY_CLEAR)
        {
            str_cpy(temp_sky_str, skycube_clear_str);
        }
        else if (i == SKY_CLOUDY)
        {
            str_cpy(temp_sky_str, skycube_cloudy_str);
        }
        else if (i == SKY_NIGHT)
        {
            str_cpy(temp_sky_str, skycube_night_str);
        }

        if (!skycube_list_str[i])
        {
            skycube_list_str[i] = str_create("");
            str_cpy(skycube_list_str[i], temp_sky_str);
        }
    }
    editor_sky_refresh(e);

    // resolution
    STRING *temp_resolution = "";
    for (i = 0; i < screen_resolutions_total; i++)
    {
        str_cpy(temp_resolution, str_for_num(NULL, screen_resolution_available_list[SCREEN_RESOLUTION_WIDTH][i]));
        str_cat(temp_resolution, "x");
        str_cat(temp_resolution, str_for_num(NULL, screen_resolution_available_list[SCREEN_RESOLUTION_HEIGHT][i]));

        if (!graphics_resolution_available_list_str[i])
        {
            graphics_resolution_available_list_str[i] = str_create("");
            str_cpy(graphics_resolution_available_list_str[i], temp_resolution);
        }
    }

    // display modes
    for (i = 0; i < DISPLAY_MODES_MAX; i++)
    {
        if (!graphics_display_mode_list_str[i])
        {
            graphics_display_mode_list_str[i] = str_create("");
            switch (i)
            {
            case DISPLAY_MODE_WINDOWED:
                str_cpy(graphics_display_mode_list_str[i], graphics_display_windowed_str);
                break;

            case DISPLAY_MODE_WINDOWED_FULLSCREEN:
                str_cpy(graphics_display_mode_list_str[i], graphics_display_windowed_fullscreen_str);
                break;
            }
        }
    }
    editor_settings_refresh();
}

void editor_main_destroy()
{
    int i = 0;
    for (i = 0; i < WEATHER_MAX; i++)
    {
        if (weather_list_str[i])
        {
            ptr_remove(weather_list_str[i]);
        }
    }

    for (i = 0; i < SKY_MAX; i++)
    {
        if (skycube_list_str[i])
        {
            ptr_remove(skycube_list_str[i]);
        }
    }

    for (i = 0; i < screen_resolutions_total; i++)
    {
        if (graphics_resolution_available_list_str[i])
        {
            ptr_remove(graphics_resolution_available_list_str[i]);
        }
    }

    // display modes
    for (i = 0; i < DISPLAY_MODES_MAX; i++)
    {
        if (graphics_display_mode_list_str[i])
        {
            ptr_remove(graphics_display_mode_list_str[i]);
        }
    }
}

void editor_main_reset(Episode *e)
{
    if (!e)
    {
        return;
    }

    current_map_id = 0;
    is_settings_opened = false;
    is_editor_popup_on = false;

    editor_weather_refresh(e);
    editor_sky_refresh(e);
}

void editor_weather_refresh(Episode *e)
{
    if (!e)
    {
        return;
    }

    Map *m = &e->maps[current_map_id];
    if (!m)
    {
        return;
    }

    // weather
    int i = 0;
    for (i = 0; i < WEATHER_MAX; i++)
    {
        if (m->weather == i)
        {
            str_cpy(weather_currently_used_str, weather_list_str[i]);
        }
    }

    // load fog preset when weather is changed
    if (m->weather == WEATHER_CLEAR)
    {
        m->fog_start = 32;
        m->fog_end = 1024;
        m->fog_color[0] = get_hsv_from_color(255); // 0...1
        m->fog_color[1] = get_hsv_from_color(255);
        m->fog_color[2] = get_hsv_from_color(255);
    }
    else if (m->weather == WEATHER_CLOUDY)
    {
        m->fog_start = 32;
        m->fog_end = 512;
        m->fog_color[0] = get_hsv_from_color(128);
        m->fog_color[1] = get_hsv_from_color(128);
        m->fog_color[2] = get_hsv_from_color(128);
    }
    else if (m->weather == WEATHER_RAINY)
    {
        m->fog_start = 32;
        m->fog_end = 256;
        m->fog_color[0] = get_hsv_from_color(96);
        m->fog_color[1] = get_hsv_from_color(96);
        m->fog_color[2] = get_hsv_from_color(96);
    }
}

void editor_sky_refresh(Episode *e)
{
    if (!e)
    {
        return;
    }

    Map *m = &e->maps[current_map_id];
    if (!m)
    {
        return;
    }

    // sky
    int i = 0;
    for (i = 0; i < SKY_MAX; i++)
    {
        if (m->sky_cube == i)
        {
            str_cpy(skycube_currently_used_str, skycube_list_str[i]);
        }
    }
}

void editor_map_settings(Episode *e)
{
    if (!e)
    {
        return;
    }

    Map *m = &e->maps[current_map_id];
    if (!m)
    {
        return;
    }

    // weather
    imgui_text("Weather:");
    imgui_same_line();
    var avail_combobox_width = imgui_get_content_region_avail_width();
    imgui_push_item_width(avail_combobox_width);
    if (imgui_begin_combo("##Weather Combobox", _chr(weather_currently_used_str), ImGuiComboFlags_HeightSmall))
    {
        int i = 0;
        for (i = 0; i < WEATHER_MAX; i++)
        {
            int is_selected = str_cmp(weather_currently_used_str, weather_list_str[i]);
            if (imgui_selectable(_chr(weather_list_str[i]), &is_selected, 0))
            {
                m->weather = i;
                str_cpy(weather_currently_used_str, weather_list_str[i]);
                editor_weather_refresh(e);
            }
        }
        imgui_end_combo();
    }
    imgui_pop_item_width();

    //sky
    imgui_text("Skycube:");
    imgui_same_line();
    var avail_combobox_width = imgui_get_content_region_avail_width();
    imgui_push_item_width(avail_combobox_width);
    if (imgui_begin_combo("##Skycube Combobox", _chr(skycube_currently_used_str), ImGuiComboFlags_HeightSmall))
    {
        int i = 0;
        for (i = 0; i < SKY_MAX; i++)
        {
            int is_selected = str_cmp(skycube_currently_used_str, skycube_list_str[i]);
            if (imgui_selectable(_chr(skycube_list_str[i]), &is_selected, 0))
            {
                m->sky_cube = i;
                str_cpy(skycube_currently_used_str, skycube_list_str[i]);
                editor_sky_refresh(e);
            }
        }
        imgui_end_combo();
    }
    imgui_pop_item_width();

    // fog settings
    imgui_text("Fog start: ");
    imgui_same_line();
    var avail_slider_width = imgui_get_content_region_avail_width();
    imgui_push_item_width(avail_slider_width);
    imgui_slider_var("##Fog start slider", &m->fog_start, 0, m->fog_end);
    m->fog_start = clamp(m->fog_start, 0, m->fog_end);
    editor_create_tooltip("Fog starting distance in quants.\nShould be smaller than 'end'.");

    imgui_text("Fog end:   ");
    imgui_same_line();
    imgui_slider_var("##Fog end slider", &m->fog_end, m->fog_start, 2048);
    m->fog_end = clamp(m->fog_end, m->fog_start, 2048);
    editor_create_tooltip("Fog end distance in quants.\nShould be higher than 'start'.");
    imgui_pop_item_width();

    imgui_text("Fog color: ");
    imgui_same_line();
    var avail_picker_width = imgui_get_content_region_avail_width();
    imgui_push_item_width(avail_picker_width);
    static int misc_flags = ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoDragDrop;
    imgui_color_edit3("##Fod color picker", m->fog_color, misc_flags);
    imgui_pop_item_width();
    imgui_separator();

    // music
    imgui_text("Music:");
    imgui_same_line();
    int len = strlen(e->maps[current_map_id].music);
    imgui_push_item_width(170);
    imgui_input_text("##Textbox", e->maps[current_map_id].music, len, ImGuiInputTextFlags_ReadOnly | ImGuiInputTextFlags_AutoSelectAll);
    imgui_pop_item_width();
    imgui_same_line();
    if (imgui_button_withsize("Browse", -1, 15))
    {
        beep();
    }
}

void editor_side_bar(Episode *e)
{
    if (!e)
    {
        return;
    }

    imgui_set_next_window_pos(screen_size.x - EDITOR_SIDE_BAR_WIDTH, EDITOR_TOP_BAR_HEIGHT, ImGuiCond_Always);
    imgui_set_next_window_size(EDITOR_SIDE_BAR_WIDTH, screen_size.y - EDITOR_TOP_BAR_HEIGHT, ImGuiCond_Always);
    int side_bar_flags = ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing;
    imgui_begin("##Side Bar", NULL, side_bar_flags);

    if (imgui_collapsing_header("Preview", NULL, ImGuiTreeNodeFlags_DefaultOpen))
    {
    }

    if (imgui_collapsing_header("Assets", NULL, ImGuiTreeNodeFlags_DefaultOpen))
    {
        imgui_begin_tabbar("Tabs", ImGuiTabBarFlags_Reorderable);
        if (imgui_begin_tabitem("Walls", NULL, NULL))
        {
            imgui_end_tabitem();
        }
        if (imgui_begin_tabitem("Floor", NULL, NULL))
        {
            imgui_end_tabitem();
        }
        if (imgui_begin_tabitem("Ceiling", NULL, NULL))
        {
            imgui_end_tabitem();
        }
        if (imgui_begin_tabitem("Objects", NULL, NULL))
        {
            imgui_end_tabitem();
        }
    }
    imgui_separator();

    if (imgui_collapsing_header("Tools", NULL, ImGuiTreeNodeFlags_DefaultOpen))
    {
        // insert tools here

        imgui_separator();

        if (is_allowed_to_draw_map())
        {
            imgui_text(_chr(str_printf(NULL, "Mouse pos x = %d; y = %d;", (long)mouse_x, (long)mouse_y)));
        }
        else
        {
            imgui_text("Mouse pos x = 0; y = 0;");
        }
    }
    imgui_separator();

    if (imgui_collapsing_header("Map settings", NULL, ImGuiTreeNodeFlags_DefaultOpen))
    {
        imgui_text(_chr(str_printf(NULL, "Size: width = %d; height = %d;", (long)MAP_WIDTH, (long)MAP_HEIGHT)));
        imgui_separator();
        editor_map_settings(e);
    }
    imgui_separator();
    imgui_end();
}

void editor_settings_refresh()
{
    // resolution
    int i = 0;
    STRING *temp_resolution = "";
    for (i = 0; i < screen_resolutions_total; i++)
    {
        str_cpy(temp_resolution, str_for_num(NULL, screen_resolution_available_list[SCREEN_RESOLUTION_WIDTH][i]));
        str_cat(temp_resolution, "x");
        str_cat(temp_resolution, str_for_num(NULL, screen_resolution_available_list[SCREEN_RESOLUTION_HEIGHT][i]));

        // updated selected one
        if (config_current.graphics_video_res_id == i)
        {
            str_cpy(graphics_resolution_currently_used_str, temp_resolution);
        }
    }

    // display modes
    for (i = 0; i < DISPLAY_MODES_MAX; i++)
    {
        // update selected one
        if (config_current.graphics_display_mode == i)
        {
            str_cpy(graphics_display_currently_used_str, graphics_display_mode_list_str[i]);
        }
    }
}

void editor_settings_window()
{
    if (is_settings_opened == false)
    {
        return;
    }

    int window_width = 480;
    int window_height = 240;
    imgui_set_next_window_pos((screen_size.x / 2) - (window_width / 2), (screen_size.y / 2) - (window_height / 2), ImGuiCond_Appearing);
    imgui_set_next_window_size(window_width, window_height, ImGuiCond_Appearing);
    int settings_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoSavedSettings;
    imgui_begin("Settings##Settings window", &is_settings_opened, settings_flags);
    imgui_separator();

    var settings_child_height = window_height - ((BUTTON_HEIGHT * 2) + engine_theme_win_padding[1]);
    int settings_child_flags = ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
    imgui_begin_child("##Settings Child", vector(-1, settings_child_height, 0), 1, settings_child_flags);

    // display mode here
    imgui_text(_chr(graphics_display_mode_str));
    imgui_same_line();
    imgui_align_right_with_offset(COMBOBOX_WIDTH);
    imgui_push_item_width(COMBOBOX_WIDTH - 1);
    if (imgui_begin_combo("##Display mode Combo", _chr(graphics_display_currently_used_str), ImGuiComboFlags_HeightSmall))
    {
        int n = 0;
        for (n = 0; n < DISPLAY_MODES_MAX; n++)
        {
            BOOL is_selected = str_cmp(graphics_display_currently_used_str, graphics_display_mode_list_str[n]);
            if (imgui_selectable(_chr(graphics_display_mode_list_str[n]), &is_selected, 0))
            {
                config_current.graphics_display_mode = n; // currently used display mode setting
                str_cpy(graphics_display_currently_used_str, graphics_display_mode_list_str[n]);

                // reset screen resolution to the first one from the list
                str_cpy(graphics_resolution_currently_used_str, graphics_resolution_available_list_str[0]);
                config_current.graphics_video_res_id = 0;
            }
            if (is_selected)
            {
                imgui_set_item_default_focus();
            }
        }
        imgui_end_combo();
    }
    imgui_pop_item_width();

    // screen resolution
    // only if in windowed mode
    if (config_current.graphics_display_mode == DISPLAY_MODE_WINDOWED)
    {
        imgui_text(_chr(graphics_res_str));
        imgui_same_line();
        imgui_align_right_with_offset(COMBOBOX_WIDTH);
        imgui_push_item_width(COMBOBOX_WIDTH - 1);
        if (imgui_begin_combo("##Resolution Combo", _chr(graphics_resolution_currently_used_str), ImGuiComboFlags_HeightSmall))
        {
            int n = 0;
            for (n = 0; n < screen_resolutions_total; n++)
            {
                // if in windowed mode then make sure to clip resolutions equal or higher than the desktop resolutions
                if (config_current.graphics_display_mode == DISPLAY_MODE_WINDOWED)
                {
                    if (n >= desktop_resolution_id)
                    {
                        continue;
                    }
                }

                // if in windowed fullscreen (borderless) then make sure to clip resolutions higher than the desktop resolution
                if (config_current.graphics_display_mode == DISPLAY_MODE_WINDOWED_FULLSCREEN)
                {
                    if (n > desktop_resolution_id)
                    {
                        continue;
                    }
                }

                BOOL is_selected = str_cmp(graphics_resolution_currently_used_str, graphics_resolution_available_list_str[n]);
                if (imgui_selectable(_chr(graphics_resolution_available_list_str[n]), &is_selected, 0))
                {
                    config_current.graphics_video_res_id = n; // currently used resolution ID
                    str_cpy(graphics_resolution_currently_used_str, graphics_resolution_available_list_str[n]);
                }
                if (is_selected)
                {
                    imgui_set_item_default_focus();
                }
            }
            imgui_end_combo();
        }
        imgui_pop_item_width();
    }
    imgui_separator();

    // tooltip
    imgui_text("Hovering cell tooltip: ");
    imgui_same_line();
    imgui_align_right_with_offset(150);
    imgui_radiobutton("Enabled", &config_current.is_cell_tooltip_enabled, true);
    imgui_same_line();
    imgui_radiobutton("Disabled", &config_current.is_cell_tooltip_enabled, false);
    imgui_separator();

    imgui_end_child();

    // reset to defaults button
    if (imgui_button_withsize("Defaults", BUTTON_WIDTH, 32))
    {
        config_reset_to_default();
        editor_settings_refresh();
    }

    imgui_same_line();
    imgui_align_right_with_offset(BUTTON_WIDTH * 2 + engine_theme_item_spacing[1]);

    // apply and save
    if (imgui_button_withsize("Ok", BUTTON_WIDTH, 32))
    {
        config_save_n_apply();
        editor_settings_refresh();
        is_settings_opened = false;
    }

    imgui_same_line();

    // cancel changes
    if (imgui_button_withsize("Cancel", BUTTON_WIDTH, 32))
    {
        config_reset_to_saved();
        editor_settings_refresh();
        is_settings_opened = false;
    }

    imgui_end();
}

void editor_top_bar(Episode *e)
{
    if (!e)
    {
        return;
    }

    imgui_set_next_window_pos(0, 0, ImGuiCond_Always);
    imgui_set_next_window_size(screen_size.x, EDITOR_TOP_BAR_HEIGHT, ImGuiCond_Always);
    int top_bar_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoFocusOnAppearing;
    imgui_begin("##Top bar", NULL, top_bar_flags);

    if (imgui_begin_menu_bar())
    {
        if (imgui_begin_menu("File", 1))
        {
            if (imgui_menu_item("New", "", 0, 1))
            {
                editor_top_bar_popup_id = EDITOR_TOP_BAR_NEW_POPUP;
                str_cpy(editor_top_bar_popup_str, editor_top_bar_new_popup_str);
                is_editor_popup_on = true;
            }
            imgui_separator();
            if (imgui_menu_item("Save", "", 0, 1))
            {
            }
            if (imgui_menu_item("Load", "", 0, 1))
            {
            }
            imgui_separator();
            if (imgui_menu_item("Exit", "", 0, 1))
            {
                editor_top_bar_popup_id = EDITOR_TOP_BAR_EXIT_POPUP;
                str_cpy(editor_top_bar_popup_str, editor_top_bar_exit_popup_str);
                is_editor_popup_on = true;
            }
            imgui_end_menu();
        }

        if (imgui_begin_menu("View", 1))
        {
            imgui_checkbox("Grid", &is_grid_visible);
            imgui_checkbox("Layer 1 (walls/floor)", &is_layer_1_visible);
            imgui_checkbox("Layer 2 (objects)", &is_layer_2_visible);
            imgui_checkbox("Layer 3 (ceiling)", &is_layer_3_visible);
            imgui_end_menu();
        }

        if (imgui_begin_menu("Editor", 1))
        {
            if (imgui_menu_item("Settings", "", 0, 1))
            {
                is_settings_opened = 1 - is_settings_opened;
            }
            imgui_end_menu();
        }

        if (imgui_begin_menu("Help", 1))
        {
            if (imgui_menu_item("About", "", 0, 1))
            {
                beep();
            }
            imgui_end_menu();
        }

        imgui_push_style_color(ImGuiCol_Button, color4_red);
        imgui_align_right_with_offset(27);
        if (imgui_button("Exit"))
        {
            editor_top_bar_popup_id = EDITOR_TOP_BAR_EXIT_POPUP;
            str_cpy(editor_top_bar_popup_str, editor_top_bar_exit_popup_str);
            is_editor_popup_on = true;
        }
        imgui_pop_style_color(1);

        imgui_end_menu_bar();
    }

    if (is_editor_popup_on == true)
    {
        imgui_open_popup("##Top bar popup");
    }

    int top_bar_modal_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;
    if (imgui_begin_popup_modals_params("##Top bar popup", NULL, top_bar_modal_flags))
    {
        imgui_text(_chr(editor_top_bar_popup_str));

        var button_height = 24;

        if (editor_top_bar_popup_id == EDITOR_TOP_BAR_NEW_POPUP)
        {
            if (imgui_button_withsize("Yes", -1, button_height))
            {
                imgui_close_current_popup();
                is_editor_popup_on = false;
                editor_switch_state_to(STATE_NEW);
            }

            if (imgui_button_withsize("No", -1, button_height) || key_esc)
            {
                imgui_close_current_popup();
                is_editor_popup_on = false;
            }
        }
        else if (editor_top_bar_popup_id == EDITOR_TOP_BAR_EXIT_POPUP)
        {
            if (imgui_button_withsize("Yes", -1, button_height))
            {
                sys_exit("");
            }

            if (imgui_button_withsize("No", -1, button_height) || key_esc)
            {
                imgui_close_current_popup();
                is_editor_popup_on = false;
            }
        }
        imgui_end_popup();
    }

    editor_settings_window();

    imgui_end();
}

void editor_main_update(Episode *e)
{
    if (!e)
    {
        return;
    }

    imgui_start_imode();

    editor_camera_resize(true);
    editor_side_bar(e);
    editor_top_bar(e);

    imgui_end_imode();
}