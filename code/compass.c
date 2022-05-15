
void compass_initialize()
{
    compass_pan = compass_pan_create(compass_pcx, NULL, 2, 25, OVERLAY | TRANSLUCENT | UNTOUCHABLE | SHOW);
    int i = 0;
    for (i = 0; i < MAX_DIRECTION_STEP; i++)
    {
        compass_txt[i] = compass_txt_create(font_arial_12b, COLOR_WHITE, 1, 1, 50, SHOW | CENTER_X | OUTLINE);

        switch (i)
        {
        case DIRECTION_N:
            str_cpy((compass_txt[i]->pstring)[0], "N");
            break;

        case DIRECTION_W:
            str_cpy((compass_txt[i]->pstring)[0], "W");
            break;

        case DIRECTION_S:
            str_cpy((compass_txt[i]->pstring)[0], "S");
            break;

        case DIRECTION_E:
            str_cpy((compass_txt[i]->pstring)[0], "E");
            break;
        }
    }
}

void compass_destroy()
{
    safe_remove(compass_pan);

    int i = 0;
    for (i = 0; i < MAX_DIRECTION_STEP; i++)
    {
        safe_remove(compass_txt[i]);
    }
}

void compass_hide()
{
    if (compass_pan)
    {
        if (is(compass_pan, SHOW))
        {
            reset(compass_pan, SHOW);
        }
    }

    int i = 0;
    for (i = 0; i < MAX_DIRECTION_STEP; i++)
    {
        if (compass_txt[i])
        {
            if (is(compass_txt[i], SHOW))
            {
                reset(compass_txt[i], SHOW);
            }
        }
    }
}

void compass_show()
{
    if (compass_pan)
    {
        if (!is(compass_pan, SHOW))
        {
            set(compass_pan, SHOW);
        }
    }

    int i = 0;
    for (i = 0; i < MAX_DIRECTION_STEP; i++)
    {
        if (compass_txt[i])
        {
            if (!is(compass_txt[i], SHOW))
            {
                set(compass_txt[i], SHOW);
            }
        }
    }
}

void compass_update()
{
    if (editor_state != EDITOR_STATE_EDIT)
    {
        compass_hide();
        return;
    }

    compass_show();

    var compass_width = bmap_width(compass_pcx);

    compass_pan->pos_x = (screen_size.x / 2) - (compass_width / 2);
    compass_pan->pos_y = screen_size.y - 64;

    compass_directions_update(&camera->x);

    int i = 0;
    for (i = 0; i < MAX_DIRECTION_STEP; i++)
    {
        var compass_cardinal_dir = compass_get_direction_to_target(&camera->x, camera->pan, &compass_direction_vec[i]);
        compass_direction(compass_txt[i], compass_pan, compass_cardinal_dir);
    }
}

void compass_directions_update(VECTOR *origin)
{
    var pan = 0;

    int i = 0;
    for (i = 0; i < MAX_DIRECTION_STEP; i++)
    {
        vec_set(&compass_direction_vec[i], vector(64, 0, 0));
        vec_rotate(&compass_direction_vec[i], vector(pan, 0, 0));
        vec_add(&compass_direction_vec[i], origin);
        pan += DIRECTION_PAN_STEP;
    }
}

PANEL *compass_pan_create(BMAP *bmap, COLOR *color, var layer, var alpha, long flags)
{
    PANEL *pan = pan_create(NULL, 0);
    if (!pan)
    {
        return NULL;
    }

    if (color != NULL)
    {
        vec_set(&pan->blue, color);
    }

    layer_sort(pan, layer);
    pan->alpha = alpha;
    pan->bmap = bmap;
    set(pan, flags);
    return pan;
}

TEXT *compass_txt_create(FONT *font, COLOR *color, var strings, var layer, var alpha, long flags)
{
    TEXT *txt = txt_create(strings, 0);
    if (!txt)
    {
        return NULL;
    }

    if (color != NULL)
    {
        vec_set(&txt->blue, color);
    }

    layer_sort(txt, layer);
    txt->font = font;
    txt->alpha = alpha;
    set(txt, flags);
    return txt;
}

var compass_get_direction_to_target(VECTOR *from_vec, var from_pan, VECTOR *target_vec)
{
    ANGLE direction_angle;
    vec_to_angle(&direction_angle, vec_diff(NULL, target_vec, from_vec));
    direction_angle.pan = ang(direction_angle.pan - from_pan);
    return direction_angle.pan;
}

void compass_direction(TEXT *direction_txt, PANEL *compass, var direction)
{
    if (!direction_txt || !compass)
    {
        return;
    }

    var compass_width = bmap_width(compass->bmap);
    var compass_height = bmap_height(compass->bmap);
    var compass_min_width = -compass_width / 2;
    var compass_max_width = compass_width / 2;

    direction_txt->skill_x = direction;
    direction_txt->skill_x = clamp(direction_txt->skill_x, compass_min_width, compass_max_width);

    direction_txt->pos_x = (compass->pos_x + (compass_width / 2)) - direction_txt->skill_x;
    direction_txt->pos_y = compass->pos_y + compass_height;

    if (direction_txt->skill_x > compass_min_width + 5 && direction_txt->skill_x < compass_max_width - 5)
    {
        set(direction_txt, SHOW);
    }
    else
    {
        reset(direction_txt, SHOW);
    }
}