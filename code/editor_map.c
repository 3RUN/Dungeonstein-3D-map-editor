
void editor_map_initialize()
{
    // asset types
    editor_asset_types_combobox[ASSET_TYPE_WALLS] = "Walls";
    editor_asset_types_combobox[ASSET_TYPE_PROPS] = "Props";
    editor_asset_types_combobox[ASSET_TYPE_EVENTS] = "Events";
    editor_asset_types_combobox[ASSET_TYPE_ITEMS] = "Items";
    editor_asset_types_combobox[ASSET_TYPE_ENEMIES] = "Enemies";
    editor_asset_types_combobox[ASSET_TYPE_BOSSES] = "Bosses";

    editor_selected_asset_type = editor_asset_types_combobox[editor_asset_type];
    editor_map_preview_update(editor_asset_type, editor_asset_index);
}

void editor_map_reset()
{
    editor_asset_type = ASSET_TYPE_WALLS; // currently active asset category
    editor_asset_index = 0;               // currently selected asset

    editor_selected_asset_type = editor_asset_types_combobox[editor_asset_type];
    editor_map_preview_update(editor_asset_type, editor_asset_index);
}

void editor_map_destroy()
{
    preview_bmap = NULL;
}

void editor_map_preview_update(int type, int index)
{
    preview_bmap = asset_get_bmap(type, index);
    strcpy(preview_name, _chr(map_preview_name_str));
    strcat(preview_name, _chr(asset_get_desc(type, index)));

    preview_cell.type = type;
    preview_cell.asset = index;
}

void editor_map_create_asset_item(void *draw_list, int type, int index)
{
    if (!draw_list)
    {
        return;
    }

    VECTOR cursor_screen_pos;
    vec_set(&cursor_screen_pos, imgui_get_cursor_screen_pos());

    var width = imgui_get_content_region_avail_width();

    int is_temp_boolean = false;
    if (editor_asset_index == index)
    {
        is_temp_boolean = true;
    }

    STRING *asset_desc_str = "";
    str_cpy(asset_desc_str, asset_get_desc(type, index));

    STRING *selectable_id_str = "";
    str_cpy(selectable_id_str, "##");
    str_cat(selectable_id_str, asset_desc_str);
    str_cat(selectable_id_str, " index:");
    str_cat(selectable_id_str, str_for_num(NULL, index));

    if (imgui_selectable_size(_chr(selectable_id_str), &is_temp_boolean, ImGuiSelectableFlags_None, vector(width, 64, 0)))
    {
        editor_asset_index = index;
        cell_copy(&preview_cell, NULL);
        editor_map_preview_update(type, index);
    }

    var text_pos_x = cursor_screen_pos.x + ASSET_PREVIEW_IMAGE_WIDTH + engine_theme_item_spacing[0];
    var text_pos_y = cursor_screen_pos.y + (ASSET_PREVIEW_IMAGE_HEIGHT / 2) - (imgui_get_font_size() / 2);
    imgui_drawlist_add_text(asset_draw_list, vector(text_pos_x, text_pos_y, 0), color4_white, _chr(asset_desc_str));

    var image_start_x = cursor_screen_pos.x;
    var image_start_y = cursor_screen_pos.y;
    var image_end_x = image_start_x + ASSET_PREVIEW_IMAGE_WIDTH;
    var image_end_y = image_start_y + ASSET_PREVIEW_IMAGE_HEIGHT;
    imgui_drawlist_add_image(asset_draw_list, asset_get_bmap(type, index), vector(image_start_x, image_start_y, 0), vector(image_end_x, image_end_y, 0), vector(0, 0, 0), vector(1, 1, 0), color4_image, 1.0);
}

void editor_map_popup_state_change_to(int state)
{
    map_popup_state = state;
    is_popup_opened = true;
}

