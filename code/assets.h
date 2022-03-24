#ifndef _ASSETS_H_
#define _ASSETS_H_

#define ASSET_DESC_LENGTH 128
#define ASSET_FILENAME_LENGTH 128

typedef struct Asset
{
    char desc[ASSET_DESC_LENGTH];
    char filename[ASSET_FILENAME_LENGTH];
    BMAP *bmap;
} Asset;

// colors for locked doors
#define DOOR_LOCKED_BLUE vector(128, 0, 0)
#define DOOR_LOCKED_RED vector(0, 0, 128)
#define DOOR_LOCKED_YELLOW vector(0, 128, 128)

// used for preview image in the asset list
#define ASSET_PREVIEW_IMAGE_WIDTH 64
#define ASSET_PREVIEW_IMAGE_HEIGHT 64
#define ASSET_IMAGE_FORMAT 8888

// asset types
#define MAX_ASSET_TYPES 7
#define ASSET_TYPE_WALLS 0
#define ASSET_TYPE_PROPS 1
#define ASSET_TYPE_EVENTS 2
#define ASSET_TYPE_EFFECT 3
#define ASSET_TYPE_ITEMS 4
#define ASSET_TYPE_ENEMIES 5
#define ASSET_TYPE_BOSSES 6

// total amount of textures per each type
#define TOTAL_WALL_TEXTURES 12
#define TOTAL_PROPS_TEXTURES 32
#define TOTAL_EVENT_TEXTURES 4
#define TOTAL_EFFECT_TEXTURES 3
#define TOTAL_ITEM_TEXTURES 17
#define TOTAL_ENEMY_TEXTURES 10
#define TOTAL_BOSS_TEXTURES 4

// wall id
#define WALLS_ELEVATOR_SWITCH 11

// props id
#define PROPS_BARREL 0
#define PROPS_COLUMN 1
#define PROPS_DOOR 2
#define PROPS_DOOR_LOCKED 3
#define PROPS_SWITCH 4
#define PROPS_TABLE_0 5
#define PROPS_TABLE_1 6
#define PROPS_TABLE_2 7
#define PROPS_FENCE 8
#define PROPS_FENCE_BROKEN 9
#define PROPS_CEILING_LAMP 10
#define PROPS_BUSH_0 11
#define PROPS_BUSH_1 12
#define PROPS_GRAVESTONE_0 13
#define PROPS_GRAVESTONE_1 14
#define PROPS_ROCKS_0 15
#define PROPS_ROCKS_1 16
#define PROPS_CEILING_SUPPORT_0 17
#define PROPS_CEILING_SUPPORT_1 18
#define PROPS_CEILING_SUPPORT_2 19
#define PROPS_CEILING_SUPPORT_3 20
#define PROPS_VASE_0 21
#define PROPS_VASE_1 22
#define PROPS_FLAG_0 23
#define PROPS_FLAG_1 24
#define PROPS_PAINTING_0 25
#define PROPS_PAINTING_1 26
#define PROPS_PAINTING_2 27
#define PROPS_SHIELD_0 28
#define PROPS_SHIELD_1 29
#define PROPS_WINDOW_0 30
#define PROPS_WINDOW_1 31

// event id
#define EVENT_PLAYER 0
#define EVENT_TRIGGER_ZONE 1
#define EVENT_SPAWN_OBJECT 2
#define EVENT_NPC_TURN_POINT 3

// effect id
#define EFFECT_EXPLO_AIR 0
#define EFFECT_EXPLO_FLOOR 1
#define EFFECT_OBJECT_BREAK 2

