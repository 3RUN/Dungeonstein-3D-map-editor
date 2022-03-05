#ifndef _EDITOR_MUSIC_BROWSER_H_
#define _EDITOR_MUSIC_BROWSER_H_

#define MAX_AMOUNT_OF_MUSIC_TO_LOAD 999

TEXT *music_found_txt = NULL;

int found_music_index = -1;
int found_music_total = 0;

int is_music_playing_failed = false;

int playing_music_index = 0;
var playing_music_handle = 0;
var playing_music_volume = 100;

char *selected_music;
char *found_music_listbox[MAX_AMOUNT_OF_MUSIC_TO_LOAD];

void editor_music_browser_initialize();

void editor_music_browser_destroy();

int editor_scan_music_folder();

void editor_music_browser_refresh_list();

void editor_play_browser_music();

#endif