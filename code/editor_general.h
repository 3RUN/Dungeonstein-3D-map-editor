#ifndef _EDITOR_GENERAL_H_
#define _EDITOR_GENERAL_H_

#define MAP_SETTINGS_WINDOW_WIDTH 480
#define MAP_SETTINGS_WINDOW_HEIGHT 178
#define MAP_SETTINGS_BUTTON_HEIGHT 24

#define MAP_SETTINGS_MUSIC_NAME_INPUT_WIDTH 280
#define MAP_SETTINGS_MUSIC_BROWSE_BUTTON_HEIGHT 17

void *asset_list_categories_draw = NULL;

var scancode_toggle_asset_list = 0;
var scancode_toggle_lights = 0;
var scancode_toggle_drawmode = 0;

void editor_load_config(Config *config);

void editor_toggle_asset_list();

void editor_toggle_lights();

void editor_toggle_drawmode();

void editor_popups(Episode *episode);

void editor_topbar(Episode *episode);

void editor_map_settings(Episode *episode);

void editor_asset_category_button(void *draw_list, STRING *category, BMAP *texture, int index);

void editor_asset_category_buttons_update();

void editor_get_cell_info(Cell *cell, STRING **out);

void editor_update(Episode *episode);

#include "editor_general.c"
#endif