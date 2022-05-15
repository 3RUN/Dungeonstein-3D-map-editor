#ifndef _ASSETS_HELPER_H_
#define _ASSETS_HELPER_H_

#define ASSET_MAX_CATEGORIES 7
#define ASSET_WALLS 0
#define ASSET_FLOORS 1
#define ASSET_EVENTS 2
#define ASSET_PROPS 3
#define ASSET_ITEMS 4
#define ASSET_ENEMIES 5
#define ASSET_BOSSES 6

#define FLOORS_TOXIC_WASTE 6
#define FLOORS_NONE 7

#define EVENTS_PLAYER 0
#define EVENTS_LEVEL_FINISH 1
#define EVENTS_TRIGGER_ZONE 2
#define EVENTS_OBJECT_SPAWN_POINT 3
#define EVENTS_SECRET_WALL 4
#define EVENTS_TELEPORT_IN 5
#define EVENTS_TELEPORT_OUT 6

#define PROPS_LIGHT 0
#define PROPS_COLUMN 1
#define PROPS_BARREL 2
#define PROPS_TABLE 3
#define PROPS_VASE 4
#define PROPS_DOOR 5
#define PROPS_GATE 6
#define PROPS_CEILING_SUPPORT 7
#define PROPS_WINDOW_BLOCK 8
#define PROPS_WINDOW_BRICK_BLUE 9
#define PROPS_WINDOW_BRICK_RED 10
#define PROPS_WINDOW_BRICK_GREY 11
#define PROPS_WINDOW_DIRT 12
#define PROPS_WINDOW_METAL 13
#define PROPS_DECOR_ON_WALL 14
#define PROPS_SWITCH 15

#define ITEMS_KEY_BLUE 0
#define ITEMS_KEY_RED 1
#define ITEMS_KEY_YELLOW 2
#define ITEMS_HEALTH_BONUS 3
#define ITEMS_MEDKIT_SMALL 4
#define ITEMS_MEDKIT_BIG 5
#define ITEMS_AMMO_BULLETS_SMALL 6
#define ITEMS_AMMO_BULLETS_BIG 7
#define ITEMS_AMMO_SHELLS_SMALL 8
#define ITEMS_AMMO_SHELLS_BIG 9
#define ITEMS_AMMO_ROCKETS_SMALL 10
#define ITEMS_AMMO_ROCKETS_BIG 11
#define ITEMS_TREASURE 12
#define ITEMS_POWERUP_MAP 13
#define ITEMS_POWERUP_SUIT 14
#define ITEMS_POWERUP_CHICKEN 15
#define ITEMS_POWERUP_LANTERN 16
#define ITEMS_POWERUP_MUSHROOM 17
#define ITEMS_WEAPON_PISTOL 18
#define ITEMS_WEAPON_SHOTGUN 19
#define ITEMS_WEAPON_CHAINGUN 20
#define ITEMS_WEAPON_ROCKETLAUNCHER 21

#define ASSET_ENEMY_BAT 0
#define ASSET_ENEMY_BOXER 1
#define ASSET_ENEMY_BUM 2
#define ASSET_ENEMY_MAGE 3
#define ASSET_ENEMY_HUMAN_PISTOL 4
#define ASSET_ENEMY_HUMAN_SHOTGUN 5
#define ASSET_ENEMY_SKELETON 6
#define ASSET_ENEMY_SLIME_FIRE 7
#define ASSET_ENEMY_SLIME_ICE 8
#define ASSET_ENEMY_ZOMBIE 9

#define ASSET_BOSS_HUMAN_CHAINGUN 0
#define ASSET_BOSS_HUMAN_ROCKETLAUNCHER 1
#define ASSET_BOSS_SLIME_TOXIC 2
#define ASSET_BOSS_MEGAEYE 3

int is_rotatable(int type, int index);

int is_on_wall(int type, int index);

int is_toxic_waste(int type, int index);

int is_light(int type, int index);

int is_door(int type, int index);

int is_gate(int type, int index);

int is_ceiling_support(int type, int index);

int is_window(int type, int index);

int is_decor_on_wall(int type, int index);

int is_switch(int type, int index);

int is_player_start(int type, int index);

int is_level_finish(int type, int index);

int is_object_spawn_point(int type, int index);

int is_secret_wall(int type, int index);

int is_trigger_zone(int type, int index);

int is_teleport_in(int type, int index);

int is_teleport_out(int type, int index);

int is_a_key_blue(int type, int index);

int is_a_key_red(int type, int index);

int is_a_key_yellow(int type, int index);

int is_enemy(int type);

int is_boss(int type);

#include "assets_helper.c"
#endif