#ifndef _EDITOR_GRID_SPRITES_H_
#define _EDITOR_GRID_SPRITES_H_

#define GRID_SPRITE_SCALE_FACTOR 0.95
#define GRID_PARENT_Z_OFFSET 0.1
#define GRID_SPRITE_DEF_COLOR vector(128, 128, 128)

#define LOCKED_BLUE_DOOR vector(128, 0, 0)
#define LOCKED_RED_DOOR vector(0, 0, 128)
#define LOCKED_YELLOW_DOOR vector(0, 128, 128)

STRING *blank_sprite_pcx = "blank.pcx";
STRING *empty_sprite_pcx = "empty.pcx";
STRING *secret_sprite_tga = "secret.tga";

array_t *grid_ents = NULL;
array_t *grid_dir = NULL;

void editor_grid_sprites_show(Episode *episode);

void editor_grid_sprites_hide();

void editor_grid_sprite_update_by_id(Cell *cell);

void editor_grid_direction_sprite_update_by_id(Cell *cell);

void editor_grid_sprites_refresh(Episode *episode);

void grid_sprite_ent_fnc();

void grid_direction_ent_fnc();

void editor_grid_sprites_create();

void editor_grid_sprite_destroy_array(array_t *array);

void editor_grid_sprites_destroy();

#endif