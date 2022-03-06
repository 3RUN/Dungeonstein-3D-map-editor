#ifndef _EDITOR_MOUSE_DRAW_H_
#define _EDITOR_MOUSE_DRAW_H_

var mouse_draw_timer = 0;
var mouse_draw_cooldown = 0.01;

var rotate_cell_once = false;

int is_cell_allowed_rotation(Cell *cell);

void editor_map_draw_cell(Cell *to, Cell *from);

void editor_map_erase_cell(Cell *cell);

void editor_mouse_draw_update(Episode *episode, Cell *drawing_cell);

#endif