
void map_sketch_sprite_ent_fnc()
{
    set(my, PASSABLE | INVISIBLE | LIGHT | NOFILTER | UNLIT);
    vec_fill(&my->scale_x, 0.5 * SKETCH_SPRITE_SCALE_FACTOR); // scale down from 64x64 to 32x32 (tile_size)
    my->pan = DEF_CELL_PAN;                                   // default pan, and don't change this !
    my->tilt = 90;                                            // look upwards !
}

void map_sketch_sprite_parent_ent_fnc()
{
    set(my, PASSABLE | INVISIBLE | NOFILTER | BRIGHT | UNLIT);
    vec_fill(&my->scale_x, 0.5 * SKETCH_SPRITE_SCALE_FACTOR); // scale down from 64x64 to 32x32 (tile_size)
    my->pan = DEF_CELL_PAN;                                   // default pan, and don't change this !
    my->tilt = 90;                                            // look upwards !
}

void map_cursor_sprite_ent_fnc()
{
    set(my, PASSABLE | TRANSLUCENT | NOFILTER | BRIGHT | UNLIT);
    vec_fill(&my->scale_x, 0.5 * SKETCH_SPRITE_SCALE_FACTOR); // scale down from 64x64 to 32x32 (tile_size)
    my->pan = DEF_CELL_PAN;                                   // default pan, and don't change this !
    my->tilt = 90;                                            // look upwards !
}

void map_sketch_initialize()
{
    cursor_sprite_ent = ent_create(cursor_sprite_tga, nullvector, map_cursor_sprite_ent_fnc);

    if (sketch_ents)
    {
        map_sketch_destroy_array(sketch_ents);
        sketch_ents = NULL;
    }
    sketch_ents = array_create(ENTITY *, 1);

    int x = 0, y = 0, id = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            VECTOR pos;
            vec_set(&pos, vector((MAP_CELL_SIZE * x), -(MAP_CELL_SIZE * y), MAP_Z_POS));

            ENTITY *sprite_ent = ent_create(empty_sprite_pcx, &pos, map_sketch_sprite_ent_fnc);
            sprite_ent->parent = ent_create(empty_sprite_pcx, vector(pos.x, pos.y, pos.z + SKETCH_PARENT_Z_OFFSET), map_sketch_sprite_parent_ent_fnc);
            sprite_ent->OBJ_ID = id;
            sprite_ent->OBJ_POS_X = x;
            sprite_ent->OBJ_POS_Y = y;
            sprite_ent->OBJ_POS_Z = 0;
            sprite_ent->OBJ_TYPE = -1;
            sprite_ent->OBJ_ASSET = -1;
            array_add(ENTITY *, sketch_ents, sprite_ent);
            id++;
        }
    }
}

void map_sketch_destroy_array(array_t *array)
{
    if (!array)
    {
        return;
    }

    array_enumerate_begin(ENTITY *, array, v)
    {
        if (v)
        {
            if (v->parent)
            {
                safe_remove(v->parent);
            }
            safe_remove(v);
        }
    }
    array_enumerate_end(array);
    array_destroy(array);
}

void map_sketch_destroy()
{
    if (cursor_sprite_ent)
    {
        safe_remove(cursor_sprite_ent);
    }

    map_sketch_destroy_array(sketch_ents);
    sketch_ents = NULL;
}

