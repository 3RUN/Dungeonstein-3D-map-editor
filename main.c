
#include <acknex.h>
#include <windows.h>
#include <strio.c>

// KNOWN ISSUE
// - due to 'camera_auto_resize()' pp shader causes issues on the lower edge of the screen (not gonna happen in game)

#define PRAGMA_POINTER

#define PRAGMA_PATH "assets"
#define PRAGMA_PATH "code"
#define PRAGMA_PATH "code\\fx"
#define PRAGMA_PATH "music"

#define TRACE_FLAGS (IGNORE_ME | IGNORE_PASSABLE | IGNORE_PASSENTS | IGNORE_MAPS | IGNORE_CONTENT)
#define MOVE_FLAGS (IGNORE_ME | IGNORE_PASSABLE | IGNORE_PASSENTS | IGNORE_MAPS | IGNORE_CONTENT)

#define MAX_ENTITIES 9999

#define MAP_WIDTH 31
#define MAP_HEIGHT 31
#define MAP_CELL_SIZE 32
#define MAP_Z_POS 0

#define EDITOR_STATE_START 0
#define EDITOR_STATE_EDIT 1
#define EDITOR_STATE_NEW 2
#define EDITOR_STATE_OPEN 3
#define EDITOR_STATE_EXIT 4

#define EDITOR_POPUP_STATE_NEW 0
#define EDITOR_POPUP_STATE_OPEN 1
#define EDITOR_POPUP_STATE_SETTINGS 2
#define EDITOR_POPUP_STATE_EXIT 3
#define EDITOR_POPUP_STATE_WAIT_FOR_INPUT 4
#define EDITOR_POPUP_STATE_CONFIRM_OPEN 5
#define EDITOR_POPUP_STATE_CONFIRM_NEW 6
#define EDITOR_POPUP_STATE_SAVE_AS 7
#define EDITOR_POPUP_STATE_EP_RESET 8
#define EDITOR_POPUP_STATE_EP_EDIT 9
#define EDITOR_POPUP_STATE_MAP_RESET 10
#define EDITOR_POPUP_STATE_HELP 11
#define EDITOR_POPUP_STATE_ASSET_LIST 12
#define EDITOR_POPUP_STATE_MUSIC_BROWSER 13

#define EDITOR_TOP_BAR_HEIGHT 16

#define DIRECTION_RANDOMNESS 2 // default 2
#define MAX_DIRECTION_STEP 4   // cardinal directions
#define TOP 0
#define RIGHT 1
#define BOTTOM 2
#define LEFT 3

#define ASSET_PREVIEW_TEXTURE_WIDTH 64
#define ASSET_PREVIEW_TEXTURE_HEIGHT 64
#define ASSETS_IN_THE_ROW 8

#define ASSET_LIST_BUTTON_ID_WALL 0
#define ASSET_LIST_BUTTON_ID_CEILING 1
#define ASSET_LIST_BUTTON_ID_FLOOR 2
#define ASSET_LIST_BUTTON_ID_OBJECT 3

#define ASSET_LIST_CATEGORY_EVENTS 0
#define ASSET_LIST_CATEGORY_PROPS 1
#define ASSET_LIST_CATEGORY_ITEMS 2
#define ASSET_LIST_CATEGORY_ENEMIES 3
#define ASSET_LIST_CATEGORY_BOSSES 4

#define DRAWING_MODE_MAP 0
#define DRAWING_MODE_OBJECT 1

#define OBJ_TYPE skill50
#define OBJ_INDEX skill51
#define OBJ_FLAG_0 skill52
#define OBJ_FLAG_1 skill53
#define OBJ_FLAG_2 skill54
#define OBJ_FLAG_3 skill55

#define LIGHT_LIGHTRANGE 32
#define WATER_LIGHTRANGE 32
#define TELEPORT_LIGHTRANGE 32

STRING *editor_config_file_str = "editor_config.ini";
STRING *project_name_str = "MapEditor";
STRING *episode_save_folder_str = "episodes\\";
STRING *episode_music_folder_str = "music\\";
STRING *episode_extension_str = ".ep";
STRING *music_extension_str = ".mp3";

int editor_state = EDITOR_STATE_START;
int editor_previous_state = EDITOR_STATE_START;

int editor_popup_state = EDITOR_POPUP_STATE_NEW;
int editor_popup_previous_state = EDITOR_POPUP_STATE_NEW;

int is_asset_list_visible = false;
int is_sidebuttons_used = false;
int is_topbar_used = false;
int is_popup_opened = false;
int is_popup_check_failed = false;
int is_esc_allowed = false;
int is_esc_popup_allowed = false;

