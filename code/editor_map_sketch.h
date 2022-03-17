#ifndef _EDITOR_MAP_SKETCH_H_
#define _EDITOR_MAP_SKETCH_H_

#define SKETCH_SPRITE_SCALE_FACTOR 0.95
#define SKETCH_PARENT_Z_OFFSET 0.1
#define SKETCH_SPRITE_DEF_COLOR vector(128, 128, 128)

STRING *empty_sprite_pcx = "empty.pcx";
STRING *rotation_sprite_tga = "rotation.tga";
STRING *secret_sprite_tga = "secret.tga";

array_t *sketch_ents = NULL;

void map_sketch_sprite_ent_fnc();

void map_sketch_sprite_parent_ent_fnc();

void map_sketch_initialize();

void map_sketch_destroy_array(array_t *array);

void map_sketch_destroy();

void map_sketch_sprite_update_from_cell(Cell *cell);

void map_sketch_refresh(Map *map);

void map_sketch_show();

void map_sketch_hide();

void map_sketch_update(Episode *episode);

#endif