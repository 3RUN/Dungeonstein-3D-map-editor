
int is_pos_on_grid(VECTOR *pos)
{
    if (!pos)
    {
        return false;
    }

    return (pos->x >= 0 && pos->x < MAP_WIDTH && pos->y >= 0 && pos->y < MAP_HEIGHT);
}

int is_allowed_to_draw_map()
{
    if (is_settings_opened == true || is_popup_opened == true || is_help_opened == true)
    {
        return false;
    }

    if (is_pos_on_grid(vector(vec_mouse_on_grid.x, -vec_mouse_on_grid.y, 0)) == false)
    {
        return false;
    }

    return true;
}

void grid_get_mouse_pos(int *x, int *y)
{
    if (is_pos_on_grid(vector(vec_mouse_on_grid.x, -vec_mouse_on_grid.y, 0)))
    {
        *x = vec_mouse_on_grid.x;
        *y = -vec_mouse_on_grid.y;
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

void grid_initialize()
{
}

void grid_clear()
{
}

void grid_destroy()
{
}

void grid_update()
{
    VECTOR grid_draw_offset;
    vec_set(&grid_draw_offset, vector(0, 0, GRID_DRAW_OFFSET));
    vec_add(&grid_draw_offset, &vec_grid_center);

    if (is_grid_visible == true)
    {
        grid_draw(&grid_draw_offset, MAP_CELL_SIZE, MAP_WIDTH, MAP_HEIGHT, GRID_COLOR);
    }
}