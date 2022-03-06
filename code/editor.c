
float get_hsv_from_color(float value)
{
    return value / 255;
}

float get_color_from_hsv(float value)
{
    return value * 255;
}

void editor_create_tooltip(char *tooltip)
{
    if (imgui_is_item_hovered())
    {
        imgui_set_tooltip(tooltip);
        imgui_begin_tooltip();
        imgui_end_tooltip();
    }
}

void editor_help_maker(char *desc)
{
    imgui_text_disabled("(?)");
    if (imgui_is_item_hovered())
    {
        imgui_begin_tooltip();
        imgui_push_text_wrap_pos(imgui_get_font_size() * 35);
        imgui_text_unformatted(desc);
        imgui_pop_text_wrap_pos();
        imgui_end_tooltip();
    }
}

void editor_camera_resize()
{
    if (editor_state == EDITOR_STATE_EDIT_MAP || editor_state == EDITOR_STATE_EMPTY)
    {
        camera->pos_x = 0;
        camera->pos_y = EDITOR_TOP_BAR_HEIGHT;
        camera->size_x = screen_size.x;
        camera->size_y = screen_size.y - EDITOR_TOP_BAR_HEIGHT;

        if (editor_state == EDITOR_STATE_EDIT_MAP)
        {
            camera->size_x = screen_size.x - EDITOR_SIDE_BAR_WIDTH;
        }
    }
    else
    {
        camera->pos_x = 0;
        camera->pos_y = 0;
        camera->size_x = screen_size.x;
        camera->size_y = screen_size.y;
    }
}

