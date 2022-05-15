#ifndef _OBJECT_PARAMS_H_
#define _OBJECT_PARAMS_H_

#define MAX_LIGHTSTYLES 5 // 0 - none, 1 - flicker, 2 - pulse, 3 - strobe, 4 - candle
#define LIGHTSTYLE_NONE 0
#define LIGHTSTYLE_FLICKER 1
#define LIGHTSTYLE_PULSE 2
#define LIGHTSTYLE_STROBE 3
#define LIGHTSTYLE_CANDLE 4

#define MAX_SPAWN_CATEGORIES 3 // 0 - item, 1 - enemy, 2 - boss

#define MAX_SPAWN_ITEMS 22
#define MAX_SPAWN_ENEMIES 10
#define MAX_SPAWN_BOSSES 4

#define MIN_ID_RANGE 0
#define MAX_ID_RANGE 999

STRING *lightstyle_list_str[MAX_LIGHTSTYLES];
STRING *used_lightstyle_str = "";

STRING *spawn_category_list_str[MAX_SPAWN_CATEGORIES];
STRING *used_spawn_category_str = "";

STRING *spawn_item_list_str[MAX_SPAWN_ITEMS];
STRING *used_spawn_item_str = "";

STRING *spawn_enemies_list_str[MAX_SPAWN_ENEMIES];
STRING *used_spawn_enemies_str = "";

STRING *spawn_bosses_list_str[MAX_SPAWN_BOSSES];
STRING *used_spawn_bosses_str = "";

void object_params_initialize();

void object_params_destroy();

void params_lights_refresh();

void params_spawn_point_refresh();

void object_params_reset(Object *object);

void params_id(Object *object);

void params_lights(Object *object);

void params_doors(Object *object);

void params_gate(Object *object);

void params_switch(Object *object);

void params_player_start(Object *object);

void params_object_spawn_point(Object *object);

void params_secret_wall(Object *object);

void params_npc(Object *objcet);

void object_params_gui(int type, int index);

#include "object_params.c"
#endif