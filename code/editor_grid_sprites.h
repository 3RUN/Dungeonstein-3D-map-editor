#ifndef _EDITOR_GRID_SPRITES_H_
#define _EDITOR_GRID_SPRITES_H_

#define GRID_SPRITE_SCALE_FACTOR 0.95

BMAP *blank_texture_pcx = "blank.pcx";

STRING *blank_sprite_pcx = "blank.pcx";

array_t *grid_ents = NULL;

void editor_grid_sprites_show(Episode *episode);

void editor_grid_sprites_hide();

void editor_grid_sprite_update_by_id(int id, var pan, int type, int asset);

void editor_grid_sprites_refresh(Episode *episode);

void editor_grid_sprites_create();

void editor_grid_sprites_reset();

void editor_grid_sprites_destroy();

#endif