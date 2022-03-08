#ifndef _EDITOR_MAP_SETTINGS_H_
#define _EDITOR_MAP_SETTINGS_H_

#define EDITOR_MAP_SETTINGS_WINDOW_WIDTH 480
#define EDITOR_MAP_SETTINGS_WINDOW_HEIGHT 246

#define EDITOR_MAP_SETTINGS_MUSIC_NAME_INPUT_WIDTH 280
#define EDITOR_MAP_SETTINGS_MUSIC_BROWSE_BUTTON_HEIGHT 17

ENTITY *map_settings_ceiling_ent = NULL;
ENTITY *map_settings_walls_ent = NULL;
ENTITY *map_settings_floor_ent = NULL;

char *map_settings_window_id = "Map settings##Map settings window";
char *map_settings_weather_combobox_id = "##Weather type combobox";
char *map_settings_fog_start_slider_id = "##Fog start slider";
char *map_settings_fog_end_slider_id = "##Fog end slider";
char *map_settings_fog_color_picker_id = "##Fog color picker";
char *map_settings_sky_color_picker_id = "##Sky color picker";
char *map_settings_floor_color_picker_id = "##Floor color picker";
char *map_settings_music_input_id = "##Music name textbox";
char *map_settings_music_browser_popup_id = "##Music browser popup";

STRING *map_settings_opened_map_id_str = "Opened Map Id:";
STRING *map_settings_weather_str = "Weather:      ";
STRING *map_settings_fog_start_str = "Fog start:    ";
STRING *map_settings_fog_start_tooltip_str = "Fog starting distance in quants.\nShould be smaller than 'end'.";
STRING *map_settings_fog_end_str = "Fog end:      ";
STRING *map_settings_fog_end_tooltip_str = "Fog end distance in quants.\nShould be higher than 'start'.";
STRING *map_settings_fog_color_str = "Fog color:    ";
STRING *map_settings_ceiling_color_str = "";
STRING *map_settings_change_ceiling_color_str = "Ceiling color:";
STRING *map_settings_change_sky_color_str = "Sky color:    ";
STRING *map_settings_floor_color_str = "Floor color:  ";
STRING *map_settings_music_str = "Music:        ";

// weather
STRING *weather_list_str[WEATHER_MAX];
STRING *weather_currently_used_str = "";
STRING *weather_clear_str = "Clear";
STRING *weather_rain_str = "Rain";
STRING *weather_snow_str = "Snow";

// map to temporary save settings at
Map map_settings;

void editor_map_settings_initialize();

void editor_map_settings_refresh();

void editor_map_settings_destroy();

void editor_map_settings_show(Map *map);

void editor_map_settings_hide();

void editor_map_settings_popup(Episode *episode);

void editor_map_settings_update(Episode *episode);

#endif