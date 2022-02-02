#ifndef _EDITOR_LOAD_EPISODE_H_
#define _EDITOR_LOAD_EPISODE_H_

#define MAX_AMOUNT_OF_EPISODES_TO_LOAD 9999

#define LOAD_BROWSER_WINDOW_WIDTH 395
#define LOAD_BROWSER_WINDOW_HEIGHT 320

#define LOAD_BROWSER_WINDOW_BUTTON_HEIGHT 24

TEXT *episodes_list_txt = NULL;

int found_episode_index = -1;
int found_episodes_total = 0;

char *selected_episode;
char *found_episodes_listbox[MAX_AMOUNT_OF_EPISODES_TO_LOAD];

void editor_load_episodes_initialize();

void editor_load_episodes_destroy();

int editor_load_episodes();

void editor_load_refresh_list();

void editor_load_update(Episode *e);

#endif