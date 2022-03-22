
void messages_initialize()
{
    var i = 0;
    for (i = 0; i < MAX_MESSAGES; i++)
    {
        message_pan[i] = pan_create(NULL, 0);
        layer_sort(message_pan[i], MESSAGES_LAYER);
        set(message_pan[i], TRANSLUCENT | UNTOUCHABLE);
        message_pan[i]->alpha = 0;

        message_str[i] = str_create("");
        pan_setstring(message_pan[i], 0, 0, 0, message_font, message_str[i]);
    }
}

void messages_destroy()
{
    var i = 0;
    for (i = 0; i < MAX_MESSAGES; i++)
    {
        if (message_pan[i])
        {
            safe_remove(message_pan[i]);
            message_pan[i] = NULL;
        }

        if (message_str[i])
        {
            safe_remove(message_str[i]);
            message_str[i] = NULL;
        }
    }
}

void messages_show()
{
    var i = 0;
    for (i = 0; i < MAX_MESSAGES; i++)
    {
        if (!is(message_pan[i], SHOW))
        {
            set(message_pan[i], SHOW);
        }
    }
}

void messages_hide()
{
    var i = 0;
    for (i = 0; i < MAX_MESSAGES; i++)
    {
        if (is(message_pan[i], SHOW))
        {
            reset(message_pan[i], SHOW);
        }
    }
}

void messages_reset()
{
    var i = 0;
    for (i = 0; i < MAX_MESSAGES; i++)
    {
        if (message_str[i])
        {
            str_cpy(message_str[i], "");
        }
    }
    messages_hide();
}

void message_add(STRING *msg)
{
    if (editor_state != EDITOR_STATE_BUILD && editor_state != EDITOR_STATE_MAP_SETTINGS)
    {
        messages_total++;
        messages_total = clamp(messages_total, 0, MAX_MESSAGES);

        var i = 0;
        for (i = MAX_MESSAGES - 1; i > 0; i--)
        {
            str_cpy(message_str[i], message_str[i - 1]);
            message_pan[i]->alpha = message_pan[i - 1]->alpha;
        }
        message_pan[0]->alpha = MESSAGES_ALPHA;
        str_cpy(message_str[0], msg);
        messages_show();
    }

    snd_play(beep_ogg, snd_beep_volume, 0);
}

void messages_update()
{
    var i = 0;
    for (i = 0; i < MAX_MESSAGES; i++)
    {
        if (message_pan[i])
        {
            message_pan[i]->scale_x = config_saved.font_scale;
            message_pan[i]->scale_y = config_saved.font_scale;

            message_pan[i]->pos_x = 5;
            message_pan[i]->pos_y = camera->pos_y + 5 + ((20 * message_pan[i]->scale_x) * i);
        }
    }

    var id = messages_total - 1;
    if (message_pan[id])
    {
        if (is(message_pan[id], SHOW))
        {
            message_pan[id]->alpha -= MESSAGE_FADE_SPEED * time_step;
            message_pan[id]->alpha = clamp(message_pan[id]->alpha, 0, MESSAGES_ALPHA);
            if (message_pan[id]->alpha <= 0)
            {
                str_cpy(message_str[id], "");
                messages_total--;
            }
        }
    }
}