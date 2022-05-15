#ifndef _CAMERA_H_
#define _CAMERA_H_

#define FOG_MAX_END 4096

#define CAMERA_ARC 110
#define CAM_MOVE_SPEED 10
#define CAM_RUN_FACTOR 2

var scancode_cam_forward = 0;
var scancode_cam_backward = 0;
var scancode_cam_strafe_left = 0;
var scancode_cam_strafe_right = 0;
var scancode_cam_fly_up = 0;
var scancode_cam_fly_down = 0;
var scancode_cam_run = 0;
var scancode_cam_rotate = 0;

var key_cam_forward = 0;
var key_cam_backward = 0;
var key_cam_strafe_left = 0;
var key_cam_strafe_right = 0;
var key_cam_fly_up = 0;
var key_cam_fly_down = 0;
var key_cam_run = 0;
var key_cam_rotate = 0;

void camera_initialize();

void camera_load_config(Config *config);

void camera_auto_resize();

void camera_update_fog();

void camera_fly();

void camera_update();

#include "camera.c"
#endif