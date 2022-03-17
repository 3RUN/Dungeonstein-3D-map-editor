
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