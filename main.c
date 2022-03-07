#include <acknex.h>
#include <windows.h>
#include <default.c>
#include <strio.c>

// to do
//
// * add connection (draw_line3d) between cells with similar ID
// * add proper functions for test build state

#define PRAGMA_POINTER

#define PRAGMA_PATH "code"
#define PRAGMA_PATH "assets"
#define PRAGMA_PATH "assets\\walls"
#define PRAGMA_PATH "assets\\props"
#define PRAGMA_PATH "assets\\events"
#define PRAGMA_PATH "assets\\items"
#define PRAGMA_PATH "assets\\enemies"
#define PRAGMA_PATH "assets\\bosses"

STRING *config_file_str = "config.ini";
STRING *project_name_str = "MapEditor"; // insert your project's name here !
STRING *episode_save_folder_str = "episodes\\";
STRING *episode_music_folder_str = "music\\";
STRING *episode_extension_str = ".ep"; // this added to the episode's file name on load/save
STRING *music_extension_str = ".mid";  // only mid music is used

#define MAX_ENTITIES 9999

#define OBJ_ID skill50
#define OBJ_POS_X skill51
#define OBJ_POS_Y skill52
#define OBJ_POS_Z skill53
#define OBJ_TYPE_INDEX skill54
#define OBJ_ASSET_INDEX skill55

#define CAMERA_ARC 90

#define MAP_WIDTH 31
#define MAP_HEIGHT 31
#define MAP_CELL_SIZE 32

#define EDITOR_STATE_EMPTY 0
#define EDITOR_STATE_OPEN 1
#define EDITOR_STATE_NEW 2
#define EDITOR_STATE_SAVE_US 3
#define EDITOR_STATE_EDIT_MAP 4
#define EDITOR_STATE_TO_MAP_SETTINGS 5
#define EDITOR_STATE_MAP_SETTINGS 6
#define EDITOR_STATE_FROM_MAP_SETTINGS 7
#define EDITOR_STATE_TO_TEST_BUILD 8
#define EDITOR_STATE_TEST_BUILD 9
#define EDITOR_STATE_FROM_TEST_BUILD 10
#define EDITOR_STATE_RESET_MAP 11
#define EDITOR_STATE_EXIT 12

int editor_state = EDITOR_STATE_EMPTY;
int editor_old_state = EDITOR_STATE_EMPTY;

// gui booleans
int is_popup_opened = false; // true when any popup was opened
int is_top_bar_used = false; // true when top bar's contex menu is opened

// view booleans
int is_grid_visible = true;
int is_walls_visible = true;
int is_objects_visible = true;
int is_connections_visible = true;

int mouse_x = 0;
int mouse_y = 0;

int current_map_id = 0;

#include "cmd.h"
#include "imgui.h"
#include "ini.h"
#include "dynamic_array.h"
#include "savedir.h"
#include "screenres_list.h"
#include "engine.h"
#include "config.h"
#include "assets.h"
#include "game_episode.h"
#include "game_episode_save_n_load.h"
#include "game_build_map.h"
#include "editor.h"
#include "editor_episode_list.h"
#include "editor_popups.h"
#include "editor_empty.h"
#include "editor_map.h"
#include "editor_map_settings.h"
#include "editor_music_browser.h"
#include "editor_grid_sprites.h"
#include "editor_cam_n_grid.h"
#include "editor_obj_params.h"
#include "editor_mouse_draw.h"
#include "weather.h"

Episode def_episode;

void editor_switch_state_to(int new_state)
{
	editor_old_state = editor_state;
	editor_state = new_state;
}

#include "savedir.c"
#include "screenres_list.c"
#include "engine.c"
#include "config.c"
#include "assets.c"
#include "game_episode.c"
#include "game_episode_save_n_load.c"
#include "game_build_map.c"
#include "editor.c"
#include "editor_episode_list.c"
#include "editor_popups.c"
#include "editor_empty.c"
#include "editor_map.c"
#include "editor_map_settings.c"
#include "editor_music_browser.c"
#include "editor_grid_sprites.c"
#include "editor_cam_n_grid.c"
#include "editor_obj_params.c"
#include "editor_mouse_draw.c"
#include "weather.c"

void editor_reset()
{
	editor_map_reset();

	current_map_id = 0;

	mouse_x = 0;
	mouse_y = 0;

	cell_info_tooltip_counter = 0;

	is_grid_visible = true;
	is_walls_visible = true;
	is_objects_visible = true;
	is_connections_visible = true;
}

void map_editor_startup()
{
	// set launcher window
	// check for existing game folder or create new one
	savedir_create_folder();
	wait_for(savedir_create_folder);

	// set proper path to the config file
	STRING *temp_str = "#256";
	str_cpy(temp_str, config_file_str);
	path_make_absolute(temp_str); // add 'save_dir' full path (in documents folder)

	screen_resolutions_find_all(); // find all available screen resolution (primary monitor only)
	config_initialize(temp_str);   // initialize config (set defaults and load from the config file)engine_initialize()
	engine_initialize();		   // initialize all engine settings
	assets_initialize();		   // load all editor assets (textures, sprites)
	imgui_init(0);				   // initialize imgui
	imgui_change_theme();		   // and apply custom theme

	game_build_map_initialize(); // initialize everything for building the map

	editor_map_initialize();				// initialize everything related to the main editor ui (preview, etc)
	editor_episode_list_initialize();		// initialize everything to load list of episodes from episodes folder
	editor_popups_initialize(&def_episode); // initialize all popups used in editor
	editor_map_settings_initialize();		// initialize map settings
	editor_music_browser_initialize();		// initialize music loading
	editor_camera_initialize();				// initialize camera and visual grid
	editor_grid_sprites_create();			// create all sprites that will visualize the map
}

