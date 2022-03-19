#ifndef _SHADERS_H_
#define _SHADERS_H_

var shader_level_ambient = 0.5;
var shader_angle_surface_darken = 0.5;

MATERIAL *mtl_solid;
MATERIAL *mtl_two_sided;

void shaders_initialize();

void shaders_destroy();

void shaders_update();

#endif