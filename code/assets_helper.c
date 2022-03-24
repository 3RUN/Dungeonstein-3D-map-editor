
int can_become_secret_wall(int type, int asset)
{
    if (type != ASSET_TYPE_WALLS)
    {
        return false;
    }

    if (asset == WALLS_ELEVATOR_SWITCH)
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

    if (cell_type != ASSET_TYPE_WALLS || cell_asset == WALLS_ELEVATOR_SWITCH)
    {
        return false;
    }

    return cell_flag;
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

int is_door(int type, int asset)
{
    if (type != ASSET_TYPE_PROPS)
    {
        return false;
    }

    if (asset != PROPS_DOOR && asset != PROPS_DOOR_LOCKED)
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

    if (asset != PROPS_FENCE && asset != PROPS_FENCE_BROKEN)
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

    if (asset != ITEM_TREASURE_SMALL_0 && asset != ITEM_TREASURE_SMALL_1 && asset != ITEM_TREASURE_BIG_0 && asset != ITEM_TREASURE_BIG_1)
    {
        return false;
    }

    return true;
}

int is_ceiling_support(int type, int asset)
{
    if (type != ASSET_TYPE_PROPS)
    {
        return false;
    }

    if (asset != PROPS_CEILING_SUPPORT_0 && asset != PROPS_CEILING_SUPPORT_1 && asset != PROPS_CEILING_SUPPORT_2 && asset != PROPS_CEILING_SUPPORT_3)
    {
        return false;
    }

    return true;
}

int is_decal(int type, int asset)
{
    if (type != ASSET_TYPE_PROPS)
    {
        return false;
    }

    if (asset < PROPS_FLAG_0)
    {
        return false;
    }

    return true;
}

int is_trigger_zone(int type, int asset)
{
    if (type != ASSET_TYPE_EVENTS)
    {
        return false;
    }

    if (asset != EVENT_TRIGGER_ZONE)
    {
        return false;
    }

    return true;
}

int is_spawn_object(int type, int asset)
{
    if (type != ASSET_TYPE_EVENTS)
    {
        return false;
    }

    if (asset != EVENT_SPAWN_OBJECT)
    {
        return false;
    }

    return true;
}

int is_npc_turn_point(int type, int asset)
{
    if (type != ASSET_TYPE_EVENTS)
    {
        return false;
    }

    if (asset != EVENT_NPC_TURN_POINT)
    {
        return false;
    }

    return true;
}

int is_effect(int type, int asset)
{
    if (type != ASSET_TYPE_EFFECT)
    {
        return false;
    }

    return true;
}

int is_enemy(int type, int asset)
{
    if (type != ASSET_TYPE_ENEMIES)
    {
        return false;
    }

    return true;
}

int is_boss(int type, int asset)
{
    if (type != ASSET_TYPE_BOSSES)
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

int is_rotatable(int type, int asset)
{
    if (is_fence(type, asset) == true)
    {
        return true;
    }

    if (is_switch(type, asset) == true)
    {
        return true;
    }

    if (is_door(type, asset) == true)
    {
        return true;
    }

    if (is_ceiling_support(type, asset) == true)
    {
        return true;
    }

    if (is_decal(type, asset) == true)
    {
        return true;
    }

    if (is_player_start(type, asset) == true)
    {
        return true;
    }

    if (is_npc_turn_point(type, asset) == true)
    {
        return true;
    }

    if (is_enemy(type, asset) == true)
    {
        return true;
    }

    if (is_boss(type, asset) == true)
    {
        return true;
    }
}