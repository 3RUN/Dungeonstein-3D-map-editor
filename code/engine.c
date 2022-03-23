
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

var engine_key_return_scancode_from_letter(STRING *key)
{
    // nothing in the string ?
    if (key == NULL || str_len(key) <= 0)
    {
        diag("\nERROR! Can't return a scancode! Nothing in the key string!");
        return SCANCODE_NONE;
    }

    str_lwr(key); // convert key into lowercase string

    // check if it's 'none'
    if (str_cmpi(key, input_none_str))
    {
        return SCANCODE_NONE;
    }

    // expand with additional keys if needed
    if (str_cmpi(key, mouse_left_str))
    {
        return SCANCODE_MOUSE_LEFT;
    }
    else if (str_cmpi(key, mouse_right_str))
    {
        return SCANCODE_MOUSE_RIGHT;
    }
    else if (str_cmpi(key, mouse_middle_str))
    {
        return SCANCODE_MOUSE_MIDDLE;
    }

    // check if the given key can return a proper scancode
    var temp_scancode = key_for_str(key);
    if (temp_scancode > 0)
    {
        return temp_scancode;
    }

    // if nothing worked correctly, then return -1
    diag("\nERROR! Can't return a scancode from key: ");
    diag(key);
    diag(". No scancode was found!");

    return SCANCODE_NONE;
}

void engine_key_return_letter_from_scancode(STRING **out_letter, int scancode)
{
    // check if scancode is correct
    // correct range is from SCANCODE_ESC to SCANCODE_MOUSE_MIDDLE
    if (scancode <= 0 || scancode > SCANCODE_MOUSE_MIDDLE)
    {
        diag("\nERROR! Given scancode: ");
        diag(str_for_num(NULL, scancode));
        diag("is out of range!");

        return;
    }

    str_for_key(*out_letter, scancode);

    switch (scancode)
    {
    case SCANCODE_MOUSE_LEFT:
        str_cpy(*out_letter, mouse_left_str);
        break;

    case SCANCODE_MOUSE_RIGHT:
        str_cpy(*out_letter, mouse_right_str);
        break;

    case SCANCODE_MOUSE_MIDDLE:
        str_cpy(*out_letter, mouse_middle_str);
        break;
    }
}

void mouse_set_position(VECTOR *pos)
{
    RECT rect;
    GetClientRect(hWnd, &rect);
    ClientToScreen(hWnd, &rect);
    ClientToScreen(hWnd, &rect.right);
    SetCursorPos(rect.left + pos->x, rect.top + pos->y);
}

void mouse_get_position(VECTOR *out)
{
    POINT cp;
    GetCursorPos(&cp);

    vec_set(out, vector(cp.x, cp.y, 0));
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

void engine_initialize()
{
    d3d_alpharef = 1;                               // proper alpha fading
    d3d_instancing = 1;                             // sprite instancing
    vec_set(&d3d_lodfactor, vector(100, 110, 120)); // disable lods (ugly)

    sun_light = 0;

    fps_max = 60;
    warn_level = 6;

    video_mode = 8;
    random_seed(0);

    mouse_enable(true);
}