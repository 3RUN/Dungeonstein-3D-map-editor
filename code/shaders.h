#ifndef _SHADERS_H_
#define _SHADERS_H_

var shader_level_ambient = 0.5;
var shader_angle_surface_darken = 0.5;

MATERIAL *mtl_solid =
{
    effect = "mtl_solid.fx";
    flags = AUTORELOAD;
}

MATERIAL *mtl_two_sided =
{
    effect = "mtl_two_sided.fx";
    flags = AUTORELOAD;
}

void shaders_update();

#include "shaders.c"
#endif