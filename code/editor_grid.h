#ifndef _EDITOR_GRID_H_
#define _EDITOR_GRID_H_

#define GRID_DRAW_OFFSET 0.01

STRING *tile_mdl = "tile.mdl";

array_t *grid_ents;

int is_pos_on_grid(VECTOR *pos);

int is_pos_within_camera(VECTOR *pos);

int is_allowed_to_draw_map();

ENTITY *grid_get_ent(int id);

void grid_get_mouse_pos(int *x, int *y);

void grid_draw(VECTOR *center, var grid_size, int width, int height, COLOR *color);

void grid_entity_refresh(ENTITY *ent, VECTOR *pos, var pan, int id, int x, int y, int type, int index);

void grid_refresh_map(Map *m);

void grid_create_tiles();

void grid_initialize();

void grid_clear();

void grid_destroy();

void grid_update();

#endif