void editor_map_popup(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    if (is_popup_opened)
    {
        imgui_open_popup(map_popup_id);
    }

    int editor_map_popup_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;
    if (imgui_begin_popup_modals_params(map_popup_id, NULL, editor_map_popup_flags))
    {
        switch (map_popup_state)
        {
        case MAP_POPUP_OPEN:
            editor_popup_open(episode);
            break;

        case MAP_POPUP_OPEN_SURE:
            editor_popup_open_sure();
            break;

        case MAP_POPUP_NEW:
            editor_popup_new(episode);
            break;

        case MAP_POPUP_NEW_SURE:
            editor_popup_new_sure();
            break;

        case MAP_POPUP_SAVE_AS:
            editor_popup_save_as(episode);
            break;

        case MAP_POPUP_SETTINGS:
            editor_popup_settings(episode);
            break;

        case MAP_POPUP_ABOUT:
            editor_popup_about();
            break;

        case MAP_POPUP_EPISODE_EDIT:
            editor_popup_episode_edit(episode);
            break;

        case MAP_POPUP_RESET_MAP:
            editor_popup_reset_map(episode);
            break;

        case MAP_POPUP_EXIT:
            editor_popup_exit();
            break;
        }

        imgui_end_popup();
    }
}

void editor_map_side_bar(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    imgui_set_next_window_pos(screen_size.x - EDITOR_SIDE_BAR_WIDTH, EDITOR_TOP_BAR_HEIGHT, ImGuiCond_Always);
    imgui_set_next_window_size(EDITOR_SIDE_BAR_WIDTH, screen_size.y - EDITOR_TOP_BAR_HEIGHT, ImGuiCond_Always);
    int side_bar_window_flags = ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing;
    imgui_begin(map_side_bar_id, NULL, side_bar_window_flags);

    if (imgui_collapsing_header(_chr(map_selected_asset_str), NULL, ImGuiTreeNodeFlags_DefaultOpen))
    {
        imgui_text(_chr(map_preview_image_str));
        imgui_align_right_with_offset((EDITOR_SIDE_BAR_WIDTH / 2) + ASSET_PREVIEW_IMAGE_WIDTH - engine_theme_win_padding[0]);
        if (preview_bmap)
        {
            imgui_image_scale(preview_bmap, vector(ASSET_PREVIEW_IMAGE_WIDTH * PREVIEW_SCALE_FACTOR, ASSET_PREVIEW_IMAGE_HEIGHT * PREVIEW_SCALE_FACTOR, 0), vector(0, 0, 0), vector(1, 1, 0));
        }
        imgui_separator();

        imgui_text(preview_name);
        imgui_separator();

        imgui_text(_chr(map_preview_parameters_str));
        int selected_asset_parameters_child_flag = ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
        var width = imgui_get_content_region_avail_width();
        imgui_begin_child(map_side_bar_asset_param_child_id, vector(width, SIDEBAR_PARAM_CHILD_HEIGHT, 0), 1, selected_asset_parameters_child_flag);

        editor_obj_params_update(&preview_cell, editor_asset_type, editor_asset_index);

        imgui_end_child();
    }
    imgui_separator();

    if (imgui_collapsing_header(_chr(map_assets_str), NULL, ImGuiTreeNodeFlags_DefaultOpen))
    {
        imgui_text(_chr(editor_category_str));
        imgui_same_line();

        imgui_push_item_width(-1);
        if (imgui_begin_combo(map_side_bar_asset_category_combobox_id, editor_selected_asset_type, ImGuiComboFlags_HeightSmall))
        {
            int n = 0;
            for (n = 0; n < MAX_ASSET_TYPES; n++)
            {
                BOOL is_selected = (editor_selected_asset_type == editor_asset_types_combobox[n]);
                if (imgui_selectable(editor_asset_types_combobox[n], &is_selected, 0))
                {
                    editor_selected_asset_type = editor_asset_types_combobox[n];
                    editor_asset_type = n;
                    editor_asset_index = 0;
                    cell_copy(&preview_cell, NULL);
                    editor_map_preview_update(editor_asset_type, editor_asset_index);
                }
            }
            imgui_end_combo();
        }
        imgui_pop_item_width();

        int assets_list_child_flags = ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
        var width = imgui_get_content_region_avail_width();
        imgui_begin_child(map_side_bar_asset_list_child_id, vector(width, SIDEBAR_ASSET_LIST_CHILD_HEIGHT, 0), 1, assets_list_child_flags);

        asset_draw_list = imgui_get_window_draw_list();

        switch (editor_asset_type)
        {
        case ASSET_TYPE_WALLS:
            int n = 0;
            for (n = 0; n < TOTAL_WALL_TEXTURES; n++)
            {
                editor_map_create_asset_item(asset_draw_list, ASSET_TYPE_WALLS, n);
            }
            break;

        case ASSET_TYPE_PROPS:
            int n = 0;
            for (n = 0; n < TOTAL_PROPS_TEXTURES; n++)
            {
                editor_map_create_asset_item(asset_draw_list, ASSET_TYPE_PROPS, n);
            }
            break;

        case ASSET_TYPE_EVENTS:
            int n = 0;
            for (n = 0; n < TOTAL_EVENT_TEXTURES; n++)
            {
                editor_map_create_asset_item(asset_draw_list, ASSET_TYPE_EVENTS, n);
            }
            break;

        case ASSET_TYPE_ITEMS:
            int n = 0;
            for (n = 0; n < TOTAL_ITEM_TEXTURES; n++)
            {
                editor_map_create_asset_item(asset_draw_list, ASSET_TYPE_ITEMS, n);
            }
            break;

        case ASSET_TYPE_ENEMIES:
            int n = 0;
            for (n = 0; n < TOTAL_ENEMY_TEXTURES; n++)
            {
                editor_map_create_asset_item(asset_draw_list, ASSET_TYPE_ENEMIES, n);
            }
            break;

        case ASSET_TYPE_BOSSES:
            int n = 0;
            for (n = 0; n < TOTAL_BOSS_TEXTURES; n++)
            {
                editor_map_create_asset_item(asset_draw_list, ASSET_TYPE_BOSSES, n);
            }
            break;
        }

        imgui_end_child();
    }
    imgui_separator();

    imgui_text(_chr(map_settings_opened_map_id_str));
    imgui_same_line();
    imgui_align_right_with_offset(80);
    if (imgui_arrow_button(_chr(editor_decrease_str), ImGuiDir_Left))
    {
        current_map_id--;
        current_map_id = clamp(current_map_id, 0, episode->map_count - 1);

        editor_grid_sprites_refresh(episode);
    }
    imgui_same_line();
    imgui_text(_chr(str_printf(NULL, "%d / %d", (long)(current_map_id + 1), (long)episode->map_count)));
    imgui_same_line();
    if (imgui_arrow_button(_chr(editor_increase_str), ImGuiDir_Right))
    {
        current_map_id++;
        current_map_id = clamp(current_map_id, 0, episode->map_count - 1);

        editor_grid_sprites_refresh(episode);
    }
    current_map_id = clamp(current_map_id, 0, episode->map_count - 1);
    imgui_separator();

    imgui_text(_chr(str_printf(NULL, map_mouse_pos_str, (long)mouse_x, (long)mouse_y)));
    imgui_text(_chr(str_printf(NULL, map_size_str, (long)MAP_WIDTH, (long)MAP_HEIGHT)));

    imgui_end();
}

