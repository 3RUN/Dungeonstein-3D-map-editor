#ifndef _DRAW_H_
#define _DRAW_H_

void draw_bbox3d(VECTOR *position, VECTOR *bbox_min, VECTOR *bbox_max, ANGLE *angle, COLOR *color, var alpha);

void draw_grid3d(VECTOR *center, var grid_size, int width, int height, COLOR *color);

#include "draw.c"
#endif