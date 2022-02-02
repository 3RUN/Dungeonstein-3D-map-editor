
void map_editor_ui_initialize()
{
    int i = 0;

    // asset types
    editor_main_asset_types[0] = "Walls";
    editor_main_asset_types[1] = "Props";
    editor_main_asset_types[2] = "Items";
    editor_main_asset_types[3] = "Weapons";
    editor_main_asset_types[4] = "Enemies";
    editor_main_asset_types[5] = "Bosses";

    // textures
    for (i = 0; i < MAX_WALL_TEXTURES; i++)
    {
        wall_textures_listbox[i] = _chr(asset_get_desc(ASSET_TYPE_WALL, i));
    }
    for (i = 0; i < MAX_PROPS_TEXTURES; i++)
    {
        props_textures_listbox[i] = _chr(asset_get_desc(ASSET_TYPE_PROPS, i));
    }
    for (i = 0; i < MAX_ITEM_TEXTURES; i++)
    {
        items_textures_listbox[i] = _chr(asset_get_desc(ASSET_TYPE_ITEMS, i));
    }
    for (i = 0; i < MAX_WEAPON_TEXTURES; i++)
    {
        weapons_textures_listbox[i] = _chr(asset_get_desc(ASSET_TYPE_WEAPON, i));
    }
    for (i = 0; i < MAX_ENEMY_TEXTURES; i++)
    {
        enemies_textures_listbox[i] = _chr(asset_get_desc(ASSET_TYPE_ENEMIES, i));
    }
    for (i = 0; i < MAX_BOSS_TEXTURES; i++)
    {
        bosses_textures_listbox[i] = _chr(asset_get_desc(ASSET_TYPE_BOSSES, i));
    }

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
}

void map_editor_ui_refresh(Episode *e)
{
    if (!e)
    {
        return;
    }

    map_editor_ui_reset(e);
    map_editor_settings_refresh();
}

void map_editor_ui_reset(Episode *e)
{
    if (!e)
    {
        return;
    }

    strcpy(episode_save_name, "");

    editor_asset_index = 0;
    editor_asset_type = ASSET_TYPE_WALL;
    editor_main_selected_asset_type = editor_main_asset_types[editor_asset_type];
    editor_preview_update(editor_asset_type, editor_asset_index);

    map_editor_weather_refresh(e);

    map_id = 0;

    is_settings_opened = false;
    is_edit_episode_opened = false;
    is_help_opened = false;

    is_grid_visible = true;
    is_walls_visible = true;
    is_objects_visible = true;
}

void map_editor_ui_destroy()
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

void editor_preview_update(int type, int index)
{
    preview_bmap = asset_get_bmap(type, index);
    strcpy(preview_name, "Name: ");
    strcat(preview_name, _chr(asset_get_desc(type, index)));
}

void map_editor_settings_refresh()
{
    int i = 0;

    // resolution
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

void map_editor_settings_window()
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
        map_editor_settings_refresh();
    }

    imgui_same_line();
    imgui_align_right_with_offset(BUTTON_WIDTH * 2 + engine_theme_item_spacing[1]);

    // apply and save
    if (imgui_button_withsize("Ok", BUTTON_WIDTH, 32))
    {
        config_save_n_apply();
        map_editor_settings_refresh();
        is_settings_opened = false;
    }

    imgui_same_line();

    // cancel changes
    if (imgui_button_withsize("Cancel", BUTTON_WIDTH, 32))
    {
        config_reset_to_saved();
        map_editor_settings_refresh();
        is_settings_opened = false;
    }

    imgui_end();
}

void map_editor_edit_episode_window(Episode *e)
{
    if (!e)
    {
        return;
    }

    if (is_edit_episode_opened == false)
    {
        return;
    }

    imgui_set_next_window_pos((screen_size.x / 2) - (EPISODE_WINDOW_WIDTH / 2), (screen_size.y / 2) - (EPISODE_WINDOW_HEIGHT / 2), ImGuiCond_Appearing);
    imgui_set_next_window_size(EPISODE_WINDOW_WIDTH, EPISODE_WINDOW_HEIGHT, ImGuiCond_Appearing);
    int edit_episode_window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoSavedSettings;
    imgui_begin("Edit Episode", &is_edit_episode_opened, edit_episode_window_flags);

    imgui_text("Name");
    imgui_same_line();
    editor_help_maker(_chr(str_printf(NULL, "The name of the episode. Character limit %d.", (long)EPISODE_NAME_LENGTH)));
    imgui_push_item_width(-1);
    imgui_input_text("##Name", e->name, EPISODE_NAME_LENGTH, NULL);
    imgui_pop_item_width();

    imgui_text("Short story");
    imgui_same_line();
    editor_help_maker(_chr(str_printf(NULL, "Short episode story. Character limit %d.", (long)EPISODE_STORY_LENGTH)));
    imgui_input_text_multiline("##Multiline", e->story, EPISODE_STORY_LENGTH, -1, 128, NULL);

    imgui_text("Map count");
    imgui_same_line();
    editor_help_maker(_chr(str_printf(NULL, "Amount of maps in the episode. Max %d.", (long)MAX_MAPS_PER_EPISODE)));
    imgui_push_item_width(-1);
    imgui_slider_int("##Slider_01", &e->map_count, 1, MAX_MAPS_PER_EPISODE);
    imgui_pop_item_width();

    if (imgui_button_withsize("Close", -1, EPISODE_WINDOW_BUTTON_HEIGHT))
    {
        is_edit_episode_opened = false;
    }

    imgui_end();
}

