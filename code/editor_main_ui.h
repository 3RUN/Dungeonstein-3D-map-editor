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

char *wall_texture_listbox[MAX_WALL_TEXTURES];
char *floor_texture_listbox[MAX_FLOOR_TEXTURES];
char *ceiling_texture_listbox[MAX_CEILING_TEXTURES];

int editor_asset_index = 0;

BMAP *preview_bmp;

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

// weather
STRING *weather_list_str[WEATHER_MAX];
STRING *weather_currently_used_str = "";
STRING *weather_clear_str = "Clear";
STRING *weather_cloudy_str = "Cloudy";
STRING *weather_rain_str = "Rainy";

// skycube
STRING *skycube_list_str[SKY_MAX];
STRING *skycube_currently_used_str = "";
STRING *skycube_clear_str = "Day Clear";
STRING *skycube_cloudy_str = "Day Cloudy";
STRING *skycube_night_str = "Night";

// imgui handles color range from 0...1
// so I do this dumb trick to get 0...255 value
float get_hsv_from_color(float value);

float get_color_from_hsv(float value);

void editor_camera_resize(int is_shrinked);

void editor_update_preview(int type, int index);

void editor_main_initialize(Episode *e);

void editor_main_destroy();

void editor_main_reset(Episode *e);

void editor_weather_refresh(Episode *e);

void editor_sky_refresh(Episode *e);

void editor_map_settings(Episode *e);

void editor_wall_textures();

void editor_floor_textures();

void editor_ceiling_textures();

void editor_side_bar(Episode *e);

void editor_settings_refresh();

void editor_settings_window();

void editor_top_bar(Episode *e);

void editor_main_update(Episode *e);

#endif