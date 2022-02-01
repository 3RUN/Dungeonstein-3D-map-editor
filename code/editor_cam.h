#ifndef _EDITOR_CAM_H_
#define _EDITOR_CAM_H_

POINTL mouse_pos_PL;

VECTOR vec_grid_center;
VECTOR vec_mouse_on_grid;
VECTOR vec_mouse_3d;
VECTOR vec_camera_center;

void camera_movement(var grid_height, var grid_size);

void camera_initialize();

void camera_update();

#endif