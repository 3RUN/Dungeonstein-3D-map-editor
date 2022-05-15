#ifndef _EPISODE_SCAN_H_
#define _EPISODE_SCAN_H_

#define MAX_EPISODES_TO_LOAD 9999
#define MAX_AMOUNT_OF_MUSIC_TO_LOAD 999

TEXT *episodes_found_txt = NULL;
TEXT *music_found_txt = NULL;

int found_episode_index = -1;
int found_episodes_total = 0;

int found_music_index = -1;
int found_music_total = 0;

char *selected_episode;
char *found_episodes_listbox[MAX_EPISODES_TO_LOAD];

char *selected_music;
char *found_music_listbox[MAX_AMOUNT_OF_MUSIC_TO_LOAD];

void episode_scanner_initialize();

void episode_scanner_destroy();

int scan_episode_folder();

void episode_list_refresh();

int scan_music_folder();

void music_list_refresh();

#include "episode_scan.c"
#endif