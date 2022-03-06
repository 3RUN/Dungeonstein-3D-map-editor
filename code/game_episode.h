#ifndef _GAME_EPISODE_H_
#define _GAME_EPISODE_H_

#define MAX_MAPS_PER_EPISODE 10
#define MAP_MUSIC_NAME_LENGTH 32

#define EPISODE_FILENAME_LENGTH 32
#define EPISODE_NAME_LENGTH 32
#define EPISODE_START_STORY_LENGTH 128
#define EPISODE_END_STORY_LENGTH 128

// default episode, map, cell settings
#define TYPE_NONE -1
#define ASSET_NONE -1

#define CELL_DEF_PAN 270

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
#define FLOOR_DEF_COLOR 64
#define CEILING_DEF_COLOR 32

char episode_save_name[EPISODE_FILENAME_LENGTH];

typedef struct Cell
{
    VECTOR worldpos;
    var pan;

    int id;
    int x;
    int y;

    int type;  // wall, props, item, etc
    int asset; // asset index (used for action assignment too)

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
    float ceiling_color[3]; // used only when in ceiling mode

    char music[MAP_MUSIC_NAME_LENGTH];
    Cell cell[MAP_WIDTH][MAP_HEIGHT];
} Map;

typedef struct Episode
{
    char name[EPISODE_NAME_LENGTH];
    char start_story[EPISODE_START_STORY_LENGTH];
    char end_story[EPISODE_END_STORY_LENGTH];

    int map_count;
    Map map[MAX_MAPS_PER_EPISODE];
} Episode;

int is_game_episode_loaded();

void episode_save_name_udpate(STRING *filename);

void cell_copy(Cell *to, Cell *from);

Map *map_get_active(Episode *episode);

void map_copy_weather(Map *to, Map *from);

void map_reset(Map *map);

void episode_change_info(Episode *episode, STRING *name, STRING *start_story, STRING *end_story, int map_count);

void episode_reset(Episode *episode);

#endif