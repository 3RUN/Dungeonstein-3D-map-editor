#ifndef _CONFIG_H_
#define _CONFIG_H_

// settings tabs
// used for ui
#define SETTINGS_TAB_GENERIC 0
#define SETTINGS_TAB_INPUT 1

// different display modes
#define DISPLAY_MODES_MAX 2
#define DISPLAY_MODE_WINDOWED 0
#define DISPLAY_MODE_WINDOWED_FULLSCREEN 1

// mouse sensitivity
#define MOUSE_SENSE_MIN 0.1
#define MOUSE_SENSE_MAX 10

// volume
#define SND_VOLUME_MIN 0
#define SND_VOLUME_MAX 100

// font scale
#define FONT_SCALE_MIN 1
#define FONT_SCALE_MAX 2

// config sections
STRING *config_input_section_str = "Input";
STRING *config_shortcuts_section_str = "Shortcuts";
STRING *config_graphics_section_str = "Graphics";
STRING *config_other_section_str = "Other";

// config input entires
STRING *input_forward_entry_str = "Move forward";
STRING *input_backward_entry_str = "Move backward";
STRING *input_strafe_left_entry_str = "Move left (strafe)";
STRING *input_strafe_right_entry_str = "Move right (strafe)";
STRING *input_interact_entry_str = "Interact/Use";
STRING *input_run_entry_str = "Run (hold)";
STRING *input_draw_entry_str = "Draw cell";
STRING *input_erase_entry_str = "Erase cell";
STRING *input_pick_entry_str = "Pick cell";
STRING *input_rotate_entry_str = "Rotate cell";

// config shortcut entries
STRING *short_help_entry_str = "Help";
STRING *short_new_entry_str = "New episode";
STRING *short_open_entry_str = "Open episode";
STRING *short_save_entry_str = "Save episode";
STRING *short_ep_reset_entry_str = "Episode reset";
STRING *short_ep_edit_entry_str = "Episode edit";
STRING *short_reset_map_entry_str = "Reset active map";
STRING *short_test_run_entry_str = "Map test run";
STRING *short_map_settings_entry_str = "Active map settings";
STRING *short_screenshot_entry_str = "Take screenshot";
STRING *short_settings_entry_str = "Settings";
STRING *short_toggle_debug_entry_str = "Debug mode ON/OFF";
STRING *short_prior_map_entry_str = "Prior map";
STRING *short_next_map_entry_str = "Next map";
STRING *short_shift_map_west_entry_str = "Shift map to the West";   // pan 90
STRING *short_shift_map_east_entry_str = "Shift map to the East";   // pan 270
STRING *short_shift_map_south_entry_str = "Shift map to the South"; // pan 180
STRING *short_shift_map_north_entry_str = "Shift map to the North"; // pan 0

// mouse
STRING *mouse_sensitivity_entry_str = "Mouse sensitivity";

// audio
STRING *other_master_volume_entry_str = "Master volume";

// config other entries
STRING *other_font_scale_entry_str = "Font scale";
STRING *other_cell_tooltip_entry_str = "Cell tooltip enabled";
STRING *other_background_color_red_entry_str = "Background color red";
STRING *other_background_color_green_entry_str = "Background color green";
STRING *other_background_color_blue_entry_str = "Background color blue";
STRING *other_grid_color_red_entry_str = "Grid color red";
STRING *other_grid_color_green_entry_str = "Grid color green";
STRING *other_grid_color_blue_entry_str = "Grid color blue";

// config graphics entries
STRING *graphics_video_res_id_entry_str = "Video resolution id";
STRING *graphics_display_mode_entry_str = "Display mode";

// default input
STRING *input_none_str = "none";
STRING *input_def_forward_str = "w";
STRING *input_def_backward_str = "s";
STRING *input_def_strafe_left_str = "a";
STRING *input_def_strafe_right_str = "d";
STRING *input_def_interact_str = "e";
STRING *input_def_run_str = "shiftl";
STRING *input_def_draw_str = "mouse_left";
STRING *input_def_erase_str = "mouse_right";
STRING *input_def_pick_str = "mouse_middle";
STRING *input_def_rotate_str = "r";

// default shortcuts
STRING *short_def_help_str = "f1";
STRING *short_def_new_str = "f2";
STRING *short_def_open_str = "f3";
STRING *short_def_save_str = "f4";
STRING *short_def_ep_reset_str = "f5";
STRING *short_def_ep_edit_str = "f6";
STRING *short_def_reset_map_str = "f7";
STRING *short_def_test_run_str = "f8";
STRING *short_def_map_settings_str = "f9";
STRING *short_def_screenshot_str = "f10";
STRING *short_def_settings_str = "f11";
STRING *short_def_toggle_debug_str = "f12";
STRING *short_def_prior_map_str = "pgdn";
STRING *short_def_next_map_str = "pgup";
STRING *short_def_shift_map_west_str = "cuu";
STRING *short_def_shift_map_east_str = "cud";
STRING *short_def_shift_map_south_str = "cul";
STRING *short_def_shift_map_north_str = "cur";

// default mouse
float mouse_def_sensitivity = 1;

// audio
float master_def_volume = 100;

// config others
float font_def_scale = 1;
int is_cell_tooltip_def_enabled = true;
float background_def_color[3];
float grid_def_color[3];

// default graphics
int graphics_video_res_def_id = 0;
int graphics_display_def_mode = DISPLAY_MODE_WINDOWED_FULLSCREEN;

// structure to save all game config
typedef struct CONFIG
{
    // input
    char input_forward[32];
    char input_backward[32];
    char input_strafe_left[32];
    char input_strafe_right[32];
    char input_interact[32];
    char input_run[32];
    char input_draw[32];
    char input_erase[32];
    char input_pick[32];
    char input_rotate[32];

    // shortcuts
    char short_help[32];
    char short_new[32];
    char short_open[32];
    char short_save[32];
    char short_ep_reset[32];
    char short_ep_edit[32];
    char short_reset_map[32];
    char short_test_run[32];
    char short_map_settings[32];
    char short_screenshot[32];
    char short_settings[32];
    char short_toggle_debug[32];
    char short_prior_map[32];
    char short_next_map[32];
    char short_shift_map_west[32];
    char short_shift_map_east[32];
    char short_shift_map_south[32];
    char short_shift_map_north[32];

    // mouse
    float mouse_sensitivity;

    // audio
    float master_volume;

    // other settings
    float font_scale;
    int is_cell_tooltip_enabled;
    float background_color[3];
    float grid_color[3];

    // graphics
    int graphics_video_res_id;
    int graphics_display_mode;

} CONFIG;

CONFIG config_default; // never changed (used for reseting to default values)
CONFIG config_current; // changed directly in options menu, if cancel button pressed - resets back to old config
CONFIG config_saved;   // previously saved config, if yes/apply button pressed - get's overwritten by current config

void config_initialize(STRING *config_file);

void config_save();

void config_apply();

void config_reset_to_default(var tab);

void config_reset_to_saved();

void config_load_from_file(STRING *config_file);

void config_save_to_file(STRING *config_file);

#endif