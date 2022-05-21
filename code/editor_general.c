
void editor_load_config(Config *config)
{
    if (!config)
    {
        return;
    }

    input_remove_on_key_binding(scancode_toggle_asset_list);
    input_remove_on_key_binding(scancode_toggle_lights);
    input_remove_on_key_binding(scancode_toggle_drawmode);

    scancode_toggle_asset_list = engine_key_return_scancode_from_letter(config->input_toggle_assets);
    scancode_toggle_lights = engine_key_return_scancode_from_letter(config->input_toggle_lights);
    scancode_toggle_drawmode = engine_key_return_scancode_from_letter(config->input_toggle_draw_mode);

    input_update_on_key_binding(scancode_toggle_asset_list, editor_toggle_asset_list);
    input_update_on_key_binding(scancode_toggle_lights, editor_toggle_lights);
    input_update_on_key_binding(scancode_toggle_drawmode, editor_toggle_drawmode);
}

void editor_toggle_asset_list()
{
    if (is_popup_opened == true)
    {
        if (is_asset_list_visible == true)
        {
            is_asset_list_visible = false;
            is_popup_opened = false;
        }
        return;
    }

    if (editor_state != EDITOR_STATE_EDIT)
    {
        return;
    }

    if (is_map_settings_visible == true)
    {
        return;
    }

    is_asset_list_visible = 1 - is_asset_list_visible;

    if (is_asset_list_visible == true)
    {
        category_button_id = category_last_id;
        drawing_mode = drawing_mode_last;
        is_popup_opened = true;
        editor_switch_popup_to(EDITOR_POPUP_STATE_ASSET_LIST);
    }
}

void editor_toggle_lights()
{
    if (is_popup_opened == true || is_asset_list_visible == true)
    {
        return;
    }

    if (editor_state != EDITOR_STATE_EDIT)
    {
        return;
    }

    if (is_map_settings_visible == true)
    {
        return;
    }

    is_lights_on = 1 - is_lights_on;
}

void editor_toggle_drawmode()
{
    if (is_topbar_used == true || is_sidebuttons_used == true)
    {
        return false;
    }

    if (is_popup_opened == true || is_asset_list_visible == true)
    {
        return false;
    }

    if (editor_state != EDITOR_STATE_EDIT)
    {
        return false;
    }

    if (is_map_settings_visible == true)
    {
        return false;
    }

    if (is_pos_within_camera(vector(mouse_pos.x, mouse_pos.y, 0)) == false)
    {
        return false;
    }

    drawing_mode = cycle(drawing_mode + 1, 0, 2);
    drawing_mode_last = drawing_mode;

    if (drawing_mode == 0)
    {
        category_button_id = ASSET_LIST_BUTTON_ID_WALL;
        category_last_id = category_button_id;
    }
    else if (drawing_mode == 1)
    {
        category_button_id = ASSET_LIST_BUTTON_ID_OBJECT;
        category_last_id = category_button_id;
    }
}

void editor_popups(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    if (is_popup_opened == true)
    {
        imgui_open_popup("##editor popup id");
    }

    int editor_pause_popup_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;
    if (imgui_begin_popup_modals_params("##editor popup id", NULL, editor_pause_popup_flags))
    {
        switch (editor_popup_state)
        {
        case EDITOR_POPUP_STATE_OPEN:
            popup_open(episode);
            break;

        case EDITOR_POPUP_STATE_NEW:
            popup_new(episode);
            break;

        case EDITOR_POPUP_STATE_SETTINGS:
            popup_settings();
            break;

        case EDITOR_POPUP_STATE_EXIT:
            popup_exit();
            break;

        case EDITOR_POPUP_STATE_WAIT_FOR_INPUT:
            popup_wait_for_input();
            break;

        case EDITOR_POPUP_STATE_CONFIRM_OPEN:
            popup_confirm_open();
            break;

        case EDITOR_POPUP_STATE_CONFIRM_NEW:
            popup_confirm_new();
            break;

        case EDITOR_POPUP_STATE_SAVE_AS:
            popup_save_as(episode);
            break;

        case EDITOR_POPUP_STATE_EP_RESET:
            popup_ep_reset(episode);
            break;

        case EDITOR_POPUP_STATE_EP_EDIT:
            popup_ep_edit(episode);
            break;

        case EDITOR_POPUP_STATE_MAP_RESET:
            Map *map = map_get_active(episode);
            popup_map_reset(map);
            break;

        case EDITOR_POPUP_STATE_HELP:
            popup_help();
            break;

        case EDITOR_POPUP_STATE_ASSET_LIST:
            popup_asset_list();
            break;

        case EDITOR_POPUP_STATE_MUSIC_BROWSER:
            popup_music_browser();
            break;
        }
        imgui_end_popup();
    }
}

