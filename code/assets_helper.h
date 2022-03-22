#ifndef _ASSETS_HELPER_H_
#define _ASSETS_HELPER_H_

var can_become_secret_wall(var type, var asset);

var is_secret_wall(Cell *cell);

var is_door(var type, var asset);

var is_fence(var type, var asset);

var is_npc(var type, var asset);

var is_player_start(var type, var asset);

var is_finish_elevator(var type, var asset);

var is_switch(var type, var asset);

var is_treasure(var type, var asset);

var is_rotatable(var type, var asset);

var is_neighbour_is_door(Map *map, VECTOR *pos, VECTOR *dir);

#endif