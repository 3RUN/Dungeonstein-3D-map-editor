
#include <acknex.h>
#include <windows.h>
#include <strio.c>

#define PRAGMA_POINTER

#define PRAGMA_PATH "code"
#define PRAGMA_PATH "assets"
#define PRAGMA_PATH "assets\\walls"
#define PRAGMA_PATH "assets\\props"
#define PRAGMA_PATH "assets\\events"
#define PRAGMA_PATH "assets\\items"
#define PRAGMA_PATH "assets\\enemies"
#define PRAGMA_PATH "assets\\bosses"

STRING *editor_config_file_str = "editor_config.ini";
STRING *project_name_str = "MapEditor";
STRING *episode_save_folder_str = "episodes\\";
STRING *episode_music_folder_str = "music\\";
STRING *episode_extension_str = ".ep"; // this added to the episode's file name on load/save
STRING *music_extension_str = ".mid";  // only mid music is used

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
#include "engine_keybind.h"
#include "debug_panel.h"
#include "config.h"
#include "assets.h"
#include "shaders.h"
#include "game_ep.h"
#include "game_ep_list.h"
#include "game_music_list.h"
#include "game_ep_save_n_load.h"
#include "assets_helper.h"
#include "editor.h"
#include "editor_msg.h"
#include "editor_shortcuts.h"
#include "editor_input.h"
#include "editor_cam_n_grid.h"
#include "editor_popups.h"
#include "editor_asset_params.h"
#include "editor_map_sketch.h"
#include "editor_draw_tools.h"
#include "editor_cell_linker.h"
#include "editor_cell_info.h"
#include "editor_main.h"
#include "editor_test_run.h"
#include "map_loader.h"

void editor_reset()
{
	episode_selection_reset();
	music_selection_reset();

	cell_info_tooltip_counter = 0;

	active_map_id = 0;

	selected_type = ASSET_TYPE_WALLS;
	selected_asset = 0;
}

#include "savedir.c"
#include "screenres_list.c"
#include "engine.c"
#include "engine_keybind.c"
#include "debug_panel.c"
#include "config.c"
#include "assets.c"
#include "shaders.c"
#include "game_ep.c"
#include "game_ep_list.c"
#include "game_music_list.c"
#include "game_ep_save_n_load.c"
#include "assets_helper.c"
#include "editor.c"
#include "editor_msg.c"
#include "editor_shortcuts.c"
#include "editor_input.c"
#include "editor_cam_n_grid.c"
#include "editor_popups.c"
#include "editor_asset_params.c"
#include "editor_map_sketch.c"
#include "editor_draw_tools.c"
#include "editor_cell_linker.c"
#include "editor_cell_info.c"
#include "editor_main.c"
#include "editor_test_run.c"
#include "map_loader.c"

void map_editor_startup()
{
	// set launcher window
	// check for existing game folder or create new one
	savedir_create_folder();
	wait_for(savedir_create_folder);

	// set proper path to the config file
	STRING *temp_str = "#256";
	str_cpy(temp_str, editor_config_file_str);
	path_make_absolute(temp_str); // add 'save_dir' full path (in documents folder)

	screen_resolutions_find_all(); // find all available screen resolution (primary monitor only)
	engine_initialize();		   // initialize all engine settings
	assets_initialize();		   // load all editor assets (textures, sprites)
	debug_panel_initialize();	   // initialize debug panel
	shaders_initialize();		   // initialize all shaders used in editor
	imgui_init(0);				   // initialize imgui
	imgui_change_theme();		   // and apply custom theme
	config_initialize(temp_str);   // initialize config (set defaults and load from the config file)engine_initialize()

	messages_initialize();				 // initialize editor message system
	episode_list_initialize();			 // load all episodes from 'episodes' folder
	music_list_initialize();			 // same as above, but for music
	camera_initialize();				 // initialize all camera
	popups_initialize();				 // initialize popups
	map_sketch_initialize();			 // grid of entities to visualize the map while drawing it
	editor_main_initialize();			 // initialize everything related to drawing/editing state ui
	episode_reset(&def_episode);		 // initialize default episode with default values
	map_loader_initialize(&def_episode); // initialize everything needed for test building the maps
}

void on_frame_event()
{
	Map *active_map = map_get_active(&def_episode);

	switch (editor_state)
	{
	case EDITOR_STATE_EDIT:
		grid_get_mouse_pos(&mouse_x, &mouse_y);
		editor_main_update(&def_episode);
		map_sketch_update(&def_episode);
		tools_update(active_map, &preview_cell);
		editor_cell_linker_update(active_map);
		break;

	case EDITOR_STATE_OPEN:
		episode_reset(&def_episode);
		episode_save_name_udpate_to(_str(selected_episode));
		episode_load(ep_save_name, &def_episode);
		map_sketch_refresh(active_map);
		editor_reset();
		editor_switch_state_to(EDITOR_STATE_EDIT);
		break;

	case EDITOR_STATE_NEW:
		episode_reset(&def_episode);
		episode_change_info(&def_episode, new_episode_name, new_episode_story_start, new_episode_story_end, new_episode_map_count);
		episode_save_name_udpate_to(_str(new_episode_filename));
		episode_save(ep_save_name, &def_episode);
		map_sketch_refresh(active_map);
		editor_reset();
		editor_switch_state_to(EDITOR_STATE_EDIT);
		break;

	case EDITOR_STATE_SAVE:
		episode_save(ep_save_name, &def_episode);
		editor_switch_state_to(editor_old_state);
		break;

	case EDITOR_STATE_TO_MAP_SETTINGS:
		camera_reset(active_map, EDITOR_STATE_MAP_SETTINGS);
		editor_switch_state_to(EDITOR_STATE_MAP_SETTINGS);
		break;

	case EDITOR_STATE_MAP_SETTINGS:
		break;

	case EDITOR_STATE_FROM_MAP_SETTINGS:
		camera_reset(active_map, EDITOR_STATE_EDIT);
		editor_switch_state_to(EDITOR_STATE_EDIT);
		break;

	case EDITOR_STATE_TO_BUILD:
		editor_reset();
		map_sketch_hide();
		map_load(active_map);
		camera_reset(active_map, EDITOR_STATE_BUILD);
		editor_switch_state_to(EDITOR_STATE_BUILD);
		break;

	case EDITOR_STATE_BUILD:
		editor_test_run_update(&def_episode);
		break;

	case EDITOR_STATE_FROM_BUILD:
		map_sketch_show();
		map_destroy(active_map);
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

	ENTITY *cell_ent = array_get_element_at(ENTITY *, sketch_ents, 0);
	if (cell_ent)
	{
		var type = cell_ent->OBJ_TYPE;
		var asset = cell_ent->OBJ_ASSET;

		DEBUG_VAR(type, 300);
		DEBUG_VAR(asset, 320);
	}

	debug_panel_update();
	shaders_update();
	camera_n_grid_update(&def_episode);
	messages_update();
	mouse_lock_in_window();

	draw_point3d(nullvector, COLOR_RED, 100, 1);

	if (key_f4 && key_alt)
	{
		sys_exit(NULL);
	}
}

void on_exit_event()
{
	assets_destroy_all();
	debug_panel_destroy();
	shaders_destroy();
	messages_destroy();
	episode_list_destroy();
	music_list_destroy();
	popups_destroy();
	map_sketch_destroy();
	editor_main_destroy();
	editor_cell_linker_destroy();
	map_loader_destroy();
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