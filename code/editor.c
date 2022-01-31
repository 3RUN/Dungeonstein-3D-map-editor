
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

// imgui handles color range from 0...1
// so I do this dumb trick to get 0...255 value
float get_hsv_from_color(float value)
{
    return value / 255;
}

float get_color_from_hsv(float value)
{
    return value * 255;
}

void editor_camera_resize(int is_shrinked)
{
    if (is_shrinked == true)
    {
        camera->pos_x = 0;
        camera->pos_y = EDITOR_TOP_BAR_HEIGHT;
        camera->size_x = screen_size.x - EDITOR_SIDE_BAR_WIDTH;
        camera->size_y = screen_size.y - EDITOR_TOP_BAR_HEIGHT;
    }
    else
    {
        camera->pos_x = 0;
        camera->pos_y = 0;
        camera->size_x = screen_size.x;
        camera->size_y = screen_size.y;
    }
}