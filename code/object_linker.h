#ifndef _OBJECT_LINKER_H_
#define _OBJECT_LINKER_H_

#define CELL_LINK_Z_OFFSET 0.5
#define LASERBEAM_COLOR COLOR_GREEN

array_t *activator_list = NULL;
array_t *objects_to_link_list = NULL;

var link_refresh_cooldown = 1; // update each second !
var link_refresh_timer = 0;

var laserbeam_fade_speed = 2;
var laserbeam_alpha = 50;
var laserbeam_size = 2.5;

void particle_laserbeam_event(PARTICLE *p);

void particle_laserbeam(PARTICLE *p);

void particle_draw_line(VECTOR *from, VECTOR *to);

int is_activation_object(Object *object);

int is_object_to_link(Object *object);

void object_linker_destroy_array(array_t *array);

void object_linker_destroy();

void object_show_links();

void object_linker_find_links(Map *map);

void object_linker_update(Episode *episode);

#include "object_linker.c"
#endif