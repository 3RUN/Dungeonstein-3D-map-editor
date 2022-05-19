
void map_draw_initialize()
{
    VECTOR map_center;
    vec_set(&map_center, vector((MAP_WIDTH / 2) * MAP_CELL_SIZE, -(MAP_HEIGHT / 2) * MAP_CELL_SIZE, MAP_Z_POS));
    ground_ent = ent_create(ground_plane_mdl, &map_center, NULL);

    set(ground_ent, POLYGON | TRANSLUCENT); // can't be INVISIBLE, because then 'mouse_ent' will ignore it...
    ground_ent->alpha = 0;
    vec_set(&ground_ent->scale_x, vector(MAP_WIDTH, MAP_HEIGHT, 1));
    c_setminmax(ground_ent);

    hovering_ent = ent_create(CUBE_MDL, &hovering_cell_pos, NULL);
    set(hovering_ent, PASSABLE | TRANSLUCENT | UNLIT | LIGHT);
    hovering_ent->alpha = HOVERING_ENT_ALPHA;
    hovering_ent->flags2 |= UNTOUCHABLE;
    vec_fill(&hovering_ent->scale_x, 2);
    vec_set(&hovering_ent->blue, COLOR_RED);
    hovering_ent->material = mtl_marker;
}

void map_draw_destroy()
{
    safe_remove(ground_ent);
    safe_remove(hovering_ent);
}

void map_draw_load_config(Config *config)
{
    if (!config)
    {
        return;
    }

    scancode_draw = engine_key_return_scancode_from_letter(config->input_draw);
    scancode_erase = engine_key_return_scancode_from_letter(config->input_erase);
    scancode_pick = engine_key_return_scancode_from_letter(config->input_pick);

    input_remove_on_key_binding(scancode_rotate);

    scancode_rotate = engine_key_return_scancode_from_letter(config->input_rotate);

    input_update_on_key_binding(scancode_rotate, map_draw_rotate);
}

void map_draw_trace()
{
    VECTOR to;
    vec_set(&to, &mouse_dir3d);
    vec_scale(&to, camera->clip_far);
    vec_add(&to, &mouse_pos3d);

    c_trace(&camera->x, &to, TRACE_FLAGS);
    if (trace_hit)
    {
        vec_set(&hovering_cell_pos, &target);
        vec_snap_to_grid(&hovering_cell_pos);
    }
}

void map_find_n_erase_player(Map *map)
{
    if (!map)
    {
        return;
    }

    int x = 0, y = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            Cell *cell = &map->cell[x][y];

            if (is_player_start(cell->object.type, cell->object.index) == false)
            {
                continue;
            }

            map_remove_object(map, cell);
            object_copy(&cell->object, NULL);
        }
    }
}

void map_find_n_erase_finish(Map *map)
{
    if (!map)
    {
        return;
    }

    int x = 0, y = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            Cell *cell = &map->cell[x][y];

            if (is_level_finish(cell->object.type, cell->object.index) == false)
            {
                continue;
            }

            map_remove_object(map, cell);
            object_copy(&cell->object, NULL);
        }
    }
}

void map_find_n_erase_teleport_out(Map *map, int id)
{
    if (!map)
    {
        return;
    }

    int x = 0, y = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            Cell *cell = &map->cell[x][y];

            if (is_teleport_out(cell->object.type, cell->object.index) == false)
            {
                continue;
            }

            if (id != cell->object.flag[1])
            {
                continue;
            }

            map_remove_object(map, cell);
            object_copy(&cell->object, NULL);
        }
    }
}

