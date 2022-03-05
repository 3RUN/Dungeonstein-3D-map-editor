#ifndef _EPISODE_LIST_H_
#define _EPISODE_LIST_H_

#define MAX_EPISODES_TO_LOAD 9999

TEXT *episodes_found_txt = NULL;

int found_episode_index = -1;
int found_episodes_total = 0;
int is_episode_open_failed = false;

char *selected_episode;
char *found_episodes_listbox[MAX_EPISODES_TO_LOAD];

void editor_episode_list_initialize();

void editor_episode_list_destroy();

int editor_episode_list_load();

void editor_episode_list_refresh();

#endif