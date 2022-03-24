#ifndef _EDITOR_POPUPS_H_
#define _EDITOR_POPUPS_H_

#define INPUT_BOTTON_WIDTH 128
#define INPUT_BUTTON_HEIGHT 16

#define POPUP_DELETE_BUTTON_ID 0

#define POPUP_OPEN_WIDTH 395
#define POPUP_OPEN_HEIGHT 320
#define POPUP_OPEN_SURE_WIDTH 340
#define POPUP_NEW_WIDTH 395
#define POPUP_NEW_SURE_WIDTH 320
#define POPUP_SAVE_AS_WIDTH 320
#define POPUP_SETTINGS_WIDTH 480
#define POPUP_SETTINGS_CHILD_HEIGHT 260
#define POPUP_EXIT_WIDTH 210
#define POPUP_EPISODE_RESET_WIDTH 340
#define POPUP_EPISODE_EDIT_WIDTH 395
#define POPUP_RESET_MAP_WIDTH 300
#define POPUP_HELP_WIDTH 550
#define POPUP_HELP_CHILD_HEIGHT 355
#define POPUP_MUSIC_BROWSER_WIDTH 395
#define POPUP_MUSIC_BROWSER_HEIGHT 320

#define POPUP_BUTTON_HEIGHT 24
#define POPUP_COMBOBOX_WIDTH 340

char *popup_episode_browser_id = "##Popup episode browser child id";
char *popup_episode_listbox_id = "##Popup episode browser listbox id";
char *popup_new_filename_input_id = "##Popup new episode filename input id";
char *popup_new_episode_name_input_id = "##Popup new episode name input id";
char *popup_new_episode_story_start_input_id = "##Popup new episode story start input id";
char *popup_new_episode_story_end_id = "##Popup new episode story end input id";
char *popup_new_episode_map_slider_id = "##Popup new episode map count slider id";
char *popup_save_as_input_id = "##Popup save as input id";
char *popup_settings_general_master_volume_slider_id = "##Popup settings general master volume slider id";
char *popup_settings_general_font_scale_slider_id = "##Popup settings general font scale slider id";
char *popup_settings_bg_color_picker_id = "##Popup settings general background color picker id";
char *popup_settings_grid_color_picker_id = "##Popup settings general grid color picker id";
char *popup_settings_display_combo_id = "##Popup settings general display mode combobox id";
char *popup_settings_resolution_combo_id = "##Popup settings general screen resolution combobox id";
char *popup_settings_input_child_id = "##Popup settings input child id";
char *popup_settings_input_mouse_slider_id = "##Popup settings input mouse slider id";
char *popup_settings_input_buttons_child_id = "##Popup settings input binding buttons child id";
char *popup_settings_tabs_id = "##Popup settings tabbar id";
char *popup_episode_edit_name_id = "##Popup episode edit name input id";
char *popup_episode_edit_story_start_id = "##Popup episode edit story start input id";
char *popup_episode_edit_story_end_id = "##Popup episode edit story end input id";
char *popup_episode_edit_map_count_slider_id = "##Popup episode edit map count slider id";
char *popup_help_child_id = "##Popup help child id";
char *popup_help_columns_id = "##Popup help columns id";
char *popup_music_browser_child_id = "##Popup music browser child id";
char *popup_music_browser_listbox_id = "##Popup music browser listbox id";
char *popup_music_browser_volume_slider_id = "##Popup music browser volume slider id";

char new_episode_filename[EPISODE_FILENAME_LENGTH];
char new_episode_name[EPISODE_NAME_LENGTH];
char new_episode_story_start[EPISODE_STORY_START_LENGTH];
char new_episode_story_end[EPISODE_STORY_END_LENGTH];

char episode_edit_name[EPISODE_NAME_LENGTH];
char episode_edit_story_start[EPISODE_STORY_START_LENGTH];
char episode_edit_story_end[EPISODE_STORY_END_LENGTH];

int new_episode_map_count = 1;
int episode_edit_map_count = 1;

int settings_tab_id = SETTINGS_TAB_GENERIC;

// new
STRING *popup_new_button_str = "";

// save as
STRING *popup_save_as_button_str = "";

// music browser
STRING *popup_currently_used_music_str = "";
STRING *popup_currently_playing_music_str = "";

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

void editor_input_overwrite(char *input, STRING *bindkey);

void editor_input_check_overwrite(STRING *bindkey);

void editor_input_bind_key(char *input, STRING *input_entry, STRING *entry, STRING *bindkey);

void editor_input_bind_new_key(STRING *entry, STRING *bindkey);

void editor_input_remove_bind_key(STRING *entry);

void editor_input_wait_for_binding(STRING *entry);

void editor_input_add_keybinding(STRING *entry, STRING *input);

void editor_shortcut_add_keybinding(STRING *entry, STRING *base_key, STRING *input);

void editor_popups_initialize();

void editor_popups_refresh();

void editor_popups_destroy();

void editor_popup_open(Episode *episode);

void editor_popup_open_sure();

void editor_popup_new_reset();

void editor_popup_new(Episode *episode);

void editor_popup_new_sure();

void editor_popup_save_as(Episode *episode);

void editor_popup_settings_general();

void editor_popup_settings_input();

void editor_popup_settings();

void editor_popup_exit();

void editor_popup_ep_reset();

void editor_popup_ep_edit_reset(Episode *episode);

void editor_popup_ep_edit(Episode *episode);

void editor_popup_map_reset();

void editor_popup_help();

void editor_popup_wait_for_input();

void editor_popup_music_browser();

#endif