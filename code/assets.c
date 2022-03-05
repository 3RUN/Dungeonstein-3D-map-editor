
BMAP *asset_get_bmap(int type, int index)
{
    if (type == ASSET_TYPE_WALLS)
    {
        Asset *asset = array_get_element_at(Asset *, wall_textures, index);
        return asset->bmap;
    }
    else if (type == ASSET_TYPE_PROPS)
    {
        Asset *asset = array_get_element_at(Asset *, props_textures, index);
        return asset->bmap;
    }
    else if (type == ASSET_TYPE_EVENTS)
    {
        Asset *asset = array_get_element_at(Asset *, event_textures, index);
        return asset->bmap;
    }
    else if (type == ASSET_TYPE_ITEMS)
    {
        Asset *asset = array_get_element_at(Asset *, item_textures, index);
        return asset->bmap;
    }
    else if (type == ASSET_TYPE_ENEMIES)
    {
        Asset *asset = array_get_element_at(Asset *, enemy_textures, index);
        return asset->bmap;
    }
    else if (type == ASSET_TYPE_BOSSES)
    {
        Asset *asset = array_get_element_at(Asset *, boss_textures, index);
        return asset->bmap;
    }
}

STRING *asset_get_desc(int type, int index)
{
    if (type == ASSET_TYPE_WALLS)
    {
        Asset *asset = array_get_element_at(Asset *, wall_textures, index);
        return _str(asset->desc);
    }
    else if (type == ASSET_TYPE_PROPS)
    {
        Asset *asset = array_get_element_at(Asset *, props_textures, index);
        return _str(asset->desc);
    }
    else if (type == ASSET_TYPE_EVENTS)
    {
        Asset *asset = array_get_element_at(Asset *, event_textures, index);
        return _str(asset->desc);
    }
    else if (type == ASSET_TYPE_ITEMS)
    {
        Asset *asset = array_get_element_at(Asset *, item_textures, index);
        return _str(asset->desc);
    }
    else if (type == ASSET_TYPE_ENEMIES)
    {
        Asset *asset = array_get_element_at(Asset *, enemy_textures, index);
        return _str(asset->desc);
    }
    else if (type == ASSET_TYPE_BOSSES)
    {
        Asset *asset = array_get_element_at(Asset *, boss_textures, index);
        return _str(asset->desc);
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
    strcpy(asset->desc, _chr(desc));
    BMAP *temp_bmap = bmap_create(bmap);
    bmap_preload(temp_bmap);
    asset->bmap = temp_bmap;

    array_add(Asset *, array, asset);
}

void assets_initialize()
{
    // walls
    {
        wall_textures = array_create(Asset *, 1);

        asset_add(wall_textures, "Grey brick 1", wall_00_pcx);
        asset_add(wall_textures, "Grey brick 2", wall_01_pcx);
        asset_add(wall_textures, "Grey brick 3", wall_02_pcx);
        asset_add(wall_textures, "Grey brick / flag", wall_03_pcx);
        asset_add(wall_textures, "Grey brick / Hitler", wall_04_pcx);
        asset_add(wall_textures, "Grey brick / eagle", wall_05_pcx);
        asset_add(wall_textures, "Grey brick / sign", wall_06_pcx);
        asset_add(wall_textures, "Dirty brick 1", wall_07_pcx);
        asset_add(wall_textures, "Dirty brick 2", wall_08_pcx);
        asset_add(wall_textures, "Cell", wall_09_pcx);
        asset_add(wall_textures, "Cell / skeleton", wall_10_pcx);
        asset_add(wall_textures, "Blue brick 1", wall_11_pcx);
        asset_add(wall_textures, "Blue brick 2", wall_12_pcx);
        asset_add(wall_textures, "Blue brick / sign", wall_13_pcx);
        asset_add(wall_textures, "Wood", wall_14_pcx);
        asset_add(wall_textures, "Wood / eagle", wall_15_pcx);
        asset_add(wall_textures, "Wood / Hitler", wall_16_pcx);
        asset_add(wall_textures, "Wood / iron cross", wall_17_pcx);
        asset_add(wall_textures, "Steal", wall_18_pcx);
        asset_add(wall_textures, "Steal / sign", wall_19_pcx);
        asset_add(wall_textures, "Red brick", wall_20_pcx);
        asset_add(wall_textures, "Red brick / swastika", wall_21_pcx);
        asset_add(wall_textures, "Red brick / flag", wall_22_pcx);
        asset_add(wall_textures, "Multicolor brick", wall_23_pcx);
        asset_add(wall_textures, "Stone wall 1", wall_24_pcx);
        asset_add(wall_textures, "Stone wall 2", wall_25_pcx);
        asset_add(wall_textures, "Stone wall / flag", wall_26_pcx);
        asset_add(wall_textures, "Stone wall / swastika", wall_27_pcx);
        asset_add(wall_textures, "Grey wall 1", wall_28_pcx);
        asset_add(wall_textures, "Grey wall 2", wall_29_pcx);
        asset_add(wall_textures, "Grey wall / Hitler", wall_30_pcx);
        asset_add(wall_textures, "Grey wall / map", wall_31_pcx);
        asset_add(wall_textures, "Grey wall / vent", wall_32_pcx);
        asset_add(wall_textures, "Blue wall", wall_33_pcx);
        asset_add(wall_textures, "Blue wall / swastika", wall_34_pcx);
        asset_add(wall_textures, "Blue wall / skull", wall_35_pcx);
        asset_add(wall_textures, "Brown stone 1", wall_36_pcx);
        asset_add(wall_textures, "Brown stone 2", wall_37_pcx);
        asset_add(wall_textures, "Brown marble 1", wall_38_pcx);
        asset_add(wall_textures, "Brown marble 2", wall_39_pcx);
        asset_add(wall_textures, "Brown marble / flag", wall_40_pcx);

        asset_add(wall_textures, "Elevator wall", wall_elevator_pcx);
        asset_add(wall_textures, "Elevator wall / switch", wall_elevator_switch_pcx);
    }

    // props
    {
        props_textures = array_create(Asset *, 1);

        asset_add(props_textures, "Knight", props_00_pcx);
        asset_add(props_textures, "Barrel / wooden", props_01_pcx);
        asset_add(props_textures, "Barrel / metal", props_02_pcx);
        asset_add(props_textures, "Table", props_03_pcx);
        asset_add(props_textures, "Table / chairs 1", props_04_pcx);
        asset_add(props_textures, "Table / chairs 2", props_05_pcx);
        asset_add(props_textures, "Lamp / floor", props_06_pcx);
        asset_add(props_textures, "Lamp / ceiling", props_07_pcx);
        asset_add(props_textures, "Column", props_08_pcx);
        asset_add(props_textures, "Basket", props_09_pcx);
        asset_add(props_textures, "Plant 1", props_10_pcx);
        asset_add(props_textures, "Plant 2", props_11_pcx);
        asset_add(props_textures, "Vase", props_12_pcx);
        asset_add(props_textures, "Vines", props_13_pcx);
        asset_add(props_textures, "Rack", props_14_pcx);
        asset_add(props_textures, "Flag", props_15_pcx);
        asset_add(props_textures, "Toilet", props_16_pcx);
        asset_add(props_textures, "Sink", props_17_pcx);
        asset_add(props_textures, "Bed", props_18_pcx);
        asset_add(props_textures, "Stove", props_19_pcx);
        asset_add(props_textures, "Pots 1", props_20_pcx);
        asset_add(props_textures, "Pots 2", props_21_pcx);
        asset_add(props_textures, "Water puddle", props_22_pcx);
        asset_add(props_textures, "Fence", props_23_pcx);
        asset_add(props_textures, "Fence / dirty", props_24_pcx);
        asset_add(props_textures, "Cage", props_25_pcx);
        asset_add(props_textures, "Cage / skeleton", props_26_pcx);
        asset_add(props_textures, "Hanging skeleton", props_27_pcx);
        asset_add(props_textures, "Skeleton", props_28_pcx);
        asset_add(props_textures, "Bones 1", props_29_pcx);
        asset_add(props_textures, "Bones 2", props_30_pcx);
        asset_add(props_textures, "Blood puddle", props_31_pcx);
        asset_add(props_textures, "Gibs 1", props_32_pcx);
        asset_add(props_textures, "Gibs 2", props_33_pcx);
        asset_add(props_textures, "Skulls on a spike", props_34_pcx);
        asset_add(props_textures, "Cow skull", props_35_pcx);
        asset_add(props_textures, "Cage / gore", props_36_pcx);
        asset_add(props_textures, "Cage / skulls", props_37_pcx);
        asset_add(props_textures, "Table / skull", props_38_pcx);
        asset_add(props_textures, "Ceiling moss 1", props_39_pcx);
        asset_add(props_textures, "Ceiling moss 2", props_40_pcx);
        asset_add(props_textures, "Grass 1", props_41_pcx);
        asset_add(props_textures, "Grass 2", props_42_pcx);
        asset_add(props_textures, "Grass 3", props_43_pcx);
        asset_add(props_textures, "Bush 1", props_44_pcx);
        asset_add(props_textures, "Bush 2", props_45_pcx);
        asset_add(props_textures, "Bush 3", props_46_pcx);
        asset_add(props_textures, "Tree", props_47_pcx);
        asset_add(props_textures, "Tree / dead", props_48_pcx);
        asset_add(props_textures, "Rocks 1", props_49_pcx);
        asset_add(props_textures, "Rocks 2", props_50_pcx);

        asset_add(props_textures, "Door", props_door_pcx);
        asset_add(props_textures, "Door / elevator", props_door_elevator_pcx);
        asset_add(props_textures, "Door / entrance (untouchable)", props_door_level_entrance_pcx);
        asset_add(props_textures, "Door / locked", props_door_locked_pcx);
        asset_add(props_textures, "Switch", props_switch_pcx);
    }

    // events
    {
        event_textures = array_create(Asset *, 1);

        asset_add(event_textures, "Player start position", event_player_pcx);
        asset_add(event_textures, "Trigger zone (id)", event_trigger_zone_pcx);
        asset_add(event_textures, "Spawn object", event_spawn_point_pcx);
        asset_add(event_textures, "NPC turn point", event_npc_turn_point_pcx);
    }

    // items
    {
        item_textures = array_create(Asset *, 1);

        asset_add(item_textures, "Key / blue", item_key_blue_pcx);
        asset_add(item_textures, "Key / red", item_key_red_pcx);
        asset_add(item_textures, "Key / yellow", item_key_yellow_pcx);
        asset_add(item_textures, "Medkit / small", item_medkit_small_pcx);
        asset_add(item_textures, "Medkit / big", item_medkit_big_pcx);
        asset_add(item_textures, "Treasure 1", item_treasure_00_pcx);
        asset_add(item_textures, "Treasure 2", item_treasure_01_pcx);
        asset_add(item_textures, "Treasure 3", item_treasure_02_pcx);
        asset_add(item_textures, "Treasure 4", item_treasure_03_pcx);
        asset_add(item_textures, "Ammo box", item_ammo_box_pcx);
        asset_add(item_textures, "Ammo / pistol", item_ammo_pistol_pcx);
        asset_add(item_textures, "Ammo / shotgun", item_ammo_shotgun_pcx);
        asset_add(item_textures, "Ammo / smg", item_ammo_smg_pcx);
        asset_add(item_textures, "Ammo / machinegun", item_ammo_machinegun_pcx);
        asset_add(item_textures, "Ammo / rocketlauncher", item_ammo_rocketlauncher_pcx);
        asset_add(item_textures, "Weapon / pistol", item_wpn_pistol_pcx);
        asset_add(item_textures, "Weapon / shotgun", item_wpn_shotgun_pcx);
        asset_add(item_textures, "Weapon / smg", item_wpn_smg_pcx);
        asset_add(item_textures, "Weapon / machinegun", item_wpn_machinegun_pcx);
        asset_add(item_textures, "Weapon / rocketlauncher", item_wpn_rocketlauncher_pcx);
    }

    // enemies
    {
        enemy_textures = array_create(Asset *, 1);

        asset_add(enemy_textures, "Mutant rat", enemy_rat_pcx);
        asset_add(enemy_textures, "Dog", enemy_dog_pcx);
        asset_add(enemy_textures, "Guard / pistol", enemy_guard_pistol_pcx);
        asset_add(enemy_textures, "Guard / shotgun", enemy_guard_shotgun_pcx);
        asset_add(enemy_textures, "Soldier / smg", enemy_soldier_smg_pcx);
        asset_add(enemy_textures, "Suicide bomber", enemy_suicider_pcx);
        asset_add(enemy_textures, "Zombie", enemy_zombie_pcx);
        asset_add(enemy_textures, "Support / machinegun", enemy_support_machinegun_pcx);
        asset_add(enemy_textures, "Support / rocketlauncher", enemy_support_rocketlauncher_pcx);
    }

    // bosses
    {
        boss_textures = array_create(Asset *, 1);

        asset_add(boss_textures, "Uber soldier", boss_uber_soldier_pcx);
        asset_add(boss_textures, "Uber officer", boss_uber_officer_pcx);
        asset_add(boss_textures, "Uber mutant", boss_uber_mutant_pcx);
        asset_add(boss_textures, "Mecha soldier", boss_mecha_soldier_pcx);
        asset_add(boss_textures, "Demon", boss_demon_pcx);
    }
}

void assets_destroy_array(array_t *array)
{
    if (!array)
    {
        return;
    }

    array_enumerate_begin(Asset *, array, v)
    {
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

void assets_destroy_all()
{
    assets_destroy_array(wall_textures);
    assets_destroy_array(props_textures);
    assets_destroy_array(event_textures);
    assets_destroy_array(item_textures);
    assets_destroy_array(enemy_textures);
    assets_destroy_array(boss_textures);
}