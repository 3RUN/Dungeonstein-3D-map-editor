#ifndef _GAME_DEBUG_PANEL_H_
#define _GAME_DEBUG_PANEL_H_

#define DEBUG_PANEL_LAYER 998
#define DEBUG_PANEL_ALPHA 75

PANEL *debug_pan = NULL;

FONT *debug_ackfont = "ackfont.pcx";

STRING *debug_ms_frame_str = "ms/frame";
STRING *debug_count_of_str = "count of";
STRING *debug_memory_MB_str = "memory MB";
STRING *debug_network_str = "network";

var def_dfps = 0;
var def_dtps = 0;
var def_dtlv = 0;
var def_dtcs = 0;
var def_dtac = 0;
var def_dtrf = 0;
var def_dsnd = 0;

void game_debug_panel_initialize();

void game_debug_panel_destroy();

void game_debug_panel_show();

void game_debug_panel_hide();

void game_debug_panel_update();

#endif