void editor_topbar(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    imgui_set_next_window_pos(0, 0, ImGuiCond_Always);
    imgui_set_next_window_size(screen_size.x, EDITOR_TOP_BAR_HEIGHT * config_saved.font_scale, ImGuiCond_Always);
    int top_bar_window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoFocusOnAppearing;
    imgui_begin("##editor topbar window id", NULL, top_bar_window_flags);

    is_topbar_used = false;

    if (imgui_begin_menu_bar())
    {
        if (imgui_begin_menu("File", 1))
        {
            is_topbar_used = true;

            if (imgui_menu_item("Open", "", 0, 1))
            {
                editor_switch_popup_to(EDITOR_POPUP_STATE_CONFIRM_OPEN);
            }
            if (imgui_menu_item("New", "", 0, 1))
            {
                editor_switch_popup_to(EDITOR_POPUP_STATE_CONFIRM_NEW);
            }
            imgui_separator();
            if (imgui_menu_item("Save", "", 0, 1))
            {
                STRING *temp_ep_name_str = "";
                str_cpy(temp_ep_name_str, ep_filename);
                str_cat(temp_ep_name_str, " saved.");
                message_add(temp_ep_name_str);

                episode_save(ep_filename, &def_episode);
            }
            if (imgui_menu_item("Save as", "", 0, 1))
            {
                strcpy(save_as_filename, ep_filename);
                editor_switch_popup_to(EDITOR_POPUP_STATE_SAVE_AS);
            }
            imgui_separator();
            if (imgui_menu_item("Settings", "", 0, 1))
            {
                editor_switch_popup_to(EDITOR_POPUP_STATE_SETTINGS);
            }
            imgui_separator();
            if (imgui_menu_item("Exit", "", 0, 1))
            {
                editor_switch_popup_to(EDITOR_POPUP_STATE_EXIT);
            }
            imgui_end_menu();
        }

        if (imgui_begin_menu("View", 1))
        {
            is_topbar_used = true;

            if (imgui_checkbox("d3d_lines", &is_d3d_lines_visible))
            {
                d3d_lines = is_d3d_lines_visible;
            }
            imgui_checkbox("Grid", &is_grid_visible);
            imgui_checkbox("Debug panel", &is_debug_panel_visible);
            imgui_checkbox("Cell connections", &is_cell_links_visible);
            imgui_checkbox("Lighting", &is_lights_on);
            if (imgui_checkbox("Object markers", &is_markers_visible))
            {
                map_toggle_marker_visibility(is_markers_visible);
            }
            if (imgui_checkbox("Bounding boxes", &is_bbox_visible))
            {
                map_toggle_bbox_visibility(is_bbox_visible);
            }
            imgui_checkbox("Hovering object", &is_selected_cell_visible);
            imgui_checkbox("Mouse cell", &is_mouse_cell_visible);
            imgui_end_menu();
        }

        if (imgui_begin_menu("Episode", 1))
        {
            is_topbar_used = true;

            if (imgui_menu_item("Reset", "", 0, 1))
            {
                editor_switch_popup_to(EDITOR_POPUP_STATE_EP_RESET);
            }
            if (imgui_menu_item("Edit", "", 0, 1))
            {
                strcpy(episode_edit_name, episode->name);
                episode_edit_map_count = episode->map_count;
                editor_switch_popup_to(EDITOR_POPUP_STATE_EP_EDIT);
            }
            imgui_end_menu();
        }

        if (imgui_begin_menu("Map", 1))
        {
            is_topbar_used = true;

            if (imgui_menu_item("Reset", "", 0, 1))
            {
                editor_switch_popup_to(EDITOR_POPUP_STATE_MAP_RESET);
            }
            if (imgui_menu_item("Copy", "", 0, 1))
            {
                message_add(str_printf(NULL, "Copied map %d", (long)active_map_id));

                is_map_copied = true;
                Map *map = map_get_active(episode);
                map_copy(&map_copied, map);
            }
            if (is_map_copied == true)
            {
                if (imgui_menu_item("Paste", "", 0, 1))
                {
                    message_add(str_printf(NULL, "Pasted copied map into %d", (long)active_map_id));

                    Map *map = map_get_active(episode);
                    map_copy(map, &map_copied);
                    map_load(map);
                }
            }
            imgui_separator();
            if (imgui_menu_item("Prior map", "", 0, 1))
            {
                map_prior();
            }
            if (imgui_menu_item("Next map", "", 0, 1))
            {
                map_next();
            }
            imgui_separator();
            if (imgui_menu_item("Shift West", "", 0, 1))
            {
                map_shift_west();
            }
            if (imgui_menu_item("Shift East", "", 0, 1))
            {
                map_shift_east();
            }
            if (imgui_menu_item("Shift South", "", 0, 1))
            {
                map_shift_south();
            }
            if (imgui_menu_item("Shift North", "", 0, 1))
            {
                map_shift_north();
            }
            imgui_separator();
            if (imgui_menu_item("Settings", "", 0, 1))
            {
                Map *active_map = map_get_active(&def_episode);
                map_copy(&map_settings, active_map);

                is_map_settings_visible = 1 - is_map_settings_visible;
            }
            imgui_end_menu();
        }

        if (imgui_begin_menu("About", 1))
        {
            is_topbar_used = true;

            if (imgui_menu_item("Help", "", 0, 1))
            {
                editor_switch_popup_to(EDITOR_POPUP_STATE_HELP);
            }
            imgui_end_menu();
        }

        imgui_end_menu_bar();
    }

    imgui_end();
}

