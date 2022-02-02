#ifndef _EPISODE_H_
#define _EPISODE_H_

#define MAX_MAPS_PER_EPISODE 10

#define MAP_MUSIC_NAME_LENGTH 32
#define EPISODE_NAME_LENGTH 32
#define EPISODE_STORY_LENGTH 303

#define TYPE_NONE -1
#define ASSET_NONE -1

#define WEATHER_MAX 3
#define WEATHER_CLEAR 0
#define WEATHER_RAIN 1
#define WEATHER_SNOW 2

#define FOG_DEF_START 32
#define FOG_DEF_END 512

typedef struct Cell
{
    VECTOR worldpos;
    var pan;

    int id;
    int x;
    int y;

    int type;  // wall, props, item, etc
    int asset; // asset index (used for action assignment too)

    var skill_x;
    var skill_y;
    var skill_z;
} Cell;

typedef struct Map
{
    int weather_id;

    var fog_start;
    var fog_end;
    float fog_color[3];
    float sky_color[3];

    char music[MAP_MUSIC_NAME_LENGTH];
    Cell cell[MAP_WIDTH][MAP_HEIGHT];
} Map;

typedef struct Episode
{
    char name[EPISODE_NAME_LENGTH];
    char story[EPISODE_STORY_LENGTH];

    int map_count;
    Map map[MAX_MAPS_PER_EPISODE];
} Episode;

Map *map_get_active(Episode *e);

void map_reset(Map *m);

void episode_reset(Episode *e);

#endif