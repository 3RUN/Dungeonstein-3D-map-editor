
void grid_ent_fnc()
{
    set(my, PASSABLE | INVISIBLE | NOFILTER);
    ent_cloneskin(my);
}

void editor_update_grid_ent_by_id(int id, var pan, int type, int asset)
{
    if (!grid_ents)
    {
        return;
    }

    ENTITY *tile = array_get_element_at(ENTITY *, grid_ents, id);
    if (!tile)
    {
        return;
    }

    tile->pan = pan;
    tile->OBJ_TYPE_INDEX = type;
    tile->OBJ_ASSET_INDEX = asset;

    // if we need to, update the skin !
    // also, make visible if this tile is used
    if (type >= 0)
    {
        reset(tile, INVISIBLE);

        BMAP *old_skin = ent_getskin(tile, 1);
        ptr_remove(old_skin);

        old_skin = bmap_createblack(ASSET_BMAP_SIZE, ASSET_BMAP_SIZE, 32);
        bmap_blit(old_skin, asset_get_bmap(type, asset), NULL, NULL);

        ent_setskin(tile, old_skin, 1);
    }
    else
    {
        set(tile, INVISIBLE);

        BMAP *old_skin = ent_getskin(tile, 1);
        ptr_remove(old_skin);

        old_skin = bmap_createblack(ASSET_BMAP_SIZE, ASSET_BMAP_SIZE, 32);
        bmap_blit(old_skin, blank_texture_tga, NULL, NULL);

        ent_setskin(tile, old_skin, 1);
    }
}

void editor_update_grid_ents(Map *m)
{
    if (!m)
    {
        return;
    }

    if (!grid_ents)
    {
        return;
    }

    int x = 0, y = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            Cell *c = &m->cell[x][y];
            var cell_pan = c->pan;
            int cell_id = c->id;
            int cell_type = c->type;
            int cell_asset = c->asset;
            editor_update_grid_ent_by_id(cell_id, cell_pan, cell_type, cell_asset);
        }
    }
}

void editor_reset_grid_ents()
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
            editor_update_grid_ent_by_id(id, 0, TYPE_NONE, ASSET_NONE);
            id++;
        }
    }
}

void editor_create_grid_ents()
{
    if (grid_ents)
    {
        editor_destroy_grid_ents();
    }

    grid_ents = array_create(ENTITY *, 1);

    int x = 0, y = 0, id = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            VECTOR pos;
            vec_set(&pos, vector((MAP_CELL_SIZE * x), -(MAP_CELL_SIZE * y), 0));

            ENTITY *tile = ent_create(tile_mdl, &pos, grid_ent_fnc);
            tile->OBJ_ID = id;
            tile->OBJ_POS_X = x;
            tile->OBJ_POS_Y = y;
            tile->OBJ_POS_Z = 0;

            array_add(ENTITY *, grid_ents, tile);

            id++;
        }
    }
}

void editor_destroy_grid_ents()
{
    if (grid_ents)
    {
        array_enumerate_begin(ENTITY *, grid_ents, v)
        {
            if (v)
            {
                ptr_remove(v);
            }
        }
        array_enumerate_end(grid_ents);
        array_destroy(grid_ents);
        grid_ents = NULL;
    }
}