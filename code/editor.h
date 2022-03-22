#ifndef _EDITOR_H_
#define _EDITOR_H_

#define EDITOR_TOP_BAR_HEIGHT 16
#define EDITOR_SIDE_BAR_WIDTH 280

#define PREVIEW_SCALE_FACTOR 2
#define SIDEBAR_ASSET_LIST_CHILD_HEIGHT 215
#define SIDEBAR_PARAM_CHILD_HEIGHT 145

#define CELL_TOOLTIP_TIME 0.5

void *asset_draw_list = NULL;

char *editor_main_popup_id = "##Main popup id";
char *editor_top_bar_id = "##Top bar menu id";
char *editor_side_bar_id = "##Side bar id";
char *editor_side_bar_category_combo_id = "##Side bar asset category combobox id";
char *editor_preview_parameters_child_id = "##Preview parameters child id";
char *editor_side_bar_asset_list_child_id = "##Side bar asset list child id";

char *selected_asset_category;
char *asset_categories_combobox[MAX_ASSET_TYPES];

char save_as_filename[EPISODE_FILENAME_LENGTH];
char preview_asset_name[ASSET_DESC_LENGTH];

#define MAIN_POPUP_OPEN 0
#define MAIN_POPUP_SURE_OPEN 1
#define MAIN_POPUP_NEW 2
#define MAIN_POPUP_SURE_NEW 3
#define MAIN_POPUP_SAVE_AS 4
#define MAIN_POPUP_SETTINGS 5
#define MAIN_POPUP_EXIT 6
#define MAIN_POPUP_EP_RESET 7
#define MAIN_POPUP_EP_EDIT 8
#define MAIN_POPUP_MAP_RESET 9
#define MAIN_POPUP_HELP 10
#define MAIN_POPUP_WAIT_FOR_INPUT 11

BMAP *preview_bmap = NULL;

Cell preview_cell;

var main_popup_state = MAIN_POPUP_OPEN;
var main_popup_old_state = MAIN_POPUP_OPEN;

var selected_type = 0;
var selected_asset = 0;

var cell_info_tooltip_counter = 0;

var editor_state = EDITOR_STATE_EDIT;
var editor_old_state = EDITOR_STATE_EDIT;

void editor_switch_state_to(var state);

void editor_main_initialize();

void editor_main_reset();

void editor_main_destroy();

void preview_update(var type, var asset);

void editor_main_switch_popup_to(var state);

void editor_popups(Episode *episode);

void editor_top_bar(Episode *episode);

void editor_asset_list_item(void *draw_list, var type, var asset);

void editor_side_bar(Episode *episode);

void editor_main_cell_tooltip(Episode *episode);

void editor_main_update(Episode *episode);

#endif