int is_map_copied = false;
int is_grid_visible = true;
int is_debug_panel_visible = false;
int is_d3d_lines_visible = false;
int is_markers_visible = true;
int is_bbox_visible = true;
int is_cell_links_visible = true;
int is_selected_cell_visible = true;
int is_mouse_cell_visible = true;

int is_map_settings_visible = false;
int is_lights_on = false;

int mouse_grid_pos_x = 0;
int mouse_grid_pos_y = 0;

int active_map_id = 0;

int drawing_mode = 0; // 0 - map mesh, 1 - objects
int drawing_mode_last = 0;

int category_button_id = ASSET_LIST_BUTTON_ID_WALL; // 0 - walls, 1 - ceiling, 2 - floor, 3 - marker
int category_last_id = ASSET_LIST_BUTTON_ID_WALL;
int category_object_tab = ASSET_LIST_CATEGORY_EVENTS; // 0 - props, 1 - events, 2 - items, 3 - weapons, 4 - enemies, 5 - bosses

VECTOR cardinal_dir[MAX_DIRECTION_STEP]; // west/north/east/south
var cardinal_rot[MAX_DIRECTION_STEP];	 // west/north/east/south

ENTITY *ground_ent;
ENTITY *hovering_ent;

#include "cmd.h"
#include "imgui.h"
#include "ini.h"
#include "dynamic_array.h"
#include "savedir.h"
#include "screenres_list.h"
#include "engine.h"
#include "config.h"
#include "draw.h"
#include "debug_panel.h"
#include "grid.h"
#include "messages.h"
#include "assets.h"
#include "shaders.h"
#include "episode.h"
#include "object_params.h"
#include "object_linker.h"
#include "lightstyle.h"
#include "map_funcs.h"
#include "map_loader.h"
#include "camera.h"
#include "editor.h"
#include "map_draw.h"
#include "shortcuts.h"
#include "compass.h"

#include "engine.c"
#include "config.c"

void map_editor_startup()
{
	set_savedir();
	wait_for(set_savedir);

	// set proper path to the config file
	STRING *temp_str = "#256";
	str_cpy(temp_str, editor_config_file_str);
	path_make_absolute(temp_str); // add 'save_dir' full path (in documents folder)

	screen_resolutions_find_all(); // find all available screen resolution (primary monitor only)
	engine_initialize();		   // all engine settings
	assets_initialize();		   // all editor assets
	imgui_init(0);				   // imgui
	imgui_change_theme();		   // and apply custom theme
	config_initialize(temp_str);   // config (set defaults and load from the config file)
	messages_initialize();		   // message system
	debug_panel_initialize();	   // debug panel
	camera_initialize();		   // camera settings
	shaders_initialize();		   // shaders

	episode_initialize();		  // default episode, preview cell, map settings, etc
	episode_scanner_initialize(); // scan episode/music folders
	popups_initialize();		  // all editor popups (settings, open episide, etc)
	object_params_initialize();	  // object params (activation, id, etc)
	map_loader_initialize();	  // map loading
	map_draw_initialize();		  // map drawing
	lightstyles();				  // update lightstyle for lights (flickering, liquids and teleport pulse)
	compass_initialize();		  // compass that shows cardinal directions
}

void on_frame_event()
{
	switch (editor_state)
	{
	case EDITOR_STATE_START:
		editor_start_update(&def_episode);
		break;

	case EDITOR_STATE_EDIT:
		editor_update(&def_episode);
		map_draw_update(&def_episode);
		object_linker_update(&def_episode);
		grid_update();
		break;

	case EDITOR_STATE_NEW:
		map_destroy();
		episode_copy(&def_episode, NULL);
		episode_edit_info(&def_episode, new_episode_name, new_episode_map_count);
		episode_set_filename(_str(new_episode_filename));
		episode_save(ep_filename, &def_episode);
		editor_switch_state_to(EDITOR_STATE_EDIT);
		break;

	case EDITOR_STATE_OPEN:
		map_destroy();
		episode_copy(&def_episode, NULL);
		episode_set_filename(_str(selected_episode));
		episode_load(ep_filename, &def_episode);
		wait_for(episode_load);

		Map *active_map = map_get_active(&def_episode);
		map_load(active_map);
		editor_switch_state_to(EDITOR_STATE_EDIT);
		break;

	case EDITOR_STATE_EXIT:
		sys_exit(NULL);
		break;
	}

	camera_update();
	shaders_update();
	compass_update();
	messages_update();
	debug_panel_update();
	mouse_lock_in_window();
}

void on_exit_event()
{
	messages_destroy();
	debug_panel_destroy();
	shaders_destroy();
	assets_destroy();
	object_params_destroy();
	object_linker_destroy();
	popups_destroy();
	episode_scanner_destroy();
	map_draw_destroy();
	map_destroy();
	compass_destroy();
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