STRING *get_cell_info(Cell *cell)
{
    if (!cell)
    {
        return;
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
    str_printf(info_str, editor_info_main_str, (long)cell_pos.x, (long)cell_pos.y, (long)cell_pos.z, (long)cell_x, (long)cell_y, (double)cell_pan, (long)cell_id);

    str_cat(info_str, "\n");

    // asset type and index
    if (cell_type == ASSET_TYPE_WALLS)
    {
        str_cat(info_str, editor_info_type_wall_str);
    }
    else if (cell_type == ASSET_TYPE_PROPS)
    {
        str_cat(info_str, editor_info_type_props_str);
    }
    else if (cell_type == ASSET_TYPE_EVENTS)
    {
        str_cat(info_str, editor_info_type_event_str);
    }
    else if (cell_type == ASSET_TYPE_ITEMS)
    {
        str_cat(info_str, editor_info_type_item_str);
    }
    else if (cell_type == ASSET_TYPE_ENEMIES)
    {
        str_cat(info_str, editor_info_type_enemy_str);
    }
    else if (cell_type == ASSET_TYPE_BOSSES)
    {
        str_cat(info_str, editor_info_type_boss_str);
    }
    str_cat(info_str, editor_info_desc_str);
    str_cat(info_str, asset_get_desc(cell_type, cell_asset));
    str_cat(info_str, editor_semicolon_str);

    // parameters
    if (cell_type == ASSET_TYPE_WALLS && cell_asset != TOTAL_WALL_TEXTURES - 1)
    {
        str_cat(info_str, editor_info_params_str);
        if (cell_flag == true)
        {
            str_cat(info_str, editor_info_wall_secret_str);
        }
        else
        {
            str_cat(info_str, editor_info_wall_solid_str);
        }
    }
    else if (cell_type == ASSET_TYPE_PROPS && cell_asset == PROPS_FENCE || cell_type == ASSET_TYPE_PROPS && cell_asset == PROPS_FENCE_DIRTY || cell_type == ASSET_TYPE_PROPS && cell_asset == PROPS_DOOR || cell_type == ASSET_TYPE_PROPS && cell_asset == PROPS_DOOR_ELEVATOR || cell_type == ASSET_TYPE_PROPS && cell_asset == PROPS_DOOR_LOCKED || cell_type == ASSET_TYPE_PROPS && cell_asset == PROPS_SWITCH)
    {
        str_cat(info_str, editor_info_params_str);
        if (cell_asset == PROPS_FENCE || cell_asset == PROPS_FENCE_DIRTY || cell_asset == PROPS_DOOR || cell_asset == PROPS_DOOR_ELEVATOR)
        {
            str_cat(info_str, editor_info_activation_str);
            if (cell_event_type == 0)
            {
                str_cat(info_str, editor_info_on_interaction_str);
            }
            else if (cell_event_type == 1)
            {
                str_cat(info_str, str_printf(NULL, editor_info_trigger_zone_id_str, (long)cell_event_id));
            }
            else if (cell_event_type == 2)
            {
                str_cat(info_str, str_printf(NULL, editor_info_siwtch_id_str, (long)cell_event_id));
            }
        }
        else if (cell_asset == PROPS_DOOR_LOCKED)
        {
            str_cat(info_str, editor_info_key_requires_str);
            if (cell_event_type == 0)
            {
                str_cat(info_str, params_drop_item_key_blue_str);
            }
            else if (cell_event_type == 1)
            {
                str_cat(info_str, params_drop_item_key_red_str);
            }
            else if (cell_event_type == 2)
            {
                str_cat(info_str, params_drop_item_key_yellow_str);
            }
            str_cat(info_str, editor_semicolon_str);
        }
        else if (cell_asset == PROPS_SWITCH)
        {
            str_cat(info_str, str_printf(NULL, editor_info_props_switch_id_str, (long)cell_event_id));
        }
    }
    else if (cell_type == ASSET_TYPE_EVENTS && cell_asset == EVENT_TRIGGER_ZONE || cell_type == ASSET_TYPE_EVENTS && cell_asset == EVENT_SPAWN_OBJECT)
    {
        if (cell_asset == EVENT_TRIGGER_ZONE)
        {
            str_cat(info_str, editor_info_params_str);
            str_cat(info_str, str_printf(NULL, editor_info_event_trigger_zone_id_str, (long)cell_event_id));
        }
        else if (cell_asset == EVENT_SPAWN_OBJECT)
        {
            str_cat(info_str, editor_info_params_str);

            // activation
            str_cat(info_str, editor_info_activation_str);
            if (cell_event_type == 0)
            {
                str_cat(info_str, editor_info_on_creation_str);
            }
            else if (cell_event_type == 1)
            {
                str_cat(info_str, str_printf(NULL, editor_info_trigger_zone_id_str, (long)cell_event_id));
            }
            else if (cell_event_type == 2)
            {
                str_cat(info_str, str_printf(NULL, editor_info_siwtch_id_str, (long)cell_event_id));
            }

            // category
            str_cat(info_str, editor_info_event_spawn_str);
            if (cell_flag == 0) // items
            {
                str_cat(info_str, params_spawn_object_type_item_str);
                str_cat(info_str, ": ");

                if (cell_temp_skill == 0)
                {
                    str_cat(info_str, params_drop_item_key_blue_str);
                }
                else if (cell_temp_skill == 1)
                {
                    str_cat(info_str, params_drop_item_key_red_str);
                }
                else if (cell_temp_skill == 2)
                {
                    str_cat(info_str, params_drop_item_key_yellow_str);
                }
                else if (cell_temp_skill == 3)
                {
                    str_cat(info_str, params_drop_item_small_medkit_str);
                }
                else if (cell_temp_skill == 4)
                {
                    str_cat(info_str, params_drop_item_big_medkit_str);
                }
                str_cat(info_str, editor_semicolon_str);
            }
            else if (cell_flag == 1) // weapons / ammo
            {
                str_cat(info_str, params_spawn_object_type_weapon_str);
                str_cat(info_str, ": ");

                if (cell_temp_skill == 0)
                {
                    str_cat(info_str, params_spawn_object_ammo_big_str);
                }
                else if (cell_temp_skill == 1)
                {
                    str_cat(info_str, params_spawn_object_weapon_pistol_str);
                }
                else if (cell_temp_skill == 2)
                {
                    str_cat(info_str, params_spawn_object_ammo_pistol_str);
                }
                else if (cell_temp_skill == 3)
                {
                    str_cat(info_str, params_spawn_object_weapon_shotgun_str);
                }
                else if (cell_temp_skill == 4)
                {
                    str_cat(info_str, params_spawn_object_ammo_shotgun_str);
                }
                else if (cell_temp_skill == 5)
                {
                    str_cat(info_str, params_spawn_object_weapon_smg_str);
                }
                else if (cell_temp_skill == 6)
                {
                    str_cat(info_str, params_spawn_object_ammo_smg_str);
                }
                else if (cell_temp_skill == 7)
                {
                    str_cat(info_str, params_spawn_object_weapon_machinegun_str);
                }
                else if (cell_temp_skill == 8)
                {
                    str_cat(info_str, params_spawn_object_ammo_machinegun_str);
                }
                else if (cell_temp_skill == 9)
                {
                    str_cat(info_str, params_spawn_object_weapon_rocketlauncher_str);
                }
                else if (cell_temp_skill == 10)
                {
                    str_cat(info_str, params_spawn_object_ammo_rocketlauncher_str);
                }
                str_cat(info_str, editor_semicolon_str);
            }
            else if (cell_flag == 2) // enemies
            {
                str_cat(info_str, params_spawn_object_type_enemy_str);
                str_cat(info_str, ": ");

                if (cell_temp_skill == 0)
                {
                    str_cat(info_str, params_spawn_object_enemy_rat_str);
                }
                else if (cell_temp_skill == 1)
                {
                    str_cat(info_str, params_spawn_object_enemy_dog_str);
                }
                else if (cell_temp_skill == 2)
                {
                    str_cat(info_str, params_spawn_object_enemy_guard_pistol_str);
                }
                else if (cell_temp_skill == 3)
                {
                    str_cat(info_str, params_spawn_object_enemy_guard_shotgun_str);
                }
                else if (cell_temp_skill == 4)
                {
                    str_cat(info_str, params_spawn_object_enemy_soldier_smg_str);
                }
                else if (cell_temp_skill == 5)
                {
                    str_cat(info_str, params_spawn_object_enemy_suicide_bomber_str);
                }
                else if (cell_temp_skill == 6)
                {
                    str_cat(info_str, params_spawn_object_enemy_zombie_str);
                }
                else if (cell_temp_skill == 7)
                {
                    str_cat(info_str, params_spawn_object_enemy_support_machinegun_str);
                }
                else if (cell_temp_skill == 8)
                {
                    str_cat(info_str, params_spawn_object_enemy_support_rocketlauncher_str);
                }
                str_cat(info_str, editor_semicolon_str);
            }
            else if (cell_flag == 3) // bosses
            {
                str_cat(info_str, params_spawn_object_type_boss_str);
                str_cat(info_str, ": ");

                if (cell_temp_skill == 0)
                {
                    str_cat(info_str, params_spawn_object_boss_uber_soldier_str);
                }
                else if (cell_temp_skill == 1)
                {
                    str_cat(info_str, params_spawn_object_boss_uber_officer_str);
                }
                else if (cell_temp_skill == 2)
                {
                    str_cat(info_str, params_spawn_object_boss_uber_mutant_str);
                }
                else if (cell_temp_skill == 3)
                {
                    str_cat(info_str, params_spawn_object_boss_mecha_soldier_str);
                }
                else if (cell_temp_skill == 4)
                {
                    str_cat(info_str, params_spawn_object_boss_demon_str);
                }
                str_cat(info_str, editor_semicolon_str);
            }
        }
    }
    else if (cell_type == ASSET_TYPE_ENEMIES)
    {
        str_cat(info_str, editor_info_params_str);
        if (cell_flag == true)
        {
            str_cat(info_str, editor_info_drop_item_str);
            if (cell_event_type == 0)
            {
                str_cat(info_str, params_drop_item_key_blue_str);
            }
            else if (cell_event_type == 1)
            {
                str_cat(info_str, params_drop_item_key_red_str);
            }
            else if (cell_event_type == 2)
            {
                str_cat(info_str, params_drop_item_key_yellow_str);
            }
            else if (cell_event_type == 3)
            {
                str_cat(info_str, params_drop_item_small_medkit_str);
            }
            else if (cell_event_type == 4)
            {
                str_cat(info_str, params_drop_item_big_medkit_str);
            }
            else if (cell_event_type == 5)
            {
                str_cat(info_str, params_drop_item_ammo_str);
            }
            else if (cell_event_type == 6)
            {
                str_cat(info_str, params_drop_item_weapon_str);
            }
            str_cat(info_str, editor_semicolon_str);
        }
        else
        {
            str_cat(info_str, editor_info_drop_item_false_str);
        }
    }
    else if (cell_type == ASSET_TYPE_BOSSES)
    {
        str_cat(info_str, editor_info_params_str);
        if (cell_flag == true)
        {
            str_cat(info_str, editor_info_drop_item_str);
            if (cell_event_type == 0)
            {
                str_cat(info_str, params_drop_item_key_blue_str);
            }
            else if (cell_event_type == 1)
            {
                str_cat(info_str, params_drop_item_key_red_str);
            }
            else if (cell_event_type == 2)
            {
                str_cat(info_str, params_drop_item_key_yellow_str);
            }
            else if (cell_event_type == 3)
            {
                str_cat(info_str, params_drop_item_small_medkit_str);
            }
            else if (cell_event_type == 4)
            {
                str_cat(info_str, params_drop_item_big_medkit_str);
            }
            str_cat(info_str, editor_semicolon_str);
        }
        else
        {
            str_cat(info_str, editor_info_drop_item_false_str);
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