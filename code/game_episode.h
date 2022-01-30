#ifndef _GAME_EPISODE_H_
#define _GAME_EPISODE_H_

#define MAX_MAPS_PER_EPISODE 10
#define EPISODE_NAME_LENGTH 32
#define EPISODE_STORY_LENGTH 512
#define MAP_MUSIC_LENGTH 64

#define FOG_DEF_START 32
#define FOG_DEF_END 512

#define SKY_MAX 3
#define SKY_CLEAR 0
#define SKY_CLOUDY 1
#define SKY_NIGHT 2

#define WEATHER_MAX 3
#define WEATHER_CLEAR 0
#define WEATHER_CLOUDY 1
#define WEATHER_RAINY 2

#define INDEX_NONE -1

typedef struct Cell
{
    VECTOR worldpos;
    int id;
    int x;
    int y;

    int base_type_index;
    int wall_asset_index;
    int floor_asset_index;
    int ceiling_asset_index;

    int obj_type_index;
    int obj_asset_index;
    int obj_id;
    int obj_pan;
    int obj_skill_x;
    int obj_skill_y;
    int obj_skill_z;
} Cell;

typedef struct Map
{
    var fog_end;
    var fog_start;
    float fog_color[3];

    int sky_cube;
    int weather;

    char *music[MAP_MUSIC_LENGTH];

    Cell cells[MAP_WIDTH][MAP_HEIGHT];
} Map;

typedef struct Episode
{
    char *name[EPISODE_NAME_LENGTH];
    char *story[EPISODE_STORY_LENGTH];

    int map_count;
    Map maps[MAX_MAPS_PER_EPISODE];
} Episode;

void map_initialize(Map *m);

void episode_reset(Episode *e);

#endif