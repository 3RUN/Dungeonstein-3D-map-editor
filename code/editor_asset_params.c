
void asset_params_activation_type(Cell *cell)
{
    if (!cell)
    {
        return;
    }

    imgui_text(_chr(params_activation_str));
    imgui_radiobutton(_chr(params_activation_type_interaction_str), &cell->event_type, 0);
    imgui_radiobutton(_chr(params_activation_type_trigger_zone_str), &cell->event_type, 1);
    imgui_radiobutton(_chr(params_activation_type_switch_str), &cell->event_type, 2);
}

void asset_params_id(Cell *cell)
{
    if (!cell)
    {
        return;
    }

    imgui_text(_chr(params_activation_id_str));
    imgui_same_line();
    imgui_align_right_with_offset(90);
    if (imgui_arrow_button(_chr(params_activation_id_decrease_str), ImGuiDir_Left))
    {
        cell->event_id--;
        cell->event_id = clamp(cell->event_id, 0, MAX_ID_RANGE);
    }
    imgui_same_line();
    imgui_text(_chr(str_printf(NULL, "%d / %d", cell->event_id, MAX_ID_RANGE)));
    imgui_same_line();
    if (imgui_arrow_button(_chr(params_activation_id_increase_str), ImGuiDir_Right))
    {
        cell->event_id++;
        cell->event_id = clamp(cell->event_id, 0, MAX_ID_RANGE);
    }
}

