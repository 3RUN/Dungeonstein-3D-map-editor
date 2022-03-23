
BMAP *asset_get_bmap(int type, int asset)
{
    if (type == ASSET_TYPE_WALLS)
    {
        Asset *asset = array_get_element_at(Asset *, wall_textures, asset);
        return asset->bmap;
    }
    else if (type == ASSET_TYPE_PROPS)
    {
        Asset *asset = array_get_element_at(Asset *, props_textures, asset);
        return asset->bmap;
    }
    else if (type == ASSET_TYPE_EVENTS)
    {
        Asset *asset = array_get_element_at(Asset *, event_textures, asset);
        return asset->bmap;
    }
    else if (type == ASSET_TYPE_EFFECT)
    {
        Asset *asset = array_get_element_at(Asset *, effect_textures, asset);
        return asset->bmap;
    }
    else if (type == ASSET_TYPE_ITEMS)
    {
        Asset *asset = array_get_element_at(Asset *, item_textures, asset);
        return asset->bmap;
    }
    else if (type == ASSET_TYPE_ENEMIES)
    {
        Asset *asset = array_get_element_at(Asset *, enemy_textures, asset);
        return asset->bmap;
    }
    else if (type == ASSET_TYPE_BOSSES)
    {
        Asset *asset = array_get_element_at(Asset *, boss_textures, asset);
        return asset->bmap;
    }
}

char *asset_get_desc(int type, int asset)
{
    if (type == ASSET_TYPE_WALLS)
    {
        Asset *asset = array_get_element_at(Asset *, wall_textures, asset);
        return asset->desc;
    }
    else if (type == ASSET_TYPE_PROPS)
    {
        Asset *asset = array_get_element_at(Asset *, props_textures, asset);
        return asset->desc;
    }
    else if (type == ASSET_TYPE_EVENTS)
    {
        Asset *asset = array_get_element_at(Asset *, event_textures, asset);
        return asset->desc;
    }
    else if (type == ASSET_TYPE_EFFECT)
    {
        Asset *asset = array_get_element_at(Asset *, effect_textures, asset);
        return asset->desc;
    }
    else if (type == ASSET_TYPE_ITEMS)
    {
        Asset *asset = array_get_element_at(Asset *, item_textures, asset);
        return asset->desc;
    }
    else if (type == ASSET_TYPE_ENEMIES)
    {
        Asset *asset = array_get_element_at(Asset *, enemy_textures, asset);
        return asset->desc;
    }
    else if (type == ASSET_TYPE_BOSSES)
    {
        Asset *asset = array_get_element_at(Asset *, boss_textures, asset);
        return asset->desc;
    }
}

char *asset_get_filename(int type, int asset)
{
    if (type == ASSET_TYPE_WALLS)
    {
        Asset *asset = array_get_element_at(Asset *, wall_textures, asset);
        return asset->filename;
    }
    else if (type == ASSET_TYPE_PROPS)
    {
        Asset *asset = array_get_element_at(Asset *, props_textures, asset);
        return asset->filename;
    }
    else if (type == ASSET_TYPE_EVENTS)
    {
        Asset *asset = array_get_element_at(Asset *, event_textures, asset);
        return asset->filename;
    }
    else if (type == ASSET_TYPE_EFFECT)
    {
        Asset *asset = array_get_element_at(Asset *, effect_textures, asset);
        return asset->filename;
    }
    else if (type == ASSET_TYPE_ITEMS)
    {
        Asset *asset = array_get_element_at(Asset *, item_textures, asset);
        return asset->filename;
    }
    else if (type == ASSET_TYPE_ENEMIES)
    {
        Asset *asset = array_get_element_at(Asset *, enemy_textures, asset);
        return asset->filename;
    }
    else if (type == ASSET_TYPE_BOSSES)
    {
        Asset *asset = array_get_element_at(Asset *, boss_textures, asset);
        return asset->filename;
    }
}

