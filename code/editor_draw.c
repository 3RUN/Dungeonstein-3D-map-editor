
void editor_draw_initialize()
{
    // asset types
    asset_categories_combobox[ASSET_TYPE_WALLS] = "Walls";
    asset_categories_combobox[ASSET_TYPE_PROPS] = "Props";
    asset_categories_combobox[ASSET_TYPE_EVENTS] = "Events";
    asset_categories_combobox[ASSET_TYPE_ITEMS] = "Items";
    asset_categories_combobox[ASSET_TYPE_ENEMIES] = "Enemies";
    asset_categories_combobox[ASSET_TYPE_BOSSES] = "Bosses";

    selected_asset_category = asset_categories_combobox[selected_type];
    preview_update(selected_type, selected_asset);
}

void editor_draw_reset()
{
    selected_type = 0;
    selected_asset = 0;

    selected_asset_category = asset_categories_combobox[selected_type];
    preview_update(selected_type, selected_asset);
}

void editor_draw_destroy()
{
    preview_bmap = NULL;
}

void preview_update(int type, int asset)
{
    preview_bmap = asset_get_bmap(type, asset);
    strcpy(preview_asset_name, "Name: ");
    strcat(preview_asset_name, _chr(asset_get_desc(type, asset)));

    preview_cell.type = type;
    preview_cell.asset = asset;
}

void editor_switch_popup_to(int state)
{
    is_popup_opened = true;
    draw_popup_old_state = draw_popup_state;
    draw_popup_state = state;
}

void editor_popups(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    if (is_popup_opened == true)
    {
        imgui_open_popup(editor_draw_popup_id);
    }

    int editor_pause_popup_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;
    if (imgui_begin_popup_modals_params(editor_draw_popup_id, NULL, editor_pause_popup_flags))
    {
        switch (draw_popup_state)
        {
        case DRAW_POPUP_OPEN:
            popup_open(episode);
            break;

        case DRAW_POPUP_SURE_OPEN:
            popup_open_sure();
            break;

        case DRAW_POPUP_NEW:
            popup_new(episode);
            break;

        case DRAW_POPUP_SURE_NEW:
            popup_new_sure();
            break;

        case DRAW_POPUP_SAVE_AS:
            popup_save_as(episode);
            break;

        case DRAW_POPUP_SETTINGS:
            popup_settings();
            break;

        case DRAW_POPUP_EXIT:
            popup_exit();
            break;

        case DRAW_POPUP_EP_RESET:
            popup_ep_reset(episode);
            break;

        case DRAW_POPUP_EP_EDIT:
            popup_ep_edit(episode);
            break;

        case DRAW_POPUP_MAP_RESET:
            popup_map_reset(episode);
            break;

        case DRAW_POPUP_HELP:
            popup_help();
            break;

        case DRAW_POPUP_WAIT_FOR_INPUT:
            popup_wait_for_input();
            break;
        }
        imgui_end_popup();
    }
}

