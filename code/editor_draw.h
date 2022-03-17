#ifndef _EDITOR_DRAW_H_
#define _EDITOR_DRAW_H_

char *editor_top_bar_id = "##Top bar menu id";

char save_as_filename[EPISODE_FILENAME_LENGTH];

void editor_top_bar(Episode *episode);

void editor_draw_update(Episode *episode);

#endif