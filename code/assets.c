
BMAP *asset_get_bmap(int type, int index)
{
    switch (type)
    {
    case ASSET_TYPE_WALL:
        Asset *asset = array_get_element_at(Asset *, wall_textures, index);
        return asset->bmap;

    case ASSET_TYPE_PROPS:
        Asset *asset = array_get_element_at(Asset *, props_textures, index);
        return asset->bmap;

    case ASSET_TYPE_ITEMS:
        Asset *asset = array_get_element_at(Asset *, item_textures, index);
        return asset->bmap;

    case ASSET_TYPE_WEAPON:
        Asset *asset = array_get_element_at(Asset *, weapon_textures, index);
        return asset->bmap;

    case ASSET_TYPE_ENEMIES:
        Asset *asset = array_get_element_at(Asset *, enemy_textures, index);
        return asset->bmap;

    case ASSET_TYPE_BOSSES:
        Asset *asset = array_get_element_at(Asset *, boss_textures, index);
        return asset->bmap;
    }
}

char *asset_get_desc(int type, int index)
{
    switch (type)
    {
    case ASSET_TYPE_WALL:
        Asset *asset = array_get_element_at(Asset *, wall_textures, index);
        return asset->desc;

    case ASSET_TYPE_PROPS:
        Asset *asset = array_get_element_at(Asset *, props_textures, index);
        return asset->desc;

    case ASSET_TYPE_ITEMS:
        Asset *asset = array_get_element_at(Asset *, item_textures, index);
        return asset->desc;

    case ASSET_TYPE_WEAPON:
        Asset *asset = array_get_element_at(Asset *, weapon_textures, index);
        return asset->desc;

    case ASSET_TYPE_ENEMIES:
        Asset *asset = array_get_element_at(Asset *, enemy_textures, index);
        return asset->desc;

    case ASSET_TYPE_BOSSES:
        Asset *asset = array_get_element_at(Asset *, boss_textures, index);
        return asset->desc;
    }
}

void asset_create_texture(array_t *array, BMAP *source, STRING *desc, int type, int u, int v)
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

    asset->bmap = bmap_createblack(64, 64, 32);
    bmap_blitpart(asset->bmap, source, nullvector, nullvector, vector(u, v, 0), vector(64, 64, 0));
    strcpy(asset->desc, desc);
    asset->type = type;
    asset->index = array_get_count(array);

    array_add(Asset *, array, asset);
}

void asset_create_object(array_t *array, BMAP *source, STRING *desc, int type, int index, int u, int v)
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

    asset->bmap = bmap_createblack(64, 64, 32);
    bmap_blitpart(asset->bmap, source, nullvector, nullvector, vector(u, v, 0), vector(64, 64, 0));
    strcpy(asset->desc, desc);
    asset->type = type;
    asset->index = index;

    array_add(Asset *, array, asset);
}

