#ifndef _MAP_LOADER_H_
#define _MAP_LOADER_H_

#define MAX_DIRECTION_STEP 4 // cardinal directions - top/right/bottom/left
#define TOP 0
#define RIGHT 1
#define BOTTOM 2
#define LEFT 3

ENTITY *floor_ent = NULL;
ENTITY *ceiling_ent = NULL;

array_t *map_walls = NULL;
array_t *map_props = NULL;
array_t *map_events = NULL;
array_t *map_items = NULL;
array_t *map_enemies = NULL;
array_t *map_bosses = NULL;

VECTOR cardinal_dir[MAX_DIRECTION_STEP]; // top/right/bottom/left
var cardinal_rot[MAX_DIRECTION_STEP];    // top/right/bottom/left

void map_floor_ent_fnc();

void map_ceiling_ent_fnc();

void map_solid_ent_fnc();

void map_loader_initialize(Episode *episode);

void map_loader_free_array(array_t *array);

void map_loader_destroy_array(array_t *array);

void map_loader_destroy();

void map_destroy(Map *map);

int is_neighbour_solid(Map *map, VECTOR *pos, VECTOR *dir);

void map_load(Map *map);

#endif