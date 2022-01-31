#ifndef _GAME_EPISODE_H_
#define _GAME_EPISODE_H_

#define MAX_MAPS_PER_EPISODE 10

#define MAP_MUSIC_NAME_LENGTH 32

#define EPISODE_NAME_LENGTH 32
#define EPISODE_STORY_LENGTH 512

#define INDEX_NONE -1
#define TYPE_NONE -1

#define WEATHER_CLEAR 0
#define WEATHER_RAIN 1
#define WEATHER_SNOW 2

#define FOG_DEF_START 32
#define FOG_DEF_END 512

typedef struct Obj
{
    var pan;

    int type; // props, item, enemy, etc
    int asset_index;

    var skill_x;
    var skill_y;
    var skill_z;
} Obj;

typedef struct Cell
{
    VECTOR worldpos;

    int id;
    int x;
    int y;
    int type;
    int asset_index;

    var skill_x;
    var skill_y;
    var skill_z;

    Obj object;
} Cell;

typedef struct Map
{
    int weather_id;

    var fog_start;
    var fog_end;
    float fog_color[3];

    char *music[MAP_MUSIC_NAME_LENGTH];

    Cell cells[MAP_WIDTH][MAP_HEIGHT];
} Map;

typedef struct Episode
{
    char *name[EPISODE_NAME_LENGTH];
    char *story[EPISODE_STORY_LENGTH];

    int map_count;
    Map map[MAX_MAPS_PER_EPISODE];
} Episode;

void obj_reset(Obj *o);

void cell_reset(Cell *c);

void map_reset(Map *m);

void episode_reset(Episode *e);

#endif