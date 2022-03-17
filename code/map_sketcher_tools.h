#ifndef _MAP_SKETCHER_TOOLS_H_
#define _MAP_SKETCHER_TOOLS_H_

var mouse_resume_drawing = true; // used to prevent drawing when 'top bar' menu is used

var mouse_draw_timer = 0;
var mouse_draw_cooldown = 0.01;
var mouse_draw_once = false;

var mouse_erase_timer = 0;
var mouse_erase_cooldown = 0.01;
var mouse_erase_once = false;

var pick_cell_once = false;

var rotate_cell_once = false;

var scancode_draw = 0;
var scancode_erase = 0;
var scancore_pick = 0;
var scancode_rotate = 0;
var scancode_rapid = 0;

var key_draw = 0;
var key_erase = 0;
var key_pick = 0;
var key_rotate = 0;
var key_rapid = 0;

void find_n_erase_player(Map *map);

void find_n_erase_finish(Map *map);

void draw_cell(Episode *episode, Cell *to, Cell *from);

void erase_cell(Cell *cell);

void pick_cell(Cell *to, Cell *from);

void sketcher_update_input_from_config(CONFIG *config);

void sketcher_tools_update(Map *map, Cell *p_cell);

#endif