void assets_initialize()
{
    wall_textures = array_create(Asset *, 1);
    props_textures = array_create(Asset *, 1);
    item_textures = array_create(Asset *, 1);
    weapon_textures = array_create(Asset *, 1);
    enemy_textures = array_create(Asset *, 1);
    boss_textures = array_create(Asset *, 1);

    // walls
    {
        asset_create_texture(wall_textures, wall_textures_tga, "Grey brick 1", ASSET_TYPE_WALL, 29, 29);
        asset_create_texture(wall_textures, wall_textures_tga, "Grey brick 2", ASSET_TYPE_WALL, 94, 29);
        asset_create_texture(wall_textures, wall_textures_tga, "Grey brick 3", ASSET_TYPE_WALL, 159, 29);
        asset_create_texture(wall_textures, wall_textures_tga, "Grey brick / flag", ASSET_TYPE_WALL, 224, 29);
        asset_create_texture(wall_textures, wall_textures_tga, "Grey brick / Hitler", ASSET_TYPE_WALL, 289, 29);
        asset_create_texture(wall_textures, wall_textures_tga, "Grey brick / eagle", ASSET_TYPE_WALL, 354, 29);
        asset_create_texture(wall_textures, wall_textures_tga, "Grey brick / sign", ASSET_TYPE_WALL, 419, 29);

        asset_create_texture(wall_textures, wall_textures_tga, "Dirty brick 1", ASSET_TYPE_WALL, 29, 94);
        asset_create_texture(wall_textures, wall_textures_tga, "Dirty brick 2", ASSET_TYPE_WALL, 94, 94);
        asset_create_texture(wall_textures, wall_textures_tga, "Cell", ASSET_TYPE_WALL, 159, 94);
        asset_create_texture(wall_textures, wall_textures_tga, "Cell / skeleton", ASSET_TYPE_WALL, 224, 94);
        asset_create_texture(wall_textures, wall_textures_tga, "Blue brick 1", ASSET_TYPE_WALL, 289, 94);
        asset_create_texture(wall_textures, wall_textures_tga, "Blue brick 2", ASSET_TYPE_WALL, 354, 94);
        asset_create_texture(wall_textures, wall_textures_tga, "Blue brick / sign", ASSET_TYPE_WALL, 419, 94);

        asset_create_texture(wall_textures, wall_textures_tga, "Wood", ASSET_TYPE_WALL, 29, 159);
        asset_create_texture(wall_textures, wall_textures_tga, "Wood / eagle", ASSET_TYPE_WALL, 94, 159);
        asset_create_texture(wall_textures, wall_textures_tga, "Wood / Hitler", ASSET_TYPE_WALL, 159, 159);
        asset_create_texture(wall_textures, wall_textures_tga, "Wood / iron cross", ASSET_TYPE_WALL, 224, 159);
        asset_create_texture(wall_textures, wall_textures_tga, "Steal", ASSET_TYPE_WALL, 289, 159);
        asset_create_texture(wall_textures, wall_textures_tga, "Steal / sign", ASSET_TYPE_WALL, 354, 159);
        asset_create_texture(wall_textures, wall_textures_tga, "Red brick", ASSET_TYPE_WALL, 419, 159);

        asset_create_texture(wall_textures, wall_textures_tga, "Red brick / swastika", ASSET_TYPE_WALL, 29, 224);
        asset_create_texture(wall_textures, wall_textures_tga, "Red brick / flag", ASSET_TYPE_WALL, 94, 224);
        asset_create_texture(wall_textures, wall_textures_tga, "Multicolor brick", ASSET_TYPE_WALL, 159, 224);
        asset_create_texture(wall_textures, wall_textures_tga, "Stone wall 1", ASSET_TYPE_WALL, 224, 224);
        asset_create_texture(wall_textures, wall_textures_tga, "Stone wall 2", ASSET_TYPE_WALL, 289, 224);
        asset_create_texture(wall_textures, wall_textures_tga, "Stone wall / flag", ASSET_TYPE_WALL, 354, 224);
        asset_create_texture(wall_textures, wall_textures_tga, "Stone wall / swastika", ASSET_TYPE_WALL, 419, 224);

        asset_create_texture(wall_textures, wall_textures_tga, "Grey wall 1", ASSET_TYPE_WALL, 29, 289);
        asset_create_texture(wall_textures, wall_textures_tga, "Grey wall 2", ASSET_TYPE_WALL, 94, 289);
        asset_create_texture(wall_textures, wall_textures_tga, "Grey wall / Hitler", ASSET_TYPE_WALL, 159, 289);
        asset_create_texture(wall_textures, wall_textures_tga, "Grey wall / map", ASSET_TYPE_WALL, 224, 289);
        asset_create_texture(wall_textures, wall_textures_tga, "Grey wall / vent", ASSET_TYPE_WALL, 289, 289);
        asset_create_texture(wall_textures, wall_textures_tga, "Blue wall", ASSET_TYPE_WALL, 354, 289);
        asset_create_texture(wall_textures, wall_textures_tga, "Blue wall / swastika", ASSET_TYPE_WALL, 419, 289);

        asset_create_texture(wall_textures, wall_textures_tga, "Blue wall / skull", ASSET_TYPE_WALL, 29, 354);
        asset_create_texture(wall_textures, wall_textures_tga, "Brown stone 1", ASSET_TYPE_WALL, 94, 354);
        asset_create_texture(wall_textures, wall_textures_tga, "Brown stone 2", ASSET_TYPE_WALL, 159, 354);
        asset_create_texture(wall_textures, wall_textures_tga, "Brown marble 1", ASSET_TYPE_WALL, 224, 354);
        asset_create_texture(wall_textures, wall_textures_tga, "Brown marble 2", ASSET_TYPE_WALL, 289, 354);
        asset_create_texture(wall_textures, wall_textures_tga, "Brown marble / flag", ASSET_TYPE_WALL, 354, 354);
        asset_create_texture(wall_textures, wall_textures_tga, "Door excavation (side of door)", ASSET_TYPE_WALL, 419, 354);

        asset_create_texture(wall_textures, wall_textures_tga, "Door", ASSET_TYPE_WALL, 29, 419);
        asset_create_texture(wall_textures, wall_textures_tga, "Door / locked", ASSET_TYPE_WALL, 94, 419);
        asset_create_texture(wall_textures, wall_textures_tga, "Entrance to level", ASSET_TYPE_WALL, 159, 419);
        asset_create_texture(wall_textures, wall_textures_tga, "Elevator door", ASSET_TYPE_WALL, 224, 419);
        asset_create_texture(wall_textures, wall_textures_tga, "Elevator wall", ASSET_TYPE_WALL, 289, 419);
        asset_create_texture(wall_textures, wall_textures_tga, "Elevator (off)", ASSET_TYPE_WALL, 354, 419);
        //asset_create_texture(wall_textures, wall_textures_tga, "Elevator (on)", ASSET_TYPE_WALL, 419, 419);
    }

    // props
    {
        asset_create_object(props_textures, props_textures_tga, "Knight", ASSET_TYPE_PROPS, PROPS_KNIGHT, 29, 29);
        asset_create_object(props_textures, props_textures_tga, "Wooden barrel", ASSET_TYPE_PROPS, PROPS_WOODEN_BARREL, 94, 29);
        asset_create_object(props_textures, props_textures_tga, "Metal barrel", ASSET_TYPE_PROPS, PROPS_METAL_BARREL, 159, 29);
        asset_create_object(props_textures, props_textures_tga, "Table / empty", ASSET_TYPE_PROPS, PROPS_TABLE_EMPTY, 224, 29);
        asset_create_object(props_textures, props_textures_tga, "Table / chairs 1", ASSET_TYPE_PROPS, PROPS_TABLE_CHAIRS_A, 289, 29);
        asset_create_object(props_textures, props_textures_tga, "Table / chairs 2", ASSET_TYPE_PROPS, PROPS_TABLE_CHAIRS_B, 354, 29);
        asset_create_object(props_textures, props_textures_tga, "Floor lamp", ASSET_TYPE_PROPS, PROPS_FLOOR_LAMP, 419, 29);

        asset_create_object(props_textures, props_textures_tga, "Ceiling lamp", ASSET_TYPE_PROPS, PROPS_CEILING_LAMP, 29, 94);
        asset_create_object(props_textures, props_textures_tga, "Column", ASSET_TYPE_PROPS, PROPS_COLUMN, 94, 94);
        asset_create_object(props_textures, props_textures_tga, "Basket", ASSET_TYPE_PROPS, PROPS_BASKET, 159, 94);
        asset_create_object(props_textures, props_textures_tga, "Plant 1", ASSET_TYPE_PROPS, PROPS_PLANT_A, 224, 94);
        asset_create_object(props_textures, props_textures_tga, "Plant 2", ASSET_TYPE_PROPS, PROPS_PLANT_B, 289, 94);
        asset_create_object(props_textures, props_textures_tga, "Blue vase", ASSET_TYPE_PROPS, PROPS_BLUE_VASE, 354, 94);
        asset_create_object(props_textures, props_textures_tga, "Vines", ASSET_TYPE_PROPS, PROPS_VINES, 419, 94);

        asset_create_object(props_textures, props_textures_tga, "Rack", ASSET_TYPE_PROPS, PROPS_RACK, 29, 159);
        asset_create_object(props_textures, props_textures_tga, "Flag", ASSET_TYPE_PROPS, PROPS_FLAG, 94, 159);
        asset_create_object(props_textures, props_textures_tga, "Toilet", ASSET_TYPE_PROPS, PROPS_TOILET, 159, 159);
        asset_create_object(props_textures, props_textures_tga, "Sink", ASSET_TYPE_PROPS, PROPS_SINK, 224, 159);
        asset_create_object(props_textures, props_textures_tga, "Bed", ASSET_TYPE_PROPS, PROPS_BED, 289, 159);
        asset_create_object(props_textures, props_textures_tga, "Stove", ASSET_TYPE_PROPS, PROPS_STOVE, 354, 159);
        asset_create_object(props_textures, props_textures_tga, "Pool of water", ASSET_TYPE_PROPS, PROPS_POOL_OF_WATER, 419, 159);

        asset_create_object(props_textures, props_textures_tga, "Fence 1", ASSET_TYPE_PROPS, PROPS_FENCE_A, 29, 224);
        asset_create_object(props_textures, props_textures_tga, "Fence 2", ASSET_TYPE_PROPS, PROPS_FENCE_B, 94, 224);
        asset_create_object(props_textures, props_textures_tga, "Cage / empty", ASSET_TYPE_PROPS, PROPS_EMPTY_CAGE, 159, 224);
        asset_create_object(props_textures, props_textures_tga, "Cage / skeleton", ASSET_TYPE_PROPS, PROPS_CAGE_SKELETON, 224, 224);
        asset_create_object(props_textures, props_textures_tga, "Hanging skeleton", ASSET_TYPE_PROPS, PROPS_HANGING_SKELETON, 289, 224);
        asset_create_object(props_textures, props_textures_tga, "Laying skeleton", ASSET_TYPE_PROPS, PROPS_LAYING_SKELETON, 354, 224);
        asset_create_object(props_textures, props_textures_tga, "Pile of bones 1", ASSET_TYPE_PROPS, PROPS_PILE_OF_BONES_A, 419, 224);

        asset_create_object(props_textures, props_textures_tga, "Pile of bones 2", ASSET_TYPE_PROPS, PROPS_PILE_OF_BONES_B, 29, 289);
        asset_create_object(props_textures, props_textures_tga, "Pool of blood", ASSET_TYPE_PROPS, PROPS_POOL_OF_BLOOD, 94, 289);
        asset_create_object(props_textures, props_textures_tga, "Bones with blood 1", ASSET_TYPE_PROPS, PROPS_BONES_WITH_BLOOD_A, 159, 289);
        asset_create_object(props_textures, props_textures_tga, "Bones with blood 2", ASSET_TYPE_PROPS, PROPS_BONES_WITH_BLOOD_B, 224, 289);
        asset_create_object(props_textures, props_textures_tga, "Bloody statue 1", ASSET_TYPE_PROPS, PROPS_BLOODY_STATUE_A, 289, 289);
        asset_create_object(props_textures, props_textures_tga, "Bloody statue 2", ASSET_TYPE_PROPS, PROPS_BLOODY_STATUE_B, 354, 289);
        asset_create_object(props_textures, props_textures_tga, "Bloody cage / empty", ASSET_TYPE_PROPS, PROPS_BLOODY_CAGE, 419, 289);

        asset_create_object(props_textures, props_textures_tga, "Bloody cage / skulls", ASSET_TYPE_PROPS, PROPS_BLOODY_CAGE_SKULLS, 29, 354);
        asset_create_object(props_textures, props_textures_tga, "Bloody table with skull", ASSET_TYPE_PROPS, PROPS_BLOODY_TABLE_WITH_SKULL, 94, 354);
        asset_create_object(props_textures, props_textures_tga, "Ceiling moss 1", ASSET_TYPE_PROPS, PROPS_CEILING_MOSS_A, 159, 354);
        asset_create_object(props_textures, props_textures_tga, "Ceiling moss 2", ASSET_TYPE_PROPS, PROPS_CEILING_MOSS_B, 224, 354);
        asset_create_object(props_textures, props_textures_tga, "Grass 1", ASSET_TYPE_PROPS, PROPS_GRASS_A, 289, 354);
        asset_create_object(props_textures, props_textures_tga, "Grass 2", ASSET_TYPE_PROPS, PROPS_GRASS_B, 354, 354);
        asset_create_object(props_textures, props_textures_tga, "Grass 3", ASSET_TYPE_PROPS, PROPS_GRASS_C, 419, 354);

        asset_create_object(props_textures, props_textures_tga, "Bush 1", ASSET_TYPE_PROPS, PROPS_BUSH_A, 29, 419);
        asset_create_object(props_textures, props_textures_tga, "Bush 2", ASSET_TYPE_PROPS, PROPS_BUSH_B, 94, 419);
        asset_create_object(props_textures, props_textures_tga, "Bush 3", ASSET_TYPE_PROPS, PROPS_BUSH_C, 159, 419);
        asset_create_object(props_textures, props_textures_tga, "Tree", ASSET_TYPE_PROPS, PROPS_TREE, 224, 419);
        asset_create_object(props_textures, props_textures_tga, "Tree / dead", ASSET_TYPE_PROPS, PROPS_DEAD_TREE, 289, 419);
        asset_create_object(props_textures, props_textures_tga, "Rocks 1", ASSET_TYPE_PROPS, PROPS_ROCKS_A, 354, 419);
        asset_create_object(props_textures, props_textures_tga, "Rocks 2", ASSET_TYPE_PROPS, PROPS_ROCKS_B, 419, 419);
    }

    // items
    {
        asset_create_object(item_textures, item_textures_tga, "Key / yellow", ASSET_TYPE_ITEMS, ITEMS_KEY_YELLOW, 29, 29);
        asset_create_object(item_textures, item_textures_tga, "Key / blue", ASSET_TYPE_ITEMS, ITEMS_KEY_BLUE, 94, 29);
        asset_create_object(item_textures, item_textures_tga, "Key / red", ASSET_TYPE_ITEMS, ITEMS_KEY_RED, 159, 29);
        asset_create_object(item_textures, item_textures_tga, "Medkit / small", ASSET_TYPE_ITEMS, ITEMS_MEDKIT_SMALL, 224, 29);
        asset_create_object(item_textures, item_textures_tga, "Medkit / big", ASSET_TYPE_ITEMS, ITEMS_MEDKIT_BIG, 289, 29);
        asset_create_object(item_textures, item_textures_tga, "Treasure 1", ASSET_TYPE_ITEMS, ITEMS_TREASURE_A, 354, 29);
        asset_create_object(item_textures, item_textures_tga, "Treasure 2", ASSET_TYPE_ITEMS, ITEMS_TREASURE_B, 419, 29);

        asset_create_object(item_textures, item_textures_tga, "Treasure 3", ASSET_TYPE_ITEMS, ITEMS_TREASURE_C, 29, 94);
        asset_create_object(item_textures, item_textures_tga, "Treasure 4", ASSET_TYPE_ITEMS, ITEMS_TREASURE_D, 94, 94);
        asset_create_object(item_textures, item_textures_tga, "Ammo box", ASSET_TYPE_ITEMS, ITEMS_AMMO_BOX, 159, 94);
        asset_create_object(item_textures, item_textures_tga, "Ammo / pistol", ASSET_TYPE_ITEMS, ITEMS_AMMO_PISTOL, 224, 94);
        asset_create_object(item_textures, item_textures_tga, "Ammo / smg", ASSET_TYPE_ITEMS, ITEMS_AMMO_SMG, 289, 94);
        asset_create_object(item_textures, item_textures_tga, "Ammo / shotgun", ASSET_TYPE_ITEMS, ITEMS_AMMO_SHOTGUN, 354, 94);
        asset_create_object(item_textures, item_textures_tga, "Ammo / machinegun", ASSET_TYPE_ITEMS, ITEMS_AMMO_MACHINEGUN, 419, 94);

        asset_create_object(item_textures, item_textures_tga, "Ammo / rocketlauncher", ASSET_TYPE_ITEMS, ITEMS_AMMO_ROCKETLAUNCHER, 29, 159);
    }

    // weapons
    {
        asset_create_object(weapon_textures, weapon_textures_tga, "Pistol", ASSET_TYPE_WEAPON, WEAPON_PISTOL, 31, 31);
        asset_create_object(weapon_textures, weapon_textures_tga, "Shotgun", ASSET_TYPE_WEAPON, WEAPON_SHOTGUN, 96, 31);
        asset_create_object(weapon_textures, weapon_textures_tga, "SMG", ASSET_TYPE_WEAPON, WEAPON_SMG, 161, 31);

        asset_create_object(weapon_textures, weapon_textures_tga, "Machinegun", ASSET_TYPE_WEAPON, WEAPON_MACHINEGUN, 31, 96);
        asset_create_object(weapon_textures, weapon_textures_tga, "Rocketlauncher", ASSET_TYPE_WEAPON, WEAPON_ROCKETLAUNCHER, 96, 96);
    }

    // enemies
    {
        asset_create_object(enemy_textures, enemy_textures_tga, "Dog", ASSET_TYPE_ENEMIES, ENEMY_DOG, 31, 31);
        asset_create_object(enemy_textures, enemy_textures_tga, "Guard / pistol", ASSET_TYPE_ENEMIES, ENEMY_GUARD_PISTOL, 96, 31);
        asset_create_object(enemy_textures, enemy_textures_tga, "Guard / shotgun", ASSET_TYPE_ENEMIES, ENEMY_GUARD_SHOTGUN, 161, 31);

        asset_create_object(enemy_textures, enemy_textures_tga, "Suicide / Dog", ASSET_TYPE_ENEMIES, ENEMY_SUICIDE_DOG, 31, 96);
        asset_create_object(enemy_textures, enemy_textures_tga, "Suicide / Inmate", ASSET_TYPE_ENEMIES, ENEMY_SUICIDE_INMATE, 96, 96);
        asset_create_object(enemy_textures, enemy_textures_tga, "Guard / SMG", ASSET_TYPE_ENEMIES, ENEMY_GUARD_SMG, 161, 96);

        asset_create_object(enemy_textures, enemy_textures_tga, "Support", ASSET_TYPE_ENEMIES, ENEMY_SUPPORT, 31, 161);
        asset_create_object(enemy_textures, enemy_textures_tga, "Zombie", ASSET_TYPE_ENEMIES, ENEMY_ZOMBIE, 96, 161);
    }

    // bosses
    {
        asset_create_object(boss_textures, boss_textures_tga, "Boss 1", ASSET_TYPE_BOSSES, BOSS_1, 31, 31);
        asset_create_object(boss_textures, boss_textures_tga, "Boss 2", ASSET_TYPE_BOSSES, BOSS_2, 96, 31);
        asset_create_object(boss_textures, boss_textures_tga, "Boss 3", ASSET_TYPE_BOSSES, BOSS_3, 161, 31);

        asset_create_object(boss_textures, boss_textures_tga, "Boss 4", ASSET_TYPE_BOSSES, BOSS_4, 31, 96);
        asset_create_object(boss_textures, boss_textures_tga, "Boss 5", ASSET_TYPE_BOSSES, BOSS_5, 96, 96);
        asset_create_object(boss_textures, boss_textures_tga, "Boss 6", ASSET_TYPE_BOSSES, BOSS_6, 161, 96);
    }
}

void assets_destroy_array(array_t *array)
{
    if (!array)
    {
        return;
    }

    Asset *temp_asset;
    array_enumerate_begin(Asset *, array, temp_asset)
    {
        if (temp_asset->bmap)
        {
            ptr_remove(temp_asset->bmap);
            temp_asset->bmap = NULL;
        }
        sys_free(temp_asset);
    }
    array_enumerate_end(array);
    array_destroy(array);
}

void assets_destroy()
{
    assets_destroy_array(wall_textures);
    assets_destroy_array(props_textures);
    assets_destroy_array(item_textures);
    assets_destroy_array(weapon_textures);
    assets_destroy_array(enemy_textures);
    assets_destroy_array(boss_textures);
}