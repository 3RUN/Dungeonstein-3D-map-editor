
int is_pos_on_grid(VECTOR *pos)
{
    if (!pos)
    {
        return false;
    }

    return (pos->x >= 0 && pos->x < MAP_WIDTH && pos->y >= 0 && pos->y < MAP_HEIGHT);
}

int is_pos_within_camera(VECTOR *pos)
{
    if (!pos)
    {
        return false;
    }

    return (pos->x >= camera->pos_x && pos->x < camera->size_x && pos->y >= camera->pos_y && pos->y < camera->size_y);
}

int is_allowed_to_draw_map()
{
    if (is_settings_opened == true || is_popup_opened == true || is_help_opened == true)
    {
        return false;
    }

    if (is_pos_on_grid(vector(vec_mouse_on_grid.x, -vec_mouse_on_grid.y, 0)) == false)
    {
        return false;
    }

    if (is_pos_within_camera(vector(mouse_pos.x, mouse_pos.y, 0)) == false)
    {
        return false;
    }

    return true;
}

ENTITY *grid_get_ent(int id)
{
    ENTITY *ent = array_get_element_at(ENTITY *, grid_ents, id);
    return ent;
}

void grid_get_mouse_pos(int *x, int *y)
{
    if (is_allowed_to_draw_map() == true)
    {
        *x = vec_mouse_on_grid.x;
        *y = -vec_mouse_on_grid.y;
    }
    else
    {
        *x = 0;
        *y = 0;
    }
}

void grid_draw(VECTOR *center, var grid_size, int width, int height, COLOR *color)
{
    int lines_x = width + 1;
    int lines_y = height + 1;
    var bounds_x = (lines_x - 1) / 2.0 * grid_size;
    var bounds_y = (lines_y - 1) / 2.0 * grid_size;

    VECTOR start, end;
    vec_set(&start, center);
    vec_set(&end, center);
    start.x -= bounds_x;
    start.y -= bounds_y;
    end.x -= bounds_x;
    end.y += bounds_y;

    int i = 0;
    for (i = 0; i < lines_x; i++)
    {
        draw_line3d(&start, color, 0);
        draw_line3d(&start, color, 100);
        draw_line3d(&end, color, 100);
        draw_line3d(&end, color, 0);
        start.x = end.x = start.x + grid_size;
    }

    vec_set(&start, center);
    vec_set(&end, center);
    start.x -= bounds_x;
    start.y -= bounds_y;
    end.x += bounds_x;
    end.y -= bounds_y;

    for (i = 0; i < lines_y; i++)
    {
        draw_line3d(&start, color, 0);
        draw_line3d(&start, color, 100);
        draw_line3d(&end, color, 100);
        draw_line3d(&end, color, 0);
        start.y = end.y = start.y + grid_size;
    }
}

void grid_ent()
{
    set(my, PASSABLE | INVISIBLE | NOFILTER);
    ent_clone(my);
}

void grid_entity_refresh(ENTITY *ent, VECTOR *pos, var pan, int id, int x, int y, int type, int index)
{
    if (!ent)
    {
        return;
    }

    set(ent, INVISIBLE);
    vec_set(&ent->x, pos);
    ent->pan = pan;
    ent->OBJ_ID = id;
    ent->OBJ_POS_X = x;
    ent->OBJ_POS_Y = y;
    ent->OBJ_TYPE_INDEX = type;
    ent->OBJ_ASSET_INDEX = index;

    // update the skin here if needed
    if (type >= 0)
    {
        reset(ent, INVISIBLE);
        ent_setskin(ent, asset_get_bmap(type, index), 1);
    }
}

void grid_refresh_map(Map *m)
{
    if (!m)
    {
        return;
    }

    int x = 0, y = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            Cell *cell = &m->cells[x][y];

            VECTOR pos;
            vec_set(&pos, &cell->worldpos);

            int cell_id = cell->id;
            int cell_x = cell->x;
            int cell_y = cell->y;

            int cell_type = cell->type;
            int cell_asset_index = cell->asset_index;

            ENTITY *ent = grid_get_ent(cell_id);
            grid_entity_refresh(ent, &pos, 0, cell_id, cell_x, cell_y, cell_type, cell_asset_index);
        }
    }
}

void grid_create_tiles()
{
    int x = 0, y = 0;
    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            ENTITY *tile = ent_create(tile_mdl, nullvector, grid_ent);
            array_add(ENTITY *, grid_ents, tile);
        }
    }
}

void grid_initialize()
{
    grid_ents = array_create(ENTITY *, 1);
}

void grid_clear()
{
    array_enumerate_begin(ENTITY *, grid_ents, v)
    {
        ptr_remove(v);
    }
    array_enumerate_end(grid_ents);
    array_clear(grid_ents);

    grid_create_tiles();
}

void grid_destroy()
{
    array_enumerate_begin(ENTITY *, grid_ents, v)
    {
        ptr_remove(v);
    }
    array_enumerate_end(grid_ents);
    array_destroy(grid_ents);
}

void grid_update()
{
    VECTOR grid_draw_offset;
    vec_set(&grid_draw_offset, vector(0, 0, GRID_DRAW_OFFSET));
    vec_add(&grid_draw_offset, &vec_grid_center);

    if (is_grid_visible == true)
    {
        COLOR grid_color;
        grid_color.red = get_color_from_hsv(config_current.grid_color[0]);
        grid_color.green = get_color_from_hsv(config_current.grid_color[1]);
        grid_color.blue = get_color_from_hsv(config_current.grid_color[2]);
        grid_draw(&grid_draw_offset, MAP_CELL_SIZE, MAP_WIDTH, MAP_HEIGHT, &grid_color);
    }
}