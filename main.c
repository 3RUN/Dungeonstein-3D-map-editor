#include <acknex.h>
#include <windows.h>
#include <default.c>
#include <strio.c>

#define PRAGMA_POINTER

#define PRAGMA_PATH "assets"
#define PRAGMA_PATH "code"

STRING *config_file_str = "config.ini";
STRING *project_name_str = "MapEditor"; // insert your project's name here !

#define MAP_WIDTH 31
#define MAP_HEIGHT 31
#define MAP_CELL_SIZE 32

int is_popup_opened = false;
int is_settings_opened = false;
int is_help_opened = false;

int is_grid_visible = true;
int is_walls_visible = true;
int is_objects_visible = true;

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
#include "game_episode.h"
#include "save_n_load.h"
#include "editor.h"
#include "editor_menu.h"
#include "editor_episode.h"
#include "editor_main.h"
#include "editor_cam.h"
#include "editor_grid.h"

#include "savedir.c"
#include "screenres_list.c"
#include "engine.c"
#include "config.c"
#include "assets.c"
#include "game_episode.c"
#include "save_n_load.c"
#include "editor.c"
#include "editor_menu.c"
#include "editor_episode.c"
#include "editor_main.c"
#include "editor_cam.c"
#include "editor_grid.c"

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
	imgui_change_theme();	  //and apply custom theme
	assets_initialize();	  // load all editor assets
	camera_initialize();	  // initialize camera
	grid_initialize();		  // initialize the map grid
	editor_main_initialize(); // initialize main editor interface
}

void on_frame_event()
{
	DEBUG_VAR(editor_asset_type, 200);
	DEBUG_VAR(editor_asset_index, 220);
	
	switch (editor_state)
	{
	case STATE_MENU:
		editor_menu_update(&def_episode);
		break;

	case STATE_LOAD:
		int load_res = episode_load();
		if (load_res == true)
		{
			editor_switch_state_to(STATE_EDITOR);
		}
		else
		{
			editor_switch_state_to(editor_old_state);
		}
		break;

	case STATE_SAVE:
		int save_res = episode_save();
		editor_switch_state_to(editor_old_state);
		break;

	case STATE_NEW:
		grid_clear();
		editor_main_reset();
		episode_reset(&def_episode);
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

	// make camera smaller + move downwards
	// so we can't interact with grid under imgui user interface
	if (editor_state == STATE_EDITOR)
	{
		editor_camera_resize(true);
	}
	else
	{
		editor_camera_resize(false);
	}

	mouse_lock_in_window();
}

void on_exit_event()
{
	assets_destroy();
	grid_destroy();
}

void on_esc_event()
{
	if (is_popup_opened == true)
	{
		return;
	}

	switch (editor_state)
	{
	case STATE_MENU:
		break;

	case STATE_LOAD:
		break;

	case STATE_SAVE:
		break;

	case STATE_NEW:
		break;

	case STATE_EPISODE:
		episode_reset(&def_episode);
		editor_switch_state_to(STATE_MENU);
		break;

	case STATE_EDITOR:
		break;

	case STATE_TEST:
		break;
	}
}

void main()
{
	max_entities = 3000;

	on_d3d_lost = imgui_reset;
	on_scanmessage = custom_scan_message;

	on_frame = on_frame_event;
	on_exit = on_exit_event;
	on_esc = on_esc_event;

	level_load("");
}