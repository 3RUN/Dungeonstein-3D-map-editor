
void editor_test_run_get_cell_info(Map *map)
{
    if (!map)
    {
        return;
    }

    int x = 0;
    int y = 0;

    vec_worldpos_to_grid(&selected_cell_pos, &x, &y);
    get_cell_info(&map->cell[x][y], &selected_cell_info_str);
}

void editor_test_run_select_player_on_start(Map *map)
{
    if (!map)
    {
        return;
    }

    int x = 0, y = 0, player_found = false;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            Cell *cell = &map->cell[x][y];
            if (!cell)
            {
                continue;
            }

            if (is_player_start(cell->type, cell->asset) == false)
            {
                continue;
            }

            vec_set(&selected_cell_pos, &cell->worldpos);
            editor_test_run_get_cell_info(map);
            return;
        }
    }

    vec_set(&selected_cell_pos, nullvector);
    editor_test_run_get_cell_info(map);
}

void editor_test_run_initialize()
{
    crosshair_pan = pan_create(NULL, CROSSHAIR_LAYER);
    layer_sort(crosshair_pan, CROSSHAIR_LAYER);
    crosshair_pan->bmap = crosshair_pcx;
    set(crosshair_pan, UNTOUCHABLE | OVERLAY);
}

void editor_test_run_destroy()
{
    if (crosshair_pan)
    {
        safe_remove(crosshair_pan);
    }
}

void editor_test_run_crosshair_show()
{
    if (!is(crosshair_pan, SHOW))
    {
        set(crosshair_pan, SHOW);
    }
}

void editor_test_run_crosshair_hide()
{
    if (is(crosshair_pan, SHOW))
    {
        reset(crosshair_pan, SHOW);
    }
}

void editor_test_run_remove_binding(var scancode)
{
    if (scancode <= 0)
    {
        return;
    }

    key_set(scancode, NULL);
}

void editor_test_run_update_binding(var scancode, void *fnc)
{
    if (scancode <= 0)
    {
        return;
    }

    key_set(scancode, NULL);
    key_set(scancode, fnc);
}

void editor_test_run_update_from_config(Config *config)
{
    editor_test_run_remove_binding(scancode_interact);

    scancode_interact = engine_key_return_scancode_from_letter(config->input_draw);

    editor_test_run_update_binding(scancode_interact, editor_test_run_info_trace);
}

void editor_test_run_info_trace()
{
    VECTOR to;
    vec_set(&to, vector(1000, 0, 0));
    vec_rotate(&to, &camera->pan);
    vec_add(&to, &camera->x);

    c_trace(&camera->x, &to, TRACE_FLAGS | ACTIVATE_SHOOT);
    if (trace_hit)
    {
        vec_set(&selected_cell_pos, &target);

        VECTOR temp_pos;
        vec_set(&temp_pos, &normal);
        vec_scale(&temp_pos, -(MAP_CELL_SIZE / 2));
        vec_add(&selected_cell_pos, &temp_pos);
        vec_snap_to_grid(&selected_cell_pos);

        Map *active_map = map_get_active(&def_episode);
        if (active_map)
        {
            editor_test_run_get_cell_info(active_map);
        }
    }
}

void editor_test_run_update()
{
    if (is_player_found == false)
    {
        draw_text("Player is not created", 5, 5 * config_saved.font_scale, COLOR_RED);
    }
    else
    {
        draw_text("Player is created", 5, 5 * config_saved.font_scale, COLOR_GREEN);
    }

    if (is_finish_found == false)
    {
        draw_text("Elevator switch is not created", 5, 25 * config_saved.font_scale, COLOR_RED);
    }
    else
    {
        draw_text("Elevator switch is created", 5, 25 * config_saved.font_scale, COLOR_GREEN);
    }

    STRING *map_stat_str = "";
    str_printf(map_stat_str, "Props: %d\nEvents: %d\nItems: %d\nEnemies: %d\nBosses: %d\nSecrets: %d\nTreasures: %d", (long)props_count, (long)event_count, (long)items_count, (long)enemies_cout, (long)bosses_count, (long)secrets_count, (long)treasure_count);
    draw_text(map_stat_str, 5, 45 * config_saved.font_scale, COLOR_WHITE);

    draw_text(selected_cell_info_str, 5, 170 * config_saved.font_scale, COLOR_WHITE);

    VECTOR selected_bbox_min, selected_bbox_max;
    vec_fill(&selected_bbox_min, -(MAP_CELL_SIZE / 2));
    selected_bbox_min.x *= 1.01;
    selected_bbox_min.y *= 1.01;
    selected_bbox_min.z *= 0.99;

    vec_fill(&selected_bbox_max, MAP_CELL_SIZE / 2);
    selected_bbox_max.x *= 1.01;
    selected_bbox_max.y *= 1.01;
    selected_bbox_max.z *= 0.99;

    draw_bbox3d(&selected_cell_pos, &selected_bbox_min, &selected_bbox_max, vector(0, 0, 0), COLOR_GREEN, 100);

    if (crosshair_pan)
    {
        crosshair_pan->pos_x = (screen_size.x / 2) - (bmap_width(crosshair_pcx) / 2);
        crosshair_pan->pos_y = (screen_size.y / 2) - (bmap_height(crosshair_pcx) / 2);
    }

    // handle esc without on_esc
    // because on_ engine events are handled after imgui
    // I've also separated esc from popup esc
    if (is_popup_opened == false)
    {
        is_esc_popup_allowed = false;

        if (key_esc)
        {
            if (is_esc_allowed == true)
            {
                editor_switch_state_to(EDITOR_STATE_FROM_BUILD);
                is_esc_allowed = false;
            }
        }
        else
        {
            is_esc_allowed = true;
        }
    }
    else // this part is used in popup functions
    {
        is_esc_allowed = false;

        if (key_esc)
        {
            if (is_esc_popup_allowed == true)
            {
                is_esc_popup_allowed = false;
            }
        }
        else
        {
            is_esc_popup_allowed = true;
        }
    }
}