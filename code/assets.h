#ifndef _ASSETS_H_
#define _ASSETS_H_

BMAP *wall_textures_tga = "walls.tga";
BMAP *floor_textures_tga = "floor.tga";
BMAP *ceiling_textures_tga = "ceiling.tga";

typedef struct Asset
{
    BMAP *bmap;
    char *description[128];
    int type;
    int index;
} Asset;

array_t *wall_textures;
array_t *floor_textures;
array_t *ceiling_textures;

#define ASSET_TYPE_WALL 0
#define ASSET_TYPE_FLOOR 1
#define ASSET_TYPE_CEILING 2

void asset_create_texture(array_t *array, BMAP *source, STRING *description, int type, int u, int v);

void asset_create_object(array_t *array, BMAP *source, STRING *description, int type, int index, int u, int v);

void assets_initialize();

void assets_destroy_array(array_t *array);

void assets_destroy();

#endif