// item id
#define ITEM_KEY_BLUE 0
#define ITEM_KEY_RED 1
#define ITEM_KEY_YELLOW 2
#define ITEM_MEDKIT_SMALL 3
#define ITEM_MEDKIT_BIG 4
#define ITEM_TREASURE_SMALL_0 5
#define ITEM_TREASURE_SMALL_1 6
#define ITEM_TREASURE_BIG_0 7
#define ITEM_TREASURE_BIG_1 8
#define ITEM_AMMO_PISTOL 9
#define ITEM_AMMO_SHOTGUN 10
#define ITEM_AMMO_CHAINGUN 11
#define ITEM_AMMO_ROCKETLAUNCHER 12
#define ITEM_WPN_PISTOL 13
#define ITEM_WPN_SHOTGUN 14
#define ITEM_WPN_CHAINGUN 15
#define ITEM_WPN_ROCKETLAUNCHER 16

// enemy id
#define ENEMY_BAT 0
#define ENEMY_SLIME_FIRE 1
#define ENEMY_SLIME_ICE 2
#define ENEMY_BUM 3
#define ENEMY_MAGE 4
#define ENEMY_ZOMBIE 5
#define ENEMY_SKELETON 6
#define ENEMY_BOXER 7
#define ENEMY_PISTOL 8
#define ENEMY_SHOTGUN 9

// boss id
#define BOSS_CHAINGUN 0
#define BOSS_ROCKETLAUNCHER 1
#define BOSS_ACID_SLIME 2
#define BOSS_EYE 3

// walls
STRING *wall_00_pcx = "wall_0.pcx";
STRING *wall_01_pcx = "wall_1.pcx";
STRING *wall_02_pcx = "wall_2.pcx";
STRING *wall_03_pcx = "wall_3.pcx";
STRING *wall_04_pcx = "wall_4.pcx";
STRING *wall_05_pcx = "wall_5.pcx";
STRING *wall_06_pcx = "wall_6.pcx";
STRING *wall_07_pcx = "wall_7.pcx";
STRING *wall_08_pcx = "wall_8.pcx";
STRING *wall_09_pcx = "wall_9.pcx";
STRING *wall_elevator_pcx = "wall_elevator.pcx";
STRING *wall_elevator_switch_pcx = "wall_elevator_switch_off.pcx";
STRING *wall_doorway_pcx = "wall_doorway.pcx";

// props
STRING *props_barrel_pcx = "props_barrel.pcx";
STRING *props_column_pcx = "props_column.pcx";
STRING *props_door_pcx = "props_door.pcx";
STRING *props_door_locked_pcx = "props_door_locked.pcx";
STRING *props_switch_pcx = "props_switch_off.pcx";
STRING *props_table_0_pcx = "props_table_0.pcx";
STRING *props_table_1_pcx = "props_table_1.pcx";
STRING *props_table_2_pcx = "props_table_2.pcx";
STRING *props_fence_pcx = "props_fence.pcx";
STRING *props_fence_broken_pcx = "props_fence_broken.pcx";
STRING *props_lamp_pcx = "props_lamp.pcx";
STRING *props_flag_0_pcx = "props_flag_0.pcx";
STRING *props_flag_1_pcx = "props_flag_1.pcx";
STRING *props_grass_0_pcx = "props_grass_0.pcx";
STRING *props_grass_1_pcx = "props_grass_1.pcx";
STRING *props_gravestone_0_pcx = "props_gravestone_0.pcx";
STRING *props_gravestone_1_pcx = "props_gravestone_1.pcx";
STRING *props_painting_0_pcx = "props_painting_0.pcx";
STRING *props_painting_1_pcx = "props_painting_1.pcx";
STRING *props_painting_2_pcx = "props_painting_2.pcx";
STRING *props_window_0_pcx = "props_window_0.pcx";
STRING *props_window_1_pcx = "props_window_1.pcx";
STRING *props_rock_0_pcx = "props_rock_0.pcx";
STRING *props_rock_1_pcx = "props_rock_1.pcx";
STRING *props_shield_0_pcx = "props_shield_0.pcx";
STRING *props_shield_1_pcx = "props_shield_1.pcx";
STRING *props_support_0_pcx = "props_support_0.pcx";
STRING *props_support_1_pcx = "props_support_1.pcx";
STRING *props_support_2_pcx = "props_support_2.pcx";
STRING *props_support_3_pcx = "props_support_3.pcx";
STRING *props_vase_0_pcx = "props_vase_0.pcx";
STRING *props_vase_1_pcx = "props_vase_1.pcx";

