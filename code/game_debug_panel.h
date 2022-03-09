#ifndef _GAME_DEBUG_PANEL_H_
#define _GAME_DEBUG_PANEL_H_

#define DEBUG_PANEL_LAYER 998
#define DEBUG_PANEL_ALPHA 75
#define DEBUG_TIP_PANEL_ALPHA 100

SOUND *beep_ogg = "beep.ogg";

PANEL *debug_pan = NULL;
PANEL *debug_tip = NULL;

FONT *debug_ackfont = "ackfont.pcx";

STRING *debug_ms_frame_str = "ms/frame";
STRING *debug_count_of_str = "count of";
STRING *debug_memory_MB_str = "memory MB";
STRING *debug_network_str = "network";

STRING *debug_tip_screenshot_saved_str = "Screenshot saved";
STRING *debug_tip_episode_saved_str = "Episode saved";

int beep_once = true;
var beep_handle = 0;
var beep_volume = 50;

var def_dfps = 0;
var def_dtps = 0;
var def_dtlv = 0;
var def_dtcs = 0;
var def_dtac = 0;
var def_dtrf = 0;
var def_dsnd = 0;

var def_shot_num = 0;

void game_debug_panel_initialize();

void game_debug_panel_destroy();

void game_debug_panel_show();

void game_debug_panel_hide();

void game_debug_tip_show(STRING *msg);

void game_debug_panel_update();

void def_shot();

void def_exit();

void def_save();

#endif