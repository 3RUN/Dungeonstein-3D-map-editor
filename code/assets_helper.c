
int is_rotatable(int type, int index)
{
    if (is_player_start(type, index) || is_teleport_in(type, index) || is_teleport_out(type, index))
    {
        return true;
    }

    if (is_door(type, index) || is_gate(type, index) || is_ceiling_support(type, index))
    {
        return true;
    }

    if (is_on_wall(type, index))
    {
        return true;
    }

    return false;
}

int is_on_wall(int type, int index)
{
    if (!is_level_finish(type, index) && !is_decor_on_wall(type, index) && !is_switch(type, index) && !is_window(type, index))
    {
        return false;
    }

    return true;
}

int is_toxic_waste(int type, int index)
{
    if (type != ASSET_FLOORS)
    {
        return false;
    }

    if (index != FLOORS_TOXIC_WASTE)
    {
        return false;
    }

    return true;
}

int is_light(int type, int index)
{
    if (type != ASSET_PROPS)
    {
        return false;
    }

    if (index != PROPS_LIGHT)
    {
        return false;
    }

    return true;
}

int is_door(int type, int index)
{
    if (type != ASSET_PROPS)
    {
        return false;
    }

    if (index != PROPS_DOOR)
    {
        return false;
    }

    return true;
}

int is_gate(int type, int index)
{
    if (type != ASSET_PROPS)
    {
        return false;
    }

    if (index != PROPS_GATE)
    {
        return false;
    }

    return true;
}

int is_ceiling_support(int type, int index)
{
    if (type != ASSET_PROPS)
    {
        return false;
    }

    if (index != PROPS_CEILING_SUPPORT)
    {
        return false;
    }

    return true;
}

int is_window(int type, int index)
{
    if (type != ASSET_PROPS)
    {
        return false;
    }

    if (index < PROPS_WINDOW_BLOCK || index > PROPS_WINDOW_METAL)
    {
        return false;
    }

    return true;
}

int is_decor_on_wall(int type, int index)
{
    if (type != ASSET_PROPS)
    {
        return false;
    }

    if (index != PROPS_DECOR_ON_WALL)
    {
        return false;
    }

    return true;
}

int is_switch(int type, int index)
{
    if (type != ASSET_PROPS)
    {
        return false;
    }

    if (index != PROPS_SWITCH)
    {
        return false;
    }

    return true;
}

int is_player_start(int type, int index)
{
    if (type != ASSET_EVENTS)
    {
        return false;
    }

    if (index != EVENTS_PLAYER)
    {
        return false;
    }

    return true;
}

int is_level_finish(int type, int index)
{
    if (type != ASSET_EVENTS)
    {
        return false;
    }

    if (index != EVENTS_LEVEL_FINISH)
    {
        return false;
    }

    return true;
}

int is_object_spawn_point(int type, int index)
{
    if (type != ASSET_EVENTS)
    {
        return false;
    }

    if (index != EVENTS_OBJECT_SPAWN_POINT)
    {
        return false;
    }

    return true;
}

int is_secret_wall(int type, int index)
{
    if (type != ASSET_EVENTS)
    {
        return false;
    }

    if (index != EVENTS_SECRET_WALL)
    {
        return false;
    }

    return true;
}

int is_trigger_zone(int type, int index)
{
    if (type != ASSET_EVENTS)
    {
        return false;
    }

    if (index != EVENTS_TRIGGER_ZONE)
    {
        return false;
    }

    return true;
}

int is_teleport_in(int type, int index)
{
    if (type != ASSET_EVENTS)
    {
        return false;
    }

    if (index != EVENTS_TELEPORT_IN)
    {
        return false;
    }

    return true;
}

int is_teleport_out(int type, int index)
{
    if (type != ASSET_EVENTS)
    {
        return false;
    }

    if (index != EVENTS_TELEPORT_OUT)
    {
        return false;
    }

    return true;
}

int is_a_key_blue(int type, int index)
{
    if (type != ASSET_ITEMS)
    {
        return false;
    }

    if (index != ITEMS_KEY_BLUE)
    {
        return false;
    }

    return true;
}

int is_a_key_red(int type, int index)
{
    if (type != ASSET_ITEMS)
    {
        return false;
    }

    if (index != ITEMS_KEY_RED)
    {
        return false;
    }

    return true;
}

int is_a_key_yellow(int type, int index)
{
    if (type != ASSET_ITEMS)
    {
        return false;
    }

    if (index != ITEMS_KEY_YELLOW)
    {
        return false;
    }

    return true;
}

int is_enemy(int type)
{
    if (type != ASSET_ENEMIES)
    {
        return false;
    }

    return true;
}

int is_boss(int type)
{
    if (type != ASSET_BOSSES)
    {
        return false;
    }

    return true;
}