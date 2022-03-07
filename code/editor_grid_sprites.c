
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
                    if (dir_ent)
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

void editor_grid_sprite_update_by_id(int id, var pan, int type, int asset)
{
    if (!grid_ents)
    {
        return;
    }

    ENTITY *cell_ent = array_get_element_at(ENTITY *, grid_ents, id);
    if (!cell_ent)
    {
        return;
    }

    set(cell_ent, INVISIBLE);

    cell_ent->OBJ_TYPE_INDEX = type;
    cell_ent->OBJ_ASSET_INDEX = asset;

    // if we need to, update the skin !
    // also, make visible if this cell is used
    if (type >= 0)
    {
        if (is_walls_visible == true && type == ASSET_TYPE_WALLS)
        {
            reset(cell_ent, INVISIBLE);
        }

        if (is_objects_visible == true && type >= ASSET_TYPE_PROPS)
        {
            reset(cell_ent, INVISIBLE);
        }

        ent_morph(cell_ent, _chr(asset_get_filename(type, asset)));
    }
    else
    {
        ent_morph(cell_ent, blank_sprite_pcx);
    }
}

void editor_grid_direction_sprite_update_by_id(int id, var pan, int type, int asset)
{
    if (!grid_dir)
    {
        return;
    }

    ENTITY *dir_ent = array_get_element_at(ENTITY *, grid_dir, id);
    if (!dir_ent)
    {
        return;
    }

    set(dir_ent, INVISIBLE);

    // if we need to, update the skin !
    // also, make visible if this tile is used
    if (type >= 0)
    {
        if (is_objects_visible == true && type >= ASSET_TYPE_PROPS)
        {
            if (is_cell_allowed_rotation(type, asset) == true)
            {
                dir_ent->pan = pan;
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
            Cell *c = &current_map->cell[x][y];
            var cell_pan = c->pan;
            int cell_id = c->id;
            int cell_type = c->type;
            int cell_asset = c->asset;
            editor_grid_sprite_update_by_id(cell_id, cell_pan, cell_type, cell_asset);
            editor_grid_direction_sprite_update_by_id(cell_id, cell_pan, cell_type, cell_asset);
        }
    }
}

void grid_sprite_ent_fnc()
{
    set(my, PASSABLE | INVISIBLE | NOFILTER | OVERLAY | UNLIT);
    
    my->ambient = 100;
    vec_fill(&my->blue, 255);
    vec_fill(&my->scale_x, 0.5 * GRID_SPRITE_SCALE_FACTOR); // scale down from 64x64 to 32x32 (tile_size)
    my->pan = CELL_DEF_PAN;                                 // default pan, and don't change this !
    my->tilt = 90;                                          // look upwards !
}

void grid_direction_ent_fnc()
{
    set(my, PASSABLE | INVISIBLE | NOFILTER | OVERLAY | UNLIT);

    my->ambient = 100;
    vec_fill(&my->blue, 255);
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

void editor_grid_sprites_reset()
{
    if (!grid_ents)
    {
        return;
    }

    int x = 0, y = 0, id = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            editor_grid_sprite_update_by_id(id, CELL_DEF_PAN, TYPE_NONE, ASSET_NONE);
            editor_grid_direction_sprite_update_by_id(id, CELL_DEF_PAN, TYPE_NONE, ASSET_NONE);
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