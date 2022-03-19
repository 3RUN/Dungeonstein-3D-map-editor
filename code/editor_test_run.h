#ifndef _EDITOR_TEST_RUN_H_
#define _EDITOR_TEST_RUN_H_

#define CROSSHAIR_LAYER 998

PANEL *crosshair_pan = NULL;

BMAP *crosshair_pcx = "crosshair.pcx";

VECTOR selected_cell_pos;

STRING *selected_cell_info_str = "";

var scancode_interact = 0;

void draw_bbox3d(VECTOR *position, VECTOR *bbox_min, VECTOR *bbox_max, ANGLE *angle, COLOR *color, var alpha);

void test_run_get_cell_info(Map *map);

void test_run_select_player_on_start(Map *map);

void test_run_initialize();

void test_run_destroy();

void test_run_crosshair_show();

void test_run_crosshair_hide();

void test_run_remove_binding(var scancode);

void test_run_update_binding(var scancode, void *fnc);

void test_run_update_from_config(CONFIG *config);

void test_run_info_trace();

void editor_test_run_update(Episode *episode);

#endif