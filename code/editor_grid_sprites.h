#ifndef _EDITOR_GRID_SPRITES_H_
#define _EDITOR_GRID_SPRITES_H_

#define GRID_SPRITE_SCALE_FACTOR 0.95

STRING *blank_sprite_pcx = "blank.pcx";
STRING *empty_sprite_pcx = "empty.pcx";

array_t *grid_ents = NULL;
array_t *grid_dir = NULL;

void editor_grid_sprites_show(Episode *episode);

void editor_grid_sprites_hide();

void editor_grid_sprite_update_by_id(int id, var pan, int type, int asset);

void editor_grid_direction_sprite_update_by_id(int id, var pan, int type, int asset);

void editor_grid_sprites_refresh(Episode *episode);

void grid_sprite_ent_fnc();

void grid_direction_ent_fnc();

void editor_grid_sprites_create();

void editor_grid_sprites_reset();

void editor_grid_sprite_destroy_array(array_t *array);

void editor_grid_sprites_destroy();

#endif