
int is_cell_allowed_rotation(Cell *cell)
{
    if (!cell)
    {
        return false;
    }

    if (cell->type == ASSET_TYPE_ENEMIES) // all enemies
    {
        return true;
    }

    if (cell->type == ASSET_TYPE_BOSSES) // all boses
    {
        return true;
    }

    if (cell->type == ASSET_TYPE_PROPS && cell->asset == PROPS_SWITCH) // switch
    {
        return true;
    }

    if (cell->type == ASSET_TYPE_EVENTS && cell->asset == EVENT_PLAYER) // player spawn point
    {
        return true;
    }

    if (cell->type == ASSET_TYPE_EVENTS && cell->asset == EVENT_NPC_TURN_POINT) // enemy/boss turn point
    {
        return true;
    }

    return false;
}

void editor_map_draw_cell(Cell *to, Cell *from)
{
    if (!to || !from)
    {
        return;
    }

    cell_copy(to, from);
    editor_grid_sprite_update_by_id(to->id, to->pan, to->type, to->asset);
}

void editor_map_erase_cell(Cell *cell)
{
    if (!cell)
    {
        return;
    }

    cell->pan = CELL_DEF_PAN;

    cell_copy(cell, NULL);
    editor_grid_sprite_update_by_id(cell->id, cell->pan, cell->type, cell->asset);
}

void editor_mouse_draw_update(Episode *episode, Cell *drawing_cell)
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
        return;
    }

    if (key_r)
    {
        if (rotate_cell_once == true)
        {
            if (is_cell_allowed_rotation(current_cell) == true)
            {
                current_cell->pan -= 90;
                current_cell->pan = cycle(current_cell->pan, 0, 360);
                editor_grid_sprite_update_by_id(current_cell->id, current_cell->pan, current_cell->type, current_cell->asset);
                rotate_cell_once = false;
            }
        }
    }
    else
    {
        rotate_cell_once = true;
    }

    if (mouse_left || mouse_right)
    {
        mouse_draw_timer += time_frame / 16;
        while (mouse_draw_timer > mouse_draw_cooldown)
        {
            if (mouse_left)
            {
                editor_map_draw_cell(current_cell, drawing_cell);
            }
            else if (mouse_right)
            {
                editor_map_erase_cell(current_cell);
            }
            mouse_draw_timer -= mouse_draw_cooldown;
        }
    }
    else
    {
        mouse_draw_timer = 0;
    }
}