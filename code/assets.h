#ifndef _ASSETS_H_
#define _ASSETS_H_

#define ASSET_TEXTURE_WIDTH 32
#define ASSET_TEXTURE_HEIGHT 32
#define ASSET_TEXTURE_FORMAT 8888

array_t *wall_textures;
array_t *floor_textures;
array_t *event_textures;
array_t *props_textures;
array_t *item_textures;
array_t *enemy_textures;
array_t *boss_textures;

BMAP *walls_pcx = "walls.pcx";
BMAP *floors_pcx = "floors.pcx";
BMAP *events_pcx = "events.pcx";
BMAP *props_pcx = "props.pcx";
BMAP *items_pcx = "items.pcx";
BMAP *enemies_pcx = "enemies.pcx";
BMAP *bosses_pcx = "bosses.pcx";

BMAP *doorway_wall_pcx = "doorway_wall.pcx";
BMAP *doorway_floor_pcx = "doorway_floor.pcx";

BMAP *door_key_blue_pcx = "door_key_blue.pcx";
BMAP *door_key_red_pcx = "door_key_red.pcx";
BMAP *door_key_yellow_pcx = "door_key_yellow.pcx";

BMAP *elevator_switch_off = "elevator_switch_off.pcx";
BMAP *elevator_switch_on = "elevator_switch_on.pcx";

STRING *empty_pcx = "empty.pcx";
STRING *direction_pcx = "direction.pcx";

int wall_asset_count = 0;
int floor_asset_count = 0;
int event_asset_count = 0;
int props_asset_count = 0;
int item_asset_count = 0;
int enemy_asset_count = 0;
int boss_asset_count = 0;

BMAP *asset_get_texture(int type, int index);

void asset_add(array_t *array, BMAP *sprite_sheet, int limit);

void assets_initialize();

void asset_destroy_array(array_t *array);

void assets_destroy();

#include "assets_helper.h"
#include "assets.c"
#endif