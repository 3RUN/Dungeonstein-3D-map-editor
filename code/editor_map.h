#ifndef _EDITOR_MAP_H_
#define _EDITOR_MAP_H_

#define PREVIEW_SCALE_FACTOR 2
#define SIDEBAR_ASSET_LIST_CHILD_HEIGHT 215
#define SIDEBAR_PARAM_CHILD_HEIGHT 145

#define MAP_POPUP_OPEN 0
#define MAP_POPUP_OPEN_SURE 1
#define MAP_POPUP_NEW 2
#define MAP_POPUP_NEW_SURE 3
#define MAP_POPUP_SAVE_AS 4
#define MAP_POPUP_SETTINGS 5
#define MAP_POPUP_ABOUT 6
#define MAP_POPUP_EPISODE_EDIT 7
#define MAP_POPUP_RESET_MAP 8
#define MAP_POPUP_EXIT 9

void *asset_draw_list = NULL;

char *map_popup_id = "##Map empty popup";
char *map_top_bar_id = "##Map top bar window";
char *map_side_bar_id = "##Map side bar window";
char *map_side_bar_asset_param_child_id = "##Selected asset param child";
char *map_side_bar_asset_category_combobox_id = "##Asset category combobox";
char *map_side_bar_asset_list_child_id = "##Assets list child";

// asset category combobox
char *editor_selected_asset_type;
char *editor_asset_types_combobox[MAX_ASSET_TYPES];

char preview_name[ASSET_DESC_LENGTH];

STRING *map_preview_name_str = "Name: ";
STRING *map_preview_image_str = "Image:";
STRING *map_preview_parameters_str = "Parameters:";
STRING *map_selected_asset_str = "Selected asset";
STRING *map_assets_str = "Assets";
STRING *map_mouse_pos_str = "Mouse pos x = %d; y = %d;";
STRING *map_size_str = "Map size: width = %d; height = %d;";

int editor_asset_type = ASSET_TYPE_WALLS; // currently active asset category
int editor_asset_index = 0;               // currently selected asset

int map_popup_state = MAP_POPUP_OPEN;

BMAP *preview_bmap = NULL; // used for selected asset preview

Cell preview_cell;

void editor_map_initialize();

void editor_map_reset();

void editor_map_destroy();

void editor_map_preview_update(int type, int index);

void editor_map_create_asset_item(void *draw_list, int type, int index);

void editor_map_popup_state_change_to(int state);

void editor_map_popup(Episode *episode);

void editor_map_side_bar(Episode *episode);

void editor_map_top_bar(Episode *episode);

void editor_map_background();

void editor_map_update(Episode *episode);

#endif