
int light_get_id(STRING *character)
{
    int i = 0;
    for (i = 0; i < str_len(light_factor_str); i++)
    {
        STRING *c = "";
        str_cut(c, light_factor_str, i + 1, i + 1);

        if (str_cmpi(character, c) == true)
        {
            return i;
        }
    }
}

void flicker_lightstyle()
{
    var loop_time = 0.1;
    var light_timer = 0;

    while (editor_state != EDITOR_STATE_EXIT)
    {
        int i = 0, id = -1;
        while (i < str_len(lightstyle_flicker_str))
        {
            STRING *c = "";
            str_cut(c, lightstyle_flicker_str, i + 1, i + 1);

            id = light_get_id(c);
            flicker_light_factor = id / (str_len(light_factor_str) - 1);

            light_timer = 0;
            while (light_timer < loop_time)
            {
                light_timer += time_frame / 16;
                wait(1);
            }

            i++;
        }
    }
}

void pulse_lightstyle()
{
    var loop_time = 0.1;
    var light_timer = 0;

    while (editor_state != EDITOR_STATE_EXIT)
    {
        int i = 0, id = -1;
        while (i < str_len(lightstyle_pulse_str))
        {
            STRING *c = "";
            str_cut(c, lightstyle_pulse_str, i + 1, i + 1);

            id = light_get_id(c);
            pulse_light_factor = id / (str_len(light_factor_str) - 1);

            light_timer = 0;
            while (light_timer < loop_time)
            {
                light_timer += time_frame / 16;
                wait(1);
            }

            i++;
        }
    }
}

void strobe_lightstyle()
{
    var loop_time = 0.1;
    var light_timer = 0;

    while (editor_state != EDITOR_STATE_EXIT)
    {
        int i = 0, id = -1;
        while (i < str_len(lightstyle_strobe_str))
        {
            STRING *c = "";
            str_cut(c, lightstyle_strobe_str, i + 1, i + 1);

            id = light_get_id(c);
            strobe_light_factor = id / (str_len(light_factor_str) - 1);

            light_timer = 0;
            while (light_timer < loop_time)
            {
                light_timer += time_frame / 16;
                wait(1);
            }

            i++;
        }
    }
}

void candle_lightstyle()
{
    var loop_time = 0.1;
    var light_timer = 0;

    while (editor_state != EDITOR_STATE_EXIT)
    {
        int i = 0, id = -1;
        while (i < str_len(lightstyle_candle_str))
        {
            STRING *c = "";
            str_cut(c, lightstyle_candle_str, i + 1, i + 1);

            id = light_get_id(c);
            candle_light_factor = id / (str_len(light_factor_str) - 1);

            light_timer = 0;
            while (light_timer < loop_time)
            {
                light_timer += time_frame / 16;
                wait(1);
            }

            i++;
        }
    }
}

void global_lightstyle()
{
    var loop_time = 0.1;
    var light_timer = 0;

    while (editor_state != EDITOR_STATE_EXIT)
    {
        int i = 0, id = -1;
        while (i < str_len(global_style_str))
        {
            STRING *c = "";
            str_cut(c, global_style_str, i + 1, i + 1);

            id = light_get_id(c);
            global_light_factor = id / (str_len(light_factor_str) - 1);

            light_timer = 0;
            while (light_timer < loop_time)
            {
                light_timer += time_frame / 16;
                wait(1);
            }

            i++;
        }
    }
}

void lightstyles()
{
    flicker_lightstyle();
    pulse_lightstyle();
    strobe_lightstyle();
    candle_lightstyle();
    global_lightstyle();
}