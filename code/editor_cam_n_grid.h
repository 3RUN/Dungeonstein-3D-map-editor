#ifndef _EDITOR_CAM_N_GRID_H_
#define _EDITOR_CAM_N_GRID_H_

#define GRID_DRAW_OFFSET 0.1

#define CAMERA_ARC 110
#define MOVEMENT_SPEED 2
#define RUN_FACTOR 4

POINTL mouse_pos_PL;

VECTOR grid_center;
VECTOR camera_center;
VECTOR mouse_on_grid;
VECTOR mouse_3d;

var scancode_forward = 0;
var scancode_backward = 0;
var scancode_strafe_left = 0;
var scancode_strafe_right = 0;
var scancode_surface = 0;
var scancode_dive = 0;
var scancode_run = 0;
var scancode_drag_map = 0;

var key_forward = 0;
var key_backward = 0;
var key_strafe_left = 0;
var key_strafe_right = 0;
var key_surface = 0;
var key_dive = 0;
var key_run = 0;
var key_drag_map = 0;

void vec_snap_to_grid(VECTOR *pos);

VECTOR *vec_world_to_grid(VECTOR *world_pos);

var is_pos_on_grid(VECTOR *pos);

var is_pos_within_camera(VECTOR *pos);

var is_allowed_to_draw();

void grid_get_mouse_pos(var *x, var *y);

void grid_draw(VECTOR *center, var grid_size, var width, var height, COLOR *color);

void camera_auto_resize();

void camera_topdown_movement(var grid_height, var grid_size);

void camera_fp_movement();

void camera_initialize();

void camera_update_input_from_config(CONFIG *config);

void camera_fog_from_config();

void camera_fog_from_map(Map *map);

void camera_reset(Map *map, var state);

void camera_n_grid_update(Episode *episode);

#endif