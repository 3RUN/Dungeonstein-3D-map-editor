
void game_debug_panel_initialize()
{
    debug_pan = pan_create(NULL, DEBUG_PANEL_LAYER);
    layer_sort(debug_pan, DEBUG_PANEL_LAYER);
    set(debug_pan, TRANSLUCENT);
    debug_pan->alpha = DEBUG_PANEL_ALPHA;

    pan_setdigits(debug_pan, 0, 0, 2, "%4.0fx", debug_ackfont, 1, &screen_size.x);
    pan_setdigits(debug_pan, 0, 30, 2, "%.0f", debug_ackfont, 1, &screen_size.y);
    pan_setdigits(debug_pan, 0, 0, 12, "fps%5.0f", debug_ackfont, 16, &def_dfps);
    pan_setdigits(debug_pan, 0, 0, 22, "pps%5.0fk", debug_ackfont, 0.016, &def_dtps);
    pan_setdigits(debug_pan, 0, 0, 32, "x%7.0f", debug_ackfont, 1, &camera->x);
    pan_setdigits(debug_pan, 0, 0, 42, "y%7.0f", debug_ackfont, 1, &camera->y);
    pan_setdigits(debug_pan, 0, 0, 52, "z%7.0f", debug_ackfont, 1, &camera->z);
    pan_setdigits(debug_pan, 0, 0, 62, "pan%5.0f", debug_ackfont, 1, &camera->pan);
    pan_setdigits(debug_pan, 0, 0, 72, "til%5.0f", debug_ackfont, 1, &camera->tilt);
    pan_setdigits(debug_pan, 0, 0, 82, "rol%5.0f", debug_ackfont, 1, &camera->roll);

    pan_setstring(debug_pan, 0, 65, 2, debug_ackfont, debug_ms_frame_str);
    pan_setdigits(debug_pan, 0, 65, 12, "geo%5.1f", debug_ackfont, 1, &def_dtlv);
    pan_setdigits(debug_pan, 0, 65, 22, "ent%5.1f", debug_ackfont, 1, &time_entities);
    pan_setdigits(debug_pan, 0, 65, 32, "par%5.1f", debug_ackfont, 1, &time_effects);
    pan_setdigits(debug_pan, 0, 65, 42, "drw%5.1f", debug_ackfont, 1, &time_draw);
    pan_setdigits(debug_pan, 0, 65, 52, "pan%5.1f", debug_ackfont, 1, &time_panels);
    pan_setdigits(debug_pan, 0, 65, 62, "ref%5.1f", debug_ackfont, 1, &def_dtrf);
    pan_setdigits(debug_pan, 0, 65, 72, "srv%5.1f", debug_ackfont, 1, &def_dtcs);
    pan_setdigits(debug_pan, 0, 65, 82, "fnc%5.1f", debug_ackfont, 1, &def_dtac);

    pan_setstring(debug_pan, 0, 130, 2, debug_ackfont, debug_count_of_str);
    pan_setdigits(debug_pan, 0, 130, 12, "ent%5.0f", debug_ackfont, 1, &num_entities);
    pan_setdigits(debug_pan, 0, 130, 22, "vis%5.0f", debug_ackfont, 1, &num_visents);
    pan_setdigits(debug_pan, 0, 130, 32, "tri%5.0fk", debug_ackfont, 0.001, &num_vistriangles);
    pan_setdigits(debug_pan, 0, 130, 42, "par%5.0f", debug_ackfont, 1, &num_particles);
    pan_setdigits(debug_pan, 0, 130, 52, "lit%5.0f", debug_ackfont, 1, &num_lights);
    pan_setdigits(debug_pan, 0, 130, 62, "snd%5.0f", debug_ackfont, 1, &def_dsnd);
    pan_setdigits(debug_pan, 0, 130, 72, "fnc%5.0f", debug_ackfont, 1, &num_actions);
    pan_setdigits(debug_pan, 0, 130, 82, "bdy%5.0f", debug_ackfont, 1, &num_bodies);

    pan_setstring(debug_pan, 0, 200, 2, debug_ackfont, debug_memory_MB_str);
    pan_setdigits(debug_pan, 0, 200, 12, "nex%5.0f", debug_ackfont, 1, &nexus);
    pan_setdigits(debug_pan, 0, 200, 22, "mem%5.0f", debug_ackfont, 1, &sys_memory);
    pan_setdigits(debug_pan, 0, 200, 32, "geo%5.0f", debug_ackfont, 1, &d3d_texsurfs);
    pan_setdigits(debug_pan, 0, 200, 42, "shd%5.0f", debug_ackfont, 1, &d3d_texsmaps);
    pan_setdigits(debug_pan, 0, 200, 52, "ent%5.0f", debug_ackfont, 1, &d3d_texskins);
    pan_setdigits(debug_pan, 0, 200, 62, "fre%5.0f", debug_ackfont, 1, &d3d_texfree);

    pan_setstring(debug_pan, 0, 270, 2, debug_ackfont, debug_network_str);
    pan_setdigits(debug_pan, 0, 270, 12, "lat%4.0f", debug_ackfont, 1, &dplay_latency);
    pan_setdigits(debug_pan, 0, 270, 22, "bps%4.0f", debug_ackfont, 1, &dplay_bps);
    pan_setdigits(debug_pan, 0, 270, 32, "rel%4.0f", debug_ackfont, 1, &dplay_bpsreliable);
    pan_setdigits(debug_pan, 0, 270, 42, "unr%4.0f", debug_ackfont, 1, &dplay_bpsunreliable);
    pan_setdigits(debug_pan, 0, 270, 52, "com%4.0f", debug_ackfont, 1, &dplay_compression);
    pan_setdigits(debug_pan, 0, 270, 62, "num%4.0f", debug_ackfont, 1, &num_clients);
}

void game_debug_panel_destroy()
{
    safe_remove(debug_pan);
}

void game_debug_panel_show()
{
    if (!is(debug_pan, SHOW))
    {
        set(debug_pan, SHOW);
    }
}

void game_debug_panel_hide()
{
    if (is(debug_pan, SHOW))
    {
        reset(debug_pan, SHOW);
    }
}

void game_debug_panel_update()
{
    def_dfps = 0.9 * def_dfps + 0.1 / time_frame;
    def_dtps = 0.9 * def_dtps + 0.1 * num_vistriangles / time_frame;
    def_dtlv = time_level + time_sky;
    def_dtcs = time_client + time_server;
    def_dtrf = time_update + time_idle;
    def_dtac = time_actions + time_pfuncs;
    def_dsnd = num_mediastreams + num_sounds;

    if (debug_pan)
    {
        debug_pan->pos_x = camera->size_x - 320;
        debug_pan->pos_y = camera->pos_y + 7;

        if (is_debug_panel_visible == true)
        {
            game_debug_panel_show();
        }
        else
        {
            game_debug_panel_hide();
        }
    }
}