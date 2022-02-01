
void editor_preview_update(int type, int index)
{
    preview_bmap = asset_get_bmap(type, index);
    strcpy(preview_name, "Name: ");
    strcat(preview_name, asset_get_desc(type, index));
}

void editor_weather_refresh(Episode *e)
{
    if (!e)
    {
        return;
    }

    Map *m = &e->map[current_map_id];
    if (!m)
    {
        return;
    }

    // weather
    int i = 0;
    for (i = 0; i < WEATHER_MAX; i++)
    {
        if (m->weather_id == i)
        {
            str_cpy(weather_currently_used_str, weather_list_str[i]);
        }
    }

    // load fog preset when weather is changed
    if (m->weather_id == WEATHER_CLEAR)
    {
        m->fog_start = 32;
        m->fog_end = 1024;
        m->fog_color[0] = get_hsv_from_color(255); // 0...1
        m->fog_color[1] = get_hsv_from_color(255);
        m->fog_color[2] = get_hsv_from_color(255);
    }
    else if (m->weather_id == WEATHER_RAIN)
    {
        m->fog_start = 32;
        m->fog_end = 512;
        m->fog_color[0] = get_hsv_from_color(128);
        m->fog_color[1] = get_hsv_from_color(128);
        m->fog_color[2] = get_hsv_from_color(128);
    }
    else if (m->weather_id == WEATHER_SNOW)
    {
        m->fog_start = 32;
        m->fog_end = 256;
        m->fog_color[0] = get_hsv_from_color(96);
        m->fog_color[1] = get_hsv_from_color(96);
        m->fog_color[2] = get_hsv_from_color(96);
    }
}

