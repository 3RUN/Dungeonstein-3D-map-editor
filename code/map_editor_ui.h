#ifndef _MAP_EDITOR_UI_H_
#define _MAP_EDITOR_UI_H_

#define EPISODE_SAVE_NAME_LENGTH 32

#define MAP_EDITOR_POPUP_EXIT 0
#define MAP_EDITOR_POPUP_SAVE 1

STRING *editor_popup_str = "";
STRING *editor_save_popup_str = "Save episode as";
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

BMAP *preview_bmap = NULL; // used for selected asset preview
char preview_name[ASSET_DESC_LENGTH];

// save button name (changes from Save to Overwrite if file with the given name is found)
STRING *save_button_name = "Save";

// all assets listbox
char *wall_textures_listbox[MAX_WALL_TEXTURES];
char *props_textures_listbox[MAX_PROPS_TEXTURES];
char *items_textures_listbox[MAX_ITEM_TEXTURES];
char *weapons_textures_listbox[MAX_WEAPON_TEXTURES];
char *enemies_textures_listbox[MAX_ENEMY_TEXTURES];
char *bosses_textures_listbox[MAX_BOSS_TEXTURES];

// asset category combobox
char *editor_main_selected_asset_type;
char *editor_main_asset_types[MAX_ASSET_TYPES];

// save name
char episode_save_name[EPISODE_SAVE_NAME_LENGTH];

int map_episode_save_failed = false;

int map_editor_popup_id = MAP_EDITOR_POPUP_EXIT;

int editor_asset_type = ASSET_TYPE_WALL; // currently active asset category
int editor_asset_index = 0;              // currently selected asset

void map_editor_ui_initialize();

void map_editor_ui_refresh(Episode *e);

void map_editor_ui_reset(Episode *e);

void map_editor_ui_destroy();

void editor_preview_update(int type, int index);

void map_editor_settings_refresh();

void map_editor_settings_window();

void map_editor_edit_episode_window(Episode *e);

void map_editor_help_window();

void map_editor_top_menu_bar(Episode *e);

void map_editor_weather_refresh(Episode *e);

void map_editor_side_menu(Episode *e);

void editor_cell_tooltip(Episode *e);

#endif