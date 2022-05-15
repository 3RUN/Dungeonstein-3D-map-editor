#ifndef _MAP_LOADER_H_
#define _MAP_LOADER_H_

// object - bbox
// object->parent - sprite
// marker - UI
// rotation - direction

#define MAX_FACES_PER_CELL 6
#define MESH_WALL_FACE_UP 0
#define MESH_WALL_FACE_RIGHT 1
#define MESH_WALL_FACE_BUTTOM 2
#define MESH_WALL_FACE_LEFT 3
#define MESH_CEILING_FACE 4
#define MESH_FLOOR_FACE 5

#define ROTATION_POS_Z 2

STRING *water_mdl = "water.mdl";

typedef struct Mesh
{
    VECTOR pos;
    ENTITY *face[MAX_FACES_PER_CELL]; // 0, 1, 2, 3 - walls; 4 - ceiling; 5 - floor;
    ENTITY *object;
    ENTITY *marker;
    ENTITY *rotation;
} Mesh;

Mesh mesh[MAP_WIDTH][MAP_HEIGHT];

void map_loader_initialize();

void bmap_fix_overlay(BMAP *bmap);

void ent_change_skin(ENTITY *ent, BMAP *bmap);

void ent_set_object_skills(ENTITY *ent, Object *object);

void map_face_fnc();

void map_water_fnc();

void map_marker_fnc();

void map_toggle_marker_visibility(int is_visible);

void map_toggle_bbox_visibility(int is_visible);

void map_remove_solid(Map *map, Cell *cell);

void map_create_solid(Map *map, Cell *cell);

void map_remove_object(Map *map, Cell *cell);

void map_rotate_object(Cell *cell);

void map_create_object(Map *map, Cell *cell);

void map_load(Map *map);

void map_destroy();

#include "map_loader.c"
#endif