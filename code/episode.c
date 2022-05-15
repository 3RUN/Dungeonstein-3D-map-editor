
void episode_initialize()
{
    cell_copy(&preview_cell, NULL);

    map_copy(&map_copied, NULL);
    map_copy(&map_settings, NULL);

    episode_copy(&def_episode, NULL);
}

int has_no_ceiling(VECTOR *pos)
{
    int x = 0, y = 0;
    vec_world_to_grid(pos, &x, &y);

    if (is_pos_on_grid(vector(x, y, 0)) == false)
    {
        return false;
    }

    Map *active_map = map_get_active(&def_episode);
    if (!active_map)
    {
        return false;
    }

    Cell *cell = &active_map->cell[x][y];
    if (!cell)
    {
        return false;
    }

    return cell_has_no_ceiling(cell);
}

int cell_has_no_ceiling(Cell *cell)
{
    if (!cell)
    {
        return false;
    }

    if (cell->ceiling_index != FLOORS_NONE && cell->floor_index != FLOORS_NONE)
    {
        return false;
    }

    return true;
}

void object_copy(Object *to, Object *from)
{
    if (!to)
    {
        return;
    }

    int i = 0;

    if (from == NULL)
    {
        to->pan = OBJ_DEF_PAN;

        to->is_occupied = false;
        to->type = OBJ_TYPE_NONE;
        to->index = OBJ_INDEX_NONE;
        for (i = 0; i < MAX_OBJECT_FLAGS; i++)
        {
            to->flag[i] = OBJ_FLAG_NONE;
        }

        return;
    }

    to->pan = from->pan;

    to->is_occupied = from->is_occupied;
    to->type = from->type;
    to->index = from->index;
    for (i = 0; i < MAX_OBJECT_FLAGS; i++)
    {
        to->flag[i] = from->flag[i];
    }
}

void cell_update_preview(int button_id, int type, int index)
{
    if (button_id == ASSET_LIST_BUTTON_ID_WALL)
    {
        preview_cell.wall_index = index;
    }
    else if (button_id == ASSET_LIST_BUTTON_ID_CEILING)
    {
        preview_cell.ceiling_index = index;
    }
    else if (button_id == ASSET_LIST_BUTTON_ID_FLOOR)
    {
        preview_cell.floor_index = index;
    }
    else if (button_id == ASSET_LIST_BUTTON_ID_OBJECT)
    {
        preview_cell.object.type = type;
        preview_cell.object.index = index;
    }
}

void cell_copy(Cell *to, Cell *from)
{
    if (!to)
    {
        return;
    }

    if (from == NULL)
    {
        to->is_solid = true;

        to->wall_index = CELL_INDEX_NONE;
        to->ceiling_index = CELL_INDEX_NONE;
        to->floor_index = CELL_INDEX_NONE;

        object_copy(&to->object, NULL);
        return;
    }

    to->is_solid = from->is_solid;

    to->wall_index = from->wall_index;
    to->ceiling_index = from->ceiling_index;
    to->floor_index = from->floor_index;

    object_copy(&to->object, &from->object);
}

Cell *map_get_neighbours(Map *map, VECTOR *pos, VECTOR *dir, var step)
{
    if (step <= 0)
    {
        step = 1;
    }

    VECTOR endpos, tempdir;
    vec_set(&tempdir, dir);
    vec_scale(&tempdir, step);
    vec_set(&endpos, pos);
    vec_add(&endpos, &tempdir);

    int x = endpos.x;
    int y = endpos.y;

    if (is_pos_on_grid(&endpos) == false)
    {
        return NULL;
    }

    return &map->cell[x][y];
}

Map *map_get_active(Episode *episode)
{
    if (!episode)
    {
        return NULL;
    }

    return &episode->map[active_map_id];
}

void map_copy(Map *to, Map *from)
{
    if (!to)
    {
        return;
    }

    if (from == NULL)
    {
        to->fog_start = MAP_DEF_FOG_START;
        to->fog_end = MAP_DEF_FOG_END;

        int i = 0;
        for (i = 0; i < 3; i++)
        {
            to->fog_color[i] = get_hsv_from_color(MAP_DEF_FOG_COLOR);
        }

        strcpy(to->music, "");

        int x = 0, y = 0;
        for (y = 0; y < MAP_HEIGHT; y++)
        {
            for (x = 0; x < MAP_WIDTH; x++)
            {
                Cell *cell = &to->cell[x][y];
                if (!cell)
                {
                    continue;
                }

                vec_set(&cell->pos, vector((MAP_CELL_SIZE * x), -(MAP_CELL_SIZE * y), MAP_Z_POS));

                cell->x = x;
                cell->y = y;

                cell_copy(cell, NULL);
            }
        }
        return;
    }

    to->fog_start = from->fog_start;
    to->fog_end = from->fog_end;

    int i = 0;
    for (i = 0; i < 3; i++)
    {
        to->fog_color[i] = from->fog_color[i];
    }

    strcpy(to->music, from->music);

    int x = 0, y = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            Cell *to_cell = &to->cell[x][y];
            Cell *from_cell = &from->cell[x][y];
            cell_copy(to_cell, from_cell);
        }
    }
}

void episode_set_filename(STRING *filename)
{
    strcpy(ep_filename, _chr(filename));
}

void episode_copy(Episode *to, Episode *from)
{
    if (!to)
    {
        return;
    }

    int i = 0;

    if (from == NULL)
    {
        active_map_id = 0;

        strcpy(to->name, "");
        to->map_count = 1;

        for (i = 0; i < MAX_MAPS_PER_EPISODE; i++)
        {
            map_copy(&to->map[i], NULL);
        }
        return;
    }

    strcpy(to->name, from->name);
    to->map_count = from->map_count;

    for (i = 0; i < to->map_count; i++)
    {
        map_copy(&to->map[i], &from->map[i]);
    }
}

void episode_edit_info(Episode *episode, char *name, int map_count)
{
    if (!episode)
    {
        return;
    }

    strcpy(episode->name, name);
    episode->map_count = map_count;
}

int episode_save(STRING *file_name, Episode *episode)
{
    if (!episode)
    {
        return false;
    }

    STRING *temp_str = "#256";
    str_cpy(temp_str, episode_save_folder_str);
    str_cat(temp_str, file_name);
    str_cat(temp_str, episode_extension_str);
    path_make_absolute(temp_str); // add 'save_dir' full path (in documents folder)

    void *returned_buffer = file_save(temp_str, episode, sizeof(Episode));
    if (returned_buffer == NULL)
    {
        return false;
    }

    return true;
}

int episode_load(STRING *file_name, Episode *episode)
{
    if (!episode)
    {
        return false;
    }

    STRING *temp_str = "#256";
    str_cpy(temp_str, episode_save_folder_str);
    str_cat(temp_str, file_name);
    str_cat(temp_str, episode_extension_str);
    path_make_absolute(temp_str); // add 'save_dir' full path (in documents folder)

    if (!file_exists(temp_str))
    {
        return false;
    }

    long _size = 0;
    void *buffer = file_load(temp_str, NULL, &_size);
    memcpy(episode, buffer, sizeof(Episode));
    void *returned_buffer = file_load(NULL, buffer, &_size);
    if (returned_buffer == NULL)
    {
        return false;
    }

    return true;
}