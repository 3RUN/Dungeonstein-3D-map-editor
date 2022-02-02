
void editor_episode_update(Episode *e)
{
    if (!e)
    {
        return;
    }

    imgui_start_imode();
    imgui_set_next_window_pos((screen_size.x / 2) - (EPISODE_WINDOW_WIDTH / 2), (screen_size.y / 2) - (EPISODE_WINDOW_HEIGHT / 2), ImGuiCond_Always);
    imgui_set_next_window_size(EPISODE_WINDOW_WIDTH, -1, ImGuiCond_Always);
    int episode_window_flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing;
    imgui_begin("Create Episode", NULL, episode_window_flags);

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

    var button_width = ((EPISODE_WINDOW_WIDTH - (engine_theme_win_padding[0] * 2)) / 2) - 2.5;
    if (imgui_button_withsize("Create", button_width, EPISODE_WINDOW_BUTTON_HEIGHT))
    {
        if (strlen(e->name) > 0 && strlen(e->story) > 0)
        {
            episode_creation_failed = false;
            editor_switch_state_to(STATE_START_EDITOR);
        }
        else
        {
            episode_creation_failed = true;
        }
    }
    imgui_same_line();
    if (imgui_button_withsize("Back", button_width, EPISODE_WINDOW_BUTTON_HEIGHT))
    {
        episode_creation_failed = false;
        episode_reset(e);
        editor_switch_state_to(STATE_MAIN_MENU);
    }

    if (episode_creation_failed == true)
    {
        imgui_push_style_color(ImGuiCol_TextDisabled, color4_red);
        imgui_text_disabled("          Make sure to enter name and a story!");
        imgui_pop_style_color(1);
    }

    imgui_end();
    imgui_end_imode();
}