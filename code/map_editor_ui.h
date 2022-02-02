#ifndef _MAP_EDITOR_UI_H_
#define _MAP_EDITOR_UI_H_

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

void map_editor_ui_initialize();

void map_editor_ui_refresh(Episode *e);

void map_editor_ui_reset(Episode *e);

void map_editor_ui_destroy();

void map_editor_settings_refresh();

void map_editor_settings_window();

void map_editor_edit_episode_window(Episode *e);

void map_editor_help_window();

void map_editor_top_menu_bar(Episode *e);

void map_editor_side_menu(Episode *e);

void editor_cell_tooltip(Episode *e);

#endif