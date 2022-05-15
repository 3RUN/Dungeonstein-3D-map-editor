#ifndef _EDITOR_POPUPS_H_
#define _EDITOR_POPUPS_H_

#define POPUP_DELETE_BUTTON_ID 0

#define POPUP_NEW_WIDTH 395
#define POPUP_OPEN_WIDTH 395
#define POPUP_OPEN_HEIGHT 320
#define POPUP_SETTINGS_WIDTH 480
#define POPUP_SETTINGS_CHILD_HEIGHT 260
#define POPUP_EXIT_WIDTH 210
#define POPUP_OPEN_CONFIRM_WIDTH 340
#define POPUP_NEW_CONFIRM_WIDTH 320
#define POPUP_SAVE_AS_WIDTH 320
#define POPUP_EPISODE_RESET_WIDTH 340
#define POPUP_EPISODE_EDIT_WIDTH 395
#define POPUP_MAP_RESET_WIDTH 300
#define POPUP_HELP_WIDTH 600
#define POPUP_HELP_CHILD_HEIGHT 355
#define POPUP_ASSET_LIST_WIDTH 558
#define POPUP_ASSET_TEXTURE_LIST_HEIGHT 148
#define POPUP_ASSET_OBJECT_LIST_HEIGHT 216
#define POPUP_ASSET_OBJECT_PARAM_HEIGHT 118
#define POPUP_MUSIC_BROWSER_WIDTH 395
#define POPUP_MUSIC_BROWSER_HEIGHT 320

char save_as_filename[EPISODE_NAME_LENGTH];
char new_episode_filename[EPISODE_NAME_LENGTH];
char new_episode_name[EPISODE_NAME_LENGTH];
char episode_edit_name[EPISODE_NAME_LENGTH];

int new_episode_map_count = 1;
int episode_edit_map_count = 1;

int settings_tab_id = SETTINGS_TAB_GENERIC;
int settings_input_reset_scrollbar = false;

int playing_music_index = 0;
var playing_music_handle = 0;
var playing_music_volume = 50;

void *asset_list_popup_draw = NULL;

STRING *popup_new_button_str = "";
STRING *popup_save_as_button_str = "";
STRING *popup_currently_used_music_str = "";
STRING *popup_currently_playing_music_str = "";
STRING *popup_asset_list_object_tooltip_str = "";
STRING *popup_asset_selected_object_name_str = "";

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

void popups_initialize();

void popups_refresh();

void popups_destroy();

void popup_new(Episode *episode);

void popup_open(Episode *episode);

void popup_settings_general();

void popup_settings_input();

void popup_settings();

void popup_exit();

void popup_wait_for_input();

void popup_confirm_open();

void popup_confirm_new();

void popup_save_as(Episode *episode);

void popup_ep_reset(Episode *episode);

void popup_ep_edit(Episode *episode);

void popup_map_reset(Map *map);

void popup_help();

void popup_asset_list_object_info(STRING *str_out, int type, int index);

void popup_assets_list_item(void *draw_list, BMAP *texture, int *selection, int type, int index);

void popup_asset_list();

void stop_playing_music();

void play_selection();

void popup_music_browser();

#include "editor_popups.c"
#endif