
void editor_grid_sprites_show(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    Map *current_map = map_get_active(episode);
    if (!current_map)
    {
        return;
    }

    int x = 0, y = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            Cell *c = &current_map->cell[x][y];
            var cell_pan = c->pan;
            int cell_id = c->id;
            int cell_type = c->type;
            int cell_asset = c->asset;

            ENTITY *sprite_ent = array_get_element_at(ENTITY *, grid_ents, cell_id);
            ENTITY *dir_ent = array_get_element_at(ENTITY *, grid_dir, cell_id);
            if (sprite_ent)
            {
                if (is_walls_visible == true && cell_type == ASSET_TYPE_WALLS)
                {
                    reset(sprite_ent, INVISIBLE);
                }

                if (is_objects_visible == true && cell_type >= ASSET_TYPE_PROPS)
                {
                    reset(sprite_ent, INVISIBLE);
                    if (dir_ent && is_cell_allowed_rotation(cell_type, cell_asset) == true)
                    {
                        reset(dir_ent, INVISIBLE);
                    }
                }
            }
        }
    }
}

void editor_grid_sprites_hide()
{
    int x = 0, y = 0, id = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            ENTITY *sprite_ent = array_get_element_at(ENTITY *, grid_ents, id);
            if (sprite_ent)
            {
                if (sprite_ent->parent)
                {
                    set(sprite_ent->parent, INVISIBLE);
                }
                set(sprite_ent, INVISIBLE);
            }
            ENTITY *dir_ent = array_get_element_at(ENTITY *, grid_dir, id);
            if (dir_ent)
            {
                set(dir_ent, INVISIBLE);
            }
            id++;
        }
    }
}

void editor_grid_sprite_update_by_id(Cell *cell)
{
    if (!grid_ents)
    {
        return;
    }

    if (!cell)
    {
        return;
    }

    int cell_id = cell->id;
    var cell_pan = cell->pan;
    int cell_type = cell->type;
    int cell_asset = cell->asset;

    int cell_flag = cell->flag;
    int cell_event_type = cell->event_type;
    int cell_event_id = cell->event_id;
    int cell_temp_skill = cell->temp_skill;

    ENTITY *cell_ent = array_get_element_at(ENTITY *, grid_ents, cell_id);
    if (!cell_ent)
    {
        return;
    }

    set(cell_ent, INVISIBLE);
    vec_set(&cell_ent->blue, GRID_SPRITE_DEF_COLOR);

    if (cell_ent->parent)
    {
        set(cell_ent->parent, INVISIBLE);
        vec_set(&cell_ent->parent->blue, GRID_SPRITE_DEF_COLOR);
    }

    cell_ent->OBJ_TYPE_INDEX = cell_type;
    cell_ent->OBJ_ASSET_INDEX = cell_asset;

    // locked door ?
    // tint with it's required key color !
    if (cell_type == ASSET_TYPE_PROPS && cell_asset == PROPS_DOOR_LOCKED)
    {
        if (cell_event_type == 0) // blue
        {
            vec_set(&cell_ent->blue, LOCKED_BLUE_DOOR);
        }
        else if (cell_event_type == 1) // red
        {
            vec_set(&cell_ent->blue, LOCKED_RED_DOOR);
        }
        else if (cell_event_type == 2) // yellow
        {
            vec_set(&cell_ent->blue, LOCKED_YELLOW_DOOR);
        }
    }

    // if we need to, update the skin !
    // also, make visible if this cell is used
    if (cell_type >= 0)
    {
        if (is_walls_visible == true && cell_type == ASSET_TYPE_WALLS)
        {
            reset(cell_ent, INVISIBLE);

            // secret wall ?
            if (cell_flag == true)
            {
                if (cell_ent->parent)
                {
                    reset(cell_ent->parent, INVISIBLE);
                }
            }
        }

        if (is_objects_visible == true && cell_type >= ASSET_TYPE_PROPS)
        {
            reset(cell_ent, INVISIBLE);
        }

        ent_morph(cell_ent, _chr(asset_get_filename(cell_type, cell_asset)));
    }
    else
    {
        ent_morph(cell_ent, blank_sprite_pcx);
    }
}

