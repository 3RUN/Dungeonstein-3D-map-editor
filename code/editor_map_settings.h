#ifndef _EDITOR_MAP_SETTINGS_H_
#define _EDITOR_MAP_SETTINGS_H_

#define MAP_SETTINGS_WINDOW_WIDTH 480
#define MAP_SETTINGS_WINDOW_HEIGHT 262

#define MAP_SETTINGS_BUTTON_HEIGHT 24

#define MAP_SETTINGS_MUSIC_NAME_INPUT_WIDTH 280
#define MAP_SETTINGS_MUSIC_BROWSE_BUTTON_HEIGHT 17

char *map_settings_window_id = "Map settings";
char *map_settings_weather_combo_id = "##Map settings weather combobox id";
char *map_settings_fog_start_slider_id = "##Map settings fog start slider id";
char *map_settings_fog_end_slider_id = "##Map settings fog end slider id";
char *map_settings_fog_color_picker_id = "##Map settings fog color picker id";
char *map_settings_sky_color_picker_id = "##Map settings sky/ceiling color picker id";
char *map_settings_floor_color_picker_id = "##Map settings floor color picker id";
char *map_settings_music_input_id = "##Map settings music input id";
char *map_settings_music_browser_popup_id = "##Map settings music browser popup id";

STRING *map_settings_ceiling_color_str = "";

STRING *weather_list_str[WEATHER_MAX];
STRING *weather_currently_used_str = "";
STRING *weather_clear_str = "Clear";
STRING *weather_rain_str = "Rain";
STRING *weather_snow_str = "Snow";

void editor_map_settings_copy_from_active(Map *map);

void editor_map_settings_copy_to_active(Map *map);

void editor_map_settings_initialize();

void editor_map_settings_refresh();

void editor_map_settings_destroy();

void editor_map_settings_popup();

void editor_map_settings_update(Map *map);

#endif