void editor_map_top_bar(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    imgui_set_next_window_pos(0, 0, ImGuiCond_Always);
    imgui_set_next_window_size(screen_size.x, EDITOR_TOP_BAR_HEIGHT, ImGuiCond_Always);
    int top_bar_window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoFocusOnAppearing;
    imgui_begin(map_top_bar_id, NULL, top_bar_window_flags);

    is_top_bar_used = false;

    if (imgui_begin_menu_bar())
    {
        if (imgui_begin_menu(_chr(editor_file_str), 1))
        {
            is_top_bar_used = true;

            if (imgui_menu_item(_chr(editor_open_str), "", 0, 1))
            {
                editor_map_popup_state_change_to(MAP_POPUP_OPEN_SURE);
            }
            if (imgui_menu_item(_chr(editor_new_str), "", 0, 1))
            {
                editor_map_popup_state_change_to(MAP_POPUP_NEW_SURE);
            }
            imgui_separator();
            if (imgui_menu_item(_chr(editor_save_str), "", 0, 1))
            {
                episode_save(episode_save_name, &def_episode);
            }
            if (imgui_menu_item(_chr(editor_save_as_str), "", 0, 1))
            {
                strcpy(save_as_filename, episode_save_name);
                editor_map_popup_state_change_to(MAP_POPUP_SAVE_AS);
            }
            imgui_separator();
            if (imgui_menu_item(_chr(editor_preferences_str), "", 0, 1))
            {
                editor_map_popup_state_change_to(MAP_POPUP_SETTINGS);
            }
            imgui_separator();
            if (imgui_menu_item(_chr(editor_exit_str), "", 0, 1))
            {
                editor_map_popup_state_change_to(MAP_POPUP_EXIT);
            }
            imgui_end_menu();
        }

        if (imgui_begin_menu(_chr(editor_view_str), 1))
        {
            is_top_bar_used = true;

            imgui_checkbox(_chr(editor_view_grid_str), &is_grid_visible);
            if (imgui_checkbox(_chr(editor_view_walls_str), &is_walls_visible) || imgui_checkbox(_chr(editor_view_objects_str), &is_objects_visible))
            {
                editor_grid_sprites_refresh(episode);
            }
            imgui_checkbox(_chr(editor_view_connections_str), &is_connections_visible);
            imgui_end_menu();
        }

        if (imgui_begin_menu(_chr(editor_episode_str), 1))
        {
            if (imgui_menu_item(_chr(editor_edit_str), "", 0, 1))
            {
                strcpy(episode_edit_name, episode->name);
                strcpy(episode_edit_story, episode->story);
                episode_edit_map_count = episode->map_count;
                editor_map_popup_state_change_to(MAP_POPUP_EPISODE_EDIT);
            }
            imgui_end_menu();
        }

        if (imgui_begin_menu(_chr(editor_map_str), 1))
        {
            is_top_bar_used = true;

            if (imgui_menu_item(_chr(editor_reset_str), "", 0, 1))
            {
                editor_map_popup_state_change_to(MAP_POPUP_RESET_MAP);
            }
            if (imgui_menu_item(_chr(editor_map_settings_str), "", 0, 1))
            {
                is_popup_opened = false;
                imgui_close_current_popup();
                editor_switch_state_to(EDITOR_STATE_TO_MAP_SETTINGS);
            }
            if (imgui_menu_item(_chr(editor_test_build_str), "", 0, 1))
            {
                is_popup_opened = false;
                imgui_close_current_popup();
                editor_switch_state_to(EDITOR_STATE_TO_TEST_BUILD);
            }
            imgui_end_menu();
        }

        if (imgui_begin_menu(_chr(editor_about_str), 1))
        {
            is_top_bar_used = true;

            if (imgui_menu_item(_chr(editor_help_str), "", 0, 1))
            {
                editor_map_popup_state_change_to(MAP_POPUP_ABOUT);
            }
            imgui_end_menu();
        }
        imgui_end_menu_bar();
    }

    imgui_end();
}

