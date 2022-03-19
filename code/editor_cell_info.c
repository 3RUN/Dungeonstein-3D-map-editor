
STRING *get_cell_info(Cell *cell)
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

    STRING *info_str = "";
    str_printf(info_str, "world position:\nx = %d; y = %d; z = %d;\n\ngrid position:\nx = %d; y = %d;\n\npan = %.0f;\nid = %d;", (long)cell_pos.x, (long)cell_pos.y, (long)cell_pos.z, (long)cell_x, (long)cell_y, (double)cell_pan, (long)cell_id);

    if (cell_type >= 0 && cell_asset >= 0)
    {
        str_cat(info_str, "\n");

        // asset type and index
        if (cell_type == ASSET_TYPE_WALLS)
        {
            str_cat(info_str, "\ntype = wall;");
        }
        else if (cell_type == ASSET_TYPE_PROPS)
        {
            str_cat(info_str, "\ntype = props;");
        }
        else if (cell_type == ASSET_TYPE_EVENTS)
        {
            str_cat(info_str, "\ntype = event;");
        }
        else if (cell_type == ASSET_TYPE_ITEMS)
        {
            str_cat(info_str, "\ntype = item;");
        }
        else if (cell_type == ASSET_TYPE_ENEMIES)
        {
            str_cat(info_str, "\ntype = enemy;");
        }
        else if (cell_type == ASSET_TYPE_BOSSES)
        {
            str_cat(info_str, "\ntype = boss;");
        }
        str_cat(info_str, "\ndesc = ");
        str_cat(info_str, asset_get_desc(cell_type, cell_asset));
        str_cat(info_str, ";");

        // parameters
        if (cell_type == ASSET_TYPE_WALLS && cell_asset != TOTAL_WALL_TEXTURES - 1)
        {
            str_cat(info_str, "\n\nparams:");
            if (cell_flag == true)
            {
                str_cat(info_str, "\n* secret wall;");
                str_cat(info_str, "\n* activation: ");
                if (cell_event_type == 0)
                {
                    str_cat(info_str, "on interaction;");
                }
                else if (cell_event_type == 1)
                {
                    str_cat(info_str, str_printf(NULL, "trigger zone id = %d;", (long)cell_event_id));
                }
                else if (cell_event_type == 2)
                {
                    str_cat(info_str, str_printf(NULL, "switch id = %d;", (long)cell_event_id));
                }
            }
            else
            {
                str_cat(info_str, "\n* solid wall;");
            }
        }
        else if (cell_type == ASSET_TYPE_WALLS && cell_asset == TOTAL_WALL_TEXTURES - 1)
        {
            str_cat(info_str, "\n\nparams:");
            str_cat(info_str, "\n* finish level switch;");
        }
        else if (cell_type == ASSET_TYPE_PROPS && cell_asset == PROPS_FENCE || cell_type == ASSET_TYPE_PROPS && cell_asset == PROPS_FENCE_DIRTY || cell_type == ASSET_TYPE_PROPS && cell_asset == PROPS_DOOR || cell_type == ASSET_TYPE_PROPS && cell_asset == PROPS_DOOR_ELEVATOR || cell_type == ASSET_TYPE_PROPS && cell_asset == PROPS_DOOR_LOCKED || cell_type == ASSET_TYPE_PROPS && cell_asset == PROPS_SWITCH)
        {
            str_cat(info_str, "\n\nparams:");
            if (cell_asset == PROPS_FENCE || cell_asset == PROPS_FENCE_DIRTY || cell_asset == PROPS_DOOR || cell_asset == PROPS_DOOR_ELEVATOR)
            {
                str_cat(info_str, "\n* activation: ");
                if (cell_event_type == 0)
                {
                    str_cat(info_str, "on interaction;");
                }
                else if (cell_event_type == 1)
                {
                    str_cat(info_str, str_printf(NULL, "trigger zone id = %d;", (long)cell_event_id));
                }
                else if (cell_event_type == 2)
                {
                    str_cat(info_str, str_printf(NULL, "switch id = %d;", (long)cell_event_id));
                }
            }
            else if (cell_asset == PROPS_DOOR_LOCKED)
            {
                str_cat(info_str, "\n* requires: ");
                if (cell_event_type == 0)
                {
                    str_cat(info_str, "Key blue");
                }
                else if (cell_event_type == 1)
                {
                    str_cat(info_str, "Key red");
                }
                else if (cell_event_type == 2)
                {
                    str_cat(info_str, "Key yellow");
                }
                str_cat(info_str, ";");
            }
            else if (cell_asset == PROPS_SWITCH)
            {
                str_cat(info_str, str_printf(NULL, "\n* switch with id: %d;", (long)cell_event_id));
            }
        }
        else if (cell_type == ASSET_TYPE_EVENTS && cell_asset == EVENT_TRIGGER_ZONE || cell_type == ASSET_TYPE_EVENTS && cell_asset == EVENT_SPAWN_OBJECT)
        {
            if (cell_asset == EVENT_TRIGGER_ZONE)
            {
                str_cat(info_str, "\n\nparams:");
                str_cat(info_str, str_printf(NULL, "\n* trigger zone with id: %d;", (long)cell_event_id));
            }
            else if (cell_asset == EVENT_SPAWN_OBJECT)
            {
                str_cat(info_str, "\n\nparams:");

                // activation
                str_cat(info_str, "\n* activation: ");
                if (cell_event_type == 0)
                {
                    str_cat(info_str, "on creation;");
                }
                else if (cell_event_type == 1)
                {
                    str_cat(info_str, str_printf(NULL, "trigger zone id = %d;", (long)cell_event_id));
                }
                else if (cell_event_type == 2)
                {
                    str_cat(info_str, str_printf(NULL, "switch id = %d;", (long)cell_event_id));
                }

                // category
                str_cat(info_str, "\n* spawn: ");
                if (cell_flag == 0) // items
                {
                    str_cat(info_str, "Item");
                    str_cat(info_str, ": ");

                    if (cell_temp_skill == 0)
                    {
                        str_cat(info_str, "Key blue");
                    }
                    else if (cell_temp_skill == 1)
                    {
                        str_cat(info_str, "Key red");
                    }
                    else if (cell_temp_skill == 2)
                    {
                        str_cat(info_str, "Key yellow");
                    }
                    else if (cell_temp_skill == 3)
                    {
                        str_cat(info_str, "Small medkit");
                    }
                    else if (cell_temp_skill == 4)
                    {
                        str_cat(info_str, "Big medkit");
                    }
                    str_cat(info_str, ";");
                }
                else if (cell_flag == 1) // weapons / ammo
                {
                    str_cat(info_str, "Weapon");
                    str_cat(info_str, ": ");

                    if (cell_temp_skill == 0)
                    {
                        str_cat(info_str, "Ammo box");
                    }
                    else if (cell_temp_skill == 1)
                    {
                        str_cat(info_str, "Pistol weapon");
                    }
                    else if (cell_temp_skill == 2)
                    {
                        str_cat(info_str, "Pistol ammo");
                    }
                    else if (cell_temp_skill == 3)
                    {
                        str_cat(info_str, "Shotgun weapon");
                    }
                    else if (cell_temp_skill == 4)
                    {
                        str_cat(info_str, "Shotgun ammo");
                    }
                    else if (cell_temp_skill == 5)
                    {
                        str_cat(info_str, "SMG weapon");
                    }
                    else if (cell_temp_skill == 6)
                    {
                        str_cat(info_str, "SMG ammo");
                    }
                    else if (cell_temp_skill == 7)
                    {
                        str_cat(info_str, "Machinegun weapon");
                    }
                    else if (cell_temp_skill == 8)
                    {
                        str_cat(info_str, "Machinegun ammo");
                    }
                    else if (cell_temp_skill == 9)
                    {
                        str_cat(info_str, "Rocketlauncher weapon");
                    }
                    else if (cell_temp_skill == 10)
                    {
                        str_cat(info_str, "Rocketlauncher ammo");
                    }
                    str_cat(info_str, ";");
                }
                else if (cell_flag == 2) // enemies
                {
                    str_cat(info_str, "Enemy");
                    str_cat(info_str, ": ");

                    if (cell_temp_skill == 0)
                    {
                        str_cat(info_str, "Rat");
                    }
                    else if (cell_temp_skill == 1)
                    {
                        str_cat(info_str, "Dog");
                    }
                    else if (cell_temp_skill == 2)
                    {
                        str_cat(info_str, "Guard pistol");
                    }
                    else if (cell_temp_skill == 3)
                    {
                        str_cat(info_str, "Guard shotgun");
                    }
                    else if (cell_temp_skill == 4)
                    {
                        str_cat(info_str, "Soldier SMG");
                    }
                    else if (cell_temp_skill == 5)
                    {
                        str_cat(info_str, "Suicide bomber");
                    }
                    else if (cell_temp_skill == 6)
                    {
                        str_cat(info_str, "Zombie");
                    }
                    else if (cell_temp_skill == 7)
                    {
                        str_cat(info_str, "Support machinegun");
                    }
                    else if (cell_temp_skill == 8)
                    {
                        str_cat(info_str, "Support rocketlauncher");
                    }
                    str_cat(info_str, ";");
                }
                else if (cell_flag == 3) // bosses
                {
                    str_cat(info_str, "Boss");
                    str_cat(info_str, ": ");

                    if (cell_temp_skill == 0)
                    {
                        str_cat(info_str, "Uber soldier");
                    }
                    else if (cell_temp_skill == 1)
                    {
                        str_cat(info_str, "Uber officer");
                    }
                    else if (cell_temp_skill == 2)
                    {
                        str_cat(info_str, "Uber mutant");
                    }
                    else if (cell_temp_skill == 3)
                    {
                        str_cat(info_str, "Mecha soldier");
                    }
                    else if (cell_temp_skill == 4)
                    {
                        str_cat(info_str, "Demon");
                    }
                    str_cat(info_str, ";");
                }
            }
        }
        else if (cell_type == ASSET_TYPE_ENEMIES)
        {
            str_cat(info_str, "\n\nparams:");

            str_cat(info_str, "\n* behaviour: ");
            if (cell_temp_skill == 0)
            {
                str_cat(info_str, "wait");
            }
            else if (cell_temp_skill == 1)
            {
                str_cat(info_str, "deaf");
            }
            else if (cell_temp_skill == 2)
            {
                str_cat(info_str, "patrol");
            }
            str_cat(info_str, ";");

            if (cell_flag == true)
            {
                str_cat(info_str, "\n* drop item: ");
                if (cell_event_type == 0)
                {
                    str_cat(info_str, "Key blue");
                }
                else if (cell_event_type == 1)
                {
                    str_cat(info_str, "Key red");
                }
                else if (cell_event_type == 2)
                {
                    str_cat(info_str, "Key yellow");
                }
                else if (cell_event_type == 3)
                {
                    str_cat(info_str, "Small medkit");
                }
                else if (cell_event_type == 4)
                {
                    str_cat(info_str, "Big medkit");
                }
                else if (cell_event_type == 5)
                {
                    str_cat(info_str, "Ammo from held weapon");
                }
                else if (cell_event_type == 6)
                {
                    str_cat(info_str, "Held weapon");
                }
                str_cat(info_str, ";");
            }
            else
            {
                str_cat(info_str, "\n* drop item: false;");
            }
        }
        else if (cell_type == ASSET_TYPE_BOSSES)
        {
            str_cat(info_str, "\n\nparams:");

            str_cat(info_str, "\n* behaviour: ");
            if (cell_temp_skill == 0)
            {
                str_cat(info_str, "wait");
            }
            else if (cell_temp_skill == 1)
            {
                str_cat(info_str, "deaf");
            }
            else if (cell_temp_skill == 2)
            {
                str_cat(info_str, "patrol");
            }
            str_cat(info_str, ";");

            if (cell_flag == true)
            {
                str_cat(info_str, "\n* drop item: ");
                if (cell_event_type == 0)
                {
                    str_cat(info_str, "Key blue");
                }
                else if (cell_event_type == 1)
                {
                    str_cat(info_str, "Key red");
                }
                else if (cell_event_type == 2)
                {
                    str_cat(info_str, "Key yellow");
                }
                else if (cell_event_type == 3)
                {
                    str_cat(info_str, "Small medkit");
                }
                else if (cell_event_type == 4)
                {
                    str_cat(info_str, "Big medkit");
                }
                str_cat(info_str, ";");
            }
            else
            {
                str_cat(info_str, "\n* drop item: false;");
            }
        }
    }

    return info_str;
}

STRING *draw_map_info(Map *current_map, int x, int y)
{
    if (!current_map)
    {
        return NULL;
    }

    if (is_allowed_to_draw() == false)
    {
        return NULL;
    }

    Cell *cell = &current_map->cell[x][y];
    if (!cell)
    {
        return NULL;
    }

    return get_cell_info(cell);
}