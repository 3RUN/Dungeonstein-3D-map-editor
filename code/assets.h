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

// used for preview image in the asset list
#define ASSET_PREVIEW_IMAGE_WIDTH 64
#define ASSET_PREVIEW_IMAGE_HEIGHT 64
#define ASSET_IMAGE_FORMAT 8888

// asset types
#define MAX_ASSET_TYPES 6
#define ASSET_TYPE_WALLS 0
#define ASSET_TYPE_PROPS 1
#define ASSET_TYPE_EVENTS 2
#define ASSET_TYPE_ITEMS 3
#define ASSET_TYPE_ENEMIES 4
#define ASSET_TYPE_BOSSES 5

// total amount of textures per each type
#define TOTAL_WALL_TEXTURES 43
#define TOTAL_PROPS_TEXTURES 56
#define TOTAL_EVENT_TEXTURES 4
#define TOTAL_ITEM_TEXTURES 20
#define TOTAL_ENEMY_TEXTURES 9
#define TOTAL_BOSS_TEXTURES 5

// walls
#define WALLS_ELEVATOR_SWITCH 42

// props id
#define PROPS_KNIGHT 0
#define PROPS_BARREL_WOODEN 1
#define PROPS_BARREL_METAL 2
#define PROPS_TABLE 3
#define PROPS_TABLE_CHAIR_1 4
#define PROPS_TABLE_CHAIR_2 5
#define PROPS_LAMP_FLOOR 6
#define PROPS_LAMP_CEILING 7
#define PROPS_COLUMN 8
#define PROPS_BASKET 9
#define PROPS_PLANT_1 10
#define PROPS_PLANT_2 11
#define PROPS_VASE 12
#define PROPS_VINES 13
#define PROPS_RACK 14
#define PROPS_FLAG 15
#define PROPS_TOILET 16
#define PROPS_SINK 17
#define PROPS_BED 18
#define PROPS_STOVE 19
#define PROPS_POTS_1 20
#define PROPS_POTS_2 21
#define PROPS_WATER_PUDDLE 22
#define PROPS_FENCE 23
#define PROPS_FENCE_DIRTY 24
#define PROPS_CAGE 25
#define PROPS_CAGE_SKELETON 26
#define PROPS_HANGING_SKELETON 27
#define PROPS_SKELETON 28
#define PROPS_BONES_1 29
#define PROPS_BONES_2 30
#define PROPS_BLOOD_PUDDLE 31
#define PROPS_GIBS_1 32
#define PROPS_GIBS_2 33
#define PROPS_SKULL_ON_SPIKE 34
#define PROPS_COW_SKULL 35
#define PROPS_CAGE_GORE 36
#define PROPS_CAGE_SKULLS 37
#define PROPS_TABLE_SKULL 38
#define PROPS_CEILING_MOSS_1 39
#define PROPS_CEILING_MOSS_2 40
#define PROPS_GRASS_1 41
#define PROPS_GRASS_2 42
#define PROPS_GRASS_3 43
#define PROPS_BUSH_1 44
#define PROPS_BUSH_2 45
#define PROPS_BUSH_3 46
#define PROPS_TREE 47
#define PROPS_TREE_DEAD 48
#define PROPS_ROCKS_1 49
#define PROPS_ROCKS_2 50
#define PROPS_DOOR 51
#define PROPS_DOOR_ELEVATOR 52
#define PROPS_DOOR_ENTRANCE 53
#define PROPS_DOOR_LOCKED 54
#define PROPS_SWITCH 55

// event id
#define EVENT_PLAYER 0
#define EVENT_TRIGGER_ZONE 1
#define EVENT_SPAWN_OBJECT 2
#define EVENT_NPC_TURN_POINT 3

// item id
#define ITEM_KEY_BLUE 0
#define ITEM_KEY_RED 1
#define ITEM_KEY_RED 2
#define ITEM_MEDKIT_SMALL 3
#define ITEM_MEDKIT_BIG 4
#define ITEM_TREASURE_1 5
#define ITEM_TREASURE_2 6
#define ITEM_TREASURE_3 7
#define ITEM_TREASURE_4 8
#define ITEM_AMMO_BOX 9
#define ITEM_AMMO_PISTOL 10
#define ITEM_AMMO_SHOTGUN 11
#define ITEM_AMMO_SMG 12
#define ITEM_AMMO_MACHINEGUN 13
#define ITEM_AMMO_ROCKETLAUNCHER 14
#define ITEM_WPN_PISTOL 15
#define ITEM_WPN_SHOTGUN 16
#define ITEM_WPN_SMG 17
#define ITEM_WPN_MACHINEGUN 18
#define ITEM_WPN_ROCKETLAUNCHER 19

