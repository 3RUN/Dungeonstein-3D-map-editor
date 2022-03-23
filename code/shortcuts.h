#ifndef _SHORTCUTS_H_
#define _SHORTCUTS_H_

var screenshot_num = 0;

var scancode_help = 0;
var scancode_new = 0;
var scancode_open = 0;
var scancode_save = 0;
var scancode_ep_reset = 0;
var scancode_ep_edit = 0;
var scancode_reset_map = 0;
var scancode_test_run = 0;
var scancode_map_settings = 0;
var scancode_screenshot = 0;
var scancode_settings = 0;
var scancode_toggle_debug = 0;
var scancode_prior_map = 0;
var scancode_next_map = 0;
var scancode_shift_map_west = 0;
var scancode_shift_map_east = 0;
var scancode_shift_map_south = 0;
var scancode_shift_map_north = 0;

int is_shortcut_allowed();

void shortcut_remove_binding(var scancode);

void shortcut_update_binding(var scancode, void *fnc);

void shortcuts_update_from_config(Config *config);

void shortcut_help();

void shortcut_new();

void shortcut_open();

void shortcut_save();

void shortcut_ep_reset();

void shortcut_ep_edit();

void shortcut_reset_map();

void shortcut_test_run();

void shortcut_map_settings();

void shortcut_screenshot();

void shortcut_settings();

void shortcut_toggle_debug();

void shortcut_prior_map();

void shortcut_next_map();

void shortcut_shift_map_west();

void shortcut_shift_map_east();

void shortcut_shift_map_south();

void shortcut_shift_map_north();

#endif