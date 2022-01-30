#ifndef _EDITOR_MAIN_UI_H_
#define _EDITOR_MAIN_UI_H_

#define COMBOBOX_WIDTH 300

#define BUTTON_WIDTH 96
#define BUTTON_HEIGHT 32

#define EDITOR_TOP_BAR_HEIGHT 16
#define EDITOR_SIDE_BAR_WIDTH 280

#define EDITOR_TOP_BAR_NEW_POPUP 0
#define EDITOR_TOP_BAR_EXIT_POPUP 1

int editor_top_bar_popup_id = EDITOR_TOP_BAR_NEW_POPUP;

STRING *editor_top_bar_popup_str = "";
STRING *editor_top_bar_new_popup_str = "Are you sure you want to create a new episode?\n         All unsaved data will be lost!";
STRING *editor_top_bar_exit_popup_str = "Are you sure you want to exit?\nAll unsaved data will be lost!";

// resolution config
STRING *graphics_resolution_available_list_str[SCREEN_RESOLUTION_MAX];
STRING *graphics_resolution_currently_used_str = "None";
STRING *graphics_res_str = "Resolution";

// display mode config
STRING *graphics_display_mode_list_str[DISPLAY_MODES_MAX]; // list of available display modes (windowed, windowed fullscreen, fullscreen)
STRING *graphics_display_currently_used_str = "None";      // currently set display mode
STRING *graphics_display_mode_str = "Display mode";
STRING *graphics_display_windowed_str = "Windowed";
STRING *graphics_display_windowed_fullscreen_str = "Borderless";

void editor_camera_resize(int is_shrinked);

void editor_main_initialize();

void editor_main_destroy();

void editor_main_reset();

void editor_side_bar(Episode *e);

void editor_settings_refresh();

void editor_settings_window();

void editor_top_bar(Episode *e);

void editor_main_update(Episode *e);

#endif