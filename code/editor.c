
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

float get_hsv_from_color(float value)
{
    return value / 255;
}

float get_color_from_hsv(float value)
{
    return value * 255;
}

void editor_camera_resize()
{
    if (editor_state == STATE_EDITOR)
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

STRING *get_cell_info(Cell *c)
{
    if (!c)
    {
        return NULL;
    }

    VECTOR cell_pos;
    vec_set(&cell_pos, &c->worldpos);
    var cell_pan = c->pan;

    int cell_id = c->id;
    int cell_x = c->x;
    int cell_y = c->y;

    int cell_type = c->type;
    int cell_asset = c->asset;

    var cell_skill_x = c->skill_x;
    var cell_skill_y = c->skill_y;
    var cell_skill_z = c->skill_z;

    STRING *info_str = "";
    str_printf(info_str, "world position:\nx = %d; y = %d; z = %d;\n\ngrid position:\nx = %d; y = %d;\n\npan = %.0f;\nid = %d;", (long)cell_pos.x, (long)cell_pos.y, (long)cell_pos.z, (long)cell_x, (long)cell_y, (double)cell_pan, (long)cell_id);

    if (cell_type < 0)
    {
        str_cat(info_str, "\ntype: none;");
        str_cat(info_str, "\nasset: none;");
    }
    else
    {
        switch (cell_type)
        {
        case ASSET_TYPE_WALL:
            str_cat(info_str, "\ntype: wall;");
            break;

        case ASSET_TYPE_PROPS:
            str_cat(info_str, "\ntype: props;");
            break;

        case ASSET_TYPE_ITEMS:
            str_cat(info_str, "\ntype: item;");
            break;

        case ASSET_TYPE_WEAPON:
            str_cat(info_str, "\ntype: weapon;");
            break;

        case ASSET_TYPE_ENEMIES:
            str_cat(info_str, "\ntype: enemy;");
            break;

        case ASSET_TYPE_BOSSES:
            str_cat(info_str, "\ntype: boss;");
            break;
        }

        str_cat(info_str, "\nasset: ");
        str_cat(info_str, asset_get_desc(cell_type, cell_asset));
        str_cat(info_str, ";");
    }

    str_cat(info_str, str_printf(NULL, "\n\nskill_x = %.0f;\nskill_y = %.0f;\nskill_z = %.0f;", (double)(cell_skill_x), (double)(cell_skill_y), (double)(cell_skill_z)));

    return info_str;
}

STRING *draw_cell_info(Map *m, int x, int y)
{
    if (!m)
    {
        return NULL;
    }

    if (is_allowed_to_draw() == false)
    {
        return NULL;
    }

    Cell *c = &m->cell[x][y];
    if (!c)
    {
        return NULL;
    }

    return get_cell_info(c);
}