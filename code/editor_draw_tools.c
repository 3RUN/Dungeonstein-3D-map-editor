
int is_cell_allowed_rotation(int type, int asset)
{
    if (is_npc(type, asset) == true) // enemies/bosses
    {
        return true;
    }

    if (is_a_door(type, asset) == true) // doors
    {
        return true;
    }

    if (is_a_fence(type, asset) == true) // dirty fences
    {
        return true;
    }

    if (type == ASSET_TYPE_PROPS && asset == PROPS_SWITCH) // switch
    {
        return true;
    }

    if (type == ASSET_TYPE_EVENTS && asset == EVENT_PLAYER) // start position (player spawn)
    {
        return true;
    }

    if (type == ASSET_TYPE_EVENTS && asset == EVENT_NPC_TURN_POINT) // turning point for npcs
    {
        return true;
    }

    return false;
}

void editor_erase_player(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    Map *current_map = map_get_active(episode);
    if (!current_map)
    {
        return;
    }

    int x = 0, y = 0, id = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            Cell *cell = &current_map->cell[x][y];

            if (is_player_start(cell->type, cell->asset) == false)
            {
                continue;
            }

            editor_erase_cell(cell);
        }
    }
}

void editor_draw_cell(Episode *episode, Cell *to, Cell *from)
{
    if (!episode)
    {
        return;
    }

    if (!to || !from)
    {
        return;
    }

    if (is_player_start(from->type, from->asset) == true)
    {
        editor_erase_player(episode);
    }

    cell_copy(to, from);
    editor_grid_sprite_update_by_id(to);
    editor_grid_direction_sprite_update_by_id(to);
}

void editor_erase_cell(Cell *cell)
{
    if (!cell)
    {
        return;
    }

    cell->pan = CELL_DEF_PAN;

    cell_copy(cell, NULL);
    editor_grid_sprite_update_by_id(cell);
    editor_grid_direction_sprite_update_by_id(cell);
}

void editor_pick_tool(Cell *to, Cell *from)
{
    if (!to || !from)
    {
        return;
    }

    int type = from->type;
    int asset = from->asset;

    editor_selected_asset_type = editor_asset_types_combobox[type];
    editor_asset_type = type;
    editor_asset_index = asset;

    cell_copy(to, from);
    cell_copy(&preview_cell, from);
    editor_map_preview_update(type, asset);
}

void editor_draw_tools_update(Episode *episode, Cell *drawing_cell)
{
    if (!episode)
    {
        return;
    }

    Map *current_map = map_get_active(episode);
    if (!current_map)
    {
        return;
    }

    Cell *current_cell = &current_map->cell[mouse_x][mouse_y];
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
        }
        else
        {
            mouse_resume_drawing = true;
            mouse_draw_once = false;
        }
        return;
    }

    if (key_alt)
    {
        mouse_pointer = 3;
        str_cpy(current_tool_str, "Editing tool: pick tile;");
    }
    else if (key_shift)
    {
        mouse_pointer = 2;
        str_cpy(current_tool_str, "Editing tool: draw/erase/rotate (shift);");
    }
    else
    {
        str_cpy(current_tool_str, "Editing tool: draw/erase/rotate;");
    }

    var tool_x = 5;
    var tool_y = 20;
    draw_text(current_tool_str, tool_x, tool_y, COLOR_WHITE);

    if (key_r)
    {
        if (rotate_cell_once == true)
        {
            if (is_cell_allowed_rotation(current_cell->type, current_cell->asset) == true)
            {
                current_cell->pan -= 90;
                current_cell->pan = cycle(current_cell->pan, 0, 360);
                editor_grid_direction_sprite_update_by_id(current_cell);
                rotate_cell_once = false;
            }
        }
    }
    else
    {
        rotate_cell_once = true;
    }

    if (mouse_resume_drawing == false)
    {
        if (mouse_left)
        {
            if (mouse_draw_once == true)
            {
                mouse_resume_drawing = true;
                mouse_draw_once = false;
            }
        }

        return;
    }

    if (mouse_left)
    {
        if (key_alt)
        {
            if (mouse_draw_once == true)
            {
                editor_pick_tool(drawing_cell, current_cell);
                mouse_draw_once = false;
            }
        }
        else if (key_shift)
        {
            mouse_draw_timer += time_frame / 16;
            while (mouse_draw_timer > mouse_draw_cooldown)
            {
                editor_draw_cell(episode, current_cell, drawing_cell);
                mouse_draw_timer -= mouse_draw_cooldown;
            }
        }
        else
        {
            if (mouse_draw_once == true)
            {
                editor_draw_cell(episode, current_cell, drawing_cell);
                mouse_draw_once = false;
            }
        }
    }
    else
    {
        mouse_draw_timer = 0;
        mouse_draw_once = true;

        if (mouse_right)
        {
            if (!key_alt)
            {
                if (key_shift)
                {
                    mouse_erase_timer += time_frame / 16;
                    while (mouse_erase_timer > mouse_erase_cooldown)
                    {
                        editor_erase_cell(current_cell);
                        mouse_erase_timer -= mouse_erase_cooldown;
                    }
                }
                else
                {
                    if (mouse_erase_once == true)
                    {
                        editor_erase_cell(current_cell);
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
}