
int is_pos_on_grid(VECTOR *pos)
{
    if (!pos)
    {
        return false;
    }

    return (pos->x >= 0 && pos->x < MAP_WIDTH && pos->y >= 0 && pos->y < MAP_HEIGHT);
}

int is_pos_within_camera(VECTOR *pos)
{
    if (!pos)
    {
        return false;
    }

    return (pos->x >= camera->pos_x && pos->x < camera->size_x && pos->y >= camera->pos_y && pos->y < camera->size_y);
}

int is_allowed_to_draw()
{
    if (is_top_bar_used == true)
    {
        return false;
    }

    if (is_popup_opened == true)
    {
        return false;
    }

    if (editor_state != EDITOR_STATE_EDIT)
    {
        return false;
    }

    if (is_pos_on_grid(vector(mouse_on_grid.x, -mouse_on_grid.y, 0)) == false)
    {
        return false;
    }

    if (is_pos_within_camera(vector(mouse_pos.x, mouse_pos.y, 0)) == false)
    {
        return false;
    }

    return true;
}

void grid_get_mouse_pos(int *x, int *y)
{
    if (is_allowed_to_draw() == true)
    {
        *x = mouse_on_grid.x;
        *y = -mouse_on_grid.y;
    }
    else
    {
        *x = 0;
        *y = 0;
    }
}

void grid_draw(VECTOR *center, var grid_size, int width, int height, COLOR *color)
{
    int lines_x = width + 1;
    int lines_y = height + 1;
    var bounds_x = (lines_x - 1) / 2.0 * grid_size;
    var bounds_y = (lines_y - 1) / 2.0 * grid_size;

    VECTOR start, end;
    vec_set(&start, center);
    vec_set(&end, center);
    start.x -= bounds_x;
    start.y -= bounds_y;
    end.x -= bounds_x;
    end.y += bounds_y;

    int i = 0;
    for (i = 0; i < lines_x; i++)
    {
        draw_line3d(&start, color, 0);
        draw_line3d(&start, color, 100);
        draw_line3d(&end, color, 100);
        draw_line3d(&end, color, 0);
        start.x = end.x = start.x + grid_size;
    }

    vec_set(&start, center);
    vec_set(&end, center);
    start.x -= bounds_x;
    start.y -= bounds_y;
    end.x += bounds_x;
    end.y -= bounds_y;

    for (i = 0; i < lines_y; i++)
    {
        draw_line3d(&start, color, 0);
        draw_line3d(&start, color, 100);
        draw_line3d(&end, color, 100);
        draw_line3d(&end, color, 0);
        start.y = end.y = start.y + grid_size;
    }
}

void camera_auto_resize()
{
    if (editor_state == EDITOR_STATE_EDIT)
    {
        camera->pos_x = 0;
        camera->pos_y = EDITOR_TOP_BAR_HEIGHT;
        camera->size_x = screen_size.x;
        camera->size_y = screen_size.y - EDITOR_TOP_BAR_HEIGHT;
        camera->size_x = screen_size.x - EDITOR_SIDE_BAR_WIDTH;
    }
    else
    {
        camera->pos_x = 0;
        camera->pos_y = 0;
        camera->size_x = screen_size.x;
        camera->size_y = screen_size.y;
    }
}

void camera_movement(var grid_height, var grid_size)
{
    int is_allowed = is_allowed_to_draw();

    DEBUG_VAR(is_allowed, 300);

    if (mouse_middle && is_allowed == true)
    {
        VECTOR vtemp;
        vec_set(&vtemp, &mouse_dir3d);
        vec_scale(&vtemp, -fsin(camera->tilt, camera->skill_y) / vtemp.z);
        vec_add(&vtemp, &mouse_3d);
        vec_set(&camera->x, &vtemp);

        camera_center.x = camera->x + fcos(camera->pan, camera->skill_x);
        camera_center.y = camera->y + fsin(camera->pan, camera->skill_x);
        camera_center.z = grid_height;

        GetCursorPos(&mouse_pos_PL);
    }
    else
    {
        VECTOR vtemp;
        vec_set(&vtemp, &mouse_dir3d);

        if (vtemp.z < 0)
        {
            vec_scale(&vtemp, fsin(camera->tilt, camera->skill_y) / vtemp.z);
            vec_add(&vtemp, &camera->x);
            vtemp.z = grid_height;
            vec_set(&mouse_3d, &vtemp);

            mouse_on_grid.x = integer((mouse_3d.x + (sign(mouse_3d.x) * (grid_size / 2))) / grid_size);
            mouse_on_grid.y = integer((mouse_3d.y + (sign(mouse_3d.y) * (grid_size / 2))) / grid_size);
            mouse_on_grid.z = grid_height / grid_size;
        }

        if (mickey.z && is_allowed == true)
        {
            var ntemp = camera->skill_y;
            camera->skill_y += mickey.z * 0.2;
            camera->skill_y = clamp(camera->skill_y, 128, 1500);
            ntemp = camera->skill_y / ntemp;
            vec_sub(&camera_center, &mouse_3d);
            vec_scale(&camera_center, ntemp);
            vec_add(&camera_center, &mouse_3d);
            camera->skill_x = fcos(camera->tilt, camera->skill_y);
            camera->x = camera_center.x - fcos(camera->pan, camera->skill_x);
            camera->y = camera_center.y - fsin(camera->pan, camera->skill_x);
            camera->z = camera_center.z - fsin(camera->tilt, camera->skill_y);
        }

        GetCursorPos(&mouse_pos_PL);
    }
}

void camera_initialize()
{
    vec_set(&grid_center, vector((MAP_WIDTH / 2) * MAP_CELL_SIZE, -(MAP_HEIGHT / 2) * MAP_CELL_SIZE, MAP_Z_POS));
    vec_set(&camera_center, &grid_center);

    camera->arc = CAMERA_ARC;
    vec_set(&camera->pan, vector(90, -90, 0));

    camera->skill_y = 1024; // initial camera height
    camera->skill_x = fcos(camera->tilt, camera->skill_y);

    camera->x = camera_center.x - fcos(camera->pan, camera->skill_x);
    camera->y = camera_center.y - fsin(camera->pan, camera->skill_x);
    camera->z = camera_center.z - fsin(camera->tilt, camera->skill_y);
}

void camera_n_grid_update()
{
    VECTOR draw_offset;
    vec_set(&draw_offset, vector(0, 0, GRID_DRAW_OFFSET));
    vec_add(&draw_offset, &grid_center);

    if (is_grid_visible == true)
    {
        COLOR grid_color;
        grid_color.red = get_color_from_hsv(config_current.grid_color[0]);
        grid_color.green = get_color_from_hsv(config_current.grid_color[1]);
        grid_color.blue = get_color_from_hsv(config_current.grid_color[2]);
        grid_draw(&draw_offset, MAP_CELL_SIZE, MAP_WIDTH, MAP_HEIGHT, &grid_color);
    }

    camera_movement(grid_center.z, MAP_CELL_SIZE);
}