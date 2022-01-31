#ifndef _EDITOR_MAIN_H_
#define _EDITOR_MAIN_H_

#define COMBOBOX_WIDTH 300

#define BUTTON_WIDTH 96
#define BUTTON_HEIGHT 32

#define EDITOR_TOP_BAR_HEIGHT 16
#define EDITOR_SIDE_BAR_WIDTH 280

STRING *editor_back_to_menu_popup_str = "You want to go back to main menu?\nAll unsaved data will be lost!";

int is_grid_visible = true;
int is_walls_visible = true;
int is_objects_visible = true;

void editor_side_bar(Episode *e);

void editor_top_bar(Episode *e);

void editor_main_update(Episode *e);

#endif