// enemy id
#define ENEMY_RAT 0
#define ENEMY_DOG 1
#define ENEMY_GUARD_PISTOL 2
#define ENEMY_GUARD_SHOTGUN 3
#define ENEMY_SOLDIER_SMG 4
#define ENEMY_SUICIDE_BOMBER 5
#define ENEMY_ZOMBIE 6
#define ENEMY_SUPPORT_MACHINEGUN 7
#define ENEMY_SUPPORT_ROCKETLAUNCHER 8

// boss id
#define BOSS_UBER_SOLDIER 0
#define BOSS_UBER_OFFICER 1
#define BOSS_UBER_MUTANT 2
#define BOSS_MECHA_SOLDIER 3
#define BOSS_DEMON 4

// map settings models and level (weather, fog, sky, etc)
STRING *map_settings_ceiling_mdl = "map_settings_ceiling.mdl";
STRING *map_settings_map_wmb = "map_settings_walls.wmb";
STRING *map_settings_floor_mdl = "map_settings_floor.mdl";

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
STRING *wall_10_pcx = "wall_10.pcx";
STRING *wall_11_pcx = "wall_11.pcx";
STRING *wall_12_pcx = "wall_12.pcx";
STRING *wall_13_pcx = "wall_13.pcx";
STRING *wall_14_pcx = "wall_14.pcx";
STRING *wall_15_pcx = "wall_15.pcx";
STRING *wall_16_pcx = "wall_16.pcx";
STRING *wall_17_pcx = "wall_17.pcx";
STRING *wall_18_pcx = "wall_18.pcx";
STRING *wall_19_pcx = "wall_19.pcx";
STRING *wall_20_pcx = "wall_20.pcx";
STRING *wall_21_pcx = "wall_21.pcx";
STRING *wall_22_pcx = "wall_22.pcx";
STRING *wall_23_pcx = "wall_23.pcx";
STRING *wall_24_pcx = "wall_24.pcx";
STRING *wall_25_pcx = "wall_25.pcx";
STRING *wall_26_pcx = "wall_26.pcx";
STRING *wall_27_pcx = "wall_27.pcx";
STRING *wall_28_pcx = "wall_28.pcx";
STRING *wall_29_pcx = "wall_29.pcx";
STRING *wall_30_pcx = "wall_30.pcx";
STRING *wall_31_pcx = "wall_31.pcx";
STRING *wall_32_pcx = "wall_32.pcx";
STRING *wall_33_pcx = "wall_33.pcx";
STRING *wall_34_pcx = "wall_34.pcx";
STRING *wall_35_pcx = "wall_35.pcx";
STRING *wall_36_pcx = "wall_36.pcx";
STRING *wall_37_pcx = "wall_37.pcx";
STRING *wall_38_pcx = "wall_38.pcx";
STRING *wall_39_pcx = "wall_39.pcx";
STRING *wall_40_pcx = "wall_40.pcx";
STRING *wall_elevator_pcx = "wall_elevator.pcx";
STRING *wall_elevator_switch_pcx = "wall_elevator_switch_off.pcx";
STRING *wall_elevator_switch_on_pcx = "wall_elevator_switch_on.pcx";
STRING *wall_doorway_pcx = "wall_doorway.pcx";

// props
STRING *props_00_pcx = "props_0.pcx";
STRING *props_01_pcx = "props_1.pcx";
STRING *props_02_pcx = "props_2.pcx";
STRING *props_03_pcx = "props_3.pcx";
STRING *props_04_pcx = "props_4.pcx";
STRING *props_05_pcx = "props_5.pcx";
STRING *props_06_pcx = "props_6.pcx";
STRING *props_07_pcx = "props_7.pcx";
STRING *props_08_pcx = "props_8.pcx";
STRING *props_09_pcx = "props_9.pcx";
STRING *props_10_pcx = "props_10.pcx";
STRING *props_11_pcx = "props_11.pcx";
STRING *props_12_pcx = "props_12.pcx";
STRING *props_13_pcx = "props_13.pcx";
STRING *props_14_pcx = "props_14.pcx";
STRING *props_15_pcx = "props_15.pcx";
STRING *props_16_pcx = "props_16.pcx";
STRING *props_17_pcx = "props_17.pcx";
STRING *props_18_pcx = "props_18.pcx";
STRING *props_19_pcx = "props_19.pcx";
STRING *props_20_pcx = "props_20.pcx";
STRING *props_21_pcx = "props_21.pcx";
STRING *props_22_pcx = "props_22.pcx";
STRING *props_23_pcx = "props_23.pcx";
STRING *props_24_pcx = "props_24.pcx";
STRING *props_25_pcx = "props_25.pcx";
STRING *props_26_pcx = "props_26.pcx";
STRING *props_27_pcx = "props_27.pcx";
STRING *props_28_pcx = "props_28.pcx";
STRING *props_29_pcx = "props_29.pcx";
STRING *props_30_pcx = "props_30.pcx";
STRING *props_31_pcx = "props_31.pcx";
STRING *props_32_pcx = "props_32.pcx";
STRING *props_33_pcx = "props_33.pcx";
STRING *props_34_pcx = "props_34.pcx";
STRING *props_35_pcx = "props_35.pcx";
STRING *props_36_pcx = "props_36.pcx";
STRING *props_37_pcx = "props_37.pcx";
STRING *props_38_pcx = "props_38.pcx";
STRING *props_39_pcx = "props_39.pcx";
STRING *props_40_pcx = "props_40.pcx";
STRING *props_41_pcx = "props_41.pcx";
STRING *props_42_pcx = "props_42.pcx";
STRING *props_43_pcx = "props_43.pcx";
STRING *props_44_pcx = "props_44.pcx";
STRING *props_45_pcx = "props_45.pcx";
STRING *props_46_pcx = "props_46.pcx";
STRING *props_47_pcx = "props_47.pcx";
STRING *props_48_pcx = "props_48.pcx";
STRING *props_49_pcx = "props_49.pcx";
STRING *props_50_pcx = "props_50.pcx";
STRING *props_door_pcx = "props_door.pcx";
STRING *props_door_elevator_pcx = "props_door_elevator.pcx";
STRING *props_door_level_entrance_pcx = "props_door_level_entrance.pcx";
STRING *props_door_locked_pcx = "props_door_locked.pcx";
STRING *props_switch_pcx = "props_switch_off.pcx";
STRING *props_switch_on_pcx = "props_switch_on.pcx";

