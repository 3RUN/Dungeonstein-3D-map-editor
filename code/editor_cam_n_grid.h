#ifndef _EDITOR_CAM_N_GRID_H_
#define _EDITOR_CAM_N_GRID_H_

#define GRID_DRAW_OFFSET 0.1

#define CAM_BUILD_STATE_ROTATE_SPEED 5
#define CAM_BUILD_STATE_MOVE_SPEED 5
#define CAM_BUILD_STATE_SPEED_INCREASE_FACTOR 2

POINTL mouse_pos_PL;

VECTOR vec_grid_center;
VECTOR vec_mouse_on_grid;
VECTOR vec_mouse_3d;
VECTOR vec_camera_center;

VECTOR cam_force;
VECTOR cam_dist;
VECTOR cam_speed;

ANGLE cam_angle_force;
ANGLE cam_angle_speed;

int is_pos_on_grid(VECTOR *pos);

int is_pos_within_camera(VECTOR *pos);

int is_allowed_to_draw();

void editor_grid_get_mouse_pos(int *x, int *y);

void editor_grid_draw(VECTOR *center, var grid_size, int width, int height, COLOR *color);

void editor_camera_movement(var grid_height, var grid_size);

void editor_camera_in_map_settings();

void editor_camera_in_test_build();

void editor_camera_restore_pos_n_angle();

void editor_camera_initialize();

void editor_camera_n_grid_update();

#endif