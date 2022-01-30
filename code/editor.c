
void editor_switch_state_to(int state)
{
    editor_old_state = editor_state;
    editor_state = state;
}

void editor_create_tooltip(STRING *tooltip)
{
    if (imgui_is_item_hovered())
    {
        imgui_set_tooltip(_chr(tooltip));
        imgui_begin_tooltip();
        imgui_end_tooltip();
    }
}

void editor_help_maker(char *desc)
{
    imgui_text_disabled("(?)");
    if (imgui_is_item_hovered())
    {
        imgui_begin_tooltip();
        imgui_push_text_wrap_pos(imgui_get_font_size() * 35);
        imgui_text_unformatted(desc);
        imgui_pop_text_wrap_pos();
        imgui_end_tooltip();
    }
}