#ifndef _GAME_EP_H_
#define _GAME_EP_H_

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

#define WEATHER_MAX 3
#define WEATHER_CLEAR 0
#define WEATHER_RAIN 1
#define WEATHER_SNOW 2

#define FOG_DEF_START 32
#define FOG_DEF_END 2048
#define FOG_MAX_END 4096

#define FOG_DEF_COLOR 128
#define FLOOR_DEF_COLOR 128
#define CEILING_DEF_COLOR 16

char ep_save_name[EPISODE_FILENAME_LENGTH];

int active_map_id = 0;

typedef struct Cell
{
    VECTOR worldpos;
    var pan;

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

Episode def_episode;

int is_game_episode_loaded();

void episode_save_name_udpate_to(STRING *filename);

void cell_copy(Cell *to, Cell *from);

Map *map_get_active(Episode *episode);

void map_copy_weather(Map *to, Map *from);

void map_reset(Map *map);

void episode_change_info(Episode *episode, STRING *name, STRING *story_start, STRING *story_end, int map_count);

void episode_reset(Episode *episode);

#endif