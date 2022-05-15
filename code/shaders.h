#ifndef _SHADERS_H_
#define _SHADERS_H_

#define PSX_DITHER

#define SKYCUBE_TGA "skycube+6.tga"

BMAP *mtl_dither_pcx = "dither.pcx";
BMAP *render_target_tga;

ENTITY *skycube_ent = NULL;

var shader_level_ambient = 0.35;
var shader_vertex_snapping = 120;
var shader_lighting_brightness = 25;
var shader_sky_fogginess = 0.5; // smaller value - less fog

VIEW *pp_view;

MATERIAL *mtl_solid;

MATERIAL *mtl_water;

MATERIAL *mtl_marker;

MATERIAL *mtl_night_sky;

MATERIAL *mtl_pp_screen;

void shaders_initialize();

void shaders_destroy();

void shaders_show_sky();

void shaders_hide_sky();

void shaders_reset();

void shaders_update();

#include "shaders.c"
#endif