void editor_top_bar(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    imgui_set_next_window_pos(0, 0, ImGuiCond_Always);
    imgui_set_next_window_size(screen_size.x, EDITOR_TOP_BAR_HEIGHT * config_saved.font_scale, ImGuiCond_Always);
    int top_bar_window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoFocusOnAppearing;
    imgui_begin(editor_top_bar_id, NULL, top_bar_window_flags);

    is_top_bar_used = false;

    if (imgui_begin_menu_bar())
    {
        if (imgui_begin_menu("File", 1))
        {
            is_top_bar_used = true;

            if (imgui_menu_item("Open", "", 0, 1))
            {
                if (is_game_episode_loaded() == true)
                {
                    editor_switch_popup_to(DRAW_POPUP_SURE_OPEN);
                }
                else
                {
                    editor_switch_popup_to(DRAW_POPUP_OPEN);
                }
            }
            if (imgui_menu_item("New", "", 0, 1))
            {
                if (is_game_episode_loaded() == true)
                {
                    editor_switch_popup_to(DRAW_POPUP_SURE_NEW);
                }
                else
                {
                    editor_switch_popup_to(DRAW_POPUP_NEW);
                }
            }
            imgui_separator();
            if (is_game_episode_loaded() == true)
            {
                if (imgui_menu_item("Save", "", 0, 1))
                {
                    editor_switch_state_to(EDITOR_STATE_SAVE);
                }
            }
            if (imgui_menu_item("Save as", "", 0, 1))
            {
                strcpy(save_as_filename, ep_save_name);
                editor_switch_popup_to(DRAW_POPUP_SAVE_AS);
            }
            imgui_separator();
            if (imgui_menu_item("Settings", "", 0, 1))
            {
                editor_switch_popup_to(DRAW_POPUP_SETTINGS);
            }
            imgui_separator();
            if (imgui_menu_item("Exit", "", 0, 1))
            {
                editor_switch_popup_to(DRAW_POPUP_EXIT);
            }
            imgui_end_menu();
        }

        if (imgui_begin_menu("View", 1))
        {
            is_top_bar_used = true;

            imgui_checkbox("Grid", &is_grid_visible);
            if (imgui_checkbox("Walls", &is_walls_visible) || imgui_checkbox("Objects", &is_objects_visible))
            {
            }
            imgui_checkbox("Cell connections", &is_cell_links_visible);
            imgui_checkbox("Debug panel", &is_debug_panel_visible);
            imgui_end_menu();
        }

        if (imgui_begin_menu("Episode", 1))
        {
            is_top_bar_used = true;

            if (imgui_menu_item("Reset", "", 0, 1))
            {
                editor_switch_popup_to(DRAW_POPUP_EP_RESET);
            }
            if (imgui_menu_item("Edit", "", 0, 1))
            {
                strcpy(episode_edit_name, episode->name);
                strcpy(episode_edit_story_start, episode->story_start);
                strcpy(episode_edit_story_end, episode->story_end);
                episode_edit_map_count = episode->map_count;
                editor_switch_popup_to(DRAW_POPUP_EP_EDIT);
            }
            imgui_end_menu();
        }

        if (imgui_begin_menu("Map", 1))
        {
            is_top_bar_used = true;

            if (imgui_menu_item("Reset", "", 0, 1))
            {
                editor_switch_popup_to(DRAW_POPUP_MAP_RESET);
            }
            if (imgui_menu_item("Settings", "", 0, 1))
            {
                editor_switch_state_to(EDITOR_STATE_TO_MAP_SETTINGS);
            }
            if (imgui_menu_item("Test run", "", 0, 1))
            {
                editor_switch_state_to(EDITOR_STATE_TO_BUILD);
            }
            imgui_end_menu();
        }

        if (imgui_begin_menu("About", 1))
        {
            is_top_bar_used = true;

            if (imgui_menu_item("Help", "", 0, 1))
            {
                editor_switch_popup_to(DRAW_POPUP_HELP);
            }
            imgui_end_menu();
        }

        imgui_end_menu_bar();
    }

    imgui_end();
}

void editor_asset_list_item(void *draw_list, int type, int asset)
{
    if (!draw_list)
    {
        return;
    }

    VECTOR cursor_screen_pos;
    vec_set(&cursor_screen_pos, imgui_get_cursor_screen_pos());

    var width = imgui_get_content_region_avail_width();

    int is_temp_boolean = false;
    if (selected_asset == asset)
    {
        is_temp_boolean = true;
    }

    STRING *asset_desc_str = "";
    str_cpy(asset_desc_str, asset_get_desc(type, asset));

    STRING *selectable_id_str = "";
    str_cpy(selectable_id_str, "##");
    str_cat(selectable_id_str, asset_desc_str);
    str_cat(selectable_id_str, " index:");
    str_cat(selectable_id_str, str_for_num(NULL, asset));

    if (imgui_selectable_size(_chr(selectable_id_str), &is_temp_boolean, ImGuiSelectableFlags_None, vector(width, 64, 0)))
    {
        selected_asset = asset;
        cell_copy(&preview_cell, NULL);
        preview_update(type, asset);
    }

    var text_pos_x = cursor_screen_pos.x + ASSET_PREVIEW_IMAGE_WIDTH + engine_theme_item_spacing[0];
    var text_pos_y = cursor_screen_pos.y + (ASSET_PREVIEW_IMAGE_HEIGHT / 2) - (imgui_get_font_size() / 2);
    imgui_drawlist_add_text(asset_draw_list, vector(text_pos_x, text_pos_y, 0), color4_white, _chr(asset_desc_str));

    var image_start_x = cursor_screen_pos.x;
    var image_start_y = cursor_screen_pos.y;
    var image_end_x = image_start_x + ASSET_PREVIEW_IMAGE_WIDTH;
    var image_end_y = image_start_y + ASSET_PREVIEW_IMAGE_HEIGHT;
    imgui_drawlist_add_image(asset_draw_list, asset_get_bmap(type, asset), vector(image_start_x, image_start_y, 0), vector(image_end_x, image_end_y, 0), vector(0, 0, 0), vector(1, 1, 0), color4_image, 1.0);
}

