#ifndef _EDITOR_CAM_N_GRID_H_
#define _EDITOR_CAM_N_GRID_H_

#define GRID_DRAW_OFFSET 0.1

#define CAMERA_ARC 110

POINTL mouse_pos_PL;

VECTOR grid_center;
VECTOR camera_center;
VECTOR mouse_on_grid;
VECTOR mouse_3d;

VECTOR *vec_world_to_grid(VECTOR *world_pos);

int is_pos_on_grid(VECTOR *pos);

int is_pos_within_camera(VECTOR *pos);

int is_allowed_to_draw();

void grid_get_mouse_pos(int *x, int *y);

void grid_draw(VECTOR *center, var grid_size, int width, int height, COLOR *color);

void camera_auto_resize();

void camera_movement(var grid_height, var grid_size);

void camera_initialize();

void camera_fog_from_config();

void camera_fog_from_map(Map *map);

void camera_n_grid_update(Episode *episode);

#endif