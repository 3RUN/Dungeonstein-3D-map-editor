
void asset_params_activation_type(Cell *cell)
{
    if (!cell)
    {
        return;
    }

    imgui_text("Activation");
    imgui_radiobutton("Interaction", &cell->event_type, 0);
    imgui_radiobutton("Trigger zone - id", &cell->event_type, 1);
    imgui_radiobutton("Switch - id", &cell->event_type, 2);

    if (is_door(cell->type, cell->asset) == true)
    {
        imgui_radiobutton("None (static)", &cell->event_type, 3);
    }
}

void asset_params_id(Cell *cell)
{
    if (!cell)
    {
        return;
    }

    imgui_text("Id:");
    imgui_same_line();
    imgui_align_right_with_offset(90);
    if (imgui_arrow_button("Id Decrease", ImGuiDir_Left))
    {
        cell->event_id--;
        cell->event_id = clamp(cell->event_id, 0, MAX_ID_RANGE);
    }
    imgui_same_line();
    imgui_text(_chr(str_printf(NULL, "%d / %d", cell->event_id, MAX_ID_RANGE)));
    imgui_same_line();
    if (imgui_arrow_button("Id Increase", ImGuiDir_Right))
    {
        cell->event_id++;
        cell->event_id = clamp(cell->event_id, 0, MAX_ID_RANGE);
    }
}

void asset_params_wall_params(Cell *cell, int asset)
{
    if (!cell)
    {
        return;
    }

    imgui_checkbox("Secret wall (moves up)", &cell->flag);

    if (cell->flag == false)
    {
        cell->event_type = 0;
        cell->event_id = 0;
        cell->temp_skill = 0;
    }

    if (cell->flag == true)
    {
        imgui_separator();
        asset_params_activation_type(cell);
    }

    // trigger zone or switch ?
    if (cell->event_type >= 1)
    {
        imgui_separator();
        asset_params_id(cell);
    }
}

void asset_params_props_params(Cell *cell, int asset)
{
    if (!cell)
    {
        return;
    }

    if (asset == PROPS_FENCE)
    {
        imgui_text("Activation");
        imgui_radiobutton("None (static)", &cell->event_type, 0);
        imgui_radiobutton("Interaction", &cell->event_type, 1);
        imgui_radiobutton("Trigger zone - id", &cell->event_type, 2);
        imgui_radiobutton("Switch - id", &cell->event_type, 3);

        // trigger zone or switch ?
        if (cell->event_type >= 2)
        {
            imgui_separator();
            asset_params_id(cell);
        }
    }
    else if (asset == PROPS_DOOR)
    {
        asset_params_activation_type(cell);

        // trigger zone or switch ?
        if (cell->event_type >= 1 && cell->event_type < 3)
        {
            imgui_separator();
            asset_params_id(cell);
        }
    }
    else if (asset == PROPS_DOOR_LOCKED)
    {
        imgui_text("Key type:");
        imgui_radiobutton("Blue", &cell->event_type, 0);
        imgui_radiobutton("Red", &cell->event_type, 1);
        imgui_radiobutton("Yellow", &cell->event_type, 2);
    }
    else if (asset == PROPS_SWITCH)
    {
        asset_params_id(cell);
    }
}

void asset_params_events_params(Cell *cell, int asset)
{
    if (!cell)
    {
        return;
    }

    if (selected_asset == EVENT_PLAYER)
    {
        imgui_text("Start weapon");
        imgui_radiobutton("Knife", &cell->event_id, 0);
        imgui_radiobutton("Pistol", &cell->event_id, 1);
        imgui_radiobutton("Shotgun", &cell->event_id, 2);
        imgui_radiobutton("Chaingun", &cell->event_id, 3);
        imgui_radiobutton("Rocketlauncher", &cell->event_id, 4);
    }
    else if (selected_asset == EVENT_TRIGGER_ZONE)
    {
        asset_params_id(cell);
    }
    else if (selected_asset == EVENT_SPAWN_OBJECT)
    {
        imgui_text("Category");
        if (imgui_radiobutton("Item", &cell->flag, 0))
        {
            cell->temp_skill = 0;
        }

        if (imgui_radiobutton("Weapon", &cell->flag, 1))
        {
            cell->temp_skill = 0;
        }

        if (imgui_radiobutton("Enemy", &cell->flag, 2))
        {
            cell->temp_skill = 0;
        }

        if (imgui_radiobutton("Boss", &cell->flag, 3))
        {
            cell->temp_skill = 0;
        }

        imgui_separator();
        imgui_text("Type");
        if (cell->flag == 0) // items
        {
            imgui_radiobutton("Key blue", &cell->temp_skill, 0);
            imgui_radiobutton("Key red", &cell->temp_skill, 1);
            imgui_radiobutton("Key yellow", &cell->temp_skill, 2);
            imgui_radiobutton("Small medkit", &cell->temp_skill, 3);
            imgui_radiobutton("Big medkit", &cell->temp_skill, 4);
        }
        else if (cell->flag == 1) // weapons
        {
            imgui_radiobutton("Ammo box", &cell->temp_skill, 0);
            imgui_radiobutton("Pistol weapon", &cell->temp_skill, 1);
            imgui_radiobutton("Pistol ammo", &cell->temp_skill, 2);
            imgui_radiobutton("Shotgun weapon", &cell->temp_skill, 3);
            imgui_radiobutton("Shotgun ammo", &cell->temp_skill, 4);
            imgui_radiobutton("SMG weapon", &cell->temp_skill, 5);
            imgui_radiobutton("SMG ammo", &cell->temp_skill, 6);
            imgui_radiobutton("Machinegun weapon", &cell->temp_skill, 7);
            imgui_radiobutton("Machinegun ammo", &cell->temp_skill, 8);
            imgui_radiobutton("Rocketlauncher weapon", &cell->temp_skill, 9);
            imgui_radiobutton("Rocketlauncher ammo", &cell->temp_skill, 10);
        }
        else if (cell->flag == 2) // enemies
        {
            imgui_radiobutton("Rat", &cell->temp_skill, 0);
            imgui_radiobutton("Dog", &cell->temp_skill, 1);
            imgui_radiobutton("Guard pistol", &cell->temp_skill, 2);
            imgui_radiobutton("Guard shotgun", &cell->temp_skill, 3);
            imgui_radiobutton("Soldier SMG", &cell->temp_skill, 4);
            imgui_radiobutton("Suicide bomber", &cell->temp_skill, 5);
            imgui_radiobutton("Zombie", &cell->temp_skill, 6);
            imgui_radiobutton("Support machinegun", &cell->temp_skill, 7);
            imgui_radiobutton("Support rocketlauncher", &cell->temp_skill, 8);
        }
        else if (cell->flag == 3) // bosses
        {
            imgui_radiobutton("Uber soldier", &cell->temp_skill, 0);
            imgui_radiobutton("Uber officer", &cell->temp_skill, 1);
            imgui_radiobutton("Uber mutant", &cell->temp_skill, 2);
            imgui_radiobutton("Mecha soldier", &cell->temp_skill, 3);
            imgui_radiobutton("Demon", &cell->temp_skill, 4);
        }

        imgui_separator();
        imgui_text("Activation");
        imgui_radiobutton("On creation", &cell->event_type, 0);
        imgui_radiobutton("Trigger zone - id", &cell->event_type, 1);
        imgui_radiobutton("Switch - id", &cell->event_type, 2);

        // trigger zone or switch ?
        if (cell->event_type >= 1)
        {
            imgui_separator();
            asset_params_id(cell);
        }
    }
}