void editor_map_settings(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    if (is_map_settings_visible == false)
    {
        return;
    }

    imgui_set_next_window_pos(screen_size.x - (MAP_SETTINGS_WINDOW_WIDTH * config_saved.font_scale) - 8, screen_size.y - (MAP_SETTINGS_WINDOW_HEIGHT * config_saved.font_scale) - 8, ImGuiCond_Always);
    imgui_set_next_window_size(MAP_SETTINGS_WINDOW_WIDTH * config_saved.font_scale, MAP_SETTINGS_WINDOW_HEIGHT * config_saved.font_scale, ImGuiCond_Always);
    int settings_window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoSavedSettings;
    imgui_begin("Map settings", &is_map_settings_visible, settings_window_flags);
    imgui_separator();
    imgui_text_disabled_centered(_chr(str_printf(NULL, "Opened map id: %d", (long)active_map_id)));
    imgui_same_line();
    if (imgui_arrow_button("##prior map button", ImGuiDir_Left))
    {
        map_prior();

        Map *active_map = map_get_active(episode);
        map_copy(&map_settings, active_map);
    }
    imgui_same_line();
    if (imgui_arrow_button("##next map button", ImGuiDir_Right))
    {
        map_next();

        Map *active_map = map_get_active(episode);
        map_copy(&map_settings, active_map);
    }
    imgui_separator();

    // fog settings
    imgui_text("Fog start:    ");
    imgui_same_line();
    var avail_slider_width = imgui_get_content_region_avail_width();
    imgui_push_item_width(avail_slider_width);
    imgui_slider_var("##map settings fog start slider id", &map_settings.fog_start, 0, map_settings.fog_end);
    map_settings.fog_start = clamp(map_settings.fog_start, 0, map_settings.fog_end);
    imgui_create_tooltip("Fog starting distance in quants.\nShould be smaller than 'end'.");

    imgui_text("Fog end:      ");
    imgui_same_line();
    imgui_slider_var("##map settings fog end slider id", &map_settings.fog_end, maxv(map_settings.fog_start, 32), MAP_FOG_END_MAX);
    map_settings.fog_end = clamp(map_settings.fog_end, maxv(map_settings.fog_start, 32), MAP_FOG_END_MAX);
    imgui_create_tooltip("Fog end distance in quants.\nShould be higher than 'start'.");
    imgui_pop_item_width();

    imgui_text("Fog color:    ");
    imgui_same_line();
    var avail_picker_width = imgui_get_content_region_avail_width();
    imgui_push_item_width(avail_picker_width);
    static int fog_color_misc_flags = ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_NoDragDrop;
    imgui_color_edit3("##map settings fog color picker id", map_settings.fog_color, fog_color_misc_flags);
    imgui_pop_item_width();
    imgui_separator();

    // music
    imgui_text("Music:        ");
    imgui_same_line();
    int len = strlen(map_settings.music);
    imgui_push_item_width(MAP_SETTINGS_MUSIC_NAME_INPUT_WIDTH);
    imgui_input_text("##map settings music name input id", map_settings.music, len, ImGuiInputTextFlags_ReadOnly | ImGuiInputTextFlags_AutoSelectAll);
    imgui_pop_item_width();
    imgui_same_line();
    if (imgui_button_withsize("Browser", -1, MAP_SETTINGS_MUSIC_BROWSE_BUTTON_HEIGHT))
    {
        editor_switch_popup_to(EDITOR_POPUP_STATE_MUSIC_BROWSER);
    }
    imgui_separator();

    var width = (((MAP_SETTINGS_WINDOW_WIDTH * config_saved.font_scale) - (engine_theme_win_padding[0] * 2)) / 5) - 3;
    if (imgui_button_withsize("Defaults", width, MAP_SETTINGS_BUTTON_HEIGHT * config_saved.font_scale)) // reset current level settings
    {
        map_settings.fog_start = MAP_DEF_FOG_START;
        map_settings.fog_end = MAP_DEF_FOG_END;

        strcpy(map_settings.music, "");

        int i = 0;
        for (i = 0; i < 3; i++)
        {
            map_settings.fog_color[i] = get_hsv_from_color(MAP_DEF_FOG_COLOR);
        }
    }

    // reset to previous ones
    imgui_same_line();
    if (imgui_button_withsize("Reset", width, MAP_SETTINGS_BUTTON_HEIGHT * config_saved.font_scale))
    {
        Map *active_map = map_get_active(episode);
        map_copy(&map_settings, active_map);
    }

    // apply settings
    imgui_same_line();
    if (imgui_button_withsize("Apply", width, MAP_SETTINGS_BUTTON_HEIGHT * config_saved.font_scale))
    {
        Map *active_map = map_get_active(episode);
        map_copy(active_map, &map_settings);
    }

    // apply and return back to the editor mode
    imgui_same_line();
    if (imgui_button_withsize("Ok", width, MAP_SETTINGS_BUTTON_HEIGHT * config_saved.font_scale))
    {
        Map *active_map = map_get_active(episode);
        map_copy(active_map, &map_settings);

        is_map_settings_visible = false;
    }

    // reset to previous ones and close
    imgui_same_line();
    if (imgui_button_withsize("Back", width, MAP_SETTINGS_BUTTON_HEIGHT * config_saved.font_scale))
    {
        Map *active_map = map_get_active(episode);
        map_copy(&map_settings, active_map);

        is_map_settings_visible = false;
    }

    imgui_end();
}

