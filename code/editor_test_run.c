
void editor_test_run_update(Episode *episode)
{
    draw_text("test run", 100, 100, COLOR_WHITE);

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
                editor_switch_state_to(EDITOR_STATE_FROM_BUILD);
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