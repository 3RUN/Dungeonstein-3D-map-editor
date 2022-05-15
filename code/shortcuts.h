#ifndef _SHORTCUTS_H_
#define _SHORTCUTS_H_

var screenshot_num = 0;

var scancode_help = 0;
var scancode_screenshot = 0;

var scancode_new = 0;
var scancode_open = 0;
var scancode_settings = 0;
var scancode_save = 0;
var scancode_ep_reset = 0;
var scancode_ep_edit = 0;
var scancode_map_reset = 0;
var scancode_map_settings = 0;
var scancode_toggle_hovering_info = 0;
var scancode_toggle_debug_panel = 0;
var scancode_map_prior = 0;
var scancode_map_next = 0;
var scancode_map_shift_west = 0;
var scancode_map_shift_east = 0;
var scancode_map_shift_south = 0;
var scancode_map_shift_north = 0;

int is_shortcut_allowed();

void shortcuts_load_config(Config *config);

void shortcut_help();

void shortcut_screenshot();

void shortcut_new();

void shortcut_open();

void shortcut_settings();

void shortcut_save();

void shortcut_ep_reset();

void shortcut_ep_edit();

void shortcut_map_reset();

void shortcut_map_settings();

void shortcut_toggle_hovering_info();

void shortcut_toggle_debug_panel();

void shortcut_map_prior();

void shortcut_map_next();

void shortcut_map_shift_west();

void shortcut_map_shift_east();

void shortcut_map_shift_south();

void shortcut_map_shift_north();

#include "shortcuts.c"
#endif