void editor_asset_category_button(void *draw_list, STRING *category, BMAP *texture, int index)
{
    if (!draw_list)
    {
        return;
    }

    VECTOR cursor_screen_pos;
    vec_set(&cursor_screen_pos, imgui_get_cursor_screen_pos());

    int is_temp_boolean = false;
    if (drawing_mode == DRAWING_MODE_MAP && index <= ASSET_LIST_BUTTON_ID_FLOOR || drawing_mode == DRAWING_MODE_OBJECT && index == ASSET_LIST_BUTTON_ID_OBJECT)
    {
        is_temp_boolean = true;
    }

    STRING *selectable_id_str = "";
    str_cpy(selectable_id_str, "##index");
    str_cat(selectable_id_str, str_for_num(NULL, index));
    if (imgui_selectable_size(_chr(selectable_id_str), &is_temp_boolean, ImGuiSelectableFlags_None, vector(ASSET_PREVIEW_TEXTURE_WIDTH * config_saved.font_scale, ASSET_PREVIEW_TEXTURE_HEIGHT * config_saved.font_scale, 0)))
    {
        category_button_id = index;
        category_last_id = category_button_id;
        is_asset_list_visible = true;

        editor_switch_popup_to(EDITOR_POPUP_STATE_ASSET_LIST);

        if (index <= ASSET_LIST_BUTTON_ID_FLOOR)
        {
            drawing_mode = DRAWING_MODE_MAP;
        }
        else
        {
            drawing_mode = DRAWING_MODE_OBJECT;
        }
        drawing_mode_last = drawing_mode;
    }

    var image_start_x = cursor_screen_pos.x;
    var image_start_y = cursor_screen_pos.y;
    var image_end_x = image_start_x + (ASSET_PREVIEW_TEXTURE_WIDTH * config_saved.font_scale);
    var image_end_y = image_start_y + (ASSET_PREVIEW_TEXTURE_HEIGHT * config_saved.font_scale);
    imgui_drawlist_add_image(draw_list, texture, vector(image_start_x, image_start_y, 0), vector(image_end_x, image_end_y, 0), vector(0, 0, 0), vector(1, 1, 0), color4_image, 1);

    var rect_padding_start = 4 * config_saved.font_scale;
    var rect_padding_end = 16 * config_saved.font_scale;
    var text_pos_x = image_start_x + rect_padding_start;
    var text_pos_y = image_start_y + rect_padding_start;
    var text_padding = 2 * config_saved.font_scale;
    imgui_drawlist_add_rect_filled(draw_list, vector(text_pos_x - rect_padding_start, text_pos_y - rect_padding_start, 0), vector(text_pos_x + rect_padding_end, text_pos_y + rect_padding_end, 0), color4_black, 0);
    imgui_drawlist_add_text(draw_list, vector(text_pos_x + text_padding, text_pos_y, 0), color4_white, _chr(category));
}

