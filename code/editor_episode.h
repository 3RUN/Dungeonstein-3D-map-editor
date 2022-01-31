#ifndef _EDITOR_EPISODE_H_
#define _EDITOR_EPISODE_H_

#define EPISODE_WINDOW_WIDTH 320
#define EPISODE_WINDOW_HEIGHT 276

#define EPISODE_WINDOW_BUTTON_HEIGHT 24

#define EPISODE_POPUP_CREATE_ID 0
#define EPISODE_POPUP_EXIT_ID 1

int episode_button_id = EPISODE_POPUP_CREATE_ID;

STRING *episode_popup_str = "";
STRING *episode_create_popup_str = "Make sure to enter name and a story!";
STRING *episode_exit_popup_str = "Are you sure you want to exit?";

void editor_episode_update(Episode *e);

#endif