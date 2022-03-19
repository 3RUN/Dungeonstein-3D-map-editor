
float get_hsv_from_color(float value)
{
    return value / 255;
}

float get_color_from_hsv(float value)
{
    return value * 255;
}

void change_color_from_hsv(COLOR *color, float color_red, float color_green, float color_blue)
{
    color->red = get_color_from_hsv(color_red);
    color->green = get_color_from_hsv(color_green);
    color->blue = get_color_from_hsv(color_blue);
}

void mouse_set_position(VECTOR *pos)
{
    VECTOR offset;
    vec_set(&offset, pos);
    RECT rect;
    GetClientRect(hWnd, &rect);
    ClientToScreen(hWnd, &rect);
    ClientToScreen(hWnd, &rect.right);
    SetCursorPos(rect.left + offset.x, rect.top + offset.y);
}

VECTOR *mouse_get_position()
{
    POINT cp;
    GetCursorPos(&cp);
    VECTOR pos;
    vec_set(&pos, vector(cp.x, cp.y, 0));
    return &pos;
}

void mouse_set_map(BMAP *new_mouse_map)
{
    if (!new_mouse_map)
    {
        return;
    }

    if (mouse_map != new_mouse_map)
    {
        mouse_map = new_mouse_map;
    }
}

void mouse_enable(int is_mouse_centered)
{
    if (mouse_mode != 4)
    {
        mouse_sync = 0;
        mouse_mode = 4;
        mouse_set_map(mouse_tga);
        mouse_pointer = 1;

        if (is_mouse_centered == true)
        {
            mouse_set_position(vector(screen_size.x / 2, screen_size.y / 2, 0));
        }
    }
}

void mouse_disable()
{
    if (mouse_mode != 0)
    {
        mouse_sync = 0;
        mouse_mode = 0;
        mouse_map = NULL;
        mouse_pointer = 0;
    }
}

void mouse_lock_in_window()
{
    if (window_focus)
    {
        if (autolock_mouse_locked == false)
        {
            RECT rect;
            rect.top = 0;
            rect.bottom = screen_size.y;
            rect.left = 0;
            rect.right = screen_size.x;

            ClientToScreen(hWnd, &rect);
            ClientToScreen(hWnd, &rect.right);
            ClipCursor(&rect);

            mouse_set_position(vector(screen_size.x / 2, screen_size.y / 2, 0));
            autolock_mouse_locked = true;
        }
    }
    else
    {
        if (autolock_mouse_locked == true)
        {
            ClipCursor(NULL);
            autolock_mouse_locked = false;
        }
    }
}

void engine_set_resolution_from_id(int id, int display_mode)
{
    // cycle the id and keep in the range
    id = cycle(id, 0, screen_resolutions_total);

    var prop_x = camera->size_x / screen_size.x;
    var prop_y = camera->size_y / screen_size.y;

    int width = screen_resolution_available_list[SCREEN_RESOLUTION_WIDTH][id];
    int height = screen_resolution_available_list[SCREEN_RESOLUTION_HEIGHT][id];

    // because on some computers screen_size doesn't get updated by itself...
    screen_size.x = width;
    screen_size.y = height;

    camera->pos_x = floor(camera->pos_x * prop_x);
    camera->pos_y = floor(camera->pos_y * prop_y);
    camera->size_x = floor(screen_size.x * prop_x);
    camera->size_y = floor(screen_size.y * prop_y);

    // windowed or fullscreen
    if (display_mode == DISPLAY_MODE_WINDOWED)
    {
        video_window(NULL, NULL, 16 + 32, project_name_str);
    }

    if (video_set(width, height, 0, 0) == 0)
    {
        engine_set_resolution_from_id(id - 1, display_mode);
        diag("\nERROR in engine_set_resolution_from_id! Can't set to selected resolution... Lowering resolution!");
        return;
    }

    // fullscreen boarderless windows
    if (display_mode == DISPLAY_MODE_WINDOWED_FULLSCREEN)
    {
        video_window(vector(0.001, 0.001, 0), vector(desktop_size_x, desktop_size_y, 0), 1, project_name_str);
    }
}

void engine_apply_video_settings()
{
    // remove window's borders
    // otherwise window won't fit the screen and will cause troubles
    video_window(NULL, NULL, 1, project_name_str);

    wait(1); // wait one frame

    // resolution id
    int id = config_current.graphics_video_res_id;

    // if in borderless, then go desktop resolution !
    if (config_current.graphics_display_mode == DISPLAY_MODE_WINDOWED_FULLSCREEN)
    {
        id = screen_resolutions_total - 1;
    }

    // selected resolutionw with display modes
    engine_set_resolution_from_id(id, config_current.graphics_display_mode);

    // relock the mouse !
    autolock_mouse_locked = false;
}

void engine_update_settings_from_config()
{
}

void engine_initialize()
{
    d3d_alpharef = 1;                               // proper alpha fading
    d3d_instancing = 1;                             // sprite instancing
    vec_set(&d3d_lodfactor, vector(100, 110, 120)); // disable lods (ugly)

    draw_textmode("Courier", 1, 16, 100);

    sun_light = 0;

    fps_max = 60;
    warn_level = 6;

    video_mode = 8;
    random_seed(0);

    mouse_enable(true);
}