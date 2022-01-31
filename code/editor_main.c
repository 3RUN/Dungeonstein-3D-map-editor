
void editor_side_bar(Episode *e)
{
    imgui_set_next_window_pos(screen_size.x - EDITOR_SIDE_BAR_WIDTH, EDITOR_TOP_BAR_HEIGHT, ImGuiCond_Always);
    imgui_set_next_window_size(EDITOR_SIDE_BAR_WIDTH, screen_size.y - EDITOR_TOP_BAR_HEIGHT, ImGuiCond_Always);
    int side_bar_flags = ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing;
    imgui_begin("##Side Bar", NULL, side_bar_flags);

    if (imgui_collapsing_header("Preview", NULL, ImGuiTreeNodeFlags_DefaultOpen))
    {
    }
    imgui_separator();

    if (imgui_collapsing_header("Assets", NULL, ImGuiTreeNodeFlags_DefaultOpen))
    {
    }
    imgui_separator();

    if (imgui_collapsing_header("Map settings", NULL, ImGuiTreeNodeFlags_DefaultOpen))
    {
    }
    imgui_separator();

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
            }
            if (imgui_menu_item("Load", "", 0, 1))
            {
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

        if (imgui_begin_menu("Editor", 1))
        {
            if (imgui_menu_item("Settings", "", 0, 1))
            {
            }
            imgui_end_menu();
        }

        if (imgui_begin_menu("Help", 1))
        {
            if (imgui_menu_item("About", "", 0, 1))
            {
            }
            imgui_end_menu();
        }

        imgui_end_menu_bar();
    }

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

void editor_main_update(Episode *e)
{
    if (!e)
    {
        return;
    }

    imgui_start_imode();

    editor_side_bar(e);
    editor_top_bar(e);

    imgui_end_imode();
}