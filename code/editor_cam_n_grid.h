#ifndef _EDITOR_CAM_N_GRID_H_
#define _EDITOR_CAM_N_GRID_H_

#define GRID_DRAW_OFFSET 0.1

POINTL mouse_pos_PL;

VECTOR vec_grid_center;
VECTOR vec_mouse_on_grid;
VECTOR vec_mouse_3d;
VECTOR vec_camera_center;

int is_pos_on_grid(VECTOR *pos);

int is_pos_within_camera(VECTOR *pos);

int is_allowed_to_draw();

void editor_grid_get_mouse_pos(int *x, int *y);

void editor_grid_draw(VECTOR *center, var grid_size, int width, int height, COLOR *color);

void editor_camera_movement(var grid_height, var grid_size);

void editor_camera_in_map_settings();

void editor_camera_restore_pos_n_angle();

void editor_camera_initialize();

void editor_camera_n_grid_update();

#endif