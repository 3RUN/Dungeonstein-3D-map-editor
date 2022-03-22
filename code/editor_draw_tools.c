
void find_n_erase_player(Map *map)
{
    if (!map)
    {
        return;
    }

    var x = 0, y = 0, id = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            Cell *cell = &map->cell[x][y];

            if (is_player_start(cell->type, cell->asset) == false)
            {
                continue;
            }

            erase_cell(cell);
        }
    }
}

void find_n_erase_finish(Map *map)
{
    if (!map)
    {
        return;
    }

    var x = 0, y = 0, id = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            Cell *cell = &map->cell[x][y];

            if (is_finish_elevator(cell->type, cell->asset) == false)
            {
                continue;
            }

            erase_cell(cell);
        }
    }
}

void draw_cell(Map *map, Cell *to, Cell *from)
{
    if (!map)
    {
        return;
    }

    if (!to || !from)
    {
        return;
    }

    if (is_player_start(from->type, from->asset) == true)
    {
        find_n_erase_player(map);
    }
    else if (is_finish_elevator(from->type, from->asset) == true)
    {
        find_n_erase_finish(map);
    }

    cell_copy(to, from);
    map_sketch_sprite_update_from_cell(to);
}

void erase_cell(Cell *cell)
{
    if (!cell)
    {
        return;
    }

    cell->pan = DEF_CELL_PAN;

    cell_copy(cell, NULL);
    map_sketch_sprite_update_from_cell(cell);
}

void pick_cell(Cell *to, Cell *from)
{
    if (!to || !from)
    {
        return;
    }

    if (from->type < 0)
    {
        return;
    }

    var type = from->type;
    var asset = from->asset;

    selected_asset_category = asset_categories_combobox[type];
    selected_type = type;
    selected_asset = asset;

    cell_copy(to, from);
    cell_copy(&preview_cell, from);
    preview_update(type, asset);
}

void tools_update_input_from_config(CONFIG *config)
{
    scancode_draw = engine_key_return_scancode_from_letter(config->input_draw);
    scancode_erase = engine_key_return_scancode_from_letter(config->input_erase);
    scancore_pick = engine_key_return_scancode_from_letter(config->input_pick);
    scancode_rotate = engine_key_return_scancode_from_letter(config->input_rotate);
    scancode_rapid = engine_key_return_scancode_from_letter(config->input_run);
}

void tools_update(Map *map, Cell *p_cell)
{
    if (!map || !p_cell)
    {
        return;
    }

    Cell *current_cell = &map->cell[mouse_x][mouse_y];
    if (!current_cell)
    {
        return;
    }

    if (is_allowed_to_draw() == false)
    {
        if (is_top_bar_used == true)
        {
            mouse_resume_drawing = false;
            mouse_draw_once = true;
            mouse_erase_once = true;
        }
        else
        {
            mouse_resume_drawing = true;
            mouse_draw_once = false;
            mouse_erase_once = false;
        }
        return;
    }

    key_draw = key_pressed(scancode_draw);
    key_erase = key_pressed(scancode_erase);
    key_pick = key_pressed(scancore_pick);
    key_rotate = key_pressed(scancode_rotate);
    key_rapid = key_pressed(scancode_rapid);

    if (mouse_resume_drawing == false)
    {
        if (key_draw || key_erase)
        {
            if (mouse_draw_once == true)
            {
                mouse_resume_drawing = true;
                mouse_draw_once = false;
                mouse_erase_once = false;
            }
        }

        return;
    }

    // draw and erase
    if (key_draw)
    {
        if (key_pick)
        {
            if (mouse_draw_once == true)
            {
                pick_cell(p_cell, current_cell);
                mouse_draw_once = false;
            }
        }
        else if (key_rapid)
        {
            mouse_draw_timer += time_frame / 16;
            while (mouse_draw_timer > mouse_draw_cooldown)
            {
                draw_cell(map, current_cell, p_cell);
                mouse_draw_timer -= mouse_draw_cooldown;
            }
        }
        else
        {
            if (mouse_draw_once == true)
            {
                draw_cell(map, current_cell, p_cell);
                mouse_draw_once = false;
            }
        }
    }
    else
    {
        mouse_draw_timer = 0;
        mouse_draw_once = true;

        if (key_erase)
        {
            if (!key_pick)
            {
                if (key_rapid)
                {
                    mouse_erase_timer += time_frame / 16;
                    while (mouse_erase_timer > mouse_erase_cooldown)
                    {
                        erase_cell(current_cell);
                        mouse_erase_timer -= mouse_erase_cooldown;
                    }
                }
                else
                {
                    if (mouse_erase_once == true)
                    {
                        erase_cell(current_cell);
                        mouse_erase_once = false;
                    }
                }
            }
        }
        else
        {
            mouse_erase_timer = 0;
            mouse_erase_once = true;
        }
    }

    // rotate cell
    if (key_rotate)
    {
        if (rotate_cell_once == true)
        {
            if (is_rotatable(current_cell->type, current_cell->asset) == true)
            {
                current_cell->pan -= 90;
                current_cell->pan = cycle(current_cell->pan, 0, 360);
                map_sketch_sprite_update_from_cell(current_cell);
                rotate_cell_once = false;
            }
        }
    }
    else
    {
        rotate_cell_once = true;
    }
}