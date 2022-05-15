#ifndef _GRID_H_
#define _GRID_H_

#define GRID_DRAW_OFFSET 0.1

int is_pos_on_grid(VECTOR *pos);

int is_pos_within_camera(VECTOR *pos);

void vec_snap_to_grid(VECTOR *pos);

void vec_world_to_grid(VECTOR *pos, int *x, int *y);

int is_allowed_to_draw();

void grid_update();

#include "grid.c"
#endif