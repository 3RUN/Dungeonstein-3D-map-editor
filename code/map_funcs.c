
// event_frame
void object_event_frame()
{
    if (event_type == EVENT_FRAME)
    {
        my->skill44 = floatv(has_no_ceiling(&my->x));
    }
}

// events
void player_controller()
{
    set(my, PASSABLE | TRANSLUCENT | UNLIT | LIGHT);
    my->alpha = OBJECT_BBOX_ALPHA;
    my->flags2 |= UNTOUCHABLE;
    vec_set(&my->blue, COLOR_GREEN);
    my->material = mtl_marker;

    if (is_bbox_visible == false)
    {
        set(my, INVISIBLE);
    }
}

void level_finish()
{
    set(my, PASSABLE | TRANSLUCENT);
    my->alpha = OBJECT_BBOX_ALPHA;
    my->flags2 |= UNTOUCHABLE;
    my->material = mtl_marker;

    if (is_bbox_visible == false)
    {
        set(my, INVISIBLE);
    }
}

void trigger_zone()
{
    set(my, PASSABLE | TRANSLUCENT | UNLIT | LIGHT);
    my->alpha = OBJECT_BBOX_ALPHA;
    my->flags2 |= UNTOUCHABLE;
    vec_set(&my->blue, COLOR_GREEN);
    my->material = mtl_marker;

    if (is_bbox_visible == false)
    {
        set(my, INVISIBLE);
    }
}

void object_spawn_point()
{
    set(my, PASSABLE | TRANSLUCENT | UNLIT | LIGHT);
    my->alpha = OBJECT_BBOX_ALPHA;
    my->flags2 |= UNTOUCHABLE;
    vec_set(&my->blue, COLOR_WHITE);
    my->material = mtl_marker;

    if (is_bbox_visible == false)
    {
        set(my, INVISIBLE);
    }
}

void secret_wall()
{
    set(my, PASSABLE | TRANSLUCENT | OVERLAY | NOFILTER);
    my->alpha = SECRET_WALL_ALPHA;
    my->flags2 |= UNTOUCHABLE;
    ent_cloneskin(my);
    vec_set(&my->blue, COLOR_BLACK);
    my->material = mtl_solid;

    my->emask |= ENABLE_FRAME;
    my->event = object_event_frame;
}

void teleport_in()
{
    set(my, PASSABLE | OVERLAY | NOFILTER);
    my->flags2 |= UNTOUCHABLE;
    vec_set(&my->blue, COLOR_BLACK);
    my->material = mtl_solid;

    my->emask |= ENABLE_FRAME;
    my->event = object_event_frame;

    wait(1);

    my->parent = ent_create(teleport_in_mdl, &my->x, NULL);
    my->parent->pan = my->pan;
    set(my->parent, PASSABLE | OVERLAY | NOFILTER);
    my->parent->flags2 |= UNTOUCHABLE;
    my->parent->material = mtl_water;

    VECTOR brightness;
    vec_set(&brightness, COLOR_GREY);
    my->lightrange = TELEPORT_LIGHTRANGE;

    while (my)
    {
        my->blue = brightness.x * global_light_factor;
        my->green = brightness.y * global_light_factor;
        my->red = brightness.z * global_light_factor;

        if (my->parent)
        {
            my->parent->skill41 = floatv(teleport_amplitude);
            my->parent->skill42 = floatv(teleport_speed);
            my->parent->skill43 = floatv(teleport_modulation);

            my->parent->blue = brightness.x * global_light_factor;
            my->parent->green = brightness.y * global_light_factor;
            my->parent->red = brightness.z * global_light_factor;
        }
        wait(1);
    }
}

void teleport_out()
{
    set(my, PASSABLE | TRANSLUCENT | UNLIT | LIGHT);
    my->alpha = OBJECT_BBOX_ALPHA;
    my->flags2 |= UNTOUCHABLE;
    vec_set(&my->blue, COLOR_BLUE);
    ent_cloneskin(my);
    my->material = mtl_marker;

    if (is_bbox_visible == false)
    {
        set(my, INVISIBLE);
    }
}

// props
void props_sprite()
{
    set(my, PASSABLE | OVERLAY | NOFILTER);
    my->flags2 |= UNTOUCHABLE;
    vec_fill(&my->scale_x, 0.5);
    ent_cloneskin(my);
    vec_set(&my->blue, COLOR_BLACK);
    my->material = mtl_solid;

    my->emask |= ENABLE_FRAME;
    my->event = object_event_frame;
}

void props_bbox()
{
    set(my, PASSABLE | TRANSLUCENT);
    my->alpha = OBJECT_BBOX_ALPHA;
    my->flags2 |= UNTOUCHABLE;
    vec_set(&my->scale_x, vector(0.5, 0.5, 1));
    my->material = mtl_marker;

    if (is_bbox_visible == false)
    {
        set(my, INVISIBLE);
    }
}

void props_passable_bbox()
{
    set(my, PASSABLE | INVISIBLE);
    my->flags2 |= UNTOUCHABLE;
    vec_set(&my->scale_x, vector(0.5, 0.5, 1));
}

void props_light()
{
    props_passable_bbox();
}

