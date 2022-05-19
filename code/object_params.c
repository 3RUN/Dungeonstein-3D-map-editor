
void object_params_initialize()
{
    int i = 0;
    for (i = 0; i < MAX_LIGHTSTYLES; i++)
    {
        lightstyle_list_str[i] = str_create("");
    }

    str_cpy(lightstyle_list_str[0], "static");
    str_cpy(lightstyle_list_str[1], "flicker");
    str_cpy(lightstyle_list_str[2], "pulse");
    str_cpy(lightstyle_list_str[3], "strobe");
    str_cpy(lightstyle_list_str[4], "candle");
    params_lights_refresh();

    for (i = 0; i < MAX_SPAWN_CATEGORIES; i++)
    {
        spawn_category_list_str[i] = str_create("");
    }

    for (i = 0; i < MAX_SPAWN_ITEMS; i++)
    {
        spawn_item_list_str[i] = str_create("");
    }

    for (i = 0; i < MAX_SPAWN_ENEMIES; i++)
    {
        spawn_enemies_list_str[i] = str_create("");
    }

    for (i = 0; i < MAX_SPAWN_BOSSES; i++)
    {
        spawn_bosses_list_str[i] = str_create("");
    }

    str_cpy(spawn_category_list_str[0], "Item");
    str_cpy(spawn_category_list_str[1], "Enemy");
    str_cpy(spawn_category_list_str[2], "Boss");

    str_cpy(spawn_item_list_str[0], "Key blue");
    str_cpy(spawn_item_list_str[1], "Key red");
    str_cpy(spawn_item_list_str[2], "Key yellow");
    str_cpy(spawn_item_list_str[3], "Health bonus");
    str_cpy(spawn_item_list_str[4], "Medkit small");
    str_cpy(spawn_item_list_str[5], "Medkit big");
    str_cpy(spawn_item_list_str[6], "Ammo bullet small");
    str_cpy(spawn_item_list_str[7], "Ammo bullet big");
    str_cpy(spawn_item_list_str[8], "Ammo shells small");
    str_cpy(spawn_item_list_str[9], "Ammo shells big");
    str_cpy(spawn_item_list_str[10], "Ammo rockets small");
    str_cpy(spawn_item_list_str[11], "Ammo rockets big");
    str_cpy(spawn_item_list_str[12], "Treasure");
    str_cpy(spawn_item_list_str[13], "Powerup map");
    str_cpy(spawn_item_list_str[14], "Powerup suit");
    str_cpy(spawn_item_list_str[15], "Powerup chicken");
    str_cpy(spawn_item_list_str[16], "Powerup lantern");
    str_cpy(spawn_item_list_str[17], "Powerup mushroom");
    str_cpy(spawn_item_list_str[18], "Weapon pistol");
    str_cpy(spawn_item_list_str[19], "Weapon shotgun");
    str_cpy(spawn_item_list_str[20], "Weapon chaingun");
    str_cpy(spawn_item_list_str[21], "Weapon rocketlauncher");

    str_cpy(spawn_enemies_list_str[0], "Bat");
    str_cpy(spawn_enemies_list_str[1], "Boxer");
    str_cpy(spawn_enemies_list_str[2], "Bum");
    str_cpy(spawn_enemies_list_str[3], "Mage");
    str_cpy(spawn_enemies_list_str[4], "Human pistol");
    str_cpy(spawn_enemies_list_str[5], "Human shotgun");
    str_cpy(spawn_enemies_list_str[6], "Skeleton");
    str_cpy(spawn_enemies_list_str[7], "Slime fire");
    str_cpy(spawn_enemies_list_str[8], "Slime ice");
    str_cpy(spawn_enemies_list_str[9], "Zombie");

    str_cpy(spawn_bosses_list_str[0], "Human chaingun");
    str_cpy(spawn_bosses_list_str[1], "Human rocketlauncher");
    str_cpy(spawn_bosses_list_str[2], "Slime toxic");
    str_cpy(spawn_bosses_list_str[3], "Megaeye");
    params_spawn_point_refresh();
}

