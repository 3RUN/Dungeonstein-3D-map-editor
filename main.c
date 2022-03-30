
#include <acknex.h>
#include <windows.h>
#include <strio.c>

#define PRAGMA_POINTER

#define PRAGMA_PATH "code"
#define PRAGMA_PATH "assets"
#define PRAGMA_PATH "assets\\animated"
#define PRAGMA_PATH "assets\\walls"
#define PRAGMA_PATH "assets\\props"
#define PRAGMA_PATH "assets\\events"
#define PRAGMA_PATH "assets\\effects"
#define PRAGMA_PATH "assets\\items"
#define PRAGMA_PATH "assets\\enemies"
#define PRAGMA_PATH "assets\\bosses"

#define TRACE_FLAGS (IGNORE_ME | IGNORE_PASSABLE | IGNORE_PASSENTS | IGNORE_MAPS | IGNORE_CONTENT)
#define MOVE_FLAGS (IGNORE_ME | IGNORE_PASSABLE | IGNORE_PASSENTS | IGNORE_MAPS | IGNORE_CONTENT)

#define MAX_ENTITIES 9999

#define MAP_WIDTH 31
#define MAP_HEIGHT 31
#define MAP_CELL_SIZE 32
#define MAP_Z_POS 0

#define OBJ_ID skill50
#define OBJ_POS_X skill51
#define OBJ_POS_Y skill52
#define OBJ_POS_Z skill53
#define OBJ_TYPE skill54
#define OBJ_ASSET skill55
#define OBJ_FLAG skill56
#define OBJ_EVENT_TYPE skill57
#define OBJ_EVENT_ID skill58
#define OBJ_TEMP_SKILL skill59
#define OBJ_TRIGGERED skill60

#define EDITOR_STATE_EDIT 0
#define EDITOR_STATE_OPEN 1
#define EDITOR_STATE_NEW 2
#define EDITOR_STATE_SAVE 3
#define EDITOR_STATE_TO_MAP_SETTINGS 4
#define EDITOR_STATE_MAP_SETTINGS 5
#define EDITOR_STATE_FROM_MAP_SETTINGS 6
#define EDITOR_STATE_TO_BUILD 7
#define EDITOR_STATE_BUILD 8
#define EDITOR_STATE_FROM_BUILD 9
#define EDITOR_STATE_RESET_EPISODE 10
#define EDITOR_STATE_RESET_MAP 11
#define EDITOR_STATE_EXIT 12

STRING *editor_config_file_str = "editor_config.ini";
STRING *project_name_str = "MapEditor";
STRING *episode_save_folder_str = "episodes\\";
STRING *episode_music_folder_str = "music\\";
STRING *episode_extension_str = ".ep";
STRING *music_extension_str = ".mp3";

// editor state machine
int editor_state = EDITOR_STATE_EDIT;
int editor_old_state = EDITOR_STATE_EDIT;

// editor booleans
int is_top_bar_used = false;
int is_popup_opened = false;
int is_popup_check_failed = false;
int is_esc_allowed = false;
int is_esc_popup_allowed = false;

// view booleans
int is_grid_visible = true;
int is_walls_visible = true;
int is_objects_visible = true;
int is_cell_links_visible = true;
int is_debug_panel_visible = false;

// mouse position on the grid
int mouse_x = 0;
int mouse_y = 0;

#include "cmd.h"
#include "imgui.h"
#include "ini.h"
#include "dynamic_array.h"
#include "savedir.h"
#include "screenres_list.h"
#include "engine.h"
#include "config.h"
#include "assets.h"
#include "assets_helper.h"
#include "assets_params.h"
#include "shaders.h"
#include "weather.h"
#include "messages.h"
#include "debug_panel.h"
#include "draw.h"
#include "game_episode.h"
#include "camera_n_grid.h"
#include "editor.h"
#include "editor_popups.h"
#include "editor_cell_linker.h"
#include "editor_tools.h"
#include "editor_map_settings.h"
#include "editor_test_run.h"
#include "shortcuts.h"
#include "map_load.h"
#include "map_sketch.h"

#include "engine.c"
#include "config.c"
#include "assets_helper.c"
#include "assets_params.c"
#include "camera_n_grid.c"
#include "editor.c"
#include "editor_popups.c"
#include "editor_cell_linker.c"
#include "editor_tools.c"
#include "editor_map_settings.c"
#include "editor_test_run.c"
#include "shortcuts.c"
#include "map_load.c"
#include "map_sketch.c"

void map_editor_startup()
{
	set_savedir();
	wait_for(set_savedir);

	// set proper path to the config file
	STRING *temp_str = "#256";
	str_cpy(temp_str, editor_config_file_str);
	path_make_absolute(temp_str); // add 'save_dir' full path (in documents folder)

	screen_resolutions_find_all(); // find all available screen resolution (primary monitor only)
	engine_initialize();		   // initialize all engine settings
	imgui_init(0);				   // initialize imgui
	imgui_change_theme();		   // and apply custom theme
	config_initialize(temp_str);   // initialize config (set defaults and load from the config file)engine_initialize()
	assets_initialize();		   // initialize assets
	messages_initialize();		   // initialize editor message system
	debug_panel_initialize();	   // initialize debug panel
	game_episode_initialize();	   // initialize everything related to game episode

	episode_reset(&def_episode);		 // reset default episode
	camera_n_grid_initialize();			 // initialize camera and grid systems
	editor_initialize(&def_episode);	 // initialize main editor system
	map_loader_initialize(&def_episode); // initialize everything needed for test building the maps
	map_sketch_initialize();			 // initialize map sketcher
}

