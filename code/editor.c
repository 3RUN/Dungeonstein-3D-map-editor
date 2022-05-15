
void editor_switch_state_to(int state)
{
    editor_previous_state = editor_state;
    editor_state = state;
}

void editor_switch_popup_to(int state)
{
    is_popup_opened = true;
    editor_popup_previous_state = editor_popup_state;
    editor_popup_state = state;
}