void editor_side_bar(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    imgui_set_next_window_pos(screen_size.x - (EDITOR_SIDE_BAR_WIDTH * config_saved.font_scale), EDITOR_TOP_BAR_HEIGHT * config_saved.font_scale, ImGuiCond_Always);
    imgui_set_next_window_size(EDITOR_SIDE_BAR_WIDTH * config_saved.font_scale, screen_size.y - (EDITOR_TOP_BAR_HEIGHT * config_saved.font_scale), ImGuiCond_Always);
    int side_bar_window_flags = ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing;
    imgui_begin(editor_side_bar_id, NULL, side_bar_window_flags);

    if (imgui_collapsing_header("Selected asset", NULL, ImGuiTreeNodeFlags_DefaultOpen))
    {
        imgui_text("Image: ");
        imgui_align_right_with_offset(((EDITOR_SIDE_BAR_WIDTH * config_saved.font_scale) / 2) + (ASSET_PREVIEW_IMAGE_WIDTH * config_saved.font_scale) - engine_theme_win_padding[0]);
        if (preview_bmap)
        {
            imgui_image_scale(preview_bmap, vector((ASSET_PREVIEW_IMAGE_WIDTH * config_saved.font_scale) * PREVIEW_SCALE_FACTOR, (ASSET_PREVIEW_IMAGE_HEIGHT * config_saved.font_scale) * PREVIEW_SCALE_FACTOR, 0), vector(0, 0, 0), vector(1, 1, 0));
        }
        imgui_separator();
        imgui_text(preview_asset_name);
        imgui_separator();

        imgui_text("Parameters:");
        int selected_asset_parameters_child_flag = ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
        var width = imgui_get_content_region_avail_width();
        imgui_begin_child(editor_preview_parameters_child_id, vector(width, (SIDEBAR_PARAM_CHILD_HEIGHT * config_saved.font_scale), 0), 1, selected_asset_parameters_child_flag);

        imgui_end_child();
    }
    imgui_separator();

    if (imgui_collapsing_header("Asset", NULL, ImGuiTreeNodeFlags_DefaultOpen))
    {
        imgui_text("Category");
        imgui_same_line();

        imgui_push_item_width(-1);
        if (imgui_begin_combo(editor_side_bar_category_combo_id, selected_asset_category, ImGuiComboFlags_HeightSmall))
        {
            int n = 0;
            for (n = 0; n < MAX_ASSET_TYPES; n++)
            {
                BOOL is_selected = (selected_asset_category == asset_categories_combobox[n]);
                if (imgui_selectable(asset_categories_combobox[n], &is_selected, 0))
                {
                    selected_asset_category = asset_categories_combobox[n];
                    selected_type = n;
                    selected_asset = 0;
                    cell_copy(&preview_cell, NULL);
                    preview_update(selected_type, selected_asset);
                }
            }
            imgui_end_combo();
        }
        imgui_pop_item_width();

        int assets_list_child_flags = ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings;
        var width = imgui_get_content_region_avail_width();
        imgui_begin_child(editor_side_bar_asset_list_child_id, vector(width, SIDEBAR_ASSET_LIST_CHILD_HEIGHT * config_saved.font_scale, 0), 1, assets_list_child_flags);

        asset_draw_list = imgui_get_window_draw_list();

        switch (selected_type)
        {
        case ASSET_TYPE_WALLS:
            int n = 0;
            for (n = 0; n < TOTAL_WALL_TEXTURES; n++)
            {
                editor_asset_list_item(asset_draw_list, ASSET_TYPE_WALLS, n);
            }
            break;

        case ASSET_TYPE_PROPS:
            int n = 0;
            for (n = 0; n < TOTAL_PROPS_TEXTURES; n++)
            {
                editor_asset_list_item(asset_draw_list, ASSET_TYPE_PROPS, n);
            }
            break;

        case ASSET_TYPE_EVENTS:
            int n = 0;
            for (n = 0; n < TOTAL_EVENT_TEXTURES; n++)
            {
                editor_asset_list_item(asset_draw_list, ASSET_TYPE_EVENTS, n);
            }
            break;

        case ASSET_TYPE_ITEMS:
            int n = 0;
            for (n = 0; n < TOTAL_ITEM_TEXTURES; n++)
            {
                editor_asset_list_item(asset_draw_list, ASSET_TYPE_ITEMS, n);
            }
            break;

        case ASSET_TYPE_ENEMIES:
            int n = 0;
            for (n = 0; n < TOTAL_ENEMY_TEXTURES; n++)
            {
                editor_asset_list_item(asset_draw_list, ASSET_TYPE_ENEMIES, n);
            }
            break;

        case ASSET_TYPE_BOSSES:
            int n = 0;
            for (n = 0; n < TOTAL_BOSS_TEXTURES; n++)
            {
                editor_asset_list_item(asset_draw_list, ASSET_TYPE_BOSSES, n);
            }
            break;
        }

        imgui_end_child();
    }
    imgui_separator();

    imgui_separator();

    imgui_text(_chr(str_printf(NULL, "Mouse pos x = %d; y = %d;", (long)mouse_x, (long)mouse_y)));
    imgui_text(_chr(str_printf(NULL, "Map size: width = %d; height = %d;", (long)MAP_WIDTH, (long)MAP_HEIGHT)));

    imgui_end();
}

void editor_draw_update(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    imgui_start_imode();
    editor_side_bar(episode);
    editor_top_bar(episode);
    editor_popups(episode);
    imgui_end_imode();

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
                editor_switch_popup_to(DRAW_POPUP_EXIT);
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