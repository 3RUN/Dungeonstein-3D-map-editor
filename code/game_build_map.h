#ifndef _GAME_BUILD_MAP_H_
#define _GAME_BUILD_MAP_H_

#define MAX_DIRECTION_STEP 4 // cardinal directions - top/right/bottom/left
#define TOP 0
#define RIGHT 1
#define BOTTOM 2
#define LEFT 3

#define OFFSET_FROM_WALL 0.01

VECTOR cardinal_dir[MAX_DIRECTION_STEP]; // top/right/bottom/left
var cardinal_rot[MAX_DIRECTION_STEP];    // top/right/bottom/left

MATERIAL *mtl_solid;
MATERIAL *mtl_two_sided;

var shader_level_ambient = 0.5;
var shader_angle_surface_darken = 0.9;

ENTITY *map_ceiling_ent = NULL;
ENTITY *map_floor_ent = NULL;

array_t *map_solid = NULL;
array_t *map_props = NULL;
array_t *map_events = NULL;
array_t *map_items = NULL;
array_t *map_enemies = NULL;
array_t *map_bosses = NULL;

void game_build_map_initialize();

void game_build_free_array(array_t *array);

void game_build_destroy_array(array_t *array);

void game_build_map_free();

void game_build_map_destroy();

int game_build_check_direction(Map *map, VECTOR *pos, VECTOR *dir);

int is_neighbour_is_door(Map *map, VECTOR *pos, VECTOR *dir);

int is_a_door(int type, int asset);

int is_a_fence(int type, int asset);

int is_npc(int type, int asset);

int is_a_switch(int type, int asset);

void attach_to_wall(ENTITY *ent);

void solid_ent_fnc();

void ceiling_floor_ent_fnc();

void dynamic_object_fnc();

void game_build_walls(Map *map, Cell *cell);

void game_build_dynamic_objects(Cell *cell);

void game_build_map(Episode *episode);

void game_build_weather_settings(Map *map);

void game_build_map_update(Episode *episode);

#endif