void asset_add(array_t *array, STRING *desc, STRING *bmap)
{
    if (!array)
    {
        return;
    }

    Asset *asset = sys_malloc(sizeof(Asset));
    if (!asset)
    {
        return;
    }
    strcpy(asset->filename, _chr(bmap));
    strcpy(asset->desc, _chr(desc));
    BMAP *temp_bmap = bmap_create(bmap);
    bmap_preload(temp_bmap);
    asset->bmap = temp_bmap;

    array_add(Asset *, array, asset);
}

void assets_initialize()
{
    // walls
    wall_textures = array_create(Asset *, 1);
    asset_add(wall_textures, "Grey block 1", wall_00_pcx);
    asset_add(wall_textures, "Grey block 2", wall_01_pcx);
    asset_add(wall_textures, "Blue brick 1", wall_02_pcx);
    asset_add(wall_textures, "Blue brick 2", wall_03_pcx);
    asset_add(wall_textures, "Red brick 1", wall_04_pcx);
    asset_add(wall_textures, "Red brick 2", wall_05_pcx);
    asset_add(wall_textures, "Grey brick 1", wall_06_pcx);
    asset_add(wall_textures, "Grey brick 2", wall_07_pcx);
    asset_add(wall_textures, "Cave 1", wall_08_pcx);
    asset_add(wall_textures, "Cave 2", wall_09_pcx);
    asset_add(wall_textures, "Elevator wall", wall_elevator_pcx);
    asset_add(wall_textures, "Elevator switch", wall_elevator_switch_pcx);

    // props
    props_textures = array_create(Asset *, 1);
    asset_add(props_textures, "Explosive barrel", props_barrel_pcx);
    asset_add(props_textures, "Column", props_column_pcx);
    asset_add(props_textures, "Door", props_door_pcx);
    asset_add(props_textures, "Door locked", props_door_locked_pcx);
    asset_add(props_textures, "Switch (on wall)", props_switch_pcx);
    asset_add(props_textures, "Table 1", props_table_0_pcx);
    asset_add(props_textures, "Table 2", props_table_1_pcx);
    asset_add(props_textures, "Table 3", props_table_2_pcx);
    asset_add(props_textures, "Fence", props_fence_pcx);
    asset_add(props_textures, "Fence broken", props_fence_broken_pcx);
    asset_add(props_textures, "Ceiling lamp", props_lamp_pcx);
    asset_add(props_textures, "Bush 1", props_grass_0_pcx);
    asset_add(props_textures, "Bush 2", props_grass_1_pcx);
    asset_add(props_textures, "Gravestone 1", props_gravestone_0_pcx);
    asset_add(props_textures, "Gravestone 2", props_gravestone_1_pcx);
    asset_add(props_textures, "Rocks 1", props_rock_0_pcx);
    asset_add(props_textures, "Rocks 2", props_rock_1_pcx);
    asset_add(props_textures, "Ceiling support 1", props_support_0_pcx);
    asset_add(props_textures, "Ceiling support 2", props_support_1_pcx);
    asset_add(props_textures, "Ceiling support 3", props_support_2_pcx);
    asset_add(props_textures, "Ceiling support 4", props_support_3_pcx);
    asset_add(props_textures, "Vase 1", props_vase_0_pcx);
    asset_add(props_textures, "Vase 2", props_vase_1_pcx);
    asset_add(props_textures, "Flag 1 (on wall)", props_flag_0_pcx);
    asset_add(props_textures, "Flag 2 (on wall)", props_flag_1_pcx);
    asset_add(props_textures, "Painting 1 (on wall)", props_painting_0_pcx);
    asset_add(props_textures, "Painting 2 (on wall)", props_painting_1_pcx);
    asset_add(props_textures, "Shield 1 (on wall)", props_shield_0_pcx);
    asset_add(props_textures, "Shield 2 (on wall)", props_shield_1_pcx);

    // events
    event_textures = array_create(Asset *, 1);
    asset_add(event_textures, "Player start position", event_player_pcx);
    asset_add(event_textures, "Trigger zone (id)", event_trigger_zone_pcx);
    asset_add(event_textures, "Spawn object", event_spawn_point_pcx);
    asset_add(event_textures, "NPC turn point", event_npc_turn_point_pcx);

    // effects
    effect_textures = array_create(Asset *, 1);
    asset_add(effect_textures, "Explosion in air", effect_explo_air_pcx);
    asset_add(effect_textures, "Explosion on floor", effect_explo_floor_pcx);
    asset_add(effect_textures, "Object break", effect_object_break_pcx);

    // items
    item_textures = array_create(Asset *, 1);
    asset_add(item_textures, "Key blue", item_key_blue_pcx);
    asset_add(item_textures, "Key red", item_key_red_pcx);
    asset_add(item_textures, "Key yellow", item_key_yellow_pcx);
    asset_add(item_textures, "Medkit small", item_medkit_small_pcx);
    asset_add(item_textures, "Medkit big", item_medkit_big_pcx);
    asset_add(item_textures, "Treasure small 1", item_treasure_small_0_pcx);
    asset_add(item_textures, "Treasure small 2", item_treasure_small_1_pcx);
    asset_add(item_textures, "Treasure big 1", item_treasure_big_0_pcx);
    asset_add(item_textures, "Treasure big 2", item_treasure_big_1_pcx);
    asset_add(item_textures, "Ammo pistol", item_ammo_pistol_pcx);
    asset_add(item_textures, "Ammo shotgun", item_ammo_shells_pcx);
    asset_add(item_textures, "Ammo chaingun", item_ammo_chaingun_pcx);
    asset_add(item_textures, "Ammo rocketlauncher", item_ammo_rockets_pcx);
    asset_add(item_textures, "Weapon pistol", item_wpn_pistol_pcx);
    asset_add(item_textures, "Weapon shotgun", item_wpn_shotgun_pcx);
    asset_add(item_textures, "Weapon chaingun", item_wpn_chaingun_pcx);
    asset_add(item_textures, "Weapon rocketlauncher", item_wpn_rocketlauncher_pcx);

    // enemies
    enemy_textures = array_create(Asset *, 1);
    asset_add(enemy_textures, "Bat", enemy_bat_pcx);
    asset_add(enemy_textures, "Blob fire", enemy_blob_fire_pcx);
    asset_add(enemy_textures, "Blob ice", enemy_blob_ice_pcx);
    asset_add(enemy_textures, "Bum", enemy_bum_pcx);
    asset_add(enemy_textures, "Mage", enemy_mage_pcx);
    asset_add(enemy_textures, "Zombie", enemy_zombie_pcx);
    asset_add(enemy_textures, "Skeleton", enemy_skeleton_pcx);
    asset_add(enemy_textures, "Boxer", enemy_boxer_pcx);
    asset_add(enemy_textures, "Human pistol", enemy_pistol_pcx);
    asset_add(enemy_textures, "Human shotgun", enemy_shotgun_pcx);

    // bosses
    boss_textures = array_create(Asset *, 1);
    asset_add(boss_textures, "Human chaingun", boss_machinegun_pcx);
    asset_add(boss_textures, "Human rocketlauncher", boss_rocketlauncher_pcx);
    asset_add(boss_textures, "Blob acid", boss_acid_blob_pcx);
    asset_add(boss_textures, "Eye", boss_eye_pcx);
}

void assets_destroy_array(array_t *array)
{
    if (!array)
    {
        return;
    }

    array_enumerate_begin(Asset *, array, v)
    {
        strcpy(v->filename, "");
        strcpy(v->desc, "");
        if (v->bmap)
        {
            safe_remove(v->bmap);
        }

        sys_free(v);
    }
    array_enumerate_end(array);
    array_destroy(array);
}

void assets_destroy()
{
    assets_destroy_array(wall_textures);
    wall_textures = NULL;

    assets_destroy_array(props_textures);
    props_textures = NULL;

    assets_destroy_array(event_textures);
    event_textures = NULL;

    assets_destroy_array(effect_textures);
    effect_textures = NULL;

    assets_destroy_array(item_textures);
    item_textures = NULL;

    assets_destroy_array(enemy_textures);
    enemy_textures = NULL;

    assets_destroy_array(boss_textures);
    boss_textures = NULL;
}