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
#define MAP_CELL_SIZE 32

#define STATE_NEW 0
#define STATE_EPISODE 1
#define STATE_EDITOR 2
#define STATE_TEST 3

int editor_state = STATE_NEW;
int editor_old_state = STATE_NEW;

int mouse_x = 0;
int mouse_y = 0;

int is_settings_opened = false;
int is_editor_popup_on = false;

void editor_switch_state_to(int state)
{
	editor_old_state = editor_state;
	editor_state = state;
}

int is_pos_on_grid(VECTOR *pos)
{
	if (!pos)
	{
		return false;
	}

	return (pos->x >= 0 && pos->x < MAP_WIDTH && pos->y >= 0 && pos->y < MAP_HEIGHT);
}

int is_allowed_to_draw_map()
{
	if (is_settings_opened == true || is_editor_popup_on == true)
	{
		return false;
	}

	if (is_pos_on_grid(vector(mouse_x, mouse_y, 0)) == false)
	{
		return false;
	}

	return true;
}

#include "cmd.h"
#include "imgui.h"
#include "ini.h"
#include "dynamic_array.h"
#include "savedir.h"
#include "screenres_list.h"
#include "engine.h"
#include "config.h"

#include "savedir.c"
#include "screenres_list.c"
#include "engine.c"
#include "config.c"

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

	// initialize imgui and apply custom theme
	imgui_init(0);
	imgui_change_theme();
}

void on_frame_event()
{
	switch (editor_state)
	{
	case STATE_NEW:
		break;

	case STATE_EPISODE:
		break;

	case STATE_EDITOR:
		break;

	case STATE_TEST:
		break;
	}

	mouse_lock_in_window();
}

void on_exit_event()
{
}

void on_esc_event()
{
	sys_exit("");
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