void object_params_destroy()
{
    int i = 0;
    for (i = 0; i < MAX_LIGHTSTYLES; i++)
    {
        str_remove(lightstyle_list_str[i]);
    }

    for (i = 0; i < MAX_SPAWN_CATEGORIES; i++)
    {
        str_remove(spawn_category_list_str[i]);
    }

    for (i = 0; i < MAX_SPAWN_ITEMS; i++)
    {
        str_remove(spawn_item_list_str[i]);
    }

    for (i = 0; i < MAX_SPAWN_ENEMIES; i++)
    {
        str_remove(spawn_enemies_list_str[i]);
    }

    for (i = 0; i < MAX_SPAWN_BOSSES; i++)
    {
        str_remove(spawn_bosses_list_str[i]);
    }
}

void params_lights_refresh()
{
    int i = 0;
    for (i = 0; i < MAX_LIGHTSTYLES; i++)
    {
        if (preview_cell.object.flag[0] == i)
        {
            if (lightstyle_list_str[i])
            {
                str_cpy(used_lightstyle_str, lightstyle_list_str[i]);
            }
        }
    }
}

void params_spawn_point_refresh()
{
    int i = 0;
    for (i = 0; i < MAX_SPAWN_CATEGORIES; i++)
    {
        if (preview_cell.object.flag[2] == i)
        {
            if (spawn_category_list_str[i])
            {
                str_cpy(used_spawn_category_str, spawn_category_list_str[i]);
            }
        }
    }

    for (i = 0; i < MAX_SPAWN_ITEMS; i++)
    {
        if (preview_cell.object.flag[3] == i)
        {
            if (spawn_item_list_str[i])
            {
                str_cpy(used_spawn_item_str, spawn_item_list_str[i]);
            }
        }
    }

    for (i = 0; i < MAX_SPAWN_ENEMIES; i++)
    {
        if (preview_cell.object.flag[3] == i)
        {
            if (spawn_enemies_list_str[i])
            {
                str_cpy(used_spawn_enemies_str, spawn_enemies_list_str[i]);
            }
        }
    }

    for (i = 0; i < MAX_SPAWN_BOSSES; i++)
    {
        if (preview_cell.object.flag[3] == i)
        {
            if (spawn_bosses_list_str[i])
            {
                str_cpy(used_spawn_bosses_str, spawn_bosses_list_str[i]);
            }
        }
    }
}

void object_params_reset(Object *object)
{
    if (!object)
    {
        return;
    }

    int i = 0;
    for (i = 0; i < MAX_OBJECT_FLAGS; i++)
    {
        object->flag[i] = OBJ_FLAG_NONE;
    }

    params_lights_refresh();
    params_spawn_point_refresh();
}

void params_id(Object *object)
{
    if (!object)
    {
        return;
    }

    imgui_text("Id:");
    imgui_same_line();
    if (imgui_arrow_button("Id Decrease", ImGuiDir_Left))
    {
        object->flag[1]--;
        object->flag[1] = clamp(object->flag[1], MIN_ID_RANGE, MAX_ID_RANGE);
    }
    imgui_same_line();
    imgui_text(_chr(str_printf(NULL, "%d / %d", object->flag[1], MAX_ID_RANGE)));
    imgui_same_line();
    if (imgui_arrow_button("Id Increase", ImGuiDir_Right))
    {
        object->flag[1]++;
        object->flag[1] = clamp(object->flag[1], MIN_ID_RANGE, MAX_ID_RANGE);
    }
}

void params_lights(Object *object)
{
    if (!object)
    {
        return;
    }

    imgui_text("Lightstyle:");
    imgui_same_line();
    var avail_combobox_width = imgui_get_content_region_avail_width();
    imgui_push_item_width(avail_combobox_width);
    if (imgui_begin_combo("##lightstyle combobox", _chr(used_lightstyle_str), ImGuiComboFlags_HeightSmall))
    {
        int i = 0;
        for (i = 0; i < MAX_LIGHTSTYLES; i++)
        {
            int is_selected = str_cmp(used_lightstyle_str, lightstyle_list_str[i]);
            if (imgui_selectable(_chr(lightstyle_list_str[i]), &is_selected, 0))
            {
                preview_cell.object.flag[0] = i;
                str_cpy(used_lightstyle_str, lightstyle_list_str[i]);
                params_lights_refresh();
            }
        }
        imgui_end_combo();
    }
    imgui_pop_item_width();
}

