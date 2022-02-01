#ifndef _EDITOR_GRID_H_
#define _EDITOR_GRID_H_

#define GRID_DRAW_OFFSET 0.01

int is_pos_on_grid(VECTOR *pos);

int is_allowed_to_draw_map();

void grid_get_mouse_pos(int *x, int *y);

void grid_draw(VECTOR *center, var grid_size, int width, int height, COLOR *color);

void grid_initialize();

void grid_clear();

void grid_destroy();

void grid_update();

#endif