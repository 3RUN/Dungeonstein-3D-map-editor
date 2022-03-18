#ifndef _ASSETS_HELPER_H_
#define _ASSETS_HELPER_H_

int can_become_secret_wall(int type, int asset);

int is_secret_wall(Cell *cell);

int is_door(int type, int asset);

int is_fence(int type, int asset);

int is_npc(int type, int asset);

int is_player_start(int type, int asset);

int is_finish_elevator(int type, int asset);

int is_switch(int type, int asset);

int is_rotatable(int type, int asset);

int is_neighbour_is_door(Map *map, VECTOR *pos, VECTOR *dir);

#endif