void params_doors(Object *object)
{
    if (!object)
    {
        return;
    }

    imgui_text("Activation:");
    imgui_same_line();
    if (imgui_radiobutton("Interaction", &object->flag[0], 0))
    {
        object->flag[1] = 0;
    }
    imgui_same_line();
    if (imgui_radiobutton("Switch", &object->flag[0], 1))
    {
        object->flag[1] = 0;
    }
    imgui_same_line();
    if (imgui_radiobutton("Trigger zone", &object->flag[0], 2))
    {
        object->flag[1] = 0;
    }
    imgui_same_line();
    if (imgui_radiobutton("Key", &object->flag[0], 3))
    {
        object->flag[1] = 0;
    }
    imgui_same_line();
    if (imgui_radiobutton("None (static)", &object->flag[0], 4))
    {
        object->flag[1] = 0;
    }

    if (object->flag[0] == 3)
    {
        imgui_text("Key type:");
        imgui_same_line();
        imgui_radio_button("blue", &object->flag[1], 0);
        imgui_same_line();
        imgui_radio_button("red", &object->flag[1], 1);
        imgui_same_line();
        imgui_radio_button("yellow", &object->flag[1], 2);
    }
    else if (object->flag[0] == 1 || object->flag[0] == 2)
    {
        params_id(object);
    }
}

void params_gate(Object *object)
{
    if (!object)
    {
        return;
    }

    imgui_text("Activation:");
    imgui_same_line();
    imgui_radiobutton("None (static)", &object->flag[0], 0);
    imgui_same_line();
    imgui_radiobutton("Switch", &object->flag[0], 1);
    imgui_same_line();
    imgui_radiobutton("Trigger zone", &object->flag[0], 2);

    if (object->flag[0] == 1 || object->flag[0] == 2)
    {
        params_id(object);
    }
}

void params_switch(Object *object)
{
    if (!object)
    {
        return;
    }

    params_id(object);
}

void params_player_start(Object *object)
{
    if (!object)
    {
        return;
    }

    imgui_text("Starting weapon:");
    imgui_same_line();
    imgui_radiobutton("Default", &object->flag[0], 0);
    imgui_same_line();
    imgui_radiobutton("Pistol", &object->flag[0], 1);
    imgui_same_line();
    imgui_radiobutton("Shotgun", &object->flag[0], 2);
    imgui_same_line();
    imgui_radiobutton("Chaingun", &object->flag[0], 3);
    imgui_same_line();
    imgui_radiobutton("Rocketlauncher", &object->flag[0], 4);
}

void params_object_spawn_point(Object *object)
{
    if (!object)
    {
        return;
    }

    imgui_text("Category:");
    imgui_same_line();
    var avail_combobox_width = imgui_get_content_region_avail_width();
    imgui_push_item_width(avail_combobox_width);
    if (imgui_begin_combo("##category combobox", _chr(used_spawn_category_str), ImGuiComboFlags_HeightSmall))
    {
        int i = 0;
        for (i = 0; i < MAX_SPAWN_CATEGORIES; i++)
        {
            int is_selected = str_cmp(used_spawn_category_str, spawn_category_list_str[i]);
            if (imgui_selectable(_chr(spawn_category_list_str[i]), &is_selected, 0))
            {
                preview_cell.object.flag[2] = i;
                preview_cell.object.flag[3] = 0;
                str_cpy(used_spawn_category_str, spawn_category_list_str[i]);
                params_spawn_point_refresh();
            }
        }
        imgui_end_combo();
    }
    imgui_pop_item_width();

    if (preview_cell.object.flag[2] == 0) // item
    {
        imgui_text("Object:  ");
        imgui_same_line();
        var avail_combobox_width = imgui_get_content_region_avail_width();
        imgui_push_item_width(avail_combobox_width);
        if (imgui_begin_combo("##object item combobox", _chr(used_spawn_item_str), ImGuiComboFlags_HeightSmall))
        {
            int i = 0;
            for (i = 0; i < MAX_SPAWN_ITEMS; i++)
            {
                int is_selected = str_cmp(used_spawn_item_str, spawn_item_list_str[i]);
                if (imgui_selectable(_chr(spawn_item_list_str[i]), &is_selected, 0))
                {
                    preview_cell.object.flag[3] = i;
                    str_cpy(used_spawn_item_str, spawn_item_list_str[i]);
                    params_spawn_point_refresh();
                }
            }
            imgui_end_combo();
        }
        imgui_pop_item_width();
    }
    else if (preview_cell.object.flag[2] == 1) // enemy
    {
        imgui_text("Object:  ");
        imgui_same_line();
        var avail_combobox_width = imgui_get_content_region_avail_width();
        imgui_push_item_width(avail_combobox_width);
        if (imgui_begin_combo("##object enemy combobox", _chr(used_spawn_enemies_str), ImGuiComboFlags_HeightSmall))
        {
            int i = 0;
            for (i = 0; i < MAX_SPAWN_ENEMIES; i++)
            {
                int is_selected = str_cmp(used_spawn_enemies_str, spawn_enemies_list_str[i]);
                if (imgui_selectable(_chr(spawn_enemies_list_str[i]), &is_selected, 0))
                {
                    preview_cell.object.flag[3] = i;
                    str_cpy(used_spawn_enemies_str, spawn_enemies_list_str[i]);
                    params_spawn_point_refresh();
                }
            }
            imgui_end_combo();
        }
        imgui_pop_item_width();
    }
    else if (preview_cell.object.flag[2] == 2) // boss
    {
        imgui_text("Object:  ");
        imgui_same_line();
        var avail_combobox_width = imgui_get_content_region_avail_width();
        imgui_push_item_width(avail_combobox_width);
        if (imgui_begin_combo("##object boss combobox", _chr(used_spawn_bosses_str), ImGuiComboFlags_HeightSmall))
        {
            int i = 0;
            for (i = 0; i < MAX_SPAWN_BOSSES; i++)
            {
                int is_selected = str_cmp(used_spawn_bosses_str, spawn_bosses_list_str[i]);
                if (imgui_selectable(_chr(spawn_bosses_list_str[i]), &is_selected, 0))
                {
                    preview_cell.object.flag[3] = i;
                    str_cpy(used_spawn_bosses_str, spawn_bosses_list_str[i]);
                    params_spawn_point_refresh();
                }
            }
            imgui_end_combo();
        }
        imgui_pop_item_width();
    }

    imgui_text("Activation:");
    imgui_same_line();
    imgui_radiobutton("On creation", &object->flag[0], 0);
    imgui_same_line();
    imgui_radiobutton("Switch", &object->flag[0], 1);
    imgui_same_line();
    imgui_radiobutton("Trigger zone", &object->flag[0], 2);

    if (object->flag[0] == 1 || object->flag[0] == 2)
    {
        params_id(object);
    }
}

