#ifndef _COMPASS_H_
#define _COMPASS_H_

#define SIDE_FRONT 0
#define SIDE_RIGHT 1
#define SIDE_BACK 2
#define SIDE_LEFT 3

BMAP *compass_pcx = "compass.pcx";

FONT *font_arial_12b = "Arial#12b";

#define DIRECTION_PAN_STEP 90
#define MAX_DIRECTIONS 4
#define DIRECTION_N 0
#define DIRECTION_W 1
#define DIRECTION_S 2
#define DIRECTION_E 3

PANEL *compass_pan;
TEXT *compass_txt[MAX_DIRECTIONS];

VECTOR compass_direction_vec[MAX_DIRECTIONS];

void compass_initialize();

void compass_destroy();

void compass_hide();

void compass_show();

void compass_update();

void compass_directions_update(VECTOR *origin);

PANEL *compass_pan_create(BMAP *bmap, COLOR *color, var layer, var alpha, long flags);

TEXT *compass_txt_create(FONT *font, COLOR *color, var strings, var layer, var alpha, long flags);

var compass_get_direction_to_target(VECTOR *from_vec, var from_pan, VECTOR *target_vec);

void compass_direction(TEXT *direction_txt, PANEL *compass, var direction);

#include "compass.c"
#endif