#ifndef _EDITOR_MAIN_H_
#define _EDITOR_MAIN_H_

#define COMBOBOX_WIDTH 300

#define BUTTON_WIDTH 96
#define BUTTON_HEIGHT 32

#define EDITOR_TOP_BAR_HEIGHT 16
#define EDITOR_SIDE_BAR_WIDTH 280

int editor_asset_type = ASSET_TYPE_WALL;
int editor_asset_index = 0;

BMAP *preview_bmap = NULL;

char *preview_name[ASSET_DESC_LENGTH];
char *wall_textures_listbox[MAX_WALL_TEXTURES];
char *props_textures_listbox[MAX_PROPS_TEXTURES];
char *items_textures_listbox[MAX_ITEM_TEXTURES];
char *weapons_textures_listbox[MAX_WEAPON_TEXTURES];
char *enemies_textures_listbox[MAX_ENEMY_TEXTURES];
char *bosses_textures_listbox[MAX_BOSS_TEXTURES];

char *editor_main_selected_asset_type = "";
char *editor_main_asset_types[MAX_ASSET_TYPES];

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

// weather
STRING *weather_list_str[WEATHER_MAX];
STRING *weather_currently_used_str = "";
STRING *weather_clear_str = "Clear";
STRING *weather_rain_str = "Rain";
STRING *weather_snow_str = "Snow";

void editor_preview_update(int type, int index);

void editor_weather_refresh(Episode *e);

void editor_side_bar(Episode *e);

void editor_settings_refresh();

void editor_settings_window();

void editor_episode_edit_window(Episode *e);

void editor_help_window();

void editor_top_bar(Episode *e);

void editor_cell_tooltip(Episode *e);

void editor_main_initialize(Episode *e);

void editor_main_reset(Episode *e);

void editor_main_destroy();

void editor_main_update(Episode *e);

#endif