void editor_grid_direction_sprite_update_by_id(Cell *cell)
{
    if (!grid_dir)
    {
        return;
    }

    if (!cell)
    {
        return;
    }

    int cell_id = cell->id;
    var cell_pan = cell->pan;
    int cell_type = cell->type;
    int cell_asset = cell->asset;

    int cell_flag = cell->flag;
    int cell_event_type = cell->event_type;
    int cell_event_id = cell->event_id;
    int cell_temp_skill = cell->temp_skill;

    ENTITY *dir_ent = array_get_element_at(ENTITY *, grid_dir, cell_id);
    if (!dir_ent)
    {
        return;
    }

    set(dir_ent, INVISIBLE);

    // if we need to, update the skin !
    // also, make visible if this tile is used
    if (cell_type >= 0)
    {
        if (is_objects_visible == true && cell_type >= ASSET_TYPE_PROPS)
        {
            if (is_cell_allowed_rotation(cell_type, cell_asset) == true)
            {
                dir_ent->pan = cell_pan;
                reset(dir_ent, INVISIBLE);
            }
        }
    }
}

void editor_grid_sprites_refresh(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    Map *current_map = map_get_active(episode);
    if (!current_map)
    {
        return;
    }

    if (!grid_ents || !grid_dir)
    {
        return;
    }

    int x = 0, y = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            Cell *cell = &current_map->cell[x][y];
            var cell_pan = cell->pan;
            int cell_id = cell->id;
            int cell_type = cell->type;
            int cell_asset = cell->asset;
            editor_grid_sprite_update_by_id(cell);
            editor_grid_direction_sprite_update_by_id(cell);
        }
    }
}

void grid_sprite_ent_fnc()
{
    set(my, PASSABLE | INVISIBLE | LIGHT | NOFILTER | UNLIT);
    vec_fill(&my->scale_x, 0.5 * GRID_SPRITE_SCALE_FACTOR); // scale down from 64x64 to 32x32 (tile_size)
    my->pan = CELL_DEF_PAN;                                 // default pan, and don't change this !
    my->tilt = 90;                                          // look upwards !
}

void grid_direction_ent_fnc()
{
    set(my, PASSABLE | INVISIBLE | NOFILTER | BRIGHT | UNLIT);
    vec_fill(&my->scale_x, 0.5 * GRID_SPRITE_SCALE_FACTOR); // scale down from 64x64 to 32x32 (tile_size)
    my->pan = CELL_DEF_PAN;                                 // default pan, and don't change this !
    my->tilt = 90;                                          // look upwards !
}

void editor_grid_sprites_create()
{
    if (grid_ents)
    {
        editor_grid_sprite_destroy_array(grid_ents);
        grid_ents = NULL;
    }
    grid_ents = array_create(ENTITY *, 1);

    if (grid_dir)
    {
        editor_grid_sprite_destroy_array(grid_dir);
        grid_dir = NULL;
    }
    grid_dir = array_create(ENTITY *, 1);

    int x = 0, y = 0, id = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            VECTOR pos;
            vec_set(&pos, vector((MAP_CELL_SIZE * x), -(MAP_CELL_SIZE * y), 0));

            ENTITY *sprite_ent = ent_create(blank_sprite_pcx, &pos, grid_sprite_ent_fnc);
            sprite_ent->parent = ent_create(secret_sprite_tga, vector(pos.x, pos.y, pos.z + GRID_PARENT_Z_OFFSET), grid_direction_ent_fnc);
            sprite_ent->OBJ_ID = id;
            sprite_ent->OBJ_POS_X = x;
            sprite_ent->OBJ_POS_Y = y;
            sprite_ent->OBJ_POS_Z = 0;
            array_add(ENTITY *, grid_ents, sprite_ent);

            ENTITY *dir_ent = ent_create(direction_tga, &pos, grid_direction_ent_fnc);
            dir_ent->z += GRID_DRAW_OFFSET;
            array_add(ENTITY *, grid_dir, dir_ent);

            id++;
        }
    }
}

void editor_grid_sprite_destroy_array(array_t *array)
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

void editor_grid_sprites_destroy()
{
    editor_grid_sprite_destroy_array(grid_ents);
    editor_grid_sprite_destroy_array(grid_dir);
}