void editor_asset_category_buttons_update()
{
    if (is_map_settings_visible == true)
    {
        return;
    }

    var window_height = (ASSET_PREVIEW_TEXTURE_HEIGHT * 4 * config_saved.font_scale) + 96;

    imgui_set_next_window_pos(0, (screen_size.y / 2) - (window_height / 2), ImGuiCond_Always);
    imgui_set_next_window_size(-1, -1, ImGuiCond_Always);
    int category_button_window_flags = ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoFocusOnAppearing;
    if (imgui_begin("##category buttons", NULL, category_button_window_flags))
    {
        imgui_text("Mode:");
        imgui_radiobutton("Map", &drawing_mode, DRAWING_MODE_MAP);
        imgui_radiobutton("Object", &drawing_mode, DRAWING_MODE_OBJECT);

        asset_list_categories_draw = imgui_get_window_draw_list();
        editor_asset_category_button(asset_list_categories_draw, "W", asset_get_texture(ASSET_WALLS, preview_cell.wall_index), 0);
        editor_asset_category_button(asset_list_categories_draw, "C", asset_get_texture(ASSET_FLOORS, preview_cell.ceiling_index), 1);
        editor_asset_category_button(asset_list_categories_draw, "F", asset_get_texture(ASSET_FLOORS, preview_cell.floor_index), 2);
        editor_asset_category_button(asset_list_categories_draw, "O", asset_get_texture(preview_cell.object.type, preview_cell.object.index), 3);

        is_sidebuttons_used = false;
        if (imgui_is_window_hovered() || imgui_is_any_item_hoverd() || imgui_is_any_item_active())
        {
            is_sidebuttons_used = true;
        }

        imgui_end();
    }
}