void map_draw_draw(Map *map, Cell *cell)
{
    if (!map || !cell)
    {
        return;
    }

    if (key_cam_rotate == true)
    {
        return;
    }

    if (drawing_mode == DRAWING_MODE_MAP)
    {
        cell->is_solid = false;
        cell->wall_index = preview_cell.wall_index;
        cell->ceiling_index = preview_cell.ceiling_index;
        cell->floor_index = preview_cell.floor_index;
        map_create_solid(map, cell);
    }
    else if (drawing_mode == DRAWING_MODE_OBJECT)
    {
        if (cell->is_solid == true)
        {
            return;
        }

        if (is_player_start(preview_cell.object.type, preview_cell.object.index))
        {
            map_find_n_erase_player(map);
        }
        else if (is_level_finish(preview_cell.object.type, preview_cell.object.index))
        {
            map_find_n_erase_finish(map);
        }
        else if (is_teleport_out(preview_cell.object.type, preview_cell.object.index))
        {
            map_find_n_erase_teleport_out(map, preview_cell.object.flag[1]);
        }

        cell->object.pan = preview_cell.object.pan;
        cell->object.is_occupied = true;
        cell->object.type = preview_cell.object.type;
        cell->object.index = preview_cell.object.index;

        int i = 0;
        for (i = 0; i < MAX_OBJECT_FLAGS; i++)
        {
            cell->object.flag[i] = preview_cell.object.flag[i];
        }
        map_create_object(map, cell);
    }
}

void map_draw_erase(Map *map, Cell *cell)
{
    if (!map || !cell)
    {
        return;
    }

    if (key_cam_rotate == true)
    {
        return;
    }

    if (cell->is_solid == true)
    {
        return;
    }

    if (drawing_mode == DRAWING_MODE_MAP)
    {
        map_remove_solid(map, cell);
        cell_copy(cell, NULL);
    }
    else if (drawing_mode == DRAWING_MODE_OBJECT)
    {
        map_remove_object(map, cell);
        object_copy(&cell->object, NULL);
    }
}

void map_draw_pick(Map *map, Cell *cell)
{
    if (!map || !cell)
    {
        return;
    }

    if (key_cam_rotate == true)
    {
        return;
    }

    if (cell->is_solid == true)
    {
        return;
    }

    if (drawing_mode == DRAWING_MODE_MAP)
    {
        preview_cell.is_solid = cell->is_solid;
        preview_cell.wall_index = cell->wall_index;
        preview_cell.ceiling_index = cell->ceiling_index;
        preview_cell.floor_index = cell->floor_index;
    }
    else if (drawing_mode == DRAWING_MODE_OBJECT)
    {
        if (cell->object.is_occupied == true)
        {
            preview_cell.object.pan = cell->object.pan;
            preview_cell.object.type = cell->object.type;
            preview_cell.object.index = cell->object.index;

            int i = 0;
            for (i = 0; i < MAX_OBJECT_FLAGS; i++)
            {
                preview_cell.object.flag[i] = cell->object.flag[i];
            }

            if (is_object_spawn_point(cell->object.type, cell->object.index))
            {
                params_spawn_point_refresh();
            }
            else if (is_light(cell->object.type, cell->object.index))
            {
                params_lights_refresh();
            }
        }
    }
}

void map_draw_rotate()
{
    Map *map = map_get_active(&def_episode);
    Cell *cell = &map->cell[mouse_grid_pos_x][mouse_grid_pos_y];

    int x = cell->x;
    int y = cell->y;

    int type = cell->object.type;
    int index = cell->object.index;

    if (cell->object.is_occupied == true && is_rotatable(type, index))
    {
        cell->object.pan = cycle(cell->object.pan + 90, 0, 360);
        map_rotate_object(cell);
    }
}

void map_shift_west()
{
    Map *active_map = map_get_active(&def_episode);
    if (!active_map)
    {
        return;
    }

    int x = 0, y = 0;
    for (x = 0; x < MAP_WIDTH; x++)
    {
        Cell saved;
        cell_copy(&saved, &active_map->cell[x][0]);

        for (y = 0; y < MAP_HEIGHT; y++)
        {
            Cell *from = &active_map->cell[x][y + 1];
            Cell *to = &active_map->cell[x][y];
            cell_copy(to, from);
        }

        cell_copy(&active_map->cell[x][MAP_HEIGHT - 1], &saved);
    }
    map_load(active_map);

    message_add("Map shifted to the West");
}

