
int can_become_secret_wall(int type, int asset)
{
    if (type != ASSET_TYPE_WALLS || asset == TOTAL_WALL_TEXTURES - 1)
    {
        return false;
    }

    return true;
}

int is_secret_wall(Cell *cell)
{
    if (!cell)
    {
        return false;
    }

    int cell_type = cell->type;
    int cell_asset = cell->asset;
    int cell_flag = cell->flag;

    if (cell_type != ASSET_TYPE_WALLS || cell_asset == TOTAL_WALL_TEXTURES - 1)
    {
        return false;
    }

    return cell_flag;
}

int is_door(int type, int asset)
{
    if (type != ASSET_TYPE_PROPS)
    {
        return false;
    }

    if (asset != PROPS_DOOR && asset != PROPS_DOOR_ELEVATOR && asset != PROPS_DOOR_ENTRANCE && asset != PROPS_DOOR_LOCKED)
    {
        return false;
    }

    return true;
}

int is_fence(int type, int asset)
{
    if (type != ASSET_TYPE_PROPS)
    {
        return false;
    }

    if (asset != PROPS_FENCE && asset != PROPS_FENCE_DIRTY)
    {
        return false;
    }

    return true;
}

int is_npc(int type, int asset)
{
    if (type != ASSET_TYPE_ENEMIES && type != ASSET_TYPE_BOSSES) // all enemies/bosses
    {
        return false;
    }

    return true;
}

int is_player_start(int type, int asset)
{
    if (type != ASSET_TYPE_EVENTS)
    {
        return false;
    }

    if (asset != EVENT_PLAYER)
    {
        return false;
    }

    return true;
}

int is_finish_elevator(int type, int asset)
{
    if (type != ASSET_TYPE_WALLS)
    {
        return false;
    }

    if (asset != WALLS_ELEVATOR_SWITCH)
    {
        return false;
    }

    return true;
}

int is_switch(int type, int asset)
{
    if (type != ASSET_TYPE_PROPS)
    {
        return false;
    }

    if (asset != PROPS_SWITCH)
    {
        return false;
    }

    return true;
}

int is_treasure(int type, int asset)
{
    if (type != ASSET_TYPE_ITEMS)
    {
        return false;
    }

    if (asset != ITEM_TREASURE_1 && asset != ITEM_TREASURE_2 && asset != ITEM_TREASURE_3 && asset != ITEM_TREASURE_4)
    {
        return false;
    }

    return true;
}

int is_rotatable(int type, int asset)
{
    if (is_npc(type, asset) == true) // enemies/bosses
    {
        return true;
    }

    if (is_door(type, asset) == true) // doors
    {
        return true;
    }

    if (is_fence(type, asset) == true) // dirty fences
    {
        return true;
    }

    if (type == ASSET_TYPE_PROPS && asset == PROPS_SWITCH) // switch
    {
        return true;
    }

    if (type == ASSET_TYPE_EVENTS && asset == EVENT_PLAYER) // start position (player spawn)
    {
        return true;
    }

    if (type == ASSET_TYPE_EVENTS && asset == EVENT_NPC_TURN_POINT) // turning point for npcs
    {
        return true;
    }

    return false;
}

int is_neighbour_is_door(Map *map, VECTOR *pos, VECTOR *dir)
{
    if (!map)
    {
        return false;
    }

    VECTOR endpos, tempdir;

    vec_set(&tempdir, dir);
    vec_set(&endpos, pos);
    vec_add(&endpos, &tempdir);

    if (is_pos_on_grid(&endpos) == false)
    {
        return false;
    }

    int x = endpos.x;
    int y = endpos.y;

    int type = map->cell[x][y].type;
    int asset = map->cell[x][y].asset;

    return is_door(type, asset);
}