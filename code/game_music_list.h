#ifndef _GAME_MUSIC_LIST_H_
#define _GAME_MUSIC_LIST_H_

#define MAX_AMOUNT_OF_MUSIC_TO_LOAD 999

#define MUSIC_DEF_VOLUME 100

TEXT *music_found_txt = NULL;

int found_music_index = -1;
int found_music_total = 0;

int is_music_playing_failed = false;

int playing_music_index = 0;
var playing_music_handle = 0;
var playing_music_volume = 50;

char *selected_music;
char *found_music_listbox[MAX_AMOUNT_OF_MUSIC_TO_LOAD];

void music_list_initialize();

void music_list_destroy();

int scan_music_folder();

void music_selection_reset();

void music_list_refresh();

void play_selection_from_music_list();

void player_music_from_map(Map *map);

void stop_playing_music();

#endif