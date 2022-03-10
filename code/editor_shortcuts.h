#ifndef _EDITOR_SHORTCUTS_H_
#define _EDITOR_SHORTCUTS_H_

#define SHORTCUT_PANEL_LAYER 999
#define SHORTCUT_INFO_PANEL_ALPHA 100

PANEL *shortcut_info_pan = NULL;

FONT *shortcut_ackfont = "Arial#16";

STRING *shortcut_screenshot_saved_str = "Screenshot saved";
STRING *shortcut_episode_saved_str = "Episode saved";
STRING *shortcut_prior_map_loaded_str = "Prior map loaded";
STRING *shortcut_next_map_loaded_str = "Next map loaded";
STRING *shortcut_map_shifted_up_str = "Map shifted up";
STRING *shortcut_map_shifted_down_str = "Map shifted down";
STRING *shortcut_map_shifted_right_str = "Map shifted right";
STRING *shortcut_map_shifted_left_str = "Map shifted left";

SOUND *beep_ogg = "beep.ogg";

var screenshot_num = 0;

int beep_once = true;
var beep_handle = 0;
var beep_volume = 50;

void editor_shortcuts_initialize();

void editor_shortcuts_destroy();

void shortcut_show_info(STRING *msg);

void editor_shortcuts_update();

int is_edit_shortcuts_allowed();

int is_empty_shortcuts_allowed();

void shortcut_exit();

void shortcut_screenshot();

void shortcut_help();

void shortcut_settings();

void shortcut_save();

void shortcut_open();

void shortcut_new();

void shortcut_episode_edit();

void shortcut_shift_map();

void shortcut_prior_map();

void shortcut_next_map();

void shortcut_reset_map();

void shortcut_map_settings();

void shortcut_test_build();

#endif