void map_sketch_sprite_update_from_cell(Cell *cell)
{
    if (!cell)
    {
        return;
    }

    var cell_pan = cell->pan;

    int cell_id = cell->id;

    int cell_type = cell->type;
    int cell_asset = cell->asset;

    int cell_flag = cell->flag;
    int cell_event_type = cell->event_type;
    int cell_event_id = cell->event_id;
    int cell_temp_skill = cell->temp_skill;

    ENTITY *cell_ent = array_get_element_at(ENTITY *, sketch_ents, cell_id);
    if (!cell_ent)
    {
        return;
    }

    set(cell_ent, INVISIBLE);
    vec_set(&cell_ent->blue, SKETCH_SPRITE_DEF_COLOR);

    set(cell_ent->parent, INVISIBLE);
    vec_set(&cell_ent->parent->blue, SKETCH_SPRITE_DEF_COLOR);

    if (cell_type >= ASSET_TYPE_WALLS)
    {
        if (cell_ent->OBJ_TYPE != cell_type || cell_ent->OBJ_ASSET != cell_asset)
        {
            ent_morph(cell_ent, _chr(asset_get_filename(cell_type, cell_asset)));
            cell_ent->OBJ_TYPE = cell_type;
            cell_ent->OBJ_ASSET = cell_asset;
            cell_ent->OBJ_FLAG = cell_flag;
            cell_ent->OBJ_EVENT_TYPE = cell_event_type;
            cell_ent->OBJ_EVENT_ID = cell_event_id;
            cell_ent->OBJ_TEMP_SKILL = cell_temp_skill;
        }

        if (is_walls_visible == true && cell_type == ASSET_TYPE_WALLS)
        {
            reset(cell_ent, INVISIBLE);
        }
        else if (is_objects_visible == true && cell_type >= ASSET_TYPE_PROPS)
        {
            reset(cell_ent, INVISIBLE);
        }

        if (is_secret_wall(cell) == true)
        {
            if (!is(cell_ent, INVISIBLE))
            {
                reset(cell_ent->parent, INVISIBLE);
            }

            if (cell_ent->parent->OBJ_TRIGGERED != 1)
            {
                ent_morph(cell_ent->parent, secret_sprite_tga);
                cell_ent->parent->OBJ_TRIGGERED = 1;
            }
        }
        else if (is_rotatable(cell_type, cell_asset) == true)
        {
            if (is_door(cell_type, cell_asset) == true && cell_asset == PROPS_DOOR_LOCKED)
            {
                if (cell_event_type == 0) // blue
                {
                    vec_set(&cell_ent->blue, DOOR_LOCKED_BLUE);
                }
                else if (cell_event_type == 1) // red
                {
                    vec_set(&cell_ent->blue, DOOR_LOCKED_RED);
                }
                else if (cell_event_type == 2) // yellow
                {
                    vec_set(&cell_ent->blue, DOOR_LOCKED_YELLOW);
                }
            }

            cell_ent->parent->pan = cell_pan;

            if (!is(cell_ent, INVISIBLE))
            {
                reset(cell_ent->parent, INVISIBLE);
            }

            if (cell_ent->parent->OBJ_TRIGGERED != 2)
            {
                ent_morph(cell_ent->parent, rotation_sprite_tga);
                cell_ent->parent->OBJ_TRIGGERED = 2;
            }
        }
    }
    else
    {
        cell_ent->OBJ_TYPE = -1;
        cell_ent->OBJ_ASSET = -1;
    }
}

void map_sketch_refresh(Map *map)
{
    if (!map)
    {
        return;
    }

    if (!sketch_ents)
    {
        return;
    }

    if (cursor_sprite_ent)
    {
        reset(cursor_sprite_ent, INVISIBLE);
    }

    int x = 0, y = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            Cell *cell = &map->cell[x][y];
            map_sketch_sprite_update_from_cell(cell);
        }
    }
}

void map_sketch_show()
{
    if (cursor_sprite_ent)
    {
        reset(cursor_sprite_ent, INVISIBLE);
    }

    int x = 0, y = 0, id = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            ENTITY *sprite_ent = array_get_element_at(ENTITY *, sketch_ents, id);
            if (sprite_ent)
            {
                if (is_walls_visible == true && sprite_ent->OBJ_TYPE == ASSET_TYPE_WALLS)
                {
                    reset(sprite_ent, INVISIBLE);
                }
                else if (is_objects_visible == true && sprite_ent->OBJ_TYPE >= ASSET_TYPE_PROPS)
                {
                    reset(sprite_ent, INVISIBLE);
                }

                if (sprite_ent->parent)
                {
                    if (sprite_ent->OBJ_TYPE == ASSET_TYPE_WALLS && sprite_ent->OBJ_ASSET != TOTAL_WALL_TEXTURES - 1 && sprite_ent->OBJ_FLAG == 1)
                    {
                        reset(sprite_ent->parent, INVISIBLE);
                    }
                    else if (is_rotatable(sprite_ent->OBJ_TYPE, sprite_ent->OBJ_ASSET) == true)
                    {
                        reset(sprite_ent->parent, INVISIBLE);
                    }
                }
            }
            id++;
        }
    }
}

void map_sketch_hide()
{
    if (cursor_sprite_ent)
    {
        set(cursor_sprite_ent, INVISIBLE);
    }

    int x = 0, y = 0, id = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            ENTITY *sprite_ent = array_get_element_at(ENTITY *, sketch_ents, id);
            if (sprite_ent)
            {
                if (sprite_ent->parent)
                {
                    set(sprite_ent->parent, INVISIBLE);
                }
                set(sprite_ent, INVISIBLE);
            }
            id++;
        }
    }
}

void map_sketch_update(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    if (is_allowed_to_draw() == false)
    {
        if (cursor_sprite_ent)
        {
            set(cursor_sprite_ent, INVISIBLE);
        }
        return;
    }

    if (cursor_sprite_ent)
    {
        if (is(cursor_sprite_ent, INVISIBLE))
        {
            reset(cursor_sprite_ent, INVISIBLE);
        }

        VECTOR cursor_pos;
        vec_set(&cursor_pos, &mouse_on_grid);
        vec_scale(&cursor_pos, MAP_CELL_SIZE);
        vec_set(&cursor_sprite_ent->x, &cursor_pos);

        cursor_sprite_ent->alpha -= cursor_fade_speed * time_step;
        cursor_sprite_ent->alpha = cycle(cursor_sprite_ent->alpha, cursor_alpha_min, cursor_alpha_max);
        cursor_sprite_ent->ambient = cursor_sprite_ent->alpha;
    }
}