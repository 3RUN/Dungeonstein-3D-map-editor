
void particle_laserbeam_event(PARTICLE *p)
{
    p->alpha -= laserbeam_fade_speed * time_step;
    if (p->alpha < 0)
    {
        p->lifespan = 0;
    }
}

void particle_laserbeam(PARTICLE *p)
{
    vec_set(&p->blue, LASERBEAM_COLOR);
    set(p, BEAM | LIGHT | BRIGHT | NOFILTER | TRANSLUCENT);
    p->alpha = laserbeam_alpha;
    p->size = laserbeam_size;
    p->event = particle_laserbeam_event;
}

var is_activation_cell(Cell *cell)
{
    if (!cell)
    {
        return false;
    }

    if (cell->type == ASSET_TYPE_EVENTS && cell->asset == EVENT_TRIGGER_ZONE)
    {
        return true;
    }

    if (cell->type == ASSET_TYPE_PROPS && cell->asset == PROPS_SWITCH)
    {
        return true;
    }

    return false;
}

var is_object_to_link(Cell *cell)
{
    if (!cell)
    {
        return false;
    }

    if (cell->type == ASSET_TYPE_WALLS && cell->event_type >= 1) // 1 - trigger zone or 2 - switch)
    {
        return true;
    }

    if (cell->type == ASSET_TYPE_PROPS && cell->event_type >= 1) // 1 - trigger zone or 2 - switch)
    {
        if (cell->asset == PROPS_DOOR || cell->asset == PROPS_DOOR_ELEVATOR || cell->asset == PROPS_FENCE || cell->asset == PROPS_FENCE_DIRTY)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    if (cell->type == ASSET_TYPE_EVENTS && cell->asset == EVENT_SPAWN_OBJECT && cell->event_type >= 1) // 1 - trigger zone or 2 - switch)
    {
        return true;
    }

    return false;
}

void editor_cell_linker_destroy_array(array_t *array)
{
    if (!array)
    {
        return;
    }

    array_enumerate_begin(Cell *, array, v)
    {
        if (v)
        {
            v = NULL;
        }
    }
    array_enumerate_end(array);
    array_destroy(array);
}

void editor_cell_linker_destroy()
{
    if (switch_n_trigger_list)
    {
        editor_cell_linker_destroy_array(switch_n_trigger_list);
        switch_n_trigger_list = NULL;
    }

    if (objects_to_link_list)
    {
        editor_cell_linker_destroy_array(objects_to_link_list);
        objects_to_link_list = NULL;
    }
}

void editor_cell_show_links()
{
    var i = 0, j = 0;
    for (i = 0; i < array_get_count(switch_n_trigger_list); i++)
    {
        Cell *activator_cell = array_get_element_at(Cell *, switch_n_trigger_list, i);
        if (!activator_cell)
        {
            continue;
        }

        VECTOR from;
        vec_set(&from, vector(activator_cell->worldpos.x, activator_cell->worldpos.y, activator_cell->worldpos.z + CELL_LINK_Z_OFFSET));
        var id = activator_cell->event_id;
        var type = activator_cell->type;
        var asset = activator_cell->asset;

        var activator_type = 1; // default is trigger zone
        if (type == ASSET_TYPE_PROPS && asset == PROPS_SWITCH)
        {
            activator_type = 2;
        }

        for (j = 0; j < array_get_count(objects_to_link_list); j++)
        {
            Cell *object_cell = array_get_element_at(Cell *, objects_to_link_list, j);
            if (!object_cell)
            {
                continue;
            }

            VECTOR to;
            vec_set(&to, vector(object_cell->worldpos.x, object_cell->worldpos.y, object_cell->worldpos.z + CELL_LINK_Z_OFFSET));
            var obj_id = object_cell->event_id;
            var obj_activator_type = object_cell->event_type; // 1 - trigger zone or 2 - switch

            if (id == obj_id && activator_type == obj_activator_type)
            {
                VECTOR diff;
                vec_diff(&diff, &to, &from);
                effect(particle_laserbeam, 1, &from, &diff);
            }
        }
    }
}

void editor_cell_find_links(Map *map)
{
    if (proc_status(editor_cell_find_links) > 1)
    {
        return;
    }

    if (!map)
    {
        return;
    }

    if (switch_n_trigger_list)
    {
        editor_cell_linker_destroy_array(switch_n_trigger_list);
        switch_n_trigger_list = NULL;
    }
    switch_n_trigger_list = array_create(Cell *, 1);

    if (objects_to_link_list)
    {
        editor_cell_linker_destroy_array(objects_to_link_list);
        objects_to_link_list = NULL;
    }
    objects_to_link_list = array_create(Cell *, 1);

    var x = 0, y = 0, id = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            Cell *cell = &map->cell[x][y];

            if (is_activation_cell(cell) == true)
            {
                array_add(Cell *, switch_n_trigger_list, cell);
            }
            else if (is_object_to_link(cell) == true)
            {
                array_add(Cell *, objects_to_link_list, cell);
            }
        }
    }

    editor_cell_show_links();
}

void editor_cell_linker_update(Map *map)
{
    if (!map)
    {
        return;
    }

    if (is_cell_links_visible == false)
    {
        return;
    }

    link_refresh_timer += time_frame / 16;
    while (link_refresh_timer > link_refresh_cooldown)
    {
        editor_cell_find_links(map);
        link_refresh_timer -= link_refresh_cooldown;
    }
}