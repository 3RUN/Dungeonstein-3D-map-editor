#ifndef _EPISODE_H_
#define _EPISODE_H_

#define MAX_OBJECT_FLAGS 4
#define MAX_MAPS_PER_EPISODE 10

#define OBJ_DEF_PAN 270
#define OBJ_TYPE_NONE 2 // ASSET_PROPS
#define OBJ_INDEX_NONE 0
#define OBJ_FLAG_NONE 0

#define CELL_INDEX_NONE 0

#define MAP_DEF_FOG_START 32
#define MAP_DEF_FOG_END 2048
#define MAP_DEF_FOG_COLOR 16
#define MAP_FOG_END_MAX 4096

#define EPISODE_NAME_LENGTH 33
#define MUSIC_NAME_LENGTH 33

char ep_filename[EPISODE_NAME_LENGTH];

typedef struct Object
{
    var pan;

    int is_occupied;
    int type;
    int index;
    int flag[MAX_OBJECT_FLAGS];
} Object;

typedef struct Cell
{
    VECTOR pos;

    int x;
    int y;

    int is_solid;

    int wall_index;
    int ceiling_index;
    int floor_index;

    Object object;
} Cell;

typedef struct Map
{
    var fog_start;
    var fog_end;
    float fog_color[3];

    char music[MUSIC_NAME_LENGTH];
    Cell cell[MAP_WIDTH][MAP_HEIGHT];
} Map;

typedef struct Episode
{
    char name[EPISODE_NAME_LENGTH];
    int map_count;
    Map map[MAX_MAPS_PER_EPISODE];
} Episode;

Cell preview_cell;

Map map_copied;
Map map_settings;

Episode def_episode;

void episode_initialize();

int has_no_ceiling(VECTOR *pos);

int cell_has_no_ceiling(Cell *cell);

void object_copy(Object *to, Object *from);

void cell_update_preview(int button_id, int type, int index);

void cell_copy(Cell *to, Cell *from);

Cell *map_get_neighbours(Map *map, VECTOR *pos, VECTOR *dir, var step);

Map *map_get_active(Episode *episode);

void map_copy(Map *to, Map *from);

void episode_set_filename(STRING *filename);

void episode_copy(Episode *to, Episode *from);

void episode_edit_info(Episode *episode, char *name, int map_count);

int episode_save(STRING *file_name, Episode *episode);

int episode_load(STRING *file_name, Episode *episode);

#include "episode_scan.h"
#include "episode.c"
#endif