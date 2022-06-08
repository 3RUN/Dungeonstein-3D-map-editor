
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

void vec_snap_to_grid(VECTOR *pos)
{
    if (!pos)
    {
        return;
    }

    pos->x += (MAP_CELL_SIZE / 2) * sign(pos->x);
    pos->x = (integer(pos->x / MAP_CELL_SIZE) * MAP_CELL_SIZE);
    pos->y += (MAP_CELL_SIZE / 2) * sign(pos->y);
    pos->y = (integer(pos->y / MAP_CELL_SIZE) * MAP_CELL_SIZE);
    pos->z = MAP_Z_POS;
}

void vec_world_to_grid(VECTOR *pos, int *x, int *y)
{
    if (!pos)
    {
        *x = -1;
        *y = -1;
        return;
    }

    *x = floor(pos->x / MAP_CELL_SIZE);
    *x = clamp(*x, -1, MAP_WIDTH);

    *y = floor(-pos->y / MAP_CELL_SIZE);
    *y = clamp(*y, -1, MAP_HEIGHT);
}

int is_allowed_to_draw()
{
    if (is_topbar_used == true || is_sidebuttons_used == true)
    {
        return false;
    }

    if (is_popup_opened == true || is_asset_list_visible == true)
    {
        return false;
    }

    if (editor_state != EDITOR_STATE_EDIT)
    {
        return false;
    }

    if (is_map_settings_visible == true)
    {
        return false;
    }

    if (is_pos_on_grid(vector(mouse_grid_pos_x, mouse_grid_pos_y, 0)) == false)
    {
        return false;
    }

    if (is_pos_within_camera(vector(mouse_pos.x, mouse_pos.y, 0)) == false)
    {
        return false;
    }

    if (mouse_ent != ground_ent)
    {
        return false;
    }

    return true;
}

void grid_update()
{
    VECTOR draw_offset, grid_center;
    vec_set(&draw_offset, vector(0, 0, GRID_DRAW_OFFSET));
    vec_set(&grid_center, vector((MAP_WIDTH / 2) * MAP_CELL_SIZE, -(MAP_HEIGHT / 2) * MAP_CELL_SIZE, MAP_Z_POS));
    vec_add(&draw_offset, &grid_center);

    if (is_grid_visible == true)
    {
        COLOR grid_color;
        grid_color.red = get_color_from_hsv(config_current.grid_color[0]);
        grid_color.green = get_color_from_hsv(config_current.grid_color[1]);
        grid_color.blue = get_color_from_hsv(config_current.grid_color[2]);
        draw_grid3d(&draw_offset, MAP_CELL_SIZE, MAP_WIDTH, MAP_HEIGHT, &grid_color);
    }
}