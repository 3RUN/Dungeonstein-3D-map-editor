#ifndef _GAME_BUILD_INFO_H_
#define _GAME_BUILD_INFO_H_

int is_level_finish_found = false;
int is_player_position_found = false;

void game_build_info_initialize();

void game_build_info_reset();

void game_build_info_update(Episode *episode);

#endif