
void get_cell_info(Cell *cell, STRING **out)
{
    if (!cell)
    {
        return NULL;
    }

    VECTOR cell_pos;
    vec_set(&cell_pos, &cell->worldpos);
    var cell_pan = cell->pan;

    var cell_id = cell->id;
    var cell_x = cell->x;
    var cell_y = cell->y;

    var cell_type = cell->type;
    var cell_asset = cell->asset;

    var cell_flag = cell->flag;
    var cell_event_type = cell->event_type;
    var cell_event_id = cell->event_id;
    var cell_temp_skill = cell->temp_skill;

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
        if (cell_type == ASSET_TYPE_WALLS && cell_asset != TOTAL_WALL_TEXTURES - 1)
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
        else if (cell_type == ASSET_TYPE_WALLS && cell_asset == TOTAL_WALL_TEXTURES - 1)
        {
            str_cat(*out, "\n\nparams:");
            str_cat(*out, "\n* finish level switch;");
        }
        else if (cell_type == ASSET_TYPE_PROPS && cell_asset == PROPS_FENCE || cell_type == ASSET_TYPE_PROPS && cell_asset == PROPS_FENCE_DIRTY || cell_type == ASSET_TYPE_PROPS && cell_asset == PROPS_DOOR || cell_type == ASSET_TYPE_PROPS && cell_asset == PROPS_DOOR_ELEVATOR || cell_type == ASSET_TYPE_PROPS && cell_asset == PROPS_DOOR_LOCKED || cell_type == ASSET_TYPE_PROPS && cell_asset == PROPS_SWITCH)
        {
            str_cat(*out, "\n\nparams:");
            if (cell_asset == PROPS_FENCE || cell_asset == PROPS_FENCE_DIRTY)
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
            else if (cell_asset == PROPS_DOOR || cell_asset == PROPS_DOOR_ELEVATOR)
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
        else if (cell_type == ASSET_TYPE_EVENTS && cell_asset == EVENT_TRIGGER_ZONE || cell_type == ASSET_TYPE_EVENTS && cell_asset == EVENT_SPAWN_OBJECT)
        {
            if (cell_asset == EVENT_TRIGGER_ZONE)
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
        else if (cell_type == ASSET_TYPE_ENEMIES)
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
        else if (cell_type == ASSET_TYPE_BOSSES)
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

void draw_map_info(Map *current_map, STRING **out, var x, var y)
{
    if (!current_map)
    {
        return;
    }

    if (is_allowed_to_draw() == false)
    {
        return;
    }

    Cell *cell = &current_map->cell[x][y];
    if (!cell)
    {
        return;
    }

    get_cell_info(cell, out);
}