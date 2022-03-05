#ifndef _EDITOR_H_
#define _EDITOR_H_

#define EDITOR_TOP_BAR_HEIGHT 16
#define EDITOR_SIDE_BAR_WIDTH 280

STRING *editor_ok_str = "Ok";
STRING *editor_yes_str = "Yes";
STRING *editor_no_str = "No";
STRING *editor_back_str = "Back";
STRING *editor_close_str = "Close";
STRING *editor_defaults_str = "Defaults";
STRING *editor_apply_str = "Apply";
STRING *editor_cancel_str = "Cancel";
STRING *editor_disabled_str = "Disabled";
STRING *editor_enabled_str = "Enabled";
STRING *editor_refresh_str = "Refresh";
STRING *editor_load_str = "Load";
STRING *editor_overwrite_str = "Overwrite";
STRING *editor_save_str = "Save";
STRING *editor_save_as_str = "Save as";
STRING *editor_edit_str = "Edit";
STRING *editor_reset_str = "Reset";
STRING *editor_map_settings_str = "Settings";
STRING *editor_test_build_str = "Test build";
STRING *editor_view_grid_str = "Grid";
STRING *editor_view_walls_str = "Walls";
STRING *editor_view_objects_str = "Objects";
STRING *editor_view_connections_str = "Connections";
STRING *editor_save_as_hint_str = "name";
STRING *editor_filename_str = "File name:";
STRING *editor_decrease_str = "Decrease";
STRING *editor_increase_str = "Increase";
STRING *editor_browse_str = "Browse";
STRING *editor_volume_str = "Volume: ";
STRING *editor_play_n_stop_str = "Play/Stop";
STRING *editor_use_str = "Use";
STRING *editor_category_str = "Category:";

STRING *editor_file_str = "File";
STRING *editor_open_str = "Open";
STRING *editor_new_str = "New";
STRING *editor_preferences_str = "Preferences";
STRING *editor_exit_str = "Exit";
STRING *editor_about_str = "About";
STRING *editor_help_str = "Help";
STRING *editor_view_str = "View";
STRING *editor_episode_str = "Episode";
STRING *editor_map_str = "Map";

float get_hsv_from_color(float value);

float get_color_from_hsv(float value);

void editor_create_tooltip(char *tooltip);

void editor_help_maker(char *desc);

void editor_camera_resize();

#endif