// events
STRING *event_player_pcx = "event_player.pcx";
STRING *event_trigger_zone_pcx = "event_trigger_zone.pcx";
STRING *event_spawn_point_pcx = "event_spawn_point.pcx";
STRING *event_npc_turn_point_pcx = "event_npc_turn_point.pcx";

// effects
STRING *effect_explo_air_pcx = "effect_explo_air.pcx";
STRING *effect_explo_floor_pcx = "effect_explo_floor.pcx";
STRING *effect_object_break_pcx = "effect_object_break.pcx";

// items
STRING *item_key_blue_pcx = "item_key_blue.pcx";
STRING *item_key_red_pcx = "item_key_red.pcx";
STRING *item_key_yellow_pcx = "item_key_yellow.pcx";
STRING *item_medkit_small_pcx = "item_medkit_small.pcx";
STRING *item_medkit_big_pcx = "item_medkit_big.pcx";
STRING *item_treasure_small_0_pcx = "item_treasure_small_0.pcx";
STRING *item_treasure_small_1_pcx = "item_treasure_small_1.pcx";
STRING *item_treasure_big_0_pcx = "item_treasure_big_0.pcx";
STRING *item_treasure_big_1_pcx = "item_treasure_big_1.pcx";
STRING *item_ammo_pistol_pcx = "item_ammo_pistol.pcx";
STRING *item_ammo_shells_pcx = "item_ammo_shells.pcx";
STRING *item_ammo_chaingun_pcx = "item_ammo_chaingun.pcx";
STRING *item_ammo_rockets_pcx = "item_ammo_rockets.pcx";
STRING *item_wpn_pistol_pcx = "item_wpn_pistol.pcx";
STRING *item_wpn_shotgun_pcx = "item_wpn_shotgun.pcx";
STRING *item_wpn_chaingun_pcx = "item_wpn_chaingun.pcx";
STRING *item_wpn_rocketlauncher_pcx = "item_wpn_rocketlauncher.pcx";

// enemies
STRING *enemy_bat_pcx = "enemy_bat.pcx";
STRING *enemy_slime_fire_pcx = "enemy_slime_fire.pcx";
STRING *enemy_slime_ice_pcx = "enemy_slime_ice.pcx";
STRING *enemy_boxer_pcx = "enemy_boxer.pcx";
STRING *enemy_bum_pcx = "enemy_bum.pcx";
STRING *enemy_mage_pcx = "enemy_mage.pcx";
STRING *enemy_zombie_pcx = "enemy_zombie.pcx";
STRING *enemy_skeleton_pcx = "enemy_skeleton.pcx";
STRING *enemy_pistol_pcx = "enemy_pistol.pcx";
STRING *enemy_shotgun_pcx = "enemy_shotgun.pcx";

// bosses
STRING *boss_machinegun_pcx = "boss_machinegun.pcx";
STRING *boss_rocketlauncher_pcx = "boss_rocketlauncher.pcx";
STRING *boss_acid_slime_pcx = "boss_acid_slime.pcx";
STRING *boss_eye_pcx = "boss_eye.pcx";

array_t *wall_textures;
array_t *props_textures;
array_t *event_textures;
array_t *effect_textures;
array_t *item_textures;
array_t *enemy_textures;
array_t *boss_textures;

BMAP *asset_get_bmap(int type, int asset);

char *asset_get_desc(int type, int asset);

char *asset_get_filename(int type, int asset);

void asset_add(array_t *array, STRING *desc, STRING *bmap);

void assets_initialize();

void assets_destroy_array(array_t *array);

void assets_destroy();

#include "assets.c"
#endif