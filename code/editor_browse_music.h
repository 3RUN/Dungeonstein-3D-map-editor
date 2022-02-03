#ifndef _EDITOR_BROWSE_MUSIC_H_
#define _EDITOR_BROWSE_MUSIC_H_

#define MAX_AMOUNT_OF_MUSIC_TO_LOAD 999

#define MUSIC_BROWSER_WINDOW_WIDTH 395
#define MUSIC_BROWSER_WINDOW_HEIGHT 320

#define MUSIC_BROWSER_WINDOW_BUTTON_HEIGHT 24

TEXT *music_list_txt = NULL;

int found_music_index = -1;
int found_music_total = 0;

char *selected_music;
char *found_music_listbox[MAX_AMOUNT_OF_MUSIC_TO_LOAD];

void editor_browse_music_initialize();

void editor_browse_music_destroy();

int editor_load_music();

void editor_browser_music_refresh_list();

void editor_browser_music_update(Episode *e);

#endif