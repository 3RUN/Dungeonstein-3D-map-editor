#ifndef _EDITOR_EMPTY_H_
#define _EDITOR_EMPTY_H_

#define EMPTY_POPUP_OPEN 0
#define EMPTY_POPUP_NEW 1
#define EMPTY_POPUP_SETTINGS 2
#define EMPTY_POPUP_ABOUT 3
#define EMPTY_POPUP_EXIT 4

#define EMPTY_BACKGROUND_COLOR vector(64, 64, 64)

char *empty_popup_id_str = "##Editor empty popup";
char *empty_top_bar_id_str = "##Empty top bar window";

int empty_popup_state = EMPTY_POPUP_OPEN;

void editor_empty_popup(Episode *episode);

void editor_empty_top_bar();

void editor_empty_background();

void editor_empty_update(Episode *episode);

#endif