#ifndef _MAP_LOADER_H_
#define _MAP_LOADER_H_

#define OBJECT_OFFSET_FROM_WALL 0.01

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
array_t *map_bboxes = NULL;

STRING *wall_mdl = "wall.mdl"; // used for secret walls, elevator switch, etc

VECTOR cardinal_dir[MAX_DIRECTION_STEP]; // top/right/bottom/left
var cardinal_rot[MAX_DIRECTION_STEP];    // top/right/bottom/left

var is_player_found = false;
var is_finish_found = false;

var props_count = 0;
var event_count = 0;
var items_count = 0;
var enemies_cout = 0;
var bosses_count = 0;
var secrets_count = 0;
var treasure_count = 0;

void map_floor_ent_fnc();

void map_ceiling_ent_fnc();

void map_solid_ent_fnc();

void map_fixed_rotation_ent_fnc();

void map_camera_facing_ent_fnc();

void map_secret_wall_ent_fnc();

void map_finish_wall_ent_fnc();

void map_info_bbox_ent_fnc();

void ceiling_update_from_map(Map *map);

void floor_update_from_map(Map *map);

void object_attach_to_wall(ENTITY *ent);

void object_change_skin_to(ENTITY *ent, STRING *bmap_filename, BMAP *bmap);

void object_update_skills(ENTITY *ent, var pan, var id, var type, var asset, var flag, var e_type, var e_id, var temp_skill);

void map_loader_initialize(Episode *episode);

void map_loader_free_array(array_t *array);

void map_loader_destroy_array(array_t *array);

void map_loader_destroy();

void map_destroy(Map *map);

var is_neighbour_solid(Map *map, VECTOR *pos, VECTOR *dir);

void map_create_walls(Map *map, Cell *cell);

void map_create_props(Map *map, Cell *cell);

void map_create_events(Map *map, Cell *cell);

void map_create_items(Map *map, Cell *cell);

void map_create_enemies(Map *map, Cell *cell);

void map_create_bosses(Map *map, Cell *cell);

void map_create_bbox(Map *map, Cell *cell);

void map_reset_statistic();

void map_load(Map *map);

void map_update(Map *map);

#endif