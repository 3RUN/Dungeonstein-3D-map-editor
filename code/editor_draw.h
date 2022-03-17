#ifndef _EDITOR_DRAW_H_
#define _EDITOR_DRAW_H_

char *editor_draw_popup_id = "##Draw popup id";
char *editor_top_bar_id = "##Top bar menu id";

char save_as_filename[EPISODE_FILENAME_LENGTH];

#define DRAW_POPUP_OPEN 0
#define DRAW_POPUP_SURE_OPEN 1
#define DRAW_POPUP_NEW 2
#define DRAW_POPUP_SURE_NEW 3
#define DRAW_POPUP_SAVE_AS 4
#define DRAW_POPUP_SETTINGS 5
#define DRAW_POPUP_EXIT 6
#define DRAW_POPUP_EP_RESET 7
#define DRAW_POPUP_EP_EDIT 8
#define DRAW_POPUP_MAP_RESET 9
#define DRAW_POPUP_HELP 10
#define DRAW_POPUP_WAIT_FOR_INPUT 11

int draw_popup_state = DRAW_POPUP_OPEN;
int draw_popup_old_state = DRAW_POPUP_OPEN;

void editor_switch_popup_to(int state);

void editor_popups(Episode *episode);

void editor_top_bar(Episode *episode);

void editor_draw_update(Episode *episode);

#endif