// events
STRING *event_player_pcx = "event_player.pcx";
STRING *event_trigger_zone_pcx = "event_trigger_zone.pcx";
STRING *event_spawn_point_pcx = "event_spawn_point.pcx";
STRING *event_npc_turn_point_pcx = "event_npc_turn_point.pcx";

// items
STRING *item_key_blue_pcx = "item_key_blue.pcx";
STRING *item_key_red_pcx = "item_key_red.pcx";
STRING *item_key_yellow_pcx = "item_key_yellow.pcx";
STRING *item_medkit_small_pcx = "item_medkit_small.pcx";
STRING *item_medkit_big_pcx = "item_medkit_big.pcx";
STRING *item_treasure_00_pcx = "item_treasure_0.pcx";
STRING *item_treasure_01_pcx = "item_treasure_1.pcx";
STRING *item_treasure_02_pcx = "item_treasure_2.pcx";
STRING *item_treasure_03_pcx = "item_treasure_3.pcx";
STRING *item_ammo_box_pcx = "item_ammo_box.pcx";
STRING *item_ammo_pistol_pcx = "item_ammo_pistol.pcx";
STRING *item_ammo_shotgun_pcx = "item_ammo_shotgun.pcx";
STRING *item_ammo_smg_pcx = "item_ammo_smg.pcx";
STRING *item_ammo_machinegun_pcx = "item_ammo_machinegun.pcx";
STRING *item_ammo_rocketlauncher_pcx = "item_ammo_rocketlauncher.pcx";
STRING *item_wpn_pistol_pcx = "item_wpn_pistol.pcx";
STRING *item_wpn_shotgun_pcx = "item_wpn_shotgun.pcx";
STRING *item_wpn_smg_pcx = "item_wpn_smg.pcx";
STRING *item_wpn_machinegun_pcx = "item_wpn_machinegun.pcx";
STRING *item_wpn_rocketlauncher_pcx = "item_wpn_rocketlauncher.pcx";

// enemies
STRING *enemy_rat_pcx = "enemy_rat.pcx";
STRING *enemy_dog_pcx = "enemy_dog.pcx";
STRING *enemy_guard_pistol_pcx = "enemy_guard_pistol.pcx";
STRING *enemy_guard_shotgun_pcx = "enemy_guard_shotgun.pcx";
STRING *enemy_soldier_smg_pcx = "enemy_soldier_smg.pcx";
STRING *enemy_suicider_pcx = "enemy_suicider.pcx";
STRING *enemy_zombie_pcx = "enemy_zombie.pcx";
STRING *enemy_support_machinegun_pcx = "enemy_s_machinegun.pcx";
STRING *enemy_support_rocketlauncher_pcx = "enemy_s_rocketlauncher.pcx";

// bosses
STRING *boss_uber_soldier_pcx = "boss_uber_soldier.pcx";
STRING *boss_uber_officer_pcx = "boss_uber_officer.pcx";
STRING *boss_uber_mutant_pcx = "boss_uber_mutant.pcx";
STRING *boss_mecha_soldier_pcx = "boss_mecha_soldier.pcx";
STRING *boss_demon_pcx = "boss_demon.pcx";

array_t *wall_textures;
array_t *props_textures;
array_t *event_textures;
array_t *item_textures;
array_t *enemy_textures;
array_t *boss_textures;

BMAP *asset_get_bmap(int type, int index);

STRING *asset_get_desc(int type, int index);

STRING *asset_get_filename(int type, int index);

void asset_add(array_t *array, STRING *desc, STRING *bmap);

void assets_initialize();

void assets_destroy_array(array_t *array);

void assets_destroy_all();

#endif