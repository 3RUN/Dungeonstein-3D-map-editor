#ifndef _GAME_EPISODE_SAVE_N_LOAD_H_
#define _GAME_EPISODE_SAVE_N_LOAD_H_

// all episodes are saved and loaded to/from 'save_dir\episodes\'
// f.e. C:\Users\Admin\Documents\MapEditor\episodes

int episode_save(STRING *file_name, Episode *episode);

int episode_load(STRING *file_name, Episode *episode);

#endif