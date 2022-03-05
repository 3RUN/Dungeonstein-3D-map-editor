
float get_hsv_from_color(float value)
{
    return value / 255;
}

float get_color_from_hsv(float value)
{
    return value * 255;
}

void editor_create_tooltip(char *tooltip)
{
    if (imgui_is_item_hovered())
    {
        imgui_set_tooltip(tooltip);
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

void editor_camera_resize()
{
    if (editor_state == EDITOR_STATE_EDIT_MAP || editor_state == EDITOR_STATE_EMPTY)
    {
        camera->pos_x = 0;
        camera->pos_y = EDITOR_TOP_BAR_HEIGHT;
        camera->size_x = screen_size.x;
        camera->size_y = screen_size.y - EDITOR_TOP_BAR_HEIGHT;

        if (editor_state == EDITOR_STATE_EDIT_MAP)
        {
            camera->size_x = screen_size.x - EDITOR_SIDE_BAR_WIDTH;
        }
    }
    else
    {
        camera->pos_x = 0;
        camera->pos_y = 0;
        camera->size_x = screen_size.x;
        camera->size_y = screen_size.y;
    }
}