
#include <acknex.h>
#include <windows.h>
#include <default.c>
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

#include "cmd.h"
#include "imgui.h"
#include "ini.h"
#include "dynamic_array.h"
#include "savedir.h"
#include "screenres_list.h"
#include "engine.h"
#include "config.h"
#include "assets.h"
#include "shaders.h"

#include "savedir.c"
#include "screenres_list.c"
#include "engine.c"
#include "config.c"
#include "assets.c"
#include "shaders.c"

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
	shaders_initialize();		   // initialize all shaders used in editor
	imgui_init(0);				   // initialize imgui
	imgui_change_theme();		   // and apply custom theme
	config_initialize(temp_str);   // initialize config (set defaults and load from the config file)engine_initialize()
}

void on_frame_event()
{
	shaders_update();
	mouse_lock_in_window();

	if (key_f4 && key_alt)
	{
		sys_exit(NULL);
	}
}

void on_exit_event()
{
	assets_destroy_all();
	shaders_destroy();
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