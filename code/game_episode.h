#ifndef _GAME_EPISODE_H_
#define _GAME_EPISODE_H_

// all episodes are saved to and loaded from 'save_dir\episodes\'
// f.e. C:\Users\Admin\Documents\MapEditor\episodes

#include "weather.h"

#define MAX_EPISODES_TO_LOAD 9999
#define MAX_AMOUNT_OF_MUSIC_TO_LOAD 999

#define MUSIC_DEF_VOLUME 100

#define EPISODE_FILENAME_LENGTH 32
#define EPISODE_NAME_LENGTH 32
#define EPISODE_STORY_START_LENGTH 128
#define EPISODE_STORY_END_LENGTH 128

#define MAX_MAPS_PER_EPISODE 10
#define MUSIC_NAME_LENGTH 32

#define CELL_TYPE_NONE -1
#define CELL_ASSET_NONE -1

#define DEF_CELL_PAN 270

#define EP_FLAG_NONE 0
#define EP_EVENT_TYPE 0
#define EP_EVENT_ID 0

#define FOG_DEF_START 32
#define FOG_DEF_END 2048
#define FOG_MAX_END 4096

#define FOG_DEF_COLOR 128
#define FLOOR_DEF_COLOR 128
#define CEILING_DEF_COLOR 16

char *selected_episode;
char *found_episodes_listbox[MAX_EPISODES_TO_LOAD];

char *selected_music;
char *found_music_listbox[MAX_AMOUNT_OF_MUSIC_TO_LOAD];

char ep_save_name[EPISODE_FILENAME_LENGTH];

int active_map_id = 0;

int found_episode_index = -1;
int found_episodes_total = 0;

int found_music_index = -1;
int found_music_total = 0;
int is_music_playing_failed = false;
int playing_music_index = 0;
var playing_music_handle = 0;
var playing_music_volume = 50;

TEXT *episodes_found_txt = NULL;
TEXT *music_found_txt = NULL;

typedef struct Cell
{
    VECTOR worldpos;
    var pan;

    int id;
    int x;
    int y;

    int type;
    int asset;

    int flag;
    int event_type;
    int event_id;
    int temp_skill;
} Cell;

typedef struct Map
{
    int weather_id;

    var fog_start;
    var fog_end;

    float fog_color[3];
    float floor_color[3];
    float ceiling_color[3];

    int is_ceiling_visible;

    char music[MUSIC_NAME_LENGTH];
    Cell cell[MAP_WIDTH][MAP_HEIGHT];
} Map;

typedef struct Episode
{
    char name[EPISODE_NAME_LENGTH];
    char story_start[EPISODE_STORY_START_LENGTH];
    char story_end[EPISODE_STORY_END_LENGTH];

    int map_count;
    Map map[MAX_MAPS_PER_EPISODE];
} Episode;

Cell preview_cell;
Map map_settings;
Episode def_episode;

void game_episode_initialize();

void game_episode_destroy();

int scan_episode_folder();

void episode_list_reset_selection();

void episode_list_refresh();

int scan_music_folder();

void music_list_reset_selection();

void music_list_refresh();

void play_selection_from_music_list();

void player_music_from_map(Map *map);

void stop_playing_music();

int is_game_episode_loaded();

void cell_copy(Cell *to, Cell *from);

Map *map_get_active(Episode *episode);

void map_copy(Map *to, Map *from);

void map_reset(Map *map);

void episode_save_name_udpate_to(STRING *filename);

void episode_change_info(Episode *episode, char *name, char *story_start, char *story_end, int map_count);

void episode_reset(Episode *episode);

int episode_save(STRING *file_name, Episode *episode);

int episode_load(STRING *file_name, Episode *episode);

#include "game_episode.c"
#endif