void editor_get_cell_info(Cell *cell, STRING **out)
{
    if (!cell)
    {
        return;
    }

    VECTOR cell_pos;
    vec_set(&cell_pos, &cell->pos);

    Object *object = &cell->object;

    var pan = object->pan;

    int is_occupied = object->is_occupied;
    int type = object->type;
    int index = object->index;

    int flag_0 = object->flag[0];
    int flag_1 = object->flag[1];
    int flag_2 = object->flag[2];
    int flag_3 = object->flag[3];

    str_printf(*out, "world pos:\nx = %d;\ny = %d;\nz = %d;", (long)cell_pos.x, (long)cell_pos.y, (long)cell_pos.z);

    if (is_rotatable(type, index))
    {
        str_cat(*out, str_printf(NULL, "\n\npan = %.0f;\n", (double)pan));
    }
    else
    {
        str_cat(*out, "\n\npan = none;\n");
    }

    if (type == ASSET_EVENTS)
    {
        str_cat(*out, "\ntype:\n* event;");

        if (index == EVENTS_PLAYER)
        {
            str_cat(*out, "\n\nindex:\n* player spawn;\n\nstarting weapon:");

            if (object->flag[0] == 0)
            {
                str_cat(*out, "\n* default;");
            }
            else if (object->flag[1] == 1)
            {
                str_cat(*out, "\n* pistol;");
            }
            else if (object->flag[2] == 2)
            {
                str_cat(*out, "\n* shotgun;");
            }
            else if (object->flag[3] == 3)
            {
                str_cat(*out, "\n* chaingun;");
            }
            else if (object->flag[4] == 4)
            {
                str_cat(*out, "\n* rocketlauncher;");
            }
        }
        else if (index == EVENTS_LEVEL_FINISH)
        {
            str_cat(*out, "\n\nindex:\n* level finish;\n\nparams: \n* none;");
        }
        else if (index == EVENTS_TRIGGER_ZONE)
        {
            str_cat(*out, str_printf(NULL, "\n\nindex:\n* trigger zone;\n\nparams: \n* id %d;", (long)flag_1));
        }
        else if (index == EVENTS_OBJECT_SPAWN_POINT)
        {
            str_cat(*out, "\n\nindex:\n* spawn object;");

            if (flag_2 == 0) // item
            {
                str_cat(*out, "\n\ncategory = item;\nobject = ");

                int i = 0;
                for (i = 0; i < MAX_SPAWN_ITEMS; i++)
                {
                    if (flag_3 == i)
                    {
                        str_cat(*out, spawn_item_list_str[i]);
                    }
                }
                str_cat(*out, ";");
            }
            else if (flag_2 == 1) // enemy
            {
                str_cat(*out, "\n\ncategory = enemy;\nobject = ");

                int i = 0;
                for (i = 0; i < MAX_SPAWN_ENEMIES; i++)
                {
                    if (flag_3 == i)
                    {
                        str_cat(*out, spawn_enemies_list_str[i]);
                    }
                }
                str_cat(*out, ";");
            }
            else if (flag_2 == 2) // boss
            {
                str_cat(*out, "\n\ncategory = boss;\nobject = ");

                int i = 0;
                for (i = 0; i < MAX_SPAWN_BOSSES; i++)
                {
                    if (flag_3 == i)
                    {
                        str_cat(*out, spawn_bosses_list_str[i]);
                    }
                }
                str_cat(*out, ";");
            }

            str_cat(*out, "\n\nactivation: \n");

            if (flag_0 == 0) // on creation
            {
                str_cat(*out, "* on creation;");
            }
            else if (flag_0 == 1) // switch
            {
                str_cat(*out, str_printf(NULL, "* switch id %d;", (long)flag_1));
            }
            else if (flag_0 == 2) // trigger zone
            {
                str_cat(*out, str_printf(NULL, "* trigger zone id %d;", (long)flag_1));
            }
        }
        else if (index == EVENTS_SECRET_WALL)
        {
            str_cat(*out, "\n\nindex:\n* secret wall;\n\nactivation: \n");

            if (flag_0 == 0) // on creation
            {
                str_cat(*out, "* interaction;");
            }
            else if (flag_0 == 1) // switch
            {
                str_cat(*out, str_printf(NULL, "* switch id %d;", (long)flag_1));
            }
            else if (flag_0 == 2) // trigger zone
            {
                str_cat(*out, str_printf(NULL, "* trigger zone id %d;", (long)flag_1));
            }
        }
        else if (index == EVENTS_TELEPORT_IN)
        {
            str_cat(*out, str_printf(NULL, "\n\nindex:\n* teleport IN;\n\nparams: \n* id %d;", (long)flag_1));
        }
        else if (index == EVENTS_TELEPORT_OUT)
        {
            str_cat(*out, str_printf(NULL, "\n\nindex:\n* teleport OUT;\n\nparams: \n* id %d;", (long)flag_1));
        }
    }
    else if (type == ASSET_PROPS)
    {
        str_cat(*out, "\ntype:\n* props;");

        if (index == PROPS_LIGHT)
        {
            str_cat(*out, "\n\nindex:\n* light source;\n\nlightstyle:\n* ");

            int i = 0;
            for (i = 0; i < MAX_LIGHTSTYLES; i++)
            {
                if (flag_0 == i)
                {
                    str_cat(*out, lightstyle_list_str[i]);
                }
            }
            str_cat(*out, ";");
        }
        else if (index == PROPS_COLUMN)
        {
            str_cat(*out, "\n\nindex:\n* column;\n\nparams: \n* none;");
        }
        else if (index == PROPS_BARREL)
        {
            str_cat(*out, "\n\nindex:\n* barrel;\n\nparams: \n* none;");
        }
        else if (index == PROPS_TABLE)
        {
            str_cat(*out, "\n\nindex:\n* table;\n\nparams: \n* none;");
        }
        else if (index == PROPS_VASE)
        {
            str_cat(*out, "\n\nindex:\n* vase;\n\nparams: \n* none;");
        }
        else if (index == PROPS_DOOR)
        {
            str_cat(*out, "\n\nindex:\n* door;\n\nactivation: \n");

            if (flag_0 == 0) // on creation
            {
                str_cat(*out, "* interaction;");
            }
            else if (flag_0 == 1) // key
            {
                if (flag_1 == 0)
                {
                    str_cat(*out, "* key blue;");
                }
                else if (flag_1 == 1)
                {
                    str_cat(*out, "* key red;");
                }
                else if (flag_1 == 2)
                {
                    str_cat(*out, "* key yellow;");
                }
            }
            else if (flag_0 == 2) // switch
            {
                str_cat(*out, str_printf(NULL, "* switch id %d;", (long)flag_1));
            }
            else if (flag_0 == 3) // trigger zone
            {
                str_cat(*out, str_printf(NULL, "* trigger zone id %d;", (long)flag_1));
            }
            else if (flag_0 == 4) // static
            {
                str_cat(*out, "* none (static);");
            }
        }
        else if (index == PROPS_GATE)
        {
            str_cat(*out, "\n\nindex:\n* gate;\n\nactivation: \n");

            if (flag_0 == 0) // none
            {
                str_cat(*out, "* none (static);");
            }
            else if (flag_0 == 1) // switch
            {
                str_cat(*out, str_printf(NULL, "* switch id %d;", (long)flag_1));
            }
            else if (flag_0 == 2) // trigger zone
            {
                str_cat(*out, str_printf(NULL, "* trigger zone id %d;", (long)flag_1));
            }
        }
        else if (index == PROPS_CEILING_SUPPORT)
        {
            str_cat(*out, "\n\nindex:\n* ceiling support;\n\nparams: \n* none;");
        }
        else if (index == PROPS_WINDOW_BLOCK || index == PROPS_WINDOW_BRICK_BLUE || index == PROPS_WINDOW_BRICK_RED || index == PROPS_WINDOW_BRICK_GREY || index == PROPS_WINDOW_DIRT || index == PROPS_WINDOW_METAL)
        {
            str_cat(*out, "\n\nindex:\n* window;\n\nparams: \n* none;");
        }
        else if (index == PROPS_DECOR_ON_WALL)
        {
            str_cat(*out, "\n\nindex:\n* decor on wall;\n\nparams: \n* none;");
        }
        else if (index == PROPS_SWITCH)
        {
            str_cat(*out, str_printf(NULL, "\n\nindex:\n* switch;\n\nparams: \n* id %d;", (long)flag_1));
        }
    }
    else if (type == ASSET_ITEMS)
    {
        str_cat(*out, "\ntype:\n* items;");

        if (index == ITEMS_KEY_BLUE)
        {
            str_cat(*out, "\n\nindex:\n* key blue;\n\nparams: \n* none;");
        }
        else if (index == ITEMS_KEY_RED)
        {
            str_cat(*out, "\n\nindex:\n* key red;\n\nparams: \n* none;");
        }
        else if (index == ITEMS_KEY_YELLOW)
        {
            str_cat(*out, "\n\nindex:\n* key yellow;\n\nparams: \n* none;");
        }
        else if (index == ITEMS_HEALTH_BONUS)
        {
            str_cat(*out, "\n\nindex:\n* health bonus;\n\nparams: \n* none;");
        }
        else if (index == ITEMS_MEDKIT_SMALL)
        {
            str_cat(*out, "\n\nindex:\n* medkit small;\n\nparams: \n* none;");
        }
        else if (index == ITEMS_MEDKIT_BIG)
        {
            str_cat(*out, "\n\nindex:\n* medkit big;\n\nparams: \n* none;");
        }
        else if (index == ITEMS_AMMO_BULLETS_SMALL)
        {
            str_cat(*out, "\n\nindex:\n* bullets small;\n\nparams: \n* none;");
        }
        else if (index == ITEMS_AMMO_BULLETS_BIG)
        {
            str_cat(*out, "\n\nindex:\n* bullets big;\n\nparams: \n* none;");
        }
        else if (index == ITEMS_AMMO_SHELLS_SMALL)
        {
            str_cat(*out, "\n\nindex:\n* shells small;\n\nparams: \n* none;");
        }
        else if (index == ITEMS_AMMO_SHELLS_BIG)
        {
            str_cat(*out, "\n\nindex:\n* shells big;\n\nparams: \n* none;");
        }
        else if (index == ITEMS_AMMO_ROCKETS_SMALL)
        {
            str_cat(*out, "\n\nindex:\n* rockets small;\n\nparams: \n* none;");
        }
        else if (index == ITEMS_AMMO_ROCKETS_BIG)
        {
            str_cat(*out, "\n\nindex:\n* rockets big;\n\nparams: \n* none;");
        }
        else if (index == ITEMS_TREASURE)
        {
            str_cat(*out, "\n\nindex:\n* treasure;\n\nparams: \n* none;");
        }
        else if (index == ITEMS_POWERUP_MAP)
        {
            str_cat(*out, "\n\nindex:\n* powerup map;\n\nparams: \n* none;");
        }
        else if (index == ITEMS_POWERUP_SUIT)
        {
            str_cat(*out, "\n\nindex:\n* powerup suit;\n\nparams: \n* none;");
        }
        else if (index == ITEMS_POWERUP_CHICKEN)
        {
            str_cat(*out, "\n\nindex:\n* powerup chicken;\n\nparams: \n* none;");
        }
        else if (index == ITEMS_POWERUP_LANTERN)
        {
            str_cat(*out, "\n\nindex:\n* powerup lantern;\n\nparams: \n* none;");
        }
        else if (index == ITEMS_POWERUP_MUSHROOM)
        {
            str_cat(*out, "\n\nindex:\n* powerup mushroom;\n\nparams: \n* none;");
        }
        else if (index == ITEMS_WEAPON_PISTOL)
        {
            str_cat(*out, "\n\nindex:\n* pistol;\n\nparams: \n* none;");
        }
        else if (index == ITEMS_WEAPON_SHOTGUN)
        {
            str_cat(*out, "\n\nindex:\n* shotgun;\n\nparams: \n* none;");
        }
        else if (index == ITEMS_WEAPON_CHAINGUN)
        {
            str_cat(*out, "\n\nindex:\n* chaingun;\n\nparams: \n* none;");
        }
        else if (index == ITEMS_WEAPON_ROCKETLAUNCHER)
        {
            str_cat(*out, "\n\nindex:\n* rocketlauncher;\n\nparams: \n* none;");
        }
    }
    else if (type == ASSET_ENEMIES)
    {
        str_cat(*out, "\ntype:\n* enemies;");

        if (index == ASSET_ENEMY_BAT)
        {
            str_cat(*out, "\n\nindex:\n* bat;\n\nparams: \n* none;");
        }
        else if (index == ASSET_ENEMY_BOXER)
        {
            str_cat(*out, "\n\nindex:\n* boxer;\n\nparams: \n* none;");
        }
        else if (index == ASSET_ENEMY_BUM)
        {
            str_cat(*out, "\n\nindex:\n* bum;\n\nparams: \n* none;");
        }
        else if (index == ASSET_ENEMY_MAGE)
        {
            str_cat(*out, "\n\nindex:\n* mage;\n\nparams: \n* none;");
        }
        else if (index == ASSET_ENEMY_HUMAN_PISTOL)
        {
            str_cat(*out, "\n\nindex:\n* human pistol;\n\nparams: \n* none;");
        }
        else if (index == ASSET_ENEMY_HUMAN_SHOTGUN)
        {
            str_cat(*out, "\n\nindex:\n* human shotgun;\n\nparams: \n* none;");
        }
        else if (index == ASSET_ENEMY_SKELETON)
        {
            str_cat(*out, "\n\nindex:\n* skeleton;\n\nparams: \n* none;");
        }
        else if (index == ASSET_ENEMY_SLIME_FIRE)
        {
            str_cat(*out, "\n\nindex:\n* slime fire;\n\nparams: \n* none;");
        }
        else if (index == ASSET_ENEMY_SLIME_ICE)
        {
            str_cat(*out, "\n\nindex:\n* slime ice;\n\nparams: \n* none;");
        }
        else if (index == ASSET_ENEMY_ZOMBIE)
        {
            str_cat(*out, "\n\nindex:\n* zombie;\n\nparams: \n* none;");
        }
    }
    else if (type == ASSET_BOSSES)
    {
        str_cat(*out, "\ntype:\n* bosses;");

        if (index == ASSET_BOSS_HUMAN_CHAINGUN)
        {
            str_cat(*out, "\n\nindex:\n* human chaingun;\n\nparams: \n* none;");
        }
        else if (index == ASSET_BOSS_HUMAN_ROCKETLAUNCHER)
        {
            str_cat(*out, "\n\nindex:\n* human rocketlauncher;\n\nparams: \n* none;");
        }
        else if (index == ASSET_BOSS_SLIME_TOXIC)
        {
            str_cat(*out, "\n\nindex:\n* slime toxic;\n\nparams: \n* none;");
        }
        else if (index == ASSET_BOSS_MEGAEYE)
        {
            str_cat(*out, "\n\nindex:\n* megaeye;\n\nparams: \n* none;");
        }
    }
}

