#ifndef _EDITOR_CELL_INFO_H_
#define _EDITOR_CELL_INFO_H_

void get_cell_info(Cell *cell, STRING **out);

void draw_map_info(Map *current_map, STRING **out, var x, var y);

#endif