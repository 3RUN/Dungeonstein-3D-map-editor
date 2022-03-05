#ifndef _EDITOR_POPUPS_H_
#define _EDITOR_POPUPS_H_

#define EDITOR_POPUP_OPEN_WIDTH 395
#define EDITOR_POPUP_OPEN_HEIGHT 320
#define EDITOR_POPUP_OPEN_SURE_WIDTH 340

#define EDITOR_POPUP_NEW_WIDTH 395
#define EDITOR_POPUP_NEW_SURE_WIDTH 320

#define EDITOR_POPUP_SAVE_AS_WIDTH 320

#define EDITOR_POPUP_SETTINGS_WIDTH 480
#define EDITOR_POPUP_EXIT_WIDTH 208

#define EDITOR_POPUP_EPISODE_EDIT_WIDTH 395
#define EDITOR_POPUP_RESET_MAP_WIDTH 300

#define EDITOR_POPUP_BUTTON_HEIGHT 24
#define EDITOR_POPUP_COMBOBOX_WIDTH 300

#define MUSIC_POPUP_MUSIC_BROWSER_WIDTH 395
#define MUSIC_POPUP_MUSIC_BROWSER_HEIGHT 320

char *editor_popup_save_as_input_id = "##Editor save as input field";

char *editor_popup_episode_browser_id = "##Editor episode browser child";
char *editor_popup_episode_listbox_id = "##Editor episode browser listbox";

char *editor_popup_new_filename_input_id = "##New filename";
char *editor_popup_new_episode_name_id = "##New episode name";
char *editor_popup_new_episode_story_id = "##New episode story";
char *editor_popup_new_episode_map_slider_id = "##New episode map slider";

char *editor_popup_episode_edit_name_id = "##Episode edit name";
char *editor_popup_episode_edit_story_id = "##Episode edit story";
char *editor_popup_episode_edit_map_slider_id = "##Episode edit map slider";

char *editor_popup_settings_display_combo_id = "##Display mode combo";
char *editor_popup_settings_resolution_combo_id = "##Resolution combo";
char *editor_popup_settings_bg_color_picker_id = "##Background color picker";
char *editor_popup_settings_grid_color_picker_id = "##Grid color picker";

char *editor_popup_music_browser_child_id = "##Music browser child";
char *editor_popup_music_browser_listbox_id = "##Music browser listbox";
char *editor_popup_music_browser_volume_slider_id = "##Music browser volume slider";

char new_filename[EPISODE_FILENAME_LENGTH];
char new_name[EPISODE_NAME_LENGTH];
char new_story[EPISODE_STORY_LENGTH];

char save_as_filename[EPISODE_FILENAME_LENGTH];

char episode_edit_name[EPISODE_NAME_LENGTH];
char episode_edit_story[EPISODE_STORY_LENGTH];

int new_map_count = 1;
int episode_edit_map_count = 1;
int is_episode_creation_failed = false;
int is_episode_save_as_failed = false;

STRING *editor_popup_open_str = "Please select episode to open.";
STRING *editor_popup_open_empty_folder_str = "'Documents\\MapEditor\\episodes' - folder is empty.";

STRING *editor_popup_open_sure_str = "Are you sure you want to open different episode?\nAll unsaved data will be lost!";

STRING *editor_popup_new_filename_str = "File name";
STRING *editor_popup_new_filename_tooltip_str = "The file name to save episode as. Character limit %d.";
STRING *editor_popup_new_episode_name_str = "Episode name";
STRING *editor_popup_new_episode_name_tooltip_str = "The name of the episode. Character limit %d.";
STRING *editor_popup_new_episode_story_str = "Short story";
STRING *editor_popup_new_episode_story_tooltip_str = "Short episode story. Character limit %d.";
STRING *editor_popup_new_episode_map_count_str = "Map count";
STRING *editor_popup_new_episode_map_count_tooltip_str = "Amount of maps in the episode. Max %d.";
STRING *editor_popup_new_creation_failed_str = " Make sure to enter filename, episode name and a story!";
STRING *editor_popup_new_file_exist_str = "          Episode with this name already exists!";
STRING *editor_popup_new_create_str = "";

STRING *editor_popup_new_sure_str = "Are you sure you want to create a new episode?\nAll unsaved data will be lost!";

STRING *editor_popup_save_as_str = "Save current episode";
STRING *editor_popup_save_as_button_str = "";
STRING *editor_popup_save_as_failed_str = "          You forgot to enter file name!";
STRING *editor_popup_save_as_overwrite_str = "      Episode with this name already exists!";

STRING *editor_popup_settings_hover_cell_tooltip_str = "Hovering cell tooltip: ";
STRING *editor_popup_settings_background_color_str = "Background color: ";
STRING *editor_popup_settings_grid_color_str = "Grid color:       ";

STRING *editor_popup_help_info_str = "blahahahaha";
STRING *editor_popup_exit_str = "Are you sure you want to exit?\nAll unsaved data will be lost!";

STRING *editor_popup_episode_edit_str = "Edit episode";

STRING *editor_popup_reset_map_str = "Are you sure you want to reset current map?";

STRING *editor_popup_currently_used_music_str = "";
STRING *editor_popup_currently_playing_music_str = "";
STRING *editor_popup_music_browser_str = "Music browser";
STRING *editor_popup_music_browser_empty_folder_str = "'Music' - folder is empty.";
STRING *editor_popup_music_browser_used_none_str = "Currently used: none";
STRING *editor_popup_music_browser_used_str = "Currently used: ";
STRING *editor_popup_music_browser_playing_str = "Currently playing: ";
STRING *editor_popup_music_browser_playing_none_str = "Currently playing: none";
STRING *editor_popup_music_browser_playing_failed_str = "         Please, select music file to play/use.";

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

void editor_popups_initialize(Episode *episode);

void editor_popups_refresh(Episode *episode);

void editor_popups_destroy();

void editor_popup_open(Episode *episode);

void editor_popup_open_sure();

void editor_popup_new(Episode *episode);

void editor_popup_new_sure();

void editor_popup_save_as(Episode *episode);

void editor_popup_settings(Episode *episode);

void editor_popup_about();

void editor_popup_episode_edit(Episode *episode);

void editor_popup_reset_map(Episode *episode);

void editor_popup_music_browser(Episode *episode);

void editor_popup_exit();

#endif