void editor_update(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    Map *active_map = map_get_active(episode);
    Cell *cell = &active_map->cell[mouse_grid_pos_x][mouse_grid_pos_y];

    draw_text(str_printf(NULL, "Opened map id: %d;", (long)active_map_id), camera->size_x - (180 * config_current.font_scale), 24 * config_current.font_scale, COLOR_WHITE);

    imgui_start_imode();
    editor_topbar(episode);
    editor_popups(episode);
    editor_map_settings(episode);
    editor_asset_category_buttons_update();
    imgui_end_imode();

    if (is_allowed_to_draw() && is_selected_cell_visible == true)
    {
        int type = cell->object.type;
        int index = cell->object.index;

        var preview_pos_x = camera->size_x - (70 * config_current.font_scale);
        var preview_pos_y = 90 * config_current.font_scale;

        var preview_scale_x = 2 * config_current.font_scale;
        var preview_scale_y = 2 * config_current.font_scale;

        if (cell->object.is_occupied == true)
        {
            draw_text("Hovering object", camera->size_x - (180 * config_current.font_scale), 60 * config_current.font_scale, COLOR_WHITE);
            draw_quad(asset_get_texture(type, index),
                      vector(preview_pos_x, preview_pos_y, 0), NULL, NULL,
                      vector(preview_scale_x, preview_scale_y, 0), NULL, 100, 0);

            STRING *cell_info_str = "";
            editor_get_cell_info(cell, &cell_info_str);
            draw_text(cell_info_str, camera->size_x - (180 * config_current.font_scale), 86 * config_current.font_scale, COLOR_WHITE);
        }
    }

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
                if (is_map_settings_visible == true)
                {
                    is_map_settings_visible = false;
                }
                else
                {
                    editor_switch_popup_to(EDITOR_POPUP_STATE_EXIT);
                }
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