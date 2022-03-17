#ifndef _GAME_EP_LIST_H_
#define _GAME_EP_LIST_H_

#define MAX_EPISODES_TO_LOAD 9999

TEXT *episodes_found_txt = NULL;

int found_episode_index = -1;
int found_episodes_total = 0;

char *selected_episode;
char *found_episodes_listbox[MAX_EPISODES_TO_LOAD];

void episode_list_initialize();

void episode_list_destroy();

int episode_list_load();

void episode_selection_reset();

void episode_list_refresh();

#endif