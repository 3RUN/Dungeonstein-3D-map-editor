#ifndef _EDITOR_MAIN_H_
#define _EDITOR_MAIN_H_

#define COMBOBOX_WIDTH 300

#define BUTTON_WIDTH 96
#define BUTTON_HEIGHT 32

#define EDITOR_TOP_BAR_HEIGHT 16
#define EDITOR_SIDE_BAR_WIDTH 280

BMAP *preview_bmap = NULL;

char *preview_name[ASSET_DESC_LENGTH];

STRING *editor_back_to_menu_popup_str = "You want to go back to main menu?\nAll unsaved data will be lost!";

// resolution config
STRING *graphics_resolution_available_list_str[SCREEN_RESOLUTION_MAX];
STRING *graphics_resolution_currently_used_str = "None";
STRING *graphics_res_str = "Resolution:";

// display mode config
STRING *graphics_display_mode_list_str[DISPLAY_MODES_MAX]; // list of available display modes (windowed, windowed fullscreen, fullscreen)
STRING *graphics_display_currently_used_str = "None";      // currently set display mode
STRING *graphics_display_mode_str = "Display mode:";
STRING *graphics_display_windowed_str = "Windowed";
STRING *graphics_display_windowed_fullscreen_str = "Borderless";

void editor_preview_update(int type, int index);

void editor_side_bar(Episode *e);

void editor_settings_refresh();

void editor_settings_window();

void editor_help_window();

void editor_top_bar(Episode *e);

void editor_main_initialize();

void editor_main_reset();

void editor_main_update(Episode *e);

#endif