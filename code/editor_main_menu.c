
void editor_menu_update(Episode *e)
{
    if (!e)
    {
        return;
    }

    imgui_start_imode();
    imgui_set_next_window_pos((screen_size.x / 2) - (MENU_WINDOW_WIDTH / 2), (screen_size.y / 2) - (MENU_WINDOW_HEIGHT / 2), ImGuiCond_Always);
    imgui_set_next_window_size(MENU_WINDOW_WIDTH, MENU_WINDOW_HEIGHT, ImGuiCond_Always);
    int menu_window_flags = ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing;
    imgui_begin("Main menu", NULL, menu_window_flags);

    if (imgui_button_withsize("New", -1, MENU_WINDOW_BUTTON_HEIGHT))
    {
        editor_switch_state_to(STATE_RESET_EPISODE);
    }

    if (imgui_button_withsize("Load", -1, MENU_WINDOW_BUTTON_HEIGHT))
    {
        editor_load_refresh_list();
        editor_switch_state_to(STATE_LOAD);
    }

    if (imgui_button_withsize("Exit", -1, MENU_WINDOW_BUTTON_HEIGHT))
    {
        is_popup_opened = true;
        imgui_open_popup("##Menu exit popup");
    }

    int menu_exit_popup_modal_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;
    if (imgui_begin_popup_modals_params("##Menu exit popup", NULL, menu_exit_popup_modal_flags))
    {
        imgui_text(_chr(episode_menu_exit_popup_str));

        if (imgui_button_withsize("Yes", -1, MENU_WINDOW_BUTTON_HEIGHT))
        {
            sys_exit("");
        }

        if (imgui_button_withsize("No", -1, MENU_WINDOW_BUTTON_HEIGHT) || key_esc)
        {
            is_popup_opened = false;
            imgui_close_current_popup();
        }

        imgui_end_popup();
    }

    imgui_end();
    imgui_end_imode();
}