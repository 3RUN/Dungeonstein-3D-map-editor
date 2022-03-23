#ifndef _DEBUG_PANEL_H_
#define _DEBUG_PANEL_H_

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

void debug_panel_initialize();

void debug_panel_destroy();

void debug_panel_show();

void debug_panel_hide();

void debug_panel_update();

#include "debug_panel.c"
#endif