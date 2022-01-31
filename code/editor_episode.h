#ifndef _EDITOR_EPISODE_H_
#define _EDITOR_EPISODE_H_

#define EPISODE_WINDOW_WIDTH 320
#define EPISODE_WINDOW_HEIGHT 276

#define EPISODE_WINDOW_BUTTON_HEIGHT 24

STRING *episode_create_popup_str = "Make sure to enter name and a story!";

void editor_episode_update(Episode *e);

#endif