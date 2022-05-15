
BMAP *asset_get_texture(int type, int index)
{
    if (type == ASSET_WALLS)
    {
        return array_get_element_at(BMAP *, wall_textures, index);
    }
    else if (type == ASSET_FLOORS)
    {
        return array_get_element_at(BMAP *, floor_textures, index);
    }
    else if (type == ASSET_EVENTS)
    {
        return array_get_element_at(BMAP *, event_textures, index);
    }
    else if (type == ASSET_PROPS)
    {
        return array_get_element_at(BMAP *, props_textures, index);
    }
    else if (type == ASSET_ITEMS)
    {
        return array_get_element_at(BMAP *, item_textures, index);
    }
    else if (type == ASSET_ENEMIES)
    {
        return array_get_element_at(BMAP *, enemy_textures, index);
    }
    else if (type == ASSET_BOSSES)
    {
        return array_get_element_at(BMAP *, boss_textures, index);
    }

    return NULL;
}

void asset_add(array_t *array, BMAP *sprite_sheet, int limit)
{
    if (!array || !sprite_sheet)
    {
        return;
    }

    var width = bmap_width(sprite_sheet);
    var height = bmap_height(sprite_sheet);

    var textures_in_column = width / ASSET_TEXTURE_WIDTH;
    var textures_in_row = height / ASSET_TEXTURE_HEIGHT;

    int i = 0, j = 0, texture_counter = 0;
    for (i = 0; i < textures_in_row; i++)
    {
        for (j = 0; j < textures_in_column; j++)
        {
            if (limit > 0 && texture_counter >= limit)
            {
                break;
            }

            BMAP *new_bmap = bmap_createblack(ASSET_TEXTURE_WIDTH, ASSET_TEXTURE_HEIGHT, ASSET_TEXTURE_FORMAT);
            bmap_blitpart(new_bmap, sprite_sheet, NULL, NULL, vector(j * ASSET_TEXTURE_HEIGHT, i * ASSET_TEXTURE_WIDTH, 0),
                          vector(ASSET_TEXTURE_HEIGHT, ASSET_TEXTURE_WIDTH, 0));
            array_add(BMAP *, array, new_bmap);
            texture_counter++;
        }
    }
}

void assets_initialize()
{
    wall_textures = array_create(BMAP *, 1);
    asset_add(wall_textures, walls_pcx, 0);
    wall_asset_count = array_get_count(wall_textures);

    floor_textures = array_create(BMAP *, 1);
    asset_add(floor_textures, floors_pcx, 0);
    floor_asset_count = array_get_count(floor_textures);

    event_textures = array_create(BMAP *, 1);
    asset_add(event_textures, events_pcx, 0);
    event_asset_count = array_get_count(event_textures);

    props_textures = array_create(BMAP *, 1);
    asset_add(props_textures, props_pcx, 0);
    props_asset_count = array_get_count(props_textures);

    item_textures = array_create(BMAP *, 1);
    asset_add(item_textures, items_pcx, 22); // load only 22 sprites
    item_asset_count = array_get_count(item_textures);

    enemy_textures = array_create(BMAP *, 1);
    asset_add(enemy_textures, enemies_pcx, 0);
    enemy_asset_count = array_get_count(enemy_textures);

    boss_textures = array_create(BMAP *, 1);
    asset_add(boss_textures, bosses_pcx, 0);
    boss_asset_count = array_get_count(boss_textures);
}

void asset_destroy_array(array_t *array)
{
    if (!array)
    {
        return;
    }

    array_enumerate_begin(BMAP *, array, v)
    {
        safe_remove(v);
    }
    array_enumerate_end(array);
    array_destroy(array);
}

void assets_destroy()
{
    asset_destroy_array(wall_textures);
    wall_textures = NULL;
    wall_asset_count = 0;

    asset_destroy_array(floor_textures);
    floor_textures = NULL;
    floor_asset_count = 0;

    asset_destroy_array(event_textures);
    event_textures = NULL;
    event_asset_count = 0;

    asset_destroy_array(props_textures);
    props_textures = NULL;
    props_asset_count = 0;

    asset_destroy_array(item_textures);
    item_textures = NULL;
    item_asset_count = 0;

    asset_destroy_array(enemy_textures);
    enemy_textures = NULL;
    enemy_asset_count = 0;

    asset_destroy_array(boss_textures);
    boss_textures = NULL;
    boss_asset_count = 0;
}