void props_light_sprite()
{
    set(my, PASSABLE | OVERLAY | NOFILTER);
    my->flags2 |= UNTOUCHABLE;
    vec_fill(&my->scale_x, 0.5);
    ent_cloneskin(my);
    vec_set(&my->blue, COLOR_BLACK);
    my->material = mtl_solid;

    my->emask |= ENABLE_FRAME;
    my->event = object_event_frame;

    my->lightrange = LIGHT_LIGHTRANGE;
    vec_set(&my->blue, COLOR_WHITE);

    wait(1);

    if (my->OBJ_FLAG_0 == LIGHTSTYLE_NONE)
    {
        return;
    }

    var light_factor = 0;

    VECTOR brightness;
    vec_set(&brightness, &my->blue);

    while (my)
    {
        if (my->OBJ_FLAG_0 == LIGHTSTYLE_FLICKER)
        {
            light_factor = flicker_light_factor;
        }
        else if (my->OBJ_FLAG_0 == LIGHTSTYLE_PULSE)
        {
            light_factor = pulse_light_factor;
        }
        else if (my->OBJ_FLAG_0 == LIGHTSTYLE_STROBE)
        {
            light_factor = strobe_light_factor;
        }
        else if (my->OBJ_FLAG_0 == LIGHTSTYLE_CANDLE)
        {
            light_factor = candle_light_factor;
        }

        my->blue = brightness.x * light_factor;
        my->green = brightness.y * light_factor;
        my->red = brightness.z * light_factor;

        wait(1);
    }
}

void props_column()
{
    props_bbox();
}

void props_barrel()
{
    props_bbox();
}

void props_table()
{
    props_bbox();
}

void props_vase()
{
    props_bbox();
}

void props_door()
{
    set(my, PASSABLE | TRANSLUCENT);
    my->alpha = OBJECT_BBOX_ALPHA;
    my->flags2 |= UNTOUCHABLE;
    my->material = mtl_marker;

    if (is_bbox_visible == false)
    {
        set(my, INVISIBLE);
    }
}

void props_gate()
{
    set(my, PASSABLE | TRANSLUCENT);
    my->alpha = OBJECT_BBOX_ALPHA;
    my->flags2 |= UNTOUCHABLE;
    my->material = mtl_marker;

    if (is_bbox_visible == false)
    {
        set(my, INVISIBLE);
    }
}

void props_ceiling_support()
{
    props_passable_bbox();
}

void props_window()
{
    set(my, PASSABLE | TRANSLUCENT);
    my->alpha = OBJECT_BBOX_ALPHA;
    my->flags2 |= UNTOUCHABLE;
    my->material = mtl_marker;

    if (is_bbox_visible == false)
    {
        set(my, INVISIBLE);
    }
}

void props_decor_on_wall()
{
    props_passable_bbox();
}

void props_switch()
{
    set(my, PASSABLE | TRANSLUCENT);
    my->alpha = OBJECT_BBOX_ALPHA;
    my->flags2 |= UNTOUCHABLE;
    my->material = mtl_marker;

    if (is_bbox_visible == false)
    {
        set(my, INVISIBLE);
    }
}

// items
void item_key_blue()
{
    props_bbox();
}

void item_key_red()
{
    props_bbox();
}

void item_key_yellow()
{
    props_bbox();
}

void item_health_bonus()
{
    props_bbox();
}

void item_medkit_small()
{
    props_bbox();
}

void item_medkit_big()
{
    props_bbox();
}

void item_ammo_bullets_small()
{
    props_bbox();
}

void item_ammo_bullets_big()
{
    props_bbox();
}

void item_ammo_shells_small()
{
    props_bbox();
}

void item_ammo_shells_big()
{
    props_bbox();
}

void item_ammo_rockets_small()
{
    props_bbox();
}

void item_ammo_rockets_big()
{
    props_bbox();
}

void item_treasure()
{
    props_bbox();
}

void item_powerup_map()
{
    props_bbox();
}

void item_powerup_suit()
{
    props_bbox();
}

void item_powerup_chicken()
{
    props_bbox();
}

void item_powerup_lantern()
{
    props_bbox();
}

void item_powerup_mushroom()
{
    props_bbox();
}

void item_weapon_pistol()
{
    props_bbox();
}

void item_weapon_shotgun()
{
    props_bbox();
}

void item_weapon_chaingun()
{
    props_bbox();
}

void item_weapon_rocketlauncher()
{
    props_bbox();
}

// enemies
void enemy_bat()
{
    props_bbox();
}

void enemy_boxer()
{
    props_bbox();
}

void enemy_bum()
{
    props_bbox();
}

void enemy_mage()
{
    props_bbox();
}

void enemy_human_pistol()
{
    props_bbox();
}

void enemy_human_shotgun()
{
    props_bbox();
}

void enemy_skeleton()
{
    props_bbox();
}

void enemy_slime_fire()
{
    props_bbox();
}

void enemy_slime_ice()
{
    props_bbox();
}

void enemy_zombie()
{
    props_bbox();
}

// bosses
void boss_human_chaingun()
{
    props_bbox();
}

void boss_human_rocketlauncher()
{
    props_bbox();
}

void boss_slime_toxic()
{
    props_bbox();
}

void boss_megaeye()
{
    props_bbox();
}