#ifndef _EDITOR_H_
#define _EDITOR_H_

#define COMBOBOX_WIDTH 300

#define BUTTON_WIDTH 96
#define BUTTON_HEIGHT 32

#define EDITOR_TOP_BAR_HEIGHT 16
#define EDITOR_SIDE_BAR_WIDTH 280

void editor_switch_state_to(int state);

void editor_create_tooltip(STRING *tooltip);

void editor_help_maker(char *desc);

float get_hsv_from_color(float value);

float get_color_from_hsv(float value);

void editor_camera_resize(int is_shrinked);

STRING *get_cell_info(Cell *c);

STRING *draw_cell_info(Map *m, int x, int y);

#endif