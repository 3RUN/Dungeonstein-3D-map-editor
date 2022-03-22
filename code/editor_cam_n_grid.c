
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

void vec_world_to_grid(VECTOR *world_pos, var *x, var *y)
{
    if (!world_pos)
    {
        *x = -1;
        *y = -1;
        return;
    }

    *x = floor(world_pos->x / MAP_CELL_SIZE);
    *x = clamp(*x, -1, MAP_WIDTH);

    *y = floor(-world_pos->y / MAP_CELL_SIZE);
    *y = clamp(*y, -1, MAP_HEIGHT);
}

var is_pos_on_grid(VECTOR *pos)
{
    if (!pos)
    {
        return false;
    }

    return (pos->x >= 0 && pos->x < MAP_WIDTH && pos->y >= 0 && pos->y < MAP_HEIGHT);
}

var is_pos_within_camera(VECTOR *pos)
{
    if (!pos)
    {
        return false;
    }

    return (pos->x >= camera->pos_x && pos->x < camera->size_x && pos->y >= camera->pos_y && pos->y < camera->size_y);
}

var is_allowed_to_draw()
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

void grid_get_mouse_pos(var *x, var *y)
{
    if (is_allowed_to_draw() == true)
    {
        *x = mouse_on_grid.x;
        *y = -mouse_on_grid.y;
    }
    else
    {
        *x = -1;
        *y = -1;
    }
}

void grid_draw(VECTOR *center, var grid_size, var width, var height, COLOR *color)
{
    var lines_x = width + 1;
    var lines_y = height + 1;
    var bounds_x = (lines_x - 1) / 2.0 * grid_size;
    var bounds_y = (lines_y - 1) / 2.0 * grid_size;

    VECTOR start, end;
    vec_set(&start, center);
    vec_set(&end, center);
    start.x -= bounds_x;
    start.y -= bounds_y;
    end.x -= bounds_x;
    end.y += bounds_y;

    var i = 0;
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
        camera->pos_y = (EDITOR_TOP_BAR_HEIGHT * config_saved.font_scale);
        camera->size_x = screen_size.x;
        camera->size_y = screen_size.y - (EDITOR_TOP_BAR_HEIGHT * config_saved.font_scale);
        camera->size_x = screen_size.x - (EDITOR_SIDE_BAR_WIDTH * config_saved.font_scale);
    }
    else
    {
        camera->pos_x = 0;
        camera->pos_y = 0;
        camera->size_x = screen_size.x;
        camera->size_y = screen_size.y;
    }
}

