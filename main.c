#include <acknex.h>
#include <windows.h>
#include <default.c>

#define PRAGMA_POINTER

#define PRAGMA_PATH "assets"
#define PRAGMA_PATH "code"

STRING *config_file_str = "config.ini";
STRING *project_name_str = "MapEditor"; // insert your project's name here !

STRING *grid_cursor_tga = "cursor.tga";
STRING *tile_mdl = "tile.mdl";

#define MAP_WIDTH 31
#define MAP_HEIGHT 31
#define MAP_TOTAL_CELLS 961 // MAP_WIDTH * MAP_HEIGHT
#define MAP_CELL_SIZE 32

int mouse_x = 0;
int mouse_y = 0;

int current_map_id = 0;

int is_settings_opened = false;
int is_editor_popup_on = false;

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
#include "editor.h"
#include "editor_cam.h"
#include "editor_grid.h"
#include "editor_episode.h"
#include "editor_main_ui.h"

#include "savedir.c"
#include "screenres_list.c"
#include "engine.c"
#include "config.c"
#include "assets.c"
#include "game_episode.c"
#include "editor.c"
#include "editor_cam.c"
#include "editor_grid.c"
#include "editor_episode.c"
#include "editor_main_ui.c"

Episode def_episode;

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

	imgui_init(0);			  // initialize imgui
	imgui_change_theme();	  // and apply custom theme
	assets_initialize();	  // initialize all assets
	camera_initialize();	  // initialize camera
	grid_initialize();		  // initialize grid
	editor_main_initialize(); // initialize main ui
}

void on_frame_event()
{
	switch (editor_state)
	{
	case STATE_NEW:
		grid_clear();
		editor_camera_resize(false);
		editor_main_reset();
		episode_reset(&def_episode);

		strcpy(def_episode.name, "a");
		strcpy(def_episode.story, "abc");
		def_episode.map_count = 2;

		editor_switch_state_to(STATE_EPISODE);
		break;

	case STATE_EPISODE:
		editor_episode_update(&def_episode);
		break;

	case STATE_EDITOR:
		grid_get_mouse_pos(&mouse_x, &mouse_y);
		editor_main_update(&def_episode);
		camera_update();
		grid_update();
		break;

	case STATE_TEST:
		break;
	}

	mouse_lock_in_window();
}

void on_exit_event()
{
	assets_destroy();
	grid_destroy();
	editor_main_destroy();
}

void on_esc_event()
{
}

void main()
{
	max_entities = (MAP_TOTAL_CELLS * 3) + 100;

	on_d3d_lost = imgui_reset;
	on_scanmessage = custom_scan_message;

	on_frame = on_frame_event;
	on_exit = on_exit_event;
	on_esc = on_esc_event;

	level_load("");
}