void on_frame_event()
{
	Map *current_map = map_get_active(&def_episode);

	switch (editor_state)
	{
	case EDITOR_STATE_EMPTY:
		editor_empty_update(&def_episode);
		break;

	case EDITOR_STATE_OPEN:
		editor_reset();
		episode_reset(&def_episode);
		episode_save_name_udpate(_str(selected_episode));
		episode_load(episode_save_name, &def_episode);
		editor_grid_sprites_refresh(&def_episode);
		editor_switch_state_to(EDITOR_STATE_EDIT_MAP);
		break;

	case EDITOR_STATE_NEW:
		editor_reset();
		episode_reset(&def_episode);
		episode_change_info(&def_episode, new_name, new_start_story, new_end_story, new_map_count);
		episode_save_name_udpate(_str(new_filename));
		episode_save(episode_save_name, &def_episode);
		editor_grid_sprites_refresh(&def_episode);
		editor_switch_state_to(EDITOR_STATE_EDIT_MAP);
		break;

	case EDITOR_STATE_SAVE_US:
		episode_save_name_udpate(_str(save_as_filename));
		episode_save(episode_save_name, &def_episode);
		editor_switch_state_to(EDITOR_STATE_EDIT_MAP);
		break;

	case EDITOR_STATE_EDIT_MAP:
		editor_grid_get_mouse_pos(&mouse_x, &mouse_y);
		editor_map_update(&def_episode);
		editor_camera_n_grid_update();
		break;

		// map settings
	case EDITOR_STATE_TO_MAP_SETTINGS:
		cell_info_tooltip_counter = 0; // reset tooltip counter
		editor_grid_sprites_hide();
		editor_map_settings_show(current_map);
		editor_camera_in_map_settings();
		editor_switch_state_to(EDITOR_STATE_MAP_SETTINGS);
		break;

	case EDITOR_STATE_MAP_SETTINGS:
		editor_map_settings_update(&def_episode);
		break;

	case EDITOR_STATE_FROM_MAP_SETTINGS:
		editor_camera_restore_pos_n_angle();
		editor_grid_sprites_show(&def_episode);
		editor_map_settings_hide();
		editor_grid_sprites_refresh(&def_episode);
		weather_stop_sound();
		editor_switch_state_to(EDITOR_STATE_EDIT_MAP);
		break;

		// map test build
	case EDITOR_STATE_TO_TEST_BUILD:
		cell_info_tooltip_counter = 0; // reset tooltip counter
		weather_play_sound(current_map->weather_id);
		editor_camera_in_map_settings(); // set camera to the nullvector position
		editor_grid_sprites_hide();
		game_build_map(&def_episode);
		editor_switch_state_to(EDITOR_STATE_TEST_BUILD);
		break;

	case EDITOR_STATE_TEST_BUILD:
		game_build_map_update(&def_episode);
		editor_camera_in_test_build();
		break;

	case EDITOR_STATE_FROM_TEST_BUILD:
		weather_stop_sound();
		editor_camera_restore_pos_n_angle();
		game_build_map_free();
		editor_grid_sprites_show(&def_episode);
		editor_switch_state_to(EDITOR_STATE_EDIT_MAP);
		break;

		// reset current map
	case EDITOR_STATE_RESET_MAP:
		map_reset(current_map);
		editor_grid_sprites_refresh(&def_episode);
		editor_switch_state_to(EDITOR_STATE_EDIT_MAP);
		break;

	case EDITOR_STATE_EXIT:
		sys_exit(NULL);
		break;
	}

	editor_camera_resize();
	mouse_lock_in_window();
}

void on_exit_event()
{
	assets_destroy_all();
	game_build_map_destroy();

	editor_map_destroy();
	editor_episode_list_destroy();
	editor_popups_destroy();
	editor_map_settings_destroy();
	editor_music_browser_destroy();
	editor_grid_sprites_destroy();
}

void on_esc_event()
{
}

void on_f_event(var scancode)
{
	switch (scancode)
	{
	case 59: // f1
		break;

	case 60: // f2
		break;

	case 61: // f3
		break;

	case 62: // f4
		break;

	case 63: // f5
		break;

	case 64: // f6
		def_shot();
		break;

	case 65: // f7
		break;

	case 66: // f8
		break;

	case 67: // f9
		break;

	case 68: // f10
		break;

	case 87: // f11
		def_debug();
		break;

	case 88: // f12
		break;
	}
}

void main()
{
	max_entities = MAX_ENTITIES;

	on_d3d_lost = imgui_reset;
	on_scanmessage = custom_scan_message;

	on_frame = on_frame_event;
	on_exit = on_exit_event;
	on_esc = on_esc_event;

	on_f1 = on_f_event;
	on_f2 = on_f_event;
	on_f3 = on_f_event;
	// on_f4 = on_f_event;
	on_f5 = on_f_event;
	on_f6 = on_f_event;
	on_f7 = on_f_event;
	on_f8 = on_f_event;
	on_f9 = on_f_event;
	on_f10 = on_f_event;
	on_f11 = on_f_event;
	on_f12 = on_f_event;

	level_load("");
}