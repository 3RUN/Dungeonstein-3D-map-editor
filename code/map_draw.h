#ifndef _MAP_DRAW_H_
#define _MAP_DRAW_H_

#define COOLDOWN_TIME 0.01
#define HOVERING_ENT_ALPHA 25

STRING *ground_plane_mdl = "trace_plane.mdl";

VECTOR hovering_cell_pos;

var tools_cooldown = 0;

var scancode_draw = 0;
var scancode_erase = 0;
var scancode_pick = 0;
var scancode_rotate = 0;

var key_draw = 0;
var key_erase = 0;
var key_pick = 0;

void map_draw_initialize();

void map_draw_destroy();

void map_draw_load_config(Config *config);

void map_draw_trace();

void map_find_n_erase_player(Map *map);

void map_find_n_erase_finish(Map *map);

void map_find_n_erase_teleport_out(Map *map);

void map_draw_draw(Map *map, Cell *cell);

void map_draw_erase(Map *map, Cell *cell);

void map_draw_pick(Map *map, Cell *cell);

void map_draw_rotate();

void map_shift_west();

void map_shift_east();

void map_shift_south();

void map_shift_north();

void map_prior();

void map_next();

void map_draw_update(Episode *episode);

#include "map_draw.c"
#endif