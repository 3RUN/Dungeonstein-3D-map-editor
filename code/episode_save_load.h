#ifndef _EPISODE_SAVE_LOAD_H_
#define _EPISODE_SAVE_LOAD_H_

// all episodes are saved and loaded to/from 'save_dir\episodes\'
// f.e. C:\Users\Admin\Documents\MapEditor\episodes

int episode_save(STRING *file_name, Episode *e);

int episode_load(STRING *file_name, Episode *e);

#endif