void camera_topdown_movement(var grid_height, var grid_size)
{
    var is_allowed = is_allowed_to_draw();

    if (key_drag_map && is_allowed == true)
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

void camera_fp_movement()
{
    camera->pan = cycle(camera->pan - mickey.x / 6.5 * config_saved.mouse_sensitivity, 0, 360);
    camera->tilt = clamp(camera->tilt - mickey.y / 6.5 * config_saved.mouse_sensitivity, -90, 90);
    camera->roll = 0;

    VECTOR input;
    input.x = MOVEMENT_SPEED * (key_forward - key_backward);
    input.y = MOVEMENT_SPEED * (key_strafe_left - key_strafe_right);
    input.z = MOVEMENT_SPEED * (key_surface - key_dive);

    if (key_run)
    {
        input.x *= RUN_FACTOR;
        input.y *= RUN_FACTOR;
    }

    vec_add(&camera->x, vec_rotate(&input, &camera->pan));
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

void camera_update_input_from_config(CONFIG *config)
{
    scancode_forward = engine_key_return_scancode_from_letter(config->input_forward);
    scancode_backward = engine_key_return_scancode_from_letter(config->input_backward);
    scancode_strafe_left = engine_key_return_scancode_from_letter(config->input_strafe_left);
    scancode_strafe_right = engine_key_return_scancode_from_letter(config->input_strafe_right);
    scancode_surface = engine_key_return_scancode_from_letter(config->input_surface);
    scancode_dive = engine_key_return_scancode_from_letter(config->input_dive);
    scancode_run = engine_key_return_scancode_from_letter(config->input_run);
    scancode_drag_map = engine_key_return_scancode_from_letter(config->input_drag_map);
}

void camera_fog_from_config()
{
    camera->fog_end = FOG_MAX_END;
    camera->fog_start = FOG_MAX_END;

    camera->clip_near = 0.1;
    camera->clip_far = FOG_MAX_END * 1.25;

    fog_color = 4;
    change_color_from_hsv(&sky_color.blue, config_current.background_color[0], config_current.background_color[1], config_current.background_color[2]);
    vec_set(&d3d_fogcolor4, &sky_color);
}

void camera_fog_from_map(Map *map)
{
    if (!map)
    {
        return;
    }

    camera->fog_end = map->fog_end;
    camera->fog_start = map->fog_start;

    camera->clip_near = 0.1;
    camera->clip_far = FOG_MAX_END * 1.25;

    fog_color = 4;
    change_color_from_hsv(&d3d_fogcolor4.blue, map->fog_color[0], map->fog_color[1], map->fog_color[2]);

    if (map->weather_id > WEATHER_CLEAR || map->is_ceiling_visible == false)
    {
        change_color_from_hsv(&sky_color.blue, map->ceiling_color[0], map->ceiling_color[1], map->ceiling_color[2]);
    }
    else
    {
        vec_set(&sky_color, &d3d_fogcolor4);
    }
}

void camera_reset(Map *map, var state)
{
    if (!map)
    {
        return;
    }

    if (state == EDITOR_STATE_MAP_SETTINGS || state == EDITOR_STATE_BUILD)
    {
        if (state == EDITOR_STATE_BUILD)
        {
            mouse_disable();
        }

        var x = 0, y = 0, player_found = false;
        for (y = 0; y < MAP_HEIGHT; y++)
        {
            for (x = 0; x < MAP_WIDTH; x++)
            {
                Cell *cell = &map->cell[x][y];
                if (!cell)
                {
                    continue;
                }

                if (is_player_start(cell->type, cell->asset) == false)
                {
                    continue;
                }

                vec_set(&camera->x, &cell->worldpos);
                vec_set(&camera->pan, vector(cell->pan, 0, 0));
                return;
            }
        }

        vec_set(&camera->x, vector(0, 0, MAP_Z_POS));
        vec_set(&camera->pan, vector(DEF_CELL_PAN, 0, 0));
    }
    else
    {
        mouse_enable(true);

        camera->arc = CAMERA_ARC;
        vec_set(&camera->pan, vector(90, -90, 0));
        camera->x = camera_center.x - fcos(camera->pan, camera->skill_x);
        camera->y = camera_center.y - fsin(camera->pan, camera->skill_x);
        camera->z = camera_center.z - fsin(camera->tilt, camera->skill_y);
    }
}

void camera_n_grid_update(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    Map *active_map = map_get_active(episode);
    if (!active_map)
    {
        return;
    }

    camera_auto_resize();

    VECTOR draw_offset;
    vec_set(&draw_offset, vector(0, 0, GRID_DRAW_OFFSET));
    vec_add(&draw_offset, &grid_center);

    key_forward = key_pressed(scancode_forward);
    key_backward = key_pressed(scancode_backward);
    key_strafe_left = key_pressed(scancode_strafe_left);
    key_strafe_right = key_pressed(scancode_strafe_right);
    key_surface = key_pressed(scancode_surface);
    key_dive = key_pressed(scancode_dive);
    key_run = key_pressed(scancode_run);
    key_drag_map = key_pressed(scancode_drag_map);

    if (editor_state == EDITOR_STATE_MAP_SETTINGS)
    {
        camera_fog_from_map(&map_settings);
    }
    else if (editor_state == EDITOR_STATE_BUILD)
    {
        camera_fp_movement();
        camera_fog_from_map(active_map);
    }
    else
    {
        if (is_grid_visible == true)
        {
            COLOR grid_color;
            grid_color.red = get_color_from_hsv(config_current.grid_color[0]);
            grid_color.green = get_color_from_hsv(config_current.grid_color[1]);
            grid_color.blue = get_color_from_hsv(config_current.grid_color[2]);
            grid_draw(&draw_offset, MAP_CELL_SIZE, MAP_WIDTH, MAP_HEIGHT, &grid_color);
        }
        camera_topdown_movement(grid_center.z, MAP_CELL_SIZE);
        camera_fog_from_config();
    }
}