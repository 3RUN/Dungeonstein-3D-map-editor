#ifndef _ASSETS_H_
#define _ASSETS_H_

#define ASSET_BMAP_SIZE 64

#define MAX_WALL_TEXTURES 48
#define MAX_PROPS_TEXTURES 49
#define MAX_ITEM_TEXTURES 15
#define MAX_WEAPON_TEXTURES 5
#define MAX_ENEMY_TEXTURES 8
#define MAX_BOSS_TEXTURES 6

#define MAX_ASSET_TYPES 6
#define ASSET_TYPE_WALL 0
#define ASSET_TYPE_PROPS 1
#define ASSET_TYPE_ITEMS 2
#define ASSET_TYPE_WEAPON 3
#define ASSET_TYPE_ENEMIES 4
#define ASSET_TYPE_BOSSES 5

#define ASSET_DESC_LENGTH 128

#define PROPS_KNIGHT 0
#define PROPS_WOODEN_BARREL 1
#define PROPS_METAL_BARREL 2
#define PROPS_TABLE_EMPTY 3
#define PROPS_TABLE_CHAIRS_A 4
#define PROPS_TABLE_CHAIRS_B 5
#define PROPS_FLOOR_LAMP 6
#define PROPS_CEILING_LAMP 7
#define PROPS_COLUMN 8
#define PROPS_BASKET 9
#define PROPS_PLANT_A 10
#define PROPS_PLANT_B 11
#define PROPS_BLUE_VASE 12
#define PROPS_VINES 13
#define PROPS_RACK 14
#define PROPS_FLAG 15
#define PROPS_TOILET 16
#define PROPS_SINK 17
#define PROPS_BED 18
#define PROPS_STOVE 19
#define PROPS_POOL_OF_WATER 20
#define PROPS_FENCE_A 21
#define PROPS_FENCE_B 22
#define PROPS_EMPTY_CAGE 23
#define PROPS_CAGE_SKELETON 24
#define PROPS_HANGING_SKELETON 25
#define PROPS_LAYING_SKELETON 26
#define PROPS_PILE_OF_BONES_A 27
#define PROPS_PILE_OF_BONES_B 28
#define PROPS_POOL_OF_BLOOD 29
#define PROPS_BONES_WITH_BLOOD_A 30
#define PROPS_BONES_WITH_BLOOD_B 31
#define PROPS_BLOODY_STATUE_A 32
#define PROPS_BLOODY_STATUE_B 33
#define PROPS_BLOODY_CAGE 34
#define PROPS_BLOODY_CAGE_SKULLS 35
#define PROPS_BLOODY_TABLE_WITH_SKULL 36
#define PROPS_CEILING_MOSS_A 37
#define PROPS_CEILING_MOSS_B 38
#define PROPS_GRASS_A 39
#define PROPS_GRASS_B 40
#define PROPS_GRASS_C 41
#define PROPS_BUSH_A 42
#define PROPS_BUSH_B 43
#define PROPS_BUSH_C 44
#define PROPS_TREE 45
#define PROPS_DEAD_TREE 46
#define PROPS_ROCKS_A 47
#define PROPS_ROCKS_B 48

#define ITEMS_KEY_YELLOW 0
#define ITEMS_KEY_BLUE 1
#define ITEMS_KEY_RED 2
#define ITEMS_MEDKIT_SMALL 3
#define ITEMS_MEDKIT_BIG 4
#define ITEMS_TREASURE_A 5
#define ITEMS_TREASURE_B 6
#define ITEMS_TREASURE_C 7
#define ITEMS_TREASURE_D 8
#define ITEMS_AMMO_BOX 9
#define ITEMS_AMMO_PISTOL 10
#define ITEMS_AMMO_SMG 11
#define ITEMS_AMMO_SHOTGUN 12
#define ITEMS_AMMO_MACHINEGUN 13
#define ITEMS_AMMO_ROCKETLAUNCHER 14

#define WEAPON_PISTOL 0
#define WEAPON_SHOTGUN 1
#define WEAPON_SMG 2
#define WEAPON_MACHINEGUN 3
#define WEAPON_ROCKETLAUNCHER 4

#define ENEMY_DOG 0
#define ENEMY_GUARD_PISTOL 1
#define ENEMY_GUARD_SHOTGUN 2
#define ENEMY_SUICIDE_DOG 3
#define ENEMY_SUICIDE_INMATE 4
#define ENEMY_GUARD_SMG 5
#define ENEMY_SUPPORT 6
#define ENEMY_ZOMBIE 7

#define BOSS_1 0
#define BOSS_2 1
#define BOSS_3 2
#define BOSS_4 3
#define BOSS_5 4
#define BOSS_6 5

BMAP *wall_textures_tga = "walls.tga";
BMAP *props_textures_tga = "props.tga";
BMAP *item_textures_tga = "items.tga";
BMAP *weapon_textures_tga = "weapons.tga";
BMAP *enemy_textures_tga = "enemies.tga";
BMAP *boss_textures_tga = "bosses.tga";

typedef struct Asset
{
    BMAP *bmap;
    char desc[ASSET_DESC_LENGTH];
    int type;
    int index;
} Asset;

array_t *wall_textures;
array_t *props_textures;
array_t *item_textures;
array_t *weapon_textures;
array_t *enemy_textures;
array_t *boss_textures;

BMAP *asset_get_bmap(int type, int index);

STRING *asset_get_desc(int type, int index);

void asset_create_texture(array_t *array, BMAP *source, STRING *desc, int type, int u, int v);

void asset_create_object(array_t *array, BMAP *source, STRING *desc, int type, int index, int u, int v);

void assets_initialize();

void assets_destroy_array(array_t *array);

void assets_destroy();

#endif