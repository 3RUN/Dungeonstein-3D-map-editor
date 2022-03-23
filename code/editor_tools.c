
void get_cell_info(Cell *cell, STRING **out)
{
    if (!cell)
    {
        return NULL;
    }

    VECTOR cell_pos;
    vec_set(&cell_pos, &cell->worldpos);
    var cell_pan = cell->pan;

    int cell_id = cell->id;
    int cell_x = cell->x;
    int cell_y = cell->y;

    int cell_type = cell->type;
    int cell_asset = cell->asset;

    int cell_flag = cell->flag;
    int cell_event_type = cell->event_type;
    int cell_event_id = cell->event_id;
    int cell_temp_skill = cell->temp_skill;

    str_printf(*out, "world position:\nx = %d; y = %d; z = %d;\n\ngrid position:\nx = %d; y = %d;\n\npan = %.0f;\nid = %d;", (long)cell_pos.x, (long)cell_pos.y, (long)cell_pos.z, (long)cell_x, (long)cell_y, (double)cell_pan, (long)cell_id);

    if (cell_type >= 0 && cell_asset >= 0)
    {
        str_cat(*out, "\n");

        // asset type and index
        if (cell_type == ASSET_TYPE_WALLS)
        {
            str_cat(*out, "\ntype = wall;");
        }
        else if (cell_type == ASSET_TYPE_PROPS)
        {
            str_cat(*out, "\ntype = props;");
        }
        else if (cell_type == ASSET_TYPE_EVENTS)
        {
            str_cat(*out, "\ntype = event;");
        }
        else if (cell_type == ASSET_TYPE_ITEMS)
        {
            str_cat(*out, "\ntype = item;");
        }
        else if (cell_type == ASSET_TYPE_ENEMIES)
        {
            str_cat(*out, "\ntype = enemy;");
        }
        else if (cell_type == ASSET_TYPE_BOSSES)
        {
            str_cat(*out, "\ntype = boss;");
        }
        str_cat(*out, "\ndesc = ");
        str_cat(*out, asset_get_desc(cell_type, cell_asset));
        str_cat(*out, ";");

        // parameters
        if (cell_type == ASSET_TYPE_WALLS && cell_asset != WALLS_ELEVATOR_SWITCH)
        {
            str_cat(*out, "\n\nparams:");
            if (cell_flag == true)
            {
                str_cat(*out, "\n* secret wall;");
                str_cat(*out, "\n* activation: ");
                if (cell_event_type == 0)
                {
                    str_cat(*out, "on interaction;");
                }
                else if (cell_event_type == 1)
                {
                    str_cat(*out, str_printf(NULL, "trigger zone id = %d;", (long)cell_event_id));
                }
                else if (cell_event_type == 2)
                {
                    str_cat(*out, str_printf(NULL, "switch id = %d;", (long)cell_event_id));
                }
            }
            else
            {
                str_cat(*out, "\n* solid wall;");
            }
        }
        else if (is_finish_elevator(cell_type, cell_asset) == true)
        {
            str_cat(*out, "\n\nparams:");
            str_cat(*out, "\n* finish level switch;");
        }
        else if (cell_type == ASSET_TYPE_PROPS && cell_asset == PROPS_FENCE || is_door(cell_type, cell_asset) == true || is_switch(cell_type, cell_asset) == true)
        {
            str_cat(*out, "\n\nparams:");
            if (cell_asset == PROPS_FENCE)
            {
                str_cat(*out, "\n* activation: ");
                if (cell_event_type == 0)
                {
                    str_cat(*out, "none (static);");
                }
                else if (cell_event_type == 1)
                {
                    str_cat(*out, "on interaction;");
                }
                else if (cell_event_type == 2)
                {
                    str_cat(*out, str_printf(NULL, "trigger zone id = %d;", (long)cell_event_id));
                }
                else if (cell_event_type == 3)
                {
                    str_cat(*out, str_printf(NULL, "switch id = %d;", (long)cell_event_id));
                }
            }
            else if (cell_asset == PROPS_DOOR)
            {
                str_cat(*out, "\n* activation: ");
                if (cell_event_type == 0)
                {
                    str_cat(*out, "on interaction;");
                }
                else if (cell_event_type == 1)
                {
                    str_cat(*out, str_printf(NULL, "trigger zone id = %d;", (long)cell_event_id));
                }
                else if (cell_event_type == 2)
                {
                    str_cat(*out, str_printf(NULL, "switch id = %d;", (long)cell_event_id));
                }
                else if (cell_event_type == 3)
                {
                    str_cat(*out, "none (static);");
                }
            }
            else if (cell_asset == PROPS_DOOR_LOCKED)
            {
                str_cat(*out, "\n* requires: ");
                if (cell_event_type == 0)
                {
                    str_cat(*out, "Key blue");
                }
                else if (cell_event_type == 1)
                {
                    str_cat(*out, "Key red");
                }
                else if (cell_event_type == 2)
                {
                    str_cat(*out, "Key yellow");
                }
                str_cat(*out, ";");
            }
            else if (cell_asset == PROPS_SWITCH)
            {
                str_cat(*out, str_printf(NULL, "\n* switch with id: %d;", (long)cell_event_id));
            }
        }
        else if (is_player_start(cell_type, cell_asset) == true || is_trigger_zone(cell_type, cell_asset) == true || is_spawn_object(cell_type, cell_asset) == true)
        {
            if (cell_asset == EVENT_PLAYER)
            {
                str_cat(*out, "\n\nparams:");
                str_cat(*out, "\n* start weapon: ");
                if (cell_event_id == 0)
                {
                    str_cat(*out, "knife;");
                }
                else if (cell_event_id == 1)
                {
                    str_cat(*out, "pistol;");
                }
                else if (cell_event_id == 2)
                {
                    str_cat(*out, "shotgun;");
                }
                else if (cell_event_id == 3)
                {
                    str_cat(*out, "chaingun;");
                }
                else if (cell_event_id == 4)
                {
                    str_cat(*out, "rocketlauncher;");
                }
            }
            else if (cell_asset == EVENT_TRIGGER_ZONE)
            {
                str_cat(*out, "\n\nparams:");
                str_cat(*out, str_printf(NULL, "\n* trigger zone with id: %d;", (long)cell_event_id));
            }
            else if (cell_asset == EVENT_SPAWN_OBJECT)
            {
                str_cat(*out, "\n\nparams:");

                // activation
                str_cat(*out, "\n* activation: ");
                if (cell_event_type == 0)
                {
                    str_cat(*out, "on creation;");
                }
                else if (cell_event_type == 1)
                {
                    str_cat(*out, str_printf(NULL, "trigger zone id = %d;", (long)cell_event_id));
                }
                else if (cell_event_type == 2)
                {
                    str_cat(*out, str_printf(NULL, "switch id = %d;", (long)cell_event_id));
                }

                // category
                str_cat(*out, "\n* spawn: ");
                if (cell_flag == 0) // items
                {
                    str_cat(*out, "Item");
                    str_cat(*out, ": ");

                    if (cell_temp_skill == 0)
                    {
                        str_cat(*out, "Key blue");
                    }
                    else if (cell_temp_skill == 1)
                    {
                        str_cat(*out, "Key red");
                    }
                    else if (cell_temp_skill == 2)
                    {
                        str_cat(*out, "Key yellow");
                    }
                    else if (cell_temp_skill == 3)
                    {
                        str_cat(*out, "Small medkit");
                    }
                    else if (cell_temp_skill == 4)
                    {
                        str_cat(*out, "Big medkit");
                    }
                    str_cat(*out, ";");
                }
                else if (cell_flag == 1) // weapons / ammo
                {
                    str_cat(*out, "Weapon");
                    str_cat(*out, ": ");

                    if (cell_temp_skill == 0)
                    {
                        str_cat(*out, "Ammo box");
                    }
                    else if (cell_temp_skill == 1)
                    {
                        str_cat(*out, "Pistol weapon");
                    }
                    else if (cell_temp_skill == 2)
                    {
                        str_cat(*out, "Pistol ammo");
                    }
                    else if (cell_temp_skill == 3)
                    {
                        str_cat(*out, "Shotgun weapon");
                    }
                    else if (cell_temp_skill == 4)
                    {
                        str_cat(*out, "Shotgun ammo");
                    }
                    else if (cell_temp_skill == 5)
                    {
                        str_cat(*out, "SMG weapon");
                    }
                    else if (cell_temp_skill == 6)
                    {
                        str_cat(*out, "SMG ammo");
                    }
                    else if (cell_temp_skill == 7)
                    {
                        str_cat(*out, "Machinegun weapon");
                    }
                    else if (cell_temp_skill == 8)
                    {
                        str_cat(*out, "Machinegun ammo");
                    }
                    else if (cell_temp_skill == 9)
                    {
                        str_cat(*out, "Rocketlauncher weapon");
                    }
                    else if (cell_temp_skill == 10)
                    {
                        str_cat(*out, "Rocketlauncher ammo");
                    }
                    str_cat(*out, ";");
                }
                else if (cell_flag == 2) // enemies
                {
                    str_cat(*out, "Enemy");
                    str_cat(*out, ": ");

                    if (cell_temp_skill == 0)
                    {
                        str_cat(*out, "Rat");
                    }
                    else if (cell_temp_skill == 1)
                    {
                        str_cat(*out, "Dog");
                    }
                    else if (cell_temp_skill == 2)
                    {
                        str_cat(*out, "Guard pistol");
                    }
                    else if (cell_temp_skill == 3)
                    {
                        str_cat(*out, "Guard shotgun");
                    }
                    else if (cell_temp_skill == 4)
                    {
                        str_cat(*out, "Soldier SMG");
                    }
                    else if (cell_temp_skill == 5)
                    {
                        str_cat(*out, "Suicide bomber");
                    }
                    else if (cell_temp_skill == 6)
                    {
                        str_cat(*out, "Zombie");
                    }
                    else if (cell_temp_skill == 7)
                    {
                        str_cat(*out, "Support machinegun");
                    }
                    else if (cell_temp_skill == 8)
                    {
                        str_cat(*out, "Support rocketlauncher");
                    }
                    str_cat(*out, ";");
                }
                else if (cell_flag == 3) // bosses
                {
                    str_cat(*out, "Boss");
                    str_cat(*out, ": ");

                    if (cell_temp_skill == 0)
                    {
                        str_cat(*out, "Uber soldier");
                    }
                    else if (cell_temp_skill == 1)
                    {
                        str_cat(*out, "Uber officer");
                    }
                    else if (cell_temp_skill == 2)
                    {
                        str_cat(*out, "Uber mutant");
                    }
                    else if (cell_temp_skill == 3)
                    {
                        str_cat(*out, "Mecha soldier");
                    }
                    else if (cell_temp_skill == 4)
                    {
                        str_cat(*out, "Demon");
                    }
                    str_cat(*out, ";");
                }
            }
        }
        else if (is_effect(cell_type, cell_asset) == true)
        {
            str_cat(*out, "\n\nparams:");

            str_cat(*out, "\n* do damage: ");
            if (cell_flag == true)
            {
                str_cat(*out, "true;");
            }
            else
            {
                str_cat(*out, "false;");
            }

            // activation
            str_cat(*out, "\n* activation: ");
            if (cell_event_type == 0)
            {
                str_cat(*out, "on creation;");
            }
            else if (cell_event_type == 1)
            {
                str_cat(*out, str_printf(NULL, "trigger zone id = %d;", (long)cell_event_id));
            }
            else if (cell_event_type == 2)
            {
                str_cat(*out, str_printf(NULL, "switch id = %d;", (long)cell_event_id));
            }
        }
        else if (is_enemy(cell_type, cell_asset) == true)
        {
            str_cat(*out, "\n\nparams:");

            str_cat(*out, "\n* behaviour: ");
            if (cell_temp_skill == 0)
            {
                str_cat(*out, "wait");
            }
            else if (cell_temp_skill == 1)
            {
                str_cat(*out, "deaf");
            }
            else if (cell_temp_skill == 2)
            {
                str_cat(*out, "patrol");
            }
            str_cat(*out, ";");

            if (cell_flag == true)
            {
                str_cat(*out, "\n* drop item: ");
                if (cell_event_type == 0)
                {
                    str_cat(*out, "Key blue");
                }
                else if (cell_event_type == 1)
                {
                    str_cat(*out, "Key red");
                }
                else if (cell_event_type == 2)
                {
                    str_cat(*out, "Key yellow");
                }
                else if (cell_event_type == 3)
                {
                    str_cat(*out, "Small medkit");
                }
                else if (cell_event_type == 4)
                {
                    str_cat(*out, "Big medkit");
                }
                else if (cell_event_type == 5)
                {
                    str_cat(*out, "Ammo from held weapon");
                }
                else if (cell_event_type == 6)
                {
                    str_cat(*out, "Held weapon");
                }
                str_cat(*out, ";");
            }
            else
            {
                str_cat(*out, "\n* drop item: false;");
            }
        }
        else if (is_boss(cell_type, cell_asset) == true)
        {
            str_cat(*out, "\n\nparams:");

            str_cat(*out, "\n* behaviour: ");
            if (cell_temp_skill == 0)
            {
                str_cat(*out, "wait");
            }
            else if (cell_temp_skill == 1)
            {
                str_cat(*out, "deaf");
            }
            else if (cell_temp_skill == 2)
            {
                str_cat(*out, "patrol");
            }
            str_cat(*out, ";");

            if (cell_flag == true)
            {
                str_cat(*out, "\n* drop item: ");
                if (cell_event_type == 0)
                {
                    str_cat(*out, "Key blue");
                }
                else if (cell_event_type == 1)
                {
                    str_cat(*out, "Key red");
                }
                else if (cell_event_type == 2)
                {
                    str_cat(*out, "Key yellow");
                }
                else if (cell_event_type == 3)
                {
                    str_cat(*out, "Small medkit");
                }
                else if (cell_event_type == 4)
                {
                    str_cat(*out, "Big medkit");
                }
                str_cat(*out, ";");
            }
            else
            {
                str_cat(*out, "\n* drop item: false;");
            }
        }
    }
}

void find_n_erase_player(Map *map)
{
    if (!map)
    {
        return;
    }

    int x = 0, y = 0, id = 0;
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

    int x = 0, y = 0, id = 0;
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

    int type = from->type;
    int asset = from->asset;

    selected_asset_category = asset_categories_combobox[type];
    selected_type = type;
    selected_asset = asset;

    cell_copy(to, from);
    cell_copy(&preview_cell, from);
    editor_preview_update(type, asset);
}

void editor_tools_update_input_from_config(Config *config)
{
    scancode_draw = engine_key_return_scancode_from_letter(config->input_draw);
    scancode_erase = engine_key_return_scancode_from_letter(config->input_erase);
    scancore_pick = engine_key_return_scancode_from_letter(config->input_pick);
    scancode_rotate = engine_key_return_scancode_from_letter(config->input_rotate);
    scancode_rapid = engine_key_return_scancode_from_letter(config->input_run);
}

void editor_tools_update(Map *map, Cell *p_cell)
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