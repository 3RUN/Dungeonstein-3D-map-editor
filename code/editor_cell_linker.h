#ifndef _EDITOR_CELL_LINKER_H_
#define _EDITOR_CELL_LINKER_H_

#define CELL_LINK_Z_OFFSET 0.5
#define LASERBEAM_COLOR COLOR_GREEN

array_t *switch_n_trigger_list = NULL;
array_t *objects_to_link_list = NULL;

var link_refresh_cooldown = 1; // update each second !
var link_refresh_timer = 0;

var laserbeam_fade_speed = 2;
var laserbeam_alpha = 70;
var laserbeam_size = 5;

void particle_laserbeam_event(PARTICLE *p);

void particle_laserbeam(PARTICLE *p);

var is_activation_cell(Cell *cell);

var is_object_to_link(Cell *cell);

void editor_cell_linker_destroy_array(array_t *array);

void editor_cell_linker_destroy();

void editor_cell_show_links();

void editor_cell_find_links(Map *map);

void editor_cell_linker_update(Map *map);

#endif