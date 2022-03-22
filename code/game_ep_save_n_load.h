#ifndef _GAME_EP_SAVE_N_LOAD_H_
#define _GAME_EP_SAVE_N_LOAD_H_

// all episodes are saved to and loaded from 'save_dir\episodes\'
// f.e. C:\Users\Admin\Documents\MapEditor\episodes

var episode_save(STRING *file_name, Episode *episode);

var episode_load(STRING *file_name, Episode *episode);

#endif