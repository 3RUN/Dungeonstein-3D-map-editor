#ifndef _EDITOR_GRID_ENTS_H_
#define _EDITOR_GRID_ENTS_H_

BMAP *blank_texture_tga = "blank.tga";

STRING *tile_mdl = "tile.mdl";

array_t *grid_ents = NULL;

void grid_ent_fnc();

void editor_update_grid_ent_by_id(int id, var pan, int type, int asset);

void editor_update_grid_ents(Map *m);

void editor_reset_grid_ents();

void editor_create_grid_ents();

void editor_destroy_grid_ents();

#endif