void asset_params_effects_params(Cell *cell, int asset)
{
    if (!cell)
    {
        return;
    }

    imgui_checkbox("Do damage", &cell->flag);
    imgui_separator();

    imgui_text("Activation");
    imgui_radiobutton("On creation", &cell->event_type, 0);
    imgui_radiobutton("Trigger zone - id", &cell->event_type, 1);
    imgui_radiobutton("Switch - id", &cell->event_type, 2);

    // trigger zone or switch ?
    if (cell->event_type >= 1)
    {
        imgui_separator();
        asset_params_id(cell);
    }
}

void asset_params_enemies_params(Cell *cell, int asset)
{
    if (!cell)
    {
        return;
    }

    // behaviour
    imgui_text("Behaviour");
    imgui_radiobutton("wait", &cell->temp_skill, 0);
    imgui_radiobutton("deaf", &cell->temp_skill, 1);
    imgui_radiobutton("patrol", &cell->temp_skill, 2);

    // item dropping
    imgui_separator();
    imgui_checkbox("Drop item", &cell->flag);
    if (cell->flag == true)
    {
        imgui_separator();
        imgui_radiobutton("Key blue", &cell->event_type, 0);
        imgui_radiobutton("Key red", &cell->event_type, 1);
        imgui_radiobutton("Key yellow", &cell->event_type, 2);
        imgui_radiobutton("Small medkit", &cell->event_type, 3);
        imgui_radiobutton("Big medkit", &cell->event_type, 4);

        if (asset >= ENEMY_PISTOL)
        {
            imgui_radiobutton("Ammo from held weapon", &cell->event_type, 5);
            imgui_radiobutton("Held weapon", &cell->event_type, 6);
        }
    }
}

void asset_params_bosses_params(Cell *cell, int asset)
{
    if (!cell)
    {
        return;
    }

    // behaviour
    imgui_text("Behaviour");
    imgui_radiobutton("wait", &cell->temp_skill, 0);
    imgui_radiobutton("deaf", &cell->temp_skill, 1);
    imgui_radiobutton("patrol", &cell->temp_skill, 2);

    // item dropping
    imgui_separator();
    imgui_checkbox("Drop item", &cell->flag);
    if (cell->flag == true)
    {
        imgui_separator();
        imgui_radiobutton("Key blue", &cell->event_type, 0);
        imgui_radiobutton("Key red", &cell->event_type, 1);
        imgui_radiobutton("Key yellow", &cell->event_type, 2);
        imgui_radiobutton("Small medkit", &cell->event_type, 3);
        imgui_radiobutton("Big medkit", &cell->event_type, 4);
    }
}

void asset_params_update(Cell *cell, int type, int asset)
{
    if (!cell)
    {
        return;
    }

    if (can_become_secret_wall(type, asset) == true)
    {
        asset_params_wall_params(cell, asset);
    }
    else if (type == ASSET_TYPE_PROPS && asset == PROPS_FENCE || is_switch(type, asset) == true || is_door(type, asset) == true)
    {
        asset_params_props_params(cell, asset);
    }
    else if (is_player_start(type, asset) == true || is_trigger_zone(type, asset) == true || is_spawn_object(type, asset) == true)
    {
        asset_params_events_params(cell, asset);
    }
    else if (is_effect(type, asset) == true)
    {
        asset_params_effects_params(cell, asset);
    }
    else if (is_enemy(type, asset) == true)
    {
        asset_params_enemies_params(cell, asset);
    }
    else if (is_boss(type, asset) == true)
    {
        asset_params_bosses_params(cell, asset);
    }
    else
    {
        imgui_text_disabled("Parameters: none");
    }
}