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

	imgui_init(0);		  // initialize imgui
	imgui_change_theme(); //and apply custom theme
	assets_initialize();  // load all editor assets
}

void on_frame_event()
{
	switch (editor_state)
	{
	case STATE_MENU:
		editor_menu_update(&def_episode);
		break;

	case STATE_LOAD:
		int load_res = map_load();
		if (load_res == true)
		{
			editor_switch_state_to(STATE_EDITOR);
		}
		else
		{
			editor_switch_state_to(STATE_MENU);
		}
		break;

	case STATE_NEW:
		episode_reset(&def_episode);
		editor_switch_state_to(STATE_EPISODE);
		break;

	case STATE_EPISODE:
		editor_episode_update(&def_episode);
		break;

	case STATE_EDITOR:
		draw_text("in editor", 100, 100, COLOR_WHITE);
		break;

	case STATE_TEST:
		break;
	}

	mouse_lock_in_window();
}

void on_exit_event()
{
	assets_destroy();
}

void on_esc_event()
{
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