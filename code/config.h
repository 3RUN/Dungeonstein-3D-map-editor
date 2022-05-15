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
STRING *input_fly_up_entry_str = "Move up";
STRING *input_fly_down_entry_str = "Move down";
STRING *input_run_entry_str = "Run (move faster)";
STRING *input_rotate_cam_entry_str = "Rotate camera (hold)";
STRING *input_draw_entry_str = "Draw cell";
STRING *input_erase_entry_str = "Erase cell (hold + draw)";
STRING *input_pick_entry_str = "Pick cell (hold + draw)";
STRING *input_rotate_entry_str = "Rotate cell";
STRING *input_toggle_assets_entry_str = "Toggle asset list";
STRING *input_toggle_lights_entry_str = "Toggle dynamic lights";
STRING *input_toggle_draw_mode_entry_str = "Toggle draw mode";

// config shortcut entries
STRING *short_help_entry_str = "Help";
STRING *short_screenshot_entry_str = "Take screenshot";
STRING *short_new_entry_str = "New episode";
STRING *short_open_entry_str = "Open episode";
STRING *short_settings_entry_str = "Settings";
STRING *short_save_entry_str = "Save episode";
STRING *short_ep_reset_entry_str = "Episode reset";
STRING *short_ep_edit_entry_str = "Episode edit";
STRING *short_map_reset_entry_str = "Map reset";
STRING *short_map_settings_entry_str = "Map settings";
STRING *short_toggle_hovering_entry_str = "Hovering obj info ON/OFF";
STRING *short_toggle_debug_entry_str = "Debug panel ON/OFF";
STRING *short_map_prior_entry_str = "Map prior";
STRING *short_map_next_entry_str = "Map next";
STRING *short_map_shift_west_entry_str = "Map shift to West";
STRING *short_map_shift_east_entry_str = "Map shift to East";
STRING *short_map_shift_south_entry_str = "Map shift to South";
STRING *short_map_shift_north_entry_str = "Map shift to North";

// mouse
STRING *mouse_sensitivity_entry_str = "Mouse sensitivity";

// audio
STRING *other_master_volume_entry_str = "Master volume";

// config other entries
STRING *other_font_scale_entry_str = "Font scale";
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
STRING *input_def_fly_up_str = "q";
STRING *input_def_fly_down_str = "e";
STRING *input_def_run_str = "shiftl";
STRING *input_def_rotate_camera_str = "mouse_right";
STRING *input_def_draw_str = "mouse_left";
STRING *input_def_erase_str = "ctrl";
STRING *input_def_pick_str = "alt";
STRING *input_def_rotate_str = "r";
STRING *input_def_toggle_assets_str = "tab";
STRING *input_def_toggle_lights_str = "l";
STRING *input_def_toggle_draw_mode_str = "mouse_middle";

// default shortcuts
STRING *short_def_help_str = "f1";
STRING *short_def_screenshot_str = "f5";
STRING *short_def_new_str = "f2";
STRING *short_def_open_str = "f3";
STRING *short_def_settings_str = "f4";
STRING *short_def_save_str = "f6";
STRING *short_def_ep_reset_str = "f7";
STRING *short_def_ep_edit_str = "f8";
STRING *short_def_map_reset_str = "f9";
STRING *short_def_map_settings_str = "f10";
STRING *short_def_toggle_hovering_str = "f11";
STRING *short_def_toggle_debug_str = "f12";
STRING *short_def_map_prior_str = "pgdn";
STRING *short_def_map_next_str = "pgup";
STRING *short_def_map_shift_west_str = "cuu";
STRING *short_def_map_shift_east_str = "cud";
STRING *short_def_map_shift_south_str = "cul";
STRING *short_def_map_shift_north_str = "cur";

// default mouse
float mouse_def_sensitivity = 1;

// audio
float master_def_volume = 50;

// config others
float font_def_scale = 1;
float background_def_color[3];
float grid_def_color[3];

// default graphics
int graphics_video_res_def_id = 0;
int graphics_display_def_mode = DISPLAY_MODE_WINDOWED_FULLSCREEN;

// structure to save all game config
typedef struct Config
{
    // input
    char input_forward[32];
    char input_backward[32];
    char input_strafe_left[32];
    char input_strafe_right[32];
    char input_fly_up[32];
    char input_fly_down[32];
    char input_run[32];
    char input_rotate_camera[32];
    char input_draw[32];
    char input_erase[32];
    char input_pick[32];
    char input_rotate[32];
    char input_toggle_assets[32];
    char input_toggle_lights[32];
    char input_toggle_draw_mode[32];

    // shortcuts
    char short_help[32];
    char short_screenshot[32];
    char short_new[32];
    char short_open[32];
    char short_settings[32];
    char short_save[32];
    char short_ep_reset[32];
    char short_ep_edit[32];
    char short_map_reset[32];
    char short_map_settings[32];
    char short_toggle_debug[32];
    char short_toggle_hovering[32];
    char short_map_prior[32];
    char short_map_next[32];
    char short_map_shift_west[32];
    char short_map_shift_east[32];
    char short_map_shift_south[32];
    char short_map_shift_north[32];

    // mouse
    float mouse_sensitivity;

    // audio
    float master_volume;

    // other settings
    float font_scale;
    float background_color[3];
    float grid_color[3];

    // graphics
    int graphics_video_res_id;
    int graphics_display_mode;

} Config;

Config config_default; // never changed (used for reseting to default values)
Config config_current; // changed directly in options menu, if cancel button pressed - resets back to old config
Config config_saved;   // previously saved config, if yes/apply button pressed - get's overwritten by current config

void config_initialize(STRING *config_file);

void config_save();

void config_apply();

void config_reset_to_default(int tab);

void config_reset_to_saved();

void config_load_from_file(STRING *config_file);

void config_save_to_file(STRING *config_file);

#endif