void map_shift_east()
{
    Map *active_map = map_get_active(&def_episode);
    if (!active_map)
    {
        return;
    }

    int x = 0, y = 0;
    for (x = 0; x < MAP_WIDTH; x++)
    {
        Cell saved;
        cell_copy(&saved, &active_map->cell[x][MAP_HEIGHT - 1]);

        for (y = MAP_HEIGHT - 1; y >= 0; y--)
        {
            Cell *from = &active_map->cell[x][y - 1];
            Cell *to = &active_map->cell[x][y];
            cell_copy(to, from);
        }

        cell_copy(&active_map->cell[x][0], &saved);
    }
    map_load(active_map);

    message_add("Map shifted to the East");
}

void map_shift_south()
{
    Map *active_map = map_get_active(&def_episode);
    if (!active_map)
    {
        return;
    }

    int x = 0, y = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        Cell saved;
        cell_copy(&saved, &active_map->cell[0][y]);

        for (x = 0; x < MAP_WIDTH; x++)
        {
            Cell *from = &active_map->cell[x + 1][y];
            Cell *to = &active_map->cell[x][y];
            cell_copy(to, from);
        }

        cell_copy(&active_map->cell[MAP_WIDTH - 1][y], &saved);
    }
    map_load(active_map);

    message_add("Map shifted to the South");
}

void map_shift_north()
{
    Map *active_map = map_get_active(&def_episode);
    if (!active_map)
    {
        return;
    }

    int x = 0, y = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        Cell saved;
        cell_copy(&saved, &active_map->cell[MAP_WIDTH - 1][y]);

        for (x = MAP_WIDTH - 1; x >= 0; x--)
        {
            Cell *from = &active_map->cell[x - 1][y];
            Cell *to = &active_map->cell[x][y];
            cell_copy(to, from);
        }

        cell_copy(&active_map->cell[0][y], &saved);
    }
    map_load(active_map);

    message_add("Map shifted to the North");
}

void map_prior()
{
    active_map_id--;
    active_map_id = clamp(active_map_id, 0, def_episode.map_count - 1);

    message_add(str_printf(NULL, "Moved to map %d", (long)active_map_id));

    Map *active_map = map_get_active(&def_episode);
    map_load(active_map);
}

void map_next()
{
    active_map_id++;
    active_map_id = clamp(active_map_id, 0, def_episode.map_count - 1);

    message_add(str_printf(NULL, "Moved to map %d", (long)active_map_id));

    Map *active_map = map_get_active(&def_episode);
    map_load(active_map);
}

void map_draw_update(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    key_draw = key_pressed(scancode_draw);
    key_erase = key_pressed(scancode_erase);
    key_pick = key_pressed(scancode_pick);

    map_draw_trace();
    vec_world_to_grid(&hovering_cell_pos, &mouse_grid_pos_x, &mouse_grid_pos_y);

    if (hovering_ent)
    {
        if (is_map_settings_visible == true || key_cam_rotate || is_mouse_cell_visible == false)
        {
            set(hovering_ent, INVISIBLE);
        }
        else
        {
            reset(hovering_ent, INVISIBLE);
        }

        hovering_ent->alpha = cycle(hovering_ent->alpha + 2 * time_step, 15, 35);

        vec_set(&hovering_ent->x, &hovering_cell_pos);
        hovering_ent->z += MAP_CELL_SIZE / 2;
    }

    if (key_draw)
    {
        tools_cooldown += time_frame / 16;
        while (tools_cooldown > COOLDOWN_TIME)
        {
            if (is_allowed_to_draw() == true)
            {
                Map *map = map_get_active(episode);
                Cell *cell = &map->cell[mouse_grid_pos_x][mouse_grid_pos_y];

                if (key_erase) // erase cell
                {
                    map_draw_erase(map, cell);
                }
                else if (key_pick) // pick cell
                {
                    map_draw_pick(map, cell);
                }
                else // draw cell
                {
                    map_draw_draw(map, cell);
                }
            }

            tools_cooldown -= COOLDOWN_TIME;
        }
    }
    else
    {
        tools_cooldown = 0;
    }
}