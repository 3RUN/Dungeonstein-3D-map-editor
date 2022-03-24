#ifndef _EDITOR_H_
#define _EDITOR_H_

#define EDITOR_TOP_BAR_HEIGHT 16
#define EDITOR_SIDE_BAR_WIDTH 280

#define PREVIEW_SCALE_FACTOR 2
#define SIDEBAR_ASSET_LIST_CHILD_HEIGHT 215
#define SIDEBAR_PARAM_CHILD_HEIGHT 145

#define CELL_TOOLTIP_TIME 0.5

#define EDITOR_POPUP_OPEN 0
#define EDITOR_POPUP_SURE_OPEN 1
#define EDITOR_POPUP_NEW 2
#define EDITOR_POPUP_SURE_NEW 3
#define EDITOR_POPUP_SAVE_AS 4
#define EDITOR_POPUP_SETTINGS 5
#define EDITOR_POPUP_EXIT 6
#define EDITOR_POPUP_EP_RESET 7
#define EDITOR_POPUP_EP_EDIT 8
#define EDITOR_POPUP_MAP_RESET 9
#define EDITOR_POPUP_HELP 10
#define EDITOR_POPUP_WAIT_FOR_INPUT 11

BMAP *preview_bmap = NULL;

void *asset_draw_list = NULL;

char *editor_popup_id = "##Editor popup id";
char *editor_top_bar_id = "##Top bar menu id";
char *editor_side_bar_id = "##Side bar id";
char *editor_side_bar_category_combo_id = "##Side bar asset category combobox id";
char *editor_preview_parameters_child_id = "##Preview parameters child id";
char *editor_side_bar_asset_list_child_id = "##Side bar asset list child id";

char *selected_asset_category;
char *asset_categories_combobox[MAX_ASSET_TYPES];

char save_as_filename[EPISODE_FILENAME_LENGTH];
char preview_asset_name[ASSET_DESC_LENGTH];

int editor_popup_state = EDITOR_POPUP_OPEN;
int editor_old_popup_state = EDITOR_POPUP_OPEN;

int selected_type = 0;
int selected_asset = 0;

int category_reset_scrollbar = false;

var cell_info_tooltip_counter = 0;

void editor_switch_state_to(int state);

void editor_switch_popup_to(int state);

void editor_initialize(Episode *episode);

void editor_preview_update(int type, int asset);

void editor_reset();

void editor_destroy();

void editor_popups(Episode *episode);

void editor_side_bar(Episode *episode);

void editor_top_bar(Episode *episode, Map *map);

void editor_cell_tooltip(Map *map);

void editor_update(Episode *episode, Map *map);

#endif