void editor_map_background()
{
    camera->fog_end = FOG_MAX_END;
    camera->fog_start = FOG_MAX_END;

    camera->clip_near = 0.1;
    camera->clip_far = FOG_MAX_END * 1.25;

    fog_color = 4;
    sky_color.red = get_color_from_hsv(config_current.background_color[0]);
    sky_color.green = get_color_from_hsv(config_current.background_color[1]);
    sky_color.blue = get_color_from_hsv(config_current.background_color[2]);
    vec_set(&d3d_fogcolor4, &sky_color);
}

void editor_map_tooltip(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    if (config_current.is_cell_tooltip_enabled == false)
    {
        return;
    }

    Map *current_map = map_get_active(episode);
    if (!current_map)
    {
        return;
    }

    if (mouse_moving == false)
    {
        cell_info_tooltip_counter += time_frame / 16;
        cell_info_tooltip_counter = clamp(cell_info_tooltip_counter, 0, CELL_TOOLTIP_TIME + 1);

        if (cell_info_tooltip_counter > CELL_TOOLTIP_TIME)
        {
            STRING *info_str = draw_map_info(current_map, mouse_x, mouse_y);
            if (info_str)
            {
                imgui_set_tooltip(_chr(info_str));
                imgui_begin_tooltip();
                imgui_end_tooltip();
            }
        }
    }
    else
    {
        cell_info_tooltip_counter = 0;
    }
}

void editor_map_update(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    imgui_start_imode();
    editor_map_side_bar(episode);
    editor_map_top_bar(episode);
    editor_map_popup(episode);
    editor_map_background();
    editor_map_tooltip(episode);
    imgui_end_imode();
}