void on_frame_event()
{
	DEBUG_VAR(props_count, 200);
	DEBUG_VAR(array_get_count(map_props), 220);

	Map *active_map = map_get_active(&def_episode);

	switch (editor_state)
	{
	case EDITOR_STATE_EDIT:
		editor_update(&def_episode, active_map);
		editor_tools_update(active_map, &preview_cell);
		editor_cell_linker_update(active_map);
		map_sketch_update(&def_episode);
		break;

	case EDITOR_STATE_OPEN:
		episode_reset(&def_episode);
		episode_save_name_udpate_to(_str(selected_episode));
		episode_load(ep_save_name, &def_episode);
		editor_reset();

		STRING *temp_ep_name_str = "";
		str_cpy(temp_ep_name_str, "Episode ");
		str_cat(temp_ep_name_str, _str(ep_save_name));
		str_cat(temp_ep_name_str, " opened.");
		message_add(temp_ep_name_str);

		Map *map = map_get_active(&def_episode); // because 'active_map' won't return 1 frame old map
		map_sketch_refresh(map);
		editor_switch_state_to(EDITOR_STATE_EDIT);
		break;

	case EDITOR_STATE_NEW:
		episode_reset(&def_episode);
		episode_change_info(&def_episode, new_episode_name, new_episode_story_start, new_episode_story_end, new_episode_map_count);
		episode_save_name_udpate_to(_str(new_episode_filename));
		episode_save(ep_save_name, &def_episode);
		editor_reset();
		episode_list_refresh();

		STRING *temp_ep_name_str = "";
		str_cpy(temp_ep_name_str, "Episode ");
		str_cat(temp_ep_name_str, _str(ep_save_name));
		str_cat(temp_ep_name_str, " created.");
		message_add(temp_ep_name_str);

		map_sketch_refresh(active_map);
		editor_switch_state_to(EDITOR_STATE_EDIT);
		break;

	case EDITOR_STATE_SAVE:
		episode_save(ep_save_name, &def_episode);
		editor_switch_state_to(editor_old_state);
		break;

	case EDITOR_STATE_TO_MAP_SETTINGS:
		editor_reset();
		map_load(active_map);
		map_sketch_hide();
		editor_map_settings_copy_from_active(active_map);
		camera_reset(active_map, EDITOR_STATE_MAP_SETTINGS);
		editor_switch_state_to(EDITOR_STATE_MAP_SETTINGS);
		break;

	case EDITOR_STATE_MAP_SETTINGS:
		editor_map_settings_update(active_map);
		map_update(&map_settings);
		break;

	case EDITOR_STATE_FROM_MAP_SETTINGS:
		weather_stop_sound();
		stop_playing_music();
		map_destroy(active_map);
		map_sketch_show();
		camera_reset(active_map, EDITOR_STATE_EDIT);
		editor_switch_state_to(EDITOR_STATE_EDIT);
		break;

	case EDITOR_STATE_TO_BUILD:
		editor_reset();
		map_load(active_map);
		map_sketch_hide();
		editor_test_run_crosshair_show();
		editor_test_run_select_player_on_start(active_map);
		camera_reset(active_map, EDITOR_STATE_BUILD);
		editor_switch_state_to(EDITOR_STATE_BUILD);
		break;

	case EDITOR_STATE_BUILD:
		editor_test_run_update();
		map_update(active_map);
		editor_cell_linker_update(active_map);
		break;

	case EDITOR_STATE_FROM_BUILD:
		weather_stop_sound();
		stop_playing_music();
		map_destroy(active_map);
		map_sketch_show();
		editor_test_run_crosshair_hide();
		camera_reset(active_map, EDITOR_STATE_EDIT);
		editor_switch_state_to(EDITOR_STATE_EDIT);
		break;

	case EDITOR_STATE_RESET_EPISODE:
		episode_reset(&def_episode);
		map_sketch_refresh(active_map);
		editor_switch_state_to(EDITOR_STATE_EDIT);
		break;

	case EDITOR_STATE_RESET_MAP:
		map_reset(active_map);
		map_sketch_refresh(active_map);
		editor_switch_state_to(EDITOR_STATE_EDIT);
		break;

	case EDITOR_STATE_EXIT:
		sys_exit(NULL);
		break;
	}

	shaders_update();
	messages_update();
	debug_panel_update();
	mouse_lock_in_window();
	camera_n_grid_update(active_map);
	grid_get_mouse_pos(&mouse_x, &mouse_y);
}

void on_exit_event()
{
	assets_destroy();
	messages_destroy();
	debug_panel_destroy();
	game_episode_destroy();
	editor_destroy();
	map_loader_destroy();
	map_sketch_destroy();
	editor_cell_linker_destroy();
}

void on_esc_event()
{
}

void main()
{
	max_entities = MAX_ENTITIES;

	on_d3d_lost = imgui_reset;
	on_scanmessage = custom_scan_message;

	on_frame = on_frame_event;
	on_exit = on_exit_event;
	on_esc = on_esc_event;

	level_load("");
}