#ifndef _EDITOR_H_
#define _EDITOR_H_

#define EDITOR_TOP_BAR_HEIGHT 16
#define EDITOR_SIDE_BAR_WIDTH 280

STRING *direction_tga = "direction.tga";

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
STRING *editor_view_cell_links_str = "Cell links";
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

STRING *editor_semicolon_str = ";";
STRING *editor_info_main_str = "world position:\nx = %d; y = %d; z = %d;\n\ngrid position:\nx = %d; y = %d;\n\npan = %.0f;\nid = %d;";
STRING *editor_info_type_wall_str = "\ntype = wall;";
STRING *editor_info_type_props_str = "\ntype = props;";
STRING *editor_info_type_event_str = "\ntype = event;";
STRING *editor_info_type_item_str = "\ntype = item;";
STRING *editor_info_type_enemy_str = "\ntype = enemy;";
STRING *editor_info_type_boss_str = "\ntype = boss;";
STRING *editor_info_desc_str = "\ndesc = ";
STRING *editor_info_params_str = "\n\nparams:";
STRING *editor_info_wall_secret_str = "\n* secret wall;";
STRING *editor_info_wall_solid_str = "\n* solid wall;";
STRING *editor_info_activation_str = "\n* activation: ";
STRING *editor_info_on_interaction_str = "on interaction;";
STRING *editor_info_on_creation_str = "on creation;";
STRING *editor_info_trigger_zone_id_str = "trigger zone id = %d;";
STRING *editor_info_switch_id_str = "switch id = %d;";
STRING *editor_info_key_requires_str = "\n* requires: ";
STRING *editor_info_props_switch_id_str = "\n* id: %d;";
STRING *editor_info_event_trigger_zone_id_str = "\n* id: %d;";
STRING *editor_info_event_spawn_str = "\n* spawn: ";
STRING *editor_info_drop_item_str = "\n* drop item: ";
STRING *editor_info_drop_item_false_str = "\n* drop item: false;";
STRING *editor_info_enemy_behaviour_str = "\n* behaviour: ";
STRING *editor_info_enemy_behaviour_wait_str = "wait";
STRING *editor_info_enemy_behaviour_deaf_str = "deaf";
STRING *editor_info_enemy_behaviour_patrol_str = "patrol";

void editor_create_tooltip(char *tooltip);

void editor_help_maker(char *desc);

void editor_camera_resize();

STRING *get_cell_info(Cell *cell);

STRING *draw_map_info(Map *current_map, int x, int y);

#endif