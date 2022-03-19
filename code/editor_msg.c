
void messages_show()
{
    if (!is(message_txt, SHOW))
    {
        set(message_txt, SHOW);
    }
}

void messages_hide()
{
    if (is(message_txt, SHOW))
    {
        reset(message_txt, SHOW);
    }
}

void messages_reset()
{
    int i = 0;
    for (i = 0; i < MAX_MESSAGES; i++)
    {
        str_cpy((message_txt->pstring)[i], "");
    }

    messages_hide();
}

void messages_initialize()
{
    message_txt = txt_create(MAX_MESSAGES, MESSAGES_LAYER);
    layer_sort(message_txt, MESSAGES_LAYER);
    set(message_txt, TRANSLUCENT | UNTOUCHABLE);
    message_txt->alpha = MESSAGES_ALPHA;
}

void messages_destroy()
{
    if (message_txt)
    {
        safe_remove(message_txt);
    }
}

void messages_update()
{
    if (message_txt)
    {
        message_txt->scale_x = config_saved.font_scale;
        message_txt->scale_y = config_saved.font_scale;

        message_txt->pos_x = 5;
        message_txt->pos_y = camera->pos_y + 5;

        int i = 0;
        for (i = 0; i < MAX_MESSAGES; i++)
        {
            message_timer[i] -= time_frame / 16;
            message_timer[i] = clamp(message_timer[i], -1, MESSAGE_FADE_SPEED);
            if (message_timer[i] <= 0)
            {
                str_cpy((message_txt->pstring)[i], "");
            }
        }
    }
}

void message_add(STRING *msg)
{
    if (editor_state != EDITOR_STATE_BUILD && editor_state != EDITOR_STATE_MAP_SETTINGS)
    {
        int i = 0;
        for (i = MAX_MESSAGES - 1; i > 0; i--)
        {
            str_cpy((message_txt->pstring)[i], (message_txt->pstring)[i - 1]);
            message_timer[i] = message_timer[i - 1];
        }
        message_timer[0] = MESSAGE_FADE_SPEED;
        str_cpy((message_txt->pstring)[0], msg);
        messages_show();
    }

    snd_play(beep_ogg, beep_volume, 0);
}