void params_secret_wall(Object *object)
{
    if (!object)
    {
        return;
    }

    imgui_text("Activation:");
    imgui_same_line();
    imgui_radiobutton("Interaction", &object->flag[0], 0);
    imgui_same_line();
    imgui_radiobutton("Switch", &object->flag[0], 1);
    imgui_same_line();
    imgui_radiobutton("Trigger zone", &object->flag[0], 2);

    if (object->flag[0] == 1 || object->flag[0] == 2)
    {
        params_id(object);
    }
}

void params_npc(Object *object)
{
    if (!object)
    {
        return;
    }

    imgui_text("Drop item:");
    imgui_same_line();
    imgui_radiobutton("false", &object->flag[0], 0);
    imgui_same_line();
    imgui_radiobutton("true", &object->flag[0], 1);

    if (object->flag[0] == true)
    {
        imgui_radiobutton("Key blue", &object->flag[1], 0);
        imgui_same_line();
        imgui_radiobutton("Key red", &object->flag[1], 1);
        imgui_same_line();
        imgui_radiobutton("Key yellow", &object->flag[1], 2);
        imgui_same_line();
        imgui_radiobutton("Health", &object->flag[1], 3);
        imgui_same_line();
        imgui_radiobutton("Ammo", &object->flag[1], 4);
    }
}

void object_params_gui(int type, int index)
{
    if (type < ASSET_EVENTS)
    {
        return;
    }

    if (is_light(type, index))
    {
        params_lights(&preview_cell.object);
    }
    else if (is_door(type, index))
    {
        params_doors(&preview_cell.object);
    }
    else if (is_gate(type, index))
    {
        params_gate(&preview_cell.object);
    }
    else if (is_player_start(type, index))
    {
        params_player_start(&preview_cell.object);
    }
    else if (is_object_spawn_point(type, index))
    {
        params_object_spawn_point(&preview_cell.object);
    }
    else if (is_secret_wall(type, index))
    {
        params_secret_wall(&preview_cell.object);
    }
    else if (is_enemy(type) || is_boss(type))
    {
        params_npc(&preview_cell.object);
    }
    else if (is_switch(type, index))
    {
        params_switch(&preview_cell.object);
    }
    else if (is_trigger_zone(type, index) || is_teleport_in(type, index) || is_teleport_out(type, index))
    {
        params_id(&preview_cell.object);
    }
}