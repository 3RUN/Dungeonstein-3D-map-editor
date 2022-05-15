
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

void particle_draw_line(VECTOR *from, VECTOR *to)
{
    VECTOR diff;
    vec_diff(&diff, to, from);
    effect(particle_laserbeam, 1, from, &diff);
}

int is_activation_object(Object *object)
{
    if (!object)
    {
        return false;
    }

    int type = object->type;
    int index = object->index;

    if (!is_switch(type, index) && !is_trigger_zone(type, index) && !is_a_key_blue(type, index) && !is_a_key_red(type, index) && !is_a_key_yellow(type, index) && !is_teleport_in(type, index))
    {
        return false;
    }

    return true;
}

int is_object_to_link(Object *object)
{
    if (!object)
    {
        return false;
    }

    int type = object->type;
    int index = object->index;

    if (!is_door(type, index) && !is_gate(type, index) && !is_object_spawn_point(type, index) && !is_secret_wall(type, index) && !is_teleport_out(type, index))
    {
        return false;
    }

    return true;
}

void object_linker_destroy_array(array_t *array)
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

void object_linker_destroy()
{
    if (activator_list)
    {
        object_linker_destroy_array(activator_list);
        activator_list = NULL;
    }

    if (objects_to_link_list)
    {
        object_linker_destroy_array(objects_to_link_list);
        objects_to_link_list = NULL;
    }
}

void object_show_links()
{
    int i = 0, j = 0;
    for (i = 0; i < array_get_count(activator_list); i++)
    {
        Cell *activator_cell = array_get_element_at(Cell *, activator_list, i);
        if (!activator_cell)
        {
            continue;
        }

        VECTOR from;
        vec_set(&from, &activator_cell->pos);
        from.z += CELL_LINK_Z_OFFSET;

        Object *activator = &activator_cell->object;
        if (!activator)
        {
            continue;
        }

        int activator_id = activator->flag[1];
        int activator_type = activator->type;
        int activator_index = activator->index;

        for (j = 0; j < array_get_count(objects_to_link_list); j++)
        {
            Cell *object_cell = array_get_element_at(Cell *, objects_to_link_list, j);
            if (!object_cell)
            {
                continue;
            }

            VECTOR to;
            vec_set(&to, &object_cell->pos);
            to.z += CELL_LINK_Z_OFFSET;

            Object *object_to_link = &object_cell->object;
            if (!object_to_link)
            {
                continue;
            }

            int requires = object_to_link->flag[0];
            int id = object_to_link->flag[1];
            int type = object_to_link->type;
            int index = object_to_link->index;

            if (is_door(type, index))
            {
                if (requires == 1) // key
                {
                    if (id == 0 && is_a_key_blue(activator_type, activator_index))
                    {
                        particle_draw_line(&from, &to);
                    }
                    else if (id == 1 && is_a_key_red(activator_type, activator_index))
                    {
                        particle_draw_line(&from, &to);
                    }
                    else if (id == 2 && is_a_key_yellow(activator_type, activator_index))
                    {
                        particle_draw_line(&from, &to);
                    }
                }
                else if (requires == 2 && is_switch(activator_type, activator_index)) // switch
                {
                    if (activator_id == id)
                    {
                        particle_draw_line(&from, &to);
                    }
                }
                else if (requires == 3 && is_trigger_zone(activator_type, activator_index)) // trigger zone
                {
                    if (activator_id == id)
                    {
                        particle_draw_line(&from, &to);
                    }
                }
            }
            else if (is_gate(type, index) || is_object_spawn_point(type, index) || is_secret_wall(type, index))
            {
                if (requires == 1 && is_switch(activator_type, activator_index)) // switch
                {
                    if (activator_id == id)
                    {
                        particle_draw_line(&from, &to);
                    }
                }
                else if (requires == 2 && is_trigger_zone(activator_type, activator_index)) // trigger zone
                {
                    if (activator_id == id)
                    {
                        particle_draw_line(&from, &to);
                    }
                }
            }
            else if (is_teleport_out(type, index))
            {
                if (is_teleport_in(activator_type, activator_index))
                {
                    if (activator_id == id)
                    {
                        particle_draw_line(&from, &to);
                    }
                }
            }
        }
    }
}

void object_linker_find_links(Map *map)
{
    if (proc_status(object_linker_find_links) > 1)
    {
        return;
    }

    if (!map)
    {
        return;
    }

    if (activator_list)
    {
        object_linker_destroy_array(activator_list);
        activator_list = NULL;
    }
    activator_list = array_create(Cell *, 1);

    if (objects_to_link_list)
    {
        object_linker_destroy_array(objects_to_link_list);
        objects_to_link_list = NULL;
    }
    objects_to_link_list = array_create(Cell *, 1);

    int x = 0, y = 0, id = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            Cell *cell = &map->cell[x][y];
            Object *object = &cell->object;

            if (is_activation_object(object) == true)
            {
                array_add(Cell *, activator_list, cell);
            }
            else if (is_object_to_link(object) == true)
            {
                array_add(Cell *, objects_to_link_list, cell);
            }
        }
    }

    object_show_links();
}

void object_linker_update(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    Map *active_map = map_get_active(episode);
    if (!active_map)
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
        object_linker_find_links(active_map);
        link_refresh_timer -= link_refresh_cooldown;
    }
}