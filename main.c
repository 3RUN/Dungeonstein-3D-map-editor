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

#define OBJ_ID skill50
#define OBJ_POS_X skill51
#define OBJ_POS_Y skill52
#define OBJ_POS_Z skill53
#define OBJ_TYPE_INDEX skill54
#define OBJ_ASSET_INDEX skill55

#define STATE_MAIN_MENU 0
#define STATE_LOAD 1
#define STATE_SAVE 2
#define STATE_RESET_EPISODE 3
#define STATE_EDIT_EPISODE 4
#define STATE_EDITOR 5
#define STATE_EXIT_EDITOR 6
#define STATE_TEST_MAP 7

int editor_state = STATE_MAIN_MENU;
int editor_old_state = STATE_MAIN_MENU;

int is_popup_opened = false;
int is_settings_opened = false;
int is_edit_episode_opened = false;
int is_help_opened = false;

int is_grid_visible = true;
int is_walls_visible = true;
int is_objects_visible = true;

int mouse_x = 0;
int mouse_y = 0;

int map_id = 0;

#include "cmd.h"
#include "imgui.h"
#include "ini.h"
#include "dynamic_array.h"
#include "savedir.h"
#include "screenres_list.h"
#include "engine.h"
#include "config.h"
#include "assets.h"
#include "episode.h"
#include "episode_save_load.h"
#include "editor.h"
#include "editor_cam.h"
#include "editor_grid.h"
#include "editor_grid_ents.h"
#include "editor_main_menu.h"
#include "editor_edit_episode.h"

#include "savedir.c"
#include "screenres_list.c"
#include "engine.c"
#include "config.c"
#include "assets.c"
#include "episode.c"
#include "episode_save_load.c"
#include "editor.c"
#include "editor_cam.c"
#include "editor_grid.c"
#include "editor_grid_ents.c"
#include "editor_main_menu.c"
#include "editor_edit_episode.c"

#include "test_scan_folder.c"

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
	imgui_init(0);				   // initialize imgui
	imgui_change_theme();		   // and apply custom theme
	assets_initialize();		   // load all editor assets
	editor_camera_initialize();	   // initialize camera (background color)
	episode_reset(&def_episode);   // initialize default episode
}

void on_frame_event()
{
	switch (editor_state)
	{
	case STATE_MAIN_MENU:
		editor_menu_update(&def_episode);
		break;

	case STATE_LOAD:
		break;

	case STATE_SAVE:
		break;

	case STATE_RESET_EPISODE:
		episode_reset(&def_episode);
		editor_switch_state_to(STATE_EDIT_EPISODE);
		break;

	case STATE_EDIT_EPISODE:
		editor_episode_update(&def_episode);
		break;

	case STATE_EDITOR:
		editor_grid_get_mouse_pos(&mouse_x, &mouse_y);

		DEBUG_VAR(mouse_x, 140);
		DEBUG_VAR(mouse_y, 160);

		Map *m = map_get_active(&def_episode);
		draw_text(draw_cell_info(m, mouse_x, mouse_y), 10, 200, COLOR_WHITE);

		editor_camera_update();
		editor_grid_update();
		break;

	case STATE_EXIT_EDITOR:
		editor_destroy_grid_ents();
		episode_reset(&def_episode);
		break;

	case STATE_TEST_MAP:
		break;
	}

	editor_camera_resize();
	mouse_lock_in_window();
}

void on_exit_event()
{
	assets_destroy();
	editor_destroy_grid_ents();
}

void on_esc_event()
{
	sys_exit("");
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

void test_grid_create()
{
	editor_create_grid_ents();
}

void test_grid_ent()
{
	Map *m = map_get_active(&def_episode);

	m->cell[0][0].type = ASSET_TYPE_WALL;
	m->cell[0][0].asset = 0;

	m->cell[16][0].type = ASSET_TYPE_WALL;
	m->cell[16][0].asset = 5;

	m->cell[2][0].type = ASSET_TYPE_WALL;
	m->cell[2][0].asset = 25;

	editor_update_grid_ents(m);
}

void test_grid_reset()
{
	editor_reset_grid_ents();
}

void test_grid_destroy()
{
	editor_destroy_grid_ents();
}

void test_save()
{
	episode_save("saved.dat", &def_episode);

	Map *m = map_get_active(&def_episode);
	editor_update_grid_ents(m);
}

void test_load()
{
	episode_load("saved.dat", &def_episode);

	Map *m = map_get_active(&def_episode);
	editor_update_grid_ents(m);
}

void test_reset()
{
	episode_reset(&def_episode);

	Map *m = map_get_active(&def_episode);
	editor_update_grid_ents(m);
}

void main()
{
	on_1 = test_save;
	on_2 = test_load;
	on_3 = test_reset;

	on_enter = test_scan_folder;

	on_z = test_grid_create;
	on_x = test_grid_ent;
	on_c = test_grid_reset;
	on_v = test_grid_destroy;

	max_entities = 2000;

	on_d3d_lost = imgui_reset;
	on_scanmessage = custom_scan_message;

	on_frame = on_frame_event;
	on_exit = on_exit_event;
	on_esc = on_esc_event;

	on_f1 = on_f_event;
	on_f2 = on_f_event;
	on_f3 = on_f_event;
	on_f4 = on_f_event;
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