#ifndef _ASSETS_HELPER_H_
#define _ASSETS_HELPER_H_

#include "game_episode.h"

int can_become_secret_wall(int type, int asset);

int is_secret_wall(Cell *cell);

int is_switch(int type, int asset);

int is_door(int type, int asset);

int is_fence(int type, int asset);

int is_treasure(int type, int asset);

int is_ceiling_support(int type, int asset);

int is_decal(int type, int asset);

int is_trigger_zone(int type, int asset);

int is_spawn_object(int type, int asset);

int is_npc_turn_point(int type, int asset);

int is_effect(int type, int asset);

int is_enemy(int type, int asset);

int is_boss(int type, int asset);

int is_player_start(int type, int asset);

int is_finish_elevator(int type, int asset);

int is_rotatable(int type, int asset);

#endif