void editor_side_bar(Episode *e)
{
    imgui_set_next_window_pos(screen_size.x - EDITOR_SIDE_BAR_WIDTH, EDITOR_TOP_BAR_HEIGHT, ImGuiCond_Always);
    imgui_set_next_window_size(EDITOR_SIDE_BAR_WIDTH, screen_size.y - EDITOR_TOP_BAR_HEIGHT, ImGuiCond_Always);
    int side_bar_flags = ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing;
    imgui_begin("##Side Bar", NULL, side_bar_flags);

    if (imgui_collapsing_header("Preview", NULL, ImGuiTreeNodeFlags_DefaultOpen))
    {
        imgui_text("Asset:");
        imgui_align_right_with_offset((EDITOR_SIDE_BAR_WIDTH / 2) + 64 - engine_theme_win_padding[0]);
        imgui_image_scale(preview_bmap, vector(128, 128, 0), vector(0, 0, 0), vector(1, 1, 0));
        imgui_separator();
        imgui_text(preview_name);
    }
    imgui_separator();

    if (imgui_collapsing_header("Assets", NULL, ImGuiTreeNodeFlags_DefaultOpen))
    {
        imgui_text("Category:");
        imgui_same_line();

        imgui_push_item_width(-1);
        if (imgui_begin_combo("##Asset Type Combobox", editor_main_selected_asset_type, ImGuiComboFlags_HeightSmall))
        {
            int n = 0;
            for (n = 0; n < MAX_ASSET_TYPES; n++)
            {
                BOOL is_selected = (editor_main_selected_asset_type == editor_main_asset_types[n]);
                if (imgui_selectable(editor_main_asset_types[n], &is_selected, 0))
                {
                    editor_main_selected_asset_type = editor_main_asset_types[n];
                    editor_asset_type = n;
                    editor_asset_index = 0;
                    editor_preview_update(editor_asset_type, editor_asset_index);
                }
            }
            imgui_end_combo();
        }
        imgui_pop_item_width();

        if (editor_asset_type == ASSET_TYPE_WALL)
        {
            int wall_texture_child_window_flags = ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
            var width = imgui_get_content_region_avail_width();
            imgui_begin_child("##Wall Texture Child", vector(width, 256, 0), 1, wall_texture_child_window_flags);

            imgui_push_item_width(-1);
            if (imgui_list_box("##Wall Texture listbox", &editor_asset_index, wall_textures_listbox, MAX_WALL_TEXTURES, MAX_WALL_TEXTURES))
            {
                int i = 0;
                for (i = 0; i < MAX_WALL_TEXTURES; i++)
                {
                    if (editor_asset_index == i)
                    {
                        editor_preview_update(editor_asset_type, editor_asset_index);
                    }
                }
            }
            imgui_pop_item_width();
            imgui_end_child();
        }
        else if (editor_asset_type >= ASSET_TYPE_PROPS)
        {
            imgui_separator();
            imgui_text("Object parameters:");
            int object_child_window_flags = ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
            var width = imgui_get_content_region_avail_width();
            imgui_begin_child("##Object Parameters Child", vector(width, 96, 0), 1, object_child_window_flags);
            switch (editor_asset_type)
            {
            case ASSET_TYPE_PROPS:
                break;

            case ASSET_TYPE_ITEMS:
                break;

            case ASSET_TYPE_WEAPON:
                break;

            case ASSET_TYPE_ENEMIES:
                break;

            case ASSET_TYPE_BOSSES:
                break;
            }
            imgui_end_child();

            imgui_separator();
            imgui_begin_child("##Object Texture Child", vector(width, 160, 0), 1, object_child_window_flags);
            switch (editor_asset_type)
            {
            case ASSET_TYPE_PROPS:
                imgui_push_item_width(-1);
                if (imgui_list_box("##Props Texture listbox", &editor_asset_index, props_textures_listbox, MAX_PROPS_TEXTURES, MAX_PROPS_TEXTURES))
                {
                    int i = 0;
                    for (i = 0; i < MAX_PROPS_TEXTURES; i++)
                    {
                        if (editor_asset_index == i)
                        {
                            editor_preview_update(editor_asset_type, editor_asset_index);
                        }
                    }
                }
                imgui_pop_item_width();
                break;

            case ASSET_TYPE_ITEMS:
                imgui_push_item_width(-1);
                if (imgui_list_box("##Item Texture listbox", &editor_asset_index, items_textures_listbox, MAX_ITEM_TEXTURES, MAX_ITEM_TEXTURES))
                {
                    int i = 0;
                    for (i = 0; i < MAX_ITEM_TEXTURES; i++)
                    {
                        if (editor_asset_index == i)
                        {
                            editor_preview_update(editor_asset_type, editor_asset_index);
                        }
                    }
                }
                imgui_pop_item_width();
                break;

            case ASSET_TYPE_WEAPON:
                imgui_push_item_width(-1);
                if (imgui_list_box("##Item Texture listbox", &editor_asset_index, weapons_textures_listbox, MAX_WEAPON_TEXTURES, MAX_WEAPON_TEXTURES))
                {
                    int i = 0;
                    for (i = 0; i < MAX_WEAPON_TEXTURES; i++)
                    {
                        if (editor_asset_index == i)
                        {
                            editor_preview_update(editor_asset_type, editor_asset_index);
                        }
                    }
                }
                imgui_pop_item_width();
                break;

            case ASSET_TYPE_ENEMIES:
                imgui_push_item_width(-1);
                if (imgui_list_box("##Item Texture listbox", &editor_asset_index, enemies_textures_listbox, MAX_ENEMY_TEXTURES, MAX_ENEMY_TEXTURES))
                {
                    int i = 0;
                    for (i = 0; i < MAX_ENEMY_TEXTURES; i++)
                    {
                        if (editor_asset_index == i)
                        {
                            editor_preview_update(editor_asset_type, editor_asset_index);
                        }
                    }
                }
                imgui_pop_item_width();
                break;

            case ASSET_TYPE_BOSSES:
                imgui_push_item_width(-1);
                if (imgui_list_box("##Item Texture listbox", &editor_asset_index, bosses_textures_listbox, MAX_BOSS_TEXTURES, MAX_BOSS_TEXTURES))
                {
                    int i = 0;
                    for (i = 0; i < MAX_BOSS_TEXTURES; i++)
                    {
                        if (editor_asset_index == i)
                        {
                            editor_preview_update(editor_asset_type, editor_asset_index);
                        }
                    }
                }
                imgui_pop_item_width();
                break;
            }
            imgui_end_child();
        }
    }
    imgui_separator();

    if (imgui_collapsing_header("Map settings", NULL, ImGuiTreeNodeFlags_DefaultOpen))
    {
        imgui_text("Active Map Id:");
        imgui_same_line();
        imgui_align_right_with_offset(50);
        if (imgui_arrow_button("Decrease", ImGuiDir_Left))
        {
            current_map_id--;
            current_map_id = clamp(current_map_id, 0, e->map_count - 1);
        }
        imgui_same_line();
        imgui_text(_chr(str_printf(NULL, "%d", (long)(current_map_id + 1))));
        imgui_same_line();
        if (imgui_arrow_button("Increase", ImGuiDir_Right))
        {
            current_map_id++;
            current_map_id = clamp(current_map_id, 0, e->map_count - 1);
        }
        imgui_text("Total map count:");
        imgui_same_line();
        imgui_align_right_with_offset(30);
        imgui_text(_chr(str_for_num(NULL, e->map_count)));
        imgui_separator();

        imgui_text(_chr(str_printf(NULL, "Mouse pos x = %d; y = %d;", (long)mouse_x, (long)mouse_y)));
        imgui_text(_chr(str_printf(NULL, "Map size: width = %d; height = %d;", (long)MAP_WIDTH, (long)MAP_HEIGHT)));
        imgui_separator();

        // get active map
        Map *m = &e->map[current_map_id];
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
                    m->weather_id = i;
                    str_cpy(weather_currently_used_str, weather_list_str[i]);
                    editor_weather_refresh(e);
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
        imgui_color_edit3("##Fog color picker", m->fog_color, misc_flags);
        imgui_pop_item_width();
        imgui_separator();

        imgui_text("Sky color: ");
        imgui_same_line();
        var avail_picker_width = imgui_get_content_region_avail_width();
        imgui_push_item_width(avail_picker_width);
        static int misc_flags = ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoDragDrop;
        imgui_color_edit3("##Sky color picker", m->sky_color, misc_flags);
        imgui_pop_item_width();

        /*
        COLOR temp_color;
        temp_color.red = get_color_from_hsv(m->sky_color[0]);
        temp_color.green = get_color_from_hsv(m->sky_color[1]);
        temp_color.blue = get_color_from_hsv(m->sky_color[2]);
        vec_set(&sky_color, &temp_color);
        */

        imgui_separator();

        // music
        imgui_text("Music:");
        imgui_same_line();
        int len = strlen(m->music);
        imgui_push_item_width(140);
        imgui_input_text("##Textbox", m->music, len, ImGuiInputTextFlags_ReadOnly | ImGuiInputTextFlags_AutoSelectAll);
        imgui_pop_item_width();
        imgui_same_line();
        if (imgui_button_withsize("Browse", -1, 15))
        {
            beep();
        }
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
    int settings_window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoSavedSettings;
    imgui_begin("Settings##Settings window", &is_settings_opened, settings_window_flags);
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

    // background color
    imgui_text("Background color: ");
    imgui_same_line();
    var avail_picker_width = imgui_get_content_region_avail_width();
    imgui_push_item_width(avail_picker_width);
    static int misc_flags = ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoDragDrop;
    imgui_color_edit3("##Background color picker", config_current.background_color, misc_flags);
    imgui_pop_item_width();

    // grid color
    imgui_text("Grid color:       ");
    imgui_same_line();
    var avail_picker_width = imgui_get_content_region_avail_width();
    imgui_push_item_width(avail_picker_width);
    static int misc_flags = ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoDragDrop;
    imgui_color_edit3("##Grid color picker", config_current.grid_color, misc_flags);
    imgui_pop_item_width();

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

void editor_help_window()
{
    if (is_help_opened == false)
    {
        return;
    }

    int window_width = 128;
    int window_height = 64;
    imgui_set_next_window_pos((screen_size.x / 2) - (window_width / 2), (screen_size.y / 2) - (window_height / 2), ImGuiCond_Appearing);
    imgui_set_next_window_size(window_width, window_height, ImGuiCond_Appearing);
    int about_window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoSavedSettings;
    imgui_begin("About##About window", &is_help_opened, about_window_flags);

    imgui_text("blahblahblah");

    imgui_end();
}

void editor_top_bar(Episode *e)
{
    imgui_set_next_window_pos(0, 0, ImGuiCond_Always);
    imgui_set_next_window_size(screen_size.x, EDITOR_TOP_BAR_HEIGHT, ImGuiCond_Always);
    int top_bar_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoFocusOnAppearing;
    imgui_begin("##Top bar", NULL, top_bar_flags);

    if (imgui_begin_menu_bar())
    {
        if (imgui_begin_menu("File", 1))
        {
            if (imgui_menu_item("Save", "", 0, 1))
            {
                editor_switch_state_to(STATE_SAVE);
            }
            if (imgui_menu_item("Load", "", 0, 1))
            {
                editor_switch_state_to(STATE_LOAD);
            }
            imgui_separator();
            if (imgui_menu_item("Preferences", "", 0, 1))
            {
                is_settings_opened = 1 - is_settings_opened;
            }
            imgui_separator();
            if (imgui_menu_item("Exit", "", 0, 1))
            {
                is_popup_opened = true;
            }
            imgui_end_menu();
        }

        if (imgui_begin_menu("View", 1))
        {
            imgui_checkbox("Grid", &is_grid_visible);
            imgui_checkbox("Walls", &is_walls_visible);
            imgui_checkbox("Objects", &is_objects_visible);
            imgui_end_menu();
        }

        if (imgui_begin_menu("Episode", 1))
        {
            if (imgui_menu_item("Edit", "", 0, 1))
            {
            }
            imgui_end_menu();
        }

        if (imgui_begin_menu("Help", 1))
        {
            if (imgui_menu_item("About", "", 0, 1))
            {
                is_help_opened = 1 - is_help_opened;
            }
            imgui_end_menu();
        }

        imgui_end_menu_bar();
    }

    editor_settings_window();
    editor_help_window();

    if (is_popup_opened == true)
    {
        imgui_open_popup("##Editor main popup");
    }

    int popup_modal_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;
    if (imgui_begin_popup_modals_params("##Editor main popup", NULL, popup_modal_flags))
    {
        imgui_text(_chr(editor_back_to_menu_popup_str));

        if (imgui_button_withsize("Yes", -1, MENU_WINDOW_BUTTON_HEIGHT))
        {
            is_popup_opened = false;
            episode_reset(e);
            editor_switch_state_to(STATE_MENU);
        }

        if (imgui_button_withsize("No", -1, MENU_WINDOW_BUTTON_HEIGHT))
        {
            is_popup_opened = false;
            imgui_close_current_popup();
        }

        imgui_end_popup();
    }

    imgui_end();
}

void editor_cell_tooltip(Episode *e)
{
    if (!e)
    {
        return;
    }

    if (config_current.is_cell_tooltip_enabled == false)
    {
        return;
    }

    if (is_allowed_to_draw_map() == true)
    {
        STRING *info_str = draw_cell_info(e, mouse_x, mouse_y);
        if (info_str)
        {
            imgui_set_tooltip(_chr(info_str));
            imgui_begin_tooltip();
            imgui_end_tooltip();
        }
    }
}

void editor_main_initialize(Episode *e)
{
    if (!e)
    {
        return;
    }

    Map *m = &e->map[current_map_id];
    if (!m)
    {
        return;
    }

    // asset types
    editor_main_asset_types[0] = "Walls";
    editor_main_asset_types[1] = "Props";
    editor_main_asset_types[2] = "Items";
    editor_main_asset_types[3] = "Weapons";
    editor_main_asset_types[4] = "Enemies";
    editor_main_asset_types[5] = "Bosses";

    // textures
    int i = 0;
    for (i = 0; i < MAX_WALL_TEXTURES; i++)
    {
        wall_textures_listbox[i] = asset_get_desc(ASSET_TYPE_WALL, i);
    }
    for (i = 0; i < MAX_PROPS_TEXTURES; i++)
    {
        props_textures_listbox[i] = asset_get_desc(ASSET_TYPE_PROPS, i);
    }
    for (i = 0; i < MAX_ITEM_TEXTURES; i++)
    {
        items_textures_listbox[i] = asset_get_desc(ASSET_TYPE_ITEMS, i);
    }
    for (i = 0; i < MAX_WEAPON_TEXTURES; i++)
    {
        weapons_textures_listbox[i] = asset_get_desc(ASSET_TYPE_WEAPON, i);
    }
    for (i = 0; i < MAX_ENEMY_TEXTURES; i++)
    {
        enemies_textures_listbox[i] = asset_get_desc(ASSET_TYPE_ENEMIES, i);
    }
    for (i = 0; i < MAX_BOSS_TEXTURES; i++)
    {
        bosses_textures_listbox[i] = asset_get_desc(ASSET_TYPE_BOSSES, i);
    }

    // update preview image
    editor_preview_update(ASSET_TYPE_WALL, 0);

    // weather
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
    editor_weather_refresh(e);

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

void editor_main_reset(Episode *e)
{
    if (!e)
    {
        return;
    }

    editor_asset_index = 0;
    editor_asset_type = ASSET_TYPE_WALL;
    editor_main_selected_asset_type = editor_main_asset_types[editor_asset_type];
    editor_preview_update(editor_asset_type, editor_asset_index);

    editor_weather_refresh(e);

    current_map_id = 0;

    is_settings_opened = false;
    is_help_opened = false;

    is_grid_visible = true;
    is_walls_visible = true;
    is_objects_visible = true;
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

    for (i = 0; i < screen_resolutions_total; i++)
    {
        if (graphics_resolution_available_list_str[i])
        {
            ptr_remove(graphics_resolution_available_list_str[i]);
        }
    }

    for (i = 0; i < DISPLAY_MODES_MAX; i++)
    {
        if (graphics_display_mode_list_str[i])
        {
            ptr_remove(graphics_display_mode_list_str[i]);
        }
    }
}

void editor_main_update(Episode *e)
{
    if (!e)
    {
        return;
    }

    imgui_start_imode();

    editor_side_bar(e);
    editor_top_bar(e);
    editor_cell_tooltip(e);

    imgui_end_imode();
}