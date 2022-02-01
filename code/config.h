#ifndef _CONFIG_H_
#define _CONFIG_H_

// different display modes
#define DISPLAY_MODES_MAX 2
#define DISPLAY_MODE_WINDOWED 0
#define DISPLAY_MODE_WINDOWED_FULLSCREEN 1

// default config
int graphics_video_res_def_id = 0;
int graphics_display_def_mode = DISPLAY_MODE_WINDOWED_FULLSCREEN;

// config sections
STRING *config_graphics_section_str = "Graphics";
STRING *config_other_section_str = "Other";

// config graphics entries
STRING *graphics_video_res_id_entry_str = "Video resolution id";
STRING *graphics_display_mode_entry_str = "Display mode";

// config other entries
STRING *other_cell_tooltip_str = "Cell tooltip enabled";

// config others
int is_cell_tooltip_def_enabled = true;

// structure to save all game config
typedef struct CONFIG
{
    // graphics
    int graphics_video_res_id;
    int graphics_display_mode;

    // other settings
    int is_cell_tooltip_enabled;

} CONFIG;

CONFIG config_default; // never changed (used for reseting to default values)
CONFIG config_current; // changed directly in options menu, if cancel button pressed - resets back to old config
CONFIG config_saved;   // previously saved config, if yes/apply button pressed - get's overwritten by current config

// initialize config into the given file
void config_initialize(STRING *config_file);

// save and apply config
void config_save_n_apply();

// reset config to defaults
void config_reset_to_default();

// reset config to saved
void config_reset_to_saved();

// load config from the file
void config_load_from_file(STRING *config_file);

// save config into the given file
void config_save_to_file(STRING *config_file);

#endif