void asset_params_wall_params(Cell *cell, int index)
{
    if (!cell)
    {
        return;
    }

    imgui_checkbox(_chr(params_is_secret_wall_str), &cell->flag);

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

void asset_params_props_params(Cell *cell, int index)
{
    if (!cell)
    {
        return;
    }

    if (index == PROPS_FENCE || index == PROPS_FENCE_DIRTY || index == PROPS_DOOR || index == PROPS_DOOR_ELEVATOR)
    {
        asset_params_activation_type(cell);

        // trigger zone or switch ?
        if (cell->event_type >= 1)
        {
            imgui_separator();
            asset_params_id(cell);
        }
    }
    else if (index == PROPS_DOOR_LOCKED)
    {
        imgui_text(_chr(params_key_type_str));
        imgui_radiobutton(_chr(params_key_type_blue_str), &cell->event_type, 0);
        imgui_radiobutton(_chr(params_key_type_red_str), &cell->event_type, 1);
        imgui_radiobutton(_chr(params_key_type_yellow_str), &cell->event_type, 2);
    }
    else if (index == PROPS_SWITCH)
    {
        asset_params_id(cell);
    }
}

void asset_params_events_params(Cell *cell, int index)
{
    if (!cell)
    {
        return;
    }

    if (selected_asset == EVENT_TRIGGER_ZONE)
    {
        asset_params_id(cell);
    }
    else if (selected_asset == EVENT_SPAWN_OBJECT)
    {
        imgui_text(_chr(params_spawn_object_category_str));
        if (imgui_radiobutton(_chr(params_spawn_object_type_item_str), &cell->flag, 0))
        {
            cell->temp_skill = 0;
        }

        if (imgui_radiobutton(_chr(params_spawn_object_type_weapon_str), &cell->flag, 1))
        {
            cell->temp_skill = 0;
        }

        if (imgui_radiobutton(_chr(params_spawn_object_type_enemy_str), &cell->flag, 2))
        {
            cell->temp_skill = 0;
        }

        if (imgui_radiobutton(_chr(params_spawn_object_type_boss_str), &cell->flag, 3))
        {
            cell->temp_skill = 0;
        }

        imgui_separator();
        imgui_text(_chr(params_spawn_object_type_str));
        if (cell->flag == 0) // items
        {
            imgui_radiobutton(_chr(params_drop_item_key_blue_str), &cell->temp_skill, 0);
            imgui_radiobutton(_chr(params_drop_item_key_red_str), &cell->temp_skill, 1);
            imgui_radiobutton(_chr(params_drop_item_key_yellow_str), &cell->temp_skill, 2);
            imgui_radiobutton(_chr(params_drop_item_small_medkit_str), &cell->temp_skill, 3);
            imgui_radiobutton(_chr(params_drop_item_big_medkit_str), &cell->temp_skill, 4);
        }
        else if (cell->flag == 1) // weapons
        {
            imgui_radiobutton(_chr(params_spawn_object_ammo_big_str), &cell->temp_skill, 0);
            imgui_radiobutton(_chr(params_spawn_object_weapon_pistol_str), &cell->temp_skill, 1);
            imgui_radiobutton(_chr(params_spawn_object_ammo_pistol_str), &cell->temp_skill, 2);
            imgui_radiobutton(_chr(params_spawn_object_weapon_shotgun_str), &cell->temp_skill, 3);
            imgui_radiobutton(_chr(params_spawn_object_ammo_shotgun_str), &cell->temp_skill, 4);
            imgui_radiobutton(_chr(params_spawn_object_weapon_smg_str), &cell->temp_skill, 5);
            imgui_radiobutton(_chr(params_spawn_object_ammo_smg_str), &cell->temp_skill, 6);
            imgui_radiobutton(_chr(params_spawn_object_weapon_machinegun_str), &cell->temp_skill, 7);
            imgui_radiobutton(_chr(params_spawn_object_ammo_machinegun_str), &cell->temp_skill, 8);
            imgui_radiobutton(_chr(params_spawn_object_weapon_rocketlauncher_str), &cell->temp_skill, 9);
            imgui_radiobutton(_chr(params_spawn_object_ammo_rocketlauncher_str), &cell->temp_skill, 10);
        }
        else if (cell->flag == 2) // enemies
        {
            imgui_radiobutton(_chr(params_spawn_object_enemy_rat_str), &cell->temp_skill, 0);
            imgui_radiobutton(_chr(params_spawn_object_enemy_dog_str), &cell->temp_skill, 1);
            imgui_radiobutton(_chr(params_spawn_object_enemy_guard_pistol_str), &cell->temp_skill, 2);
            imgui_radiobutton(_chr(params_spawn_object_enemy_guard_shotgun_str), &cell->temp_skill, 3);
            imgui_radiobutton(_chr(params_spawn_object_enemy_soldier_smg_str), &cell->temp_skill, 4);
            imgui_radiobutton(_chr(params_spawn_object_enemy_suicide_bomber_str), &cell->temp_skill, 5);
            imgui_radiobutton(_chr(params_spawn_object_enemy_zombie_str), &cell->temp_skill, 6);
            imgui_radiobutton(_chr(params_spawn_object_enemy_support_machinegun_str), &cell->temp_skill, 7);
            imgui_radiobutton(_chr(params_spawn_object_enemy_support_rocketlauncher_str), &cell->temp_skill, 8);
        }
        else if (cell->flag == 3) // bosses
        {
            imgui_radiobutton(_chr(params_spawn_object_boss_uber_soldier_str), &cell->temp_skill, 0);
            imgui_radiobutton(_chr(params_spawn_object_boss_uber_officer_str), &cell->temp_skill, 1);
            imgui_radiobutton(_chr(params_spawn_object_boss_uber_mutant_str), &cell->temp_skill, 2);
            imgui_radiobutton(_chr(params_spawn_object_boss_mecha_soldier_str), &cell->temp_skill, 3);
            imgui_radiobutton(_chr(params_spawn_object_boss_demon_str), &cell->temp_skill, 4);
        }

        imgui_separator();
        imgui_text(_chr(params_activation_str));
        imgui_radiobutton(_chr(params_activation_type_on_creation_str), &cell->event_type, 0);
        imgui_radiobutton(_chr(params_activation_type_trigger_zone_str), &cell->event_type, 1);
        imgui_radiobutton(_chr(params_activation_type_switch_str), &cell->event_type, 2);

        // trigger zone or switch ?
        if (cell->event_type >= 1)
        {
            imgui_separator();
            asset_params_id(cell);
        }
    }
}

void asset_params_enemies_params(Cell *cell, int index)
{
    if (!cell)
    {
        return;
    }

    // behaviour
    imgui_text(_chr(params_enemy_behaviour_str));
    imgui_radiobutton(_chr(params_enemy_behaviour_wait_str), &cell->temp_skill, 0);
    imgui_radiobutton(_chr(params_enemy_behaviour_deaf_str), &cell->temp_skill, 1);
    imgui_radiobutton(_chr(params_enemy_behaviour_patrol_str), &cell->temp_skill, 2);

    // item dropping
    imgui_separator();
    imgui_checkbox(_chr(params_drop_item_str), &cell->flag);
    if (cell->flag == true)
    {
        imgui_separator();
        imgui_radiobutton(_chr(params_drop_item_key_blue_str), &cell->event_type, 0);
        imgui_radiobutton(_chr(params_drop_item_key_red_str), &cell->event_type, 1);
        imgui_radiobutton(_chr(params_drop_item_key_yellow_str), &cell->event_type, 2);
        imgui_radiobutton(_chr(params_drop_item_small_medkit_str), &cell->event_type, 3);
        imgui_radiobutton(_chr(params_drop_item_big_medkit_str), &cell->event_type, 4);
        if (index >= ENEMY_GUARD_PISTOL && index != ENEMY_SUICIDE_BOMBER && index != ENEMY_ZOMBIE)
        {
            imgui_radiobutton(_chr(params_drop_item_ammo_str), &cell->event_type, 5);
            imgui_radiobutton(_chr(params_drop_item_weapon_str), &cell->event_type, 6);
        }
    }
}

void asset_params_bosses_params(Cell *cell, int index)
{
    if (!cell)
    {
        return;
    }

    // behaviour
    imgui_text(_chr(params_enemy_behaviour_str));
    imgui_radiobutton(_chr(params_enemy_behaviour_wait_str), &cell->temp_skill, 0);
    imgui_radiobutton(_chr(params_enemy_behaviour_deaf_str), &cell->temp_skill, 1);
    imgui_radiobutton(_chr(params_enemy_behaviour_patrol_str), &cell->temp_skill, 2);

    // item dropping
    imgui_separator();
    imgui_checkbox(_chr(params_drop_item_str), &cell->flag);
    if (cell->flag == true)
    {
        imgui_separator();
        imgui_radiobutton(_chr(params_drop_item_key_blue_str), &cell->event_type, 0);
        imgui_radiobutton(_chr(params_drop_item_key_red_str), &cell->event_type, 1);
        imgui_radiobutton(_chr(params_drop_item_key_yellow_str), &cell->event_type, 2);
        imgui_radiobutton(_chr(params_drop_item_small_medkit_str), &cell->event_type, 3);
        imgui_radiobutton(_chr(params_drop_item_big_medkit_str), &cell->event_type, 4);
    }
}

void asset_params_obj_params_update(Cell *cell, int type, int index)
{
    if (!cell)
    {
        return;
    }

    // walls
    if (type == ASSET_TYPE_WALLS && index != TOTAL_WALL_TEXTURES - 1)
    {
        asset_params_wall_params(cell, index);
    }
    else if (is_fence(type, index) == true || type == ASSET_TYPE_PROPS && index == PROPS_DOOR || type == ASSET_TYPE_PROPS && index == PROPS_DOOR_ELEVATOR || type == ASSET_TYPE_PROPS && index == PROPS_DOOR_LOCKED || type == ASSET_TYPE_PROPS && index == PROPS_SWITCH)
    {
        asset_params_props_params(cell, index);
    }
    else if (type == ASSET_TYPE_EVENTS && index == EVENT_TRIGGER_ZONE || type == ASSET_TYPE_EVENTS && index == EVENT_SPAWN_OBJECT)
    {
        asset_params_events_params(cell, index);
    }
    else if (type == ASSET_TYPE_ENEMIES)
    {
        asset_params_enemies_params(cell, index);
    }
    else if (type == ASSET_TYPE_BOSSES)
    {
        asset_params_bosses_params(cell, index);
    }
    else
    {
        imgui_text_disabled(_chr(params_none_str));
    }
}