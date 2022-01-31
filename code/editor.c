
void editor_switch_state_to(int state)
{
    editor_old_state = editor_state;
    editor_state = state;
}

void editor_create_tooltip(STRING *tooltip)
{
    if (imgui_is_item_hovered())
    {
        imgui_set_tooltip(_chr(tooltip));
        imgui_begin_tooltip();
        imgui_end_tooltip();
    }
}

void editor_help_maker(char *desc)
{
    imgui_text_disabled("(?)");
    if (imgui_is_item_hovered())
    {
        imgui_begin_tooltip();
        imgui_push_text_wrap_pos(imgui_get_font_size() * 35);
        imgui_text_unformatted(desc);
        imgui_pop_text_wrap_pos();
        imgui_end_tooltip();
    }
}

// imgui handles color range from 0...1
// so I do this dumb trick to get 0...255 value
float get_hsv_from_color(float value)
{
    return value / 255;
}

float get_color_from_hsv(float value)
{
    return value * 255;
}

void editor_camera_resize(int is_shrinked)
{
    if (is_shrinked == true)
    {
        camera->pos_x = 0;
        camera->pos_y = EDITOR_TOP_BAR_HEIGHT;
        camera->size_x = screen_size.x - EDITOR_SIDE_BAR_WIDTH;
        camera->size_y = screen_size.y - EDITOR_TOP_BAR_HEIGHT;
    }
    else
    {
        camera->pos_x = 0;
        camera->pos_y = 0;
        camera->size_x = screen_size.x;
        camera->size_y = screen_size.y;
    }
}

STRING *get_cell_info(Cell *cell)
{
    if (!cell)
    {
        return NULL;
    }

    VECTOR cellpos;
    vec_set(&cellpos, &cell->worldpos);

    int cell_id = cell->id;
    int cell_x = cell->x;
    int cell_y = cell->y;
    int cell_type = cell->type;
    int cell_asset_index = cell->asset_index;

    var cell_skill_x = cell->skill_x;
    var cell_skill_y = cell->skill_y;
    var cell_skill_z = cell->skill_z;

    Obj *cell_object = &cell->object;

    var obj_pan = cell_object->pan;

    int obj_type = cell_object->type;
    int obj_asset_index = cell_object->asset_index;

    var obj_skill_x = cell_object->skill_x;
    var obj_skill_y = cell_object->skill_y;
    var obj_skill_z = cell_object->skill_z;

    STRING *info_str = "";
    str_cpy(info_str, "");
    str_printf(info_str, "world position:\nx = %d; y = %d; z = %d;\n\non grid position:\nx = %d; y = %d;\n\nid = %d;\n", (long)(cellpos.x), (long)(cellpos.y), (long)(cellpos.z), (long)(cell_x), (long)(cell_y), (long)(cell_id));

    if (cell_type == EDITOR_ASSET_WALLS)
    {
        str_cat(info_str, "\ntype: wall;");
        if (cell_asset_index > 0)
        {
            str_cat(info_str, "\nasset: ");
            str_cat(info_str, asset_get_desc(ASSET_TYPE_WALL, cell_asset_index));
            str_cat(info_str, ";");
        }
        else
        {
            str_cat(info_str, "\nasset: none;");
        }
    }
    else if (cell_type == EDITOR_ASSET_OBJECTS)
    {
        str_cat(info_str, "\ntype: object;");
        if (cell_asset_index > 0)
        {
            str_cat(info_str, "\nasset: ");
            str_cat(info_str, asset_get_desc(ASSET_TYPE_OBJECT, cell_asset_index));
            str_cat(info_str, ";");

            str_cat(info_str, str_printf(NULL, "pan = %d;\nskill_x = %d;\n\nskill_y = %d;\nskill_z = %d;", (long)obj_pan, (long)obj_skill_x, (long)obj_skill_y, (long)obj_skill_z));
        }
        else
        {
            str_cat(info_str, "\nasset: none;");
        }
    }
    else
    {
        str_cat(info_str, "\ntype: none;");
        str_cat(info_str, "\nasset: none;");
    }

    str_cat(info_str, str_printf(NULL, "\n\ntile skill_x = %d;\ntile skill_y = %d;\ntile skill_z = %d;", (long)(cell_skill_x), (long)(cell_skill_y), (long)(cell_skill_z)));
    str_cat(info_str, "\n");

    return info_str;
}

STRING *draw_cell_info(Episode *e, int x, int y)
{
    if (is_pos_on_grid(vector(x, y, 0)) == false)
    {
        return NULL;
    }

    if (!e)
    {
        return NULL;
    }

    Map *map = &e->map[current_map_id];
    if (!map)
    {
        return NULL;
    }

    Cell *cell = &map->cells[x][y];
    if (!cell)
    {
        return NULL;
    }

    return get_cell_info(cell);
}