void map_editor_help_window()
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

void map_editor_top_menu_bar(Episode *e)
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
            if (strlen(episode_save_name) > 0)
            {
                char file_name[64];
                strcpy(file_name, "Save \"");
                strcat(file_name, episode_save_name);
                strcat(file_name, "\"");

                if (imgui_menu_item(file_name, "", 0, 1))
                {
                    char save_file_name[64];
                    strcpy(save_file_name, episode_save_name);
                    strcat(save_file_name, _chr(episode_extension_str));
                    episode_save(save_file_name, e);
                }
            }
            if (imgui_menu_item("Save As", "", 0, 1))
            {
                map_editor_popup_id = MAP_EDITOR_POPUP_SAVE;
                str_cpy(editor_popup_str, editor_save_popup_str);
                is_popup_opened = true;
            }
            imgui_separator();
            if (imgui_menu_item("Preferences", "", 0, 1))
            {
                is_settings_opened = 1 - is_settings_opened;
            }
            imgui_separator();
            if (imgui_menu_item("Exit", "", 0, 1))
            {
                map_editor_popup_id = MAP_EDITOR_POPUP_EXIT;
                str_cpy(editor_popup_str, editor_back_to_menu_popup_str);
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
                is_edit_episode_opened = 1 - is_edit_episode_opened;
            }
            if (imgui_menu_item("Reset", "", 0, 1))
            {
                episode_reset(e);

                map_id = 0;

                Map *current_map = map_get_active(e);
                editor_update_grid_ents(current_map);
                map_editor_weather_refresh(e);
            }
            imgui_end_menu();
        }

        if (imgui_begin_menu("Map", 1))
        {
            if (imgui_menu_item("Reset", "", 0, 1))
            {
                Map *current_map = map_get_active(e);
                map_reset(current_map);
                editor_update_grid_ents(current_map);
                map_editor_weather_refresh(e);
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

    map_editor_settings_window();
    map_editor_edit_episode_window(e);
    map_editor_help_window();

    if (is_popup_opened == true)
    {
        imgui_open_popup("##Editor main popup");
    }

    int popup_modal_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;
    if (imgui_begin_popup_modals_params("##Editor main popup", NULL, popup_modal_flags))
    {
        var popup_width = 256;
        imgui_text(_chr(editor_popup_str));

        if (map_editor_popup_id == MAP_EDITOR_POPUP_EXIT)
        {
            if (imgui_button_withsize("Yes", -1, MENU_WINDOW_BUTTON_HEIGHT))
            {
                is_popup_opened = false;
                editor_switch_state_to(STATE_EXIT_EDITOR);
            }

            if (imgui_button_withsize("No", -1, MENU_WINDOW_BUTTON_HEIGHT))
            {
                is_popup_opened = false;
                imgui_close_current_popup();
            }
        }
        else if (map_editor_popup_id == MAP_EDITOR_POPUP_SAVE)
        {
            imgui_push_item_width(-1);
            imgui_input_text_with_hint("##File Name", "name", episode_save_name, EPISODE_SAVE_NAME_LENGTH, NULL);
            imgui_pop_item_width();

            var button_width = ((popup_width - (engine_theme_win_padding[0] * 2)) / 2) - 2.5;

            if (imgui_button_withsize("Save", button_width, MENU_WINDOW_BUTTON_HEIGHT))
            {
                if (strlen(episode_save_name) > 0)
                {
                    char save_file_name[64];
                    strcpy(save_file_name, episode_save_name);
                    strcat(save_file_name, _chr(episode_extension_str));
                    episode_save(save_file_name, e);

                    is_popup_opened = false;
                    map_episode_save_failed = false;
                    imgui_close_current_popup();
                }
                else
                {
                    map_episode_save_failed = true;
                }
            }
            imgui_same_line();
            if (imgui_button_withsize("Cancel", button_width, MENU_WINDOW_BUTTON_HEIGHT))
            {
                is_popup_opened = false;
                map_episode_save_failed = false;
                imgui_close_current_popup();
            }

            if (map_episode_save_failed == true)
            {
                imgui_push_style_color(ImGuiCol_TextDisabled, color4_red);
                imgui_text_disabled("  You forgot to enter file name!");
                imgui_pop_style_color(1);
            }
        }

        imgui_end_popup();
    }

    imgui_end();
}

void map_editor_weather_refresh(Episode *e)
{
    if (!e)
    {
        return;
    }

    Map *m = map_get_active(e);
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
}

void map_editor_side_menu(Episode *e)
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
                if (imgui_list_box("##Weapon Texture listbox", &editor_asset_index, weapons_textures_listbox, MAX_WEAPON_TEXTURES, MAX_WEAPON_TEXTURES))
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
                if (imgui_list_box("##Enemies Texture listbox", &editor_asset_index, enemies_textures_listbox, MAX_ENEMY_TEXTURES, MAX_ENEMY_TEXTURES))
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
                if (imgui_list_box("##Bosses Texture listbox", &editor_asset_index, bosses_textures_listbox, MAX_BOSS_TEXTURES, MAX_BOSS_TEXTURES))
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
            map_id--;
            map_id = clamp(map_id, 0, e->map_count - 1);

            Map *previous_map = map_get_active(e);
            editor_update_grid_ents(previous_map);
            map_editor_weather_refresh(e);
        }
        imgui_same_line();
        imgui_text(_chr(str_printf(NULL, "%d", (long)(map_id + 1))));
        imgui_same_line();
        if (imgui_arrow_button("Increase", ImGuiDir_Right))
        {
            map_id++;
            map_id = clamp(map_id, 0, e->map_count - 1);

            Map *next_map = map_get_active(e);
            editor_update_grid_ents(next_map);
            map_editor_weather_refresh(e);
        }
        map_id = clamp(map_id, 0, e->map_count - 1);

        imgui_text("Total map count:");
        imgui_same_line();
        imgui_align_right_with_offset(31);
        imgui_text(_chr(str_for_num(NULL, e->map_count)));
        imgui_separator();

        imgui_text(_chr(str_printf(NULL, "Mouse pos x = %d; y = %d;", (long)mouse_x, (long)mouse_y)));
        imgui_text(_chr(str_printf(NULL, "Map size: width = %d; height = %d;", (long)MAP_WIDTH, (long)MAP_HEIGHT)));
        imgui_separator();

        // get currently active map
        Map *current_map = map_get_active(e);
        if (!current_map)
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
                    current_map->weather_id = i;
                    str_cpy(weather_currently_used_str, weather_list_str[i]);
                    map_editor_weather_refresh(e);
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
        imgui_slider_var("##Fog start slider", &current_map->fog_start, 0, current_map->fog_end);
        current_map->fog_start = clamp(current_map->fog_start, 0, current_map->fog_end);
        editor_create_tooltip("Fog starting distance in quants.\nShould be smaller than 'end'.");

        imgui_text("Fog end:   ");
        imgui_same_line();
        imgui_slider_var("##Fog end slider", &current_map->fog_end, current_map->fog_start, 2048);
        current_map->fog_end = clamp(current_map->fog_end, current_map->fog_start, 2048);
        editor_create_tooltip("Fog end distance in quants.\nShould be higher than 'start'.");
        imgui_pop_item_width();

        imgui_text("Fog color: ");
        imgui_same_line();
        var avail_picker_width = imgui_get_content_region_avail_width();
        imgui_push_item_width(avail_picker_width);
        static int misc_flags = ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoDragDrop;
        imgui_color_edit3("##Fog color picker", current_map->fog_color, misc_flags);
        imgui_pop_item_width();
        imgui_separator();

        imgui_text("Sky color: ");
        imgui_same_line();
        var avail_picker_width = imgui_get_content_region_avail_width();
        imgui_push_item_width(avail_picker_width);
        static int misc_flags = ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoDragDrop;
        imgui_color_edit3("##Sky color picker", current_map->sky_color, misc_flags);
        imgui_pop_item_width();
        imgui_separator();

        // music
        imgui_text("Music:");
        imgui_same_line();
        int len = strlen(current_map->music);
        imgui_push_item_width(140);
        imgui_input_text("##Textbox", current_map->music, len, ImGuiInputTextFlags_ReadOnly | ImGuiInputTextFlags_AutoSelectAll);
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

    Map *m = map_get_active(e);
    if (!m)
    {
        return;
    }

    if (is_allowed_to_draw() == true)
    {
        STRING *info_str = draw_cell_info(m, mouse_x, mouse_y);
        if (info_str)
        {
            imgui_set_tooltip(_chr(info_str));
            imgui_begin_tooltip();
            imgui_end_tooltip();
        }
    }
}