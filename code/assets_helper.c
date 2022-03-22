
var can_become_secret_wall(var type, var asset)
{
    if (type != ASSET_TYPE_WALLS || asset == TOTAL_WALL_TEXTURES - 1)
    {
        return false;
    }

    return true;
}

var is_secret_wall(Cell *cell)
{
    if (!cell)
    {
        return false;
    }

    var cell_type = cell->type;
    var cell_asset = cell->asset;
    var cell_flag = cell->flag;

    if (cell_type != ASSET_TYPE_WALLS || cell_asset == TOTAL_WALL_TEXTURES - 1)
    {
        return false;
    }

    return cell_flag;
}

var is_door(var type, var asset)
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

var is_fence(var type, var asset)
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

var is_npc(var type, var asset)
{
    if (type != ASSET_TYPE_ENEMIES && type != ASSET_TYPE_BOSSES) // all enemies/bosses
    {
        return false;
    }

    return true;
}

var is_player_start(var type, var asset)
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

var is_finish_elevator(var type, var asset)
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

var is_switch(var type, var asset)
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

var is_treasure(var type, var asset)
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

var is_rotatable(var type, var asset)
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

var is_neighbour_is_door(Map *map, VECTOR *pos, VECTOR *dir)
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

    var x = endpos.x;
    var y = endpos.y;

    var type = map->cell[x][y].type;
    var asset = map->cell[x][y].asset;

    return is_door(type, asset);
}