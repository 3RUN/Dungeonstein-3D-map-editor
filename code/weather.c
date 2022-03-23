
void vec_randomize(VECTOR *vec, var range)
{
    vec_set(vec, vector(random(1) - 0.5, random(1) - 0.5, random(1) - 0.5));
    vec_normalize(vec, random(range));
}

void particle_hide(PARTICLE *p)
{
    if (editor_state != EDITOR_STATE_BUILD && editor_state != EDITOR_STATE_MAP_SETTINGS)
    {
        p->lifespan = 0;
    }
}

void weather_impact_particle_event(PARTICLE *p)
{
    p->alpha -= p->skill_x * time_step;
    if (p->alpha < 0)
    {
        p->lifespan = 0;
    }
    else
    {
        p->lifespan = 1;
    }

    if (p->z < WEATHER_PARTICLE_Z_LIMIT)
    {
        p->z = WEATHER_PARTICLE_Z_LIMIT + WEATHER_PARTICLE_Z_OFFSET;
        vec_fill(&p->vel_x, 0);
        p->gravity = 0;
    }

    particle_hide(p);
}

void weather_rain_splash_particle(PARTICLE *p)
{
    vec_randomize(&p->vel_x, rain_splash_spread);
    p->vel_z = rain_splash_vel_z + random(rain_splash_random_vel_z);
    p->gravity = rain_splash_gravity;

    set(p, MOVE | NOFILTER | TRANSLUCENT);
    p->bmap = weather_particle_pcx;
    p->size = rain_splash_size + random(rain_splash_random_size);
    p->alpha = rain_splash_alpha + random(rain_splash_random_alpha);
    p->skill_x = rain_splash_fadeout_speed;

    p->event = weather_impact_particle_event;
}

void weather_snow_impact_particle(PARTICLE *p)
{
    set(p, MOVE | NOFILTER | TRANSLUCENT);
    p->bmap = weather_particle_pcx;
    p->size = snow_splash_size + random(snow_splash_random_size);
    p->alpha = snow_splash_alpha + random(snow_splash_random_alpha);
    p->skill_x = snow_splash_fadeout_speed;

    p->event = weather_impact_particle_event;
}

void weather_particle_event(PARTICLE *p)
{
    if (p->z < WEATHER_PARTICLE_Z_LIMIT)
    {
        VECTOR particle_pos;
        vec_set(&particle_pos, vector(p->x, p->y, WEATHER_PARTICLE_Z_LIMIT + WEATHER_PARTICLE_Z_OFFSET));

        if (p->skill_x == 0)
        {
            effect(weather_rain_splash_particle, maxv(2, rain_splash_density * time_step), &particle_pos, nullvector);
        }
        else if (p->skill_x == 1)
        {
            effect(weather_snow_impact_particle, maxv(1, 1 * time_step), &particle_pos, nullvector);
        }
        vec_set(&p->vel_x, nullvector);
        p->lifespan = 0;
    }
    else
    {
        p->lifespan = 1;
        p->x = cycle(p->x, camera->x - weather_seedbox.x, camera->x + weather_seedbox.x);
        p->y = cycle(p->y, camera->y - weather_seedbox.y, camera->y + weather_seedbox.y);
        p->z = cycle(p->z, WEATHER_PARTICLE_Z_LIMIT, weather_seedbox.z);
    }

    particle_hide(p);
}

void weather_rain_particle(PARTICLE *p)
{
    p->x = camera->x + random(weather_seedbox.x * 2) - weather_seedbox.x;
    p->y = camera->y + random(weather_seedbox.y * 2) - weather_seedbox.y;
    p->z = weather_seedbox.z;

    vec_set(&p->vel_x, &weather_velocity);

    set(p, MOVE | NOFILTER | TRANSLUCENT | BEAM);
    p->bmap = weather_particle_pcx;
    p->size = random(rain_random_size) + rain_size;
    p->alpha = random(rain_random_alpha) + rain_alpha;
    p->skill_x = 0; // rain

    p->event = weather_particle_event;
}

void weather_snow_particle(PARTICLE *p)
{
    p->x = camera->x + random(weather_seedbox.x * 2) - weather_seedbox.x;
    p->y = camera->y + random(weather_seedbox.y * 2) - weather_seedbox.y;
    p->z = weather_seedbox.z;

    vec_set(&p->vel_x, &weather_velocity);

    set(p, MOVE | NOFILTER | TRANSLUCENT);
    p->bmap = weather_particle_pcx;
    p->size = random(snow_random_size) + snow_size;
    p->alpha = random(snow_random_alpha) + snow_alpha;
    p->skill_x = 1; // snow

    p->event = weather_particle_event;
}

void weather_update(int type)
{
    if (type < WEATHER_RAIN)
    {
        return;
    }

    weather_seedbox.x = WEATHER_SEEDBOX_LENGTH / 2;
    weather_seedbox.y = WEATHER_SEEDBOX_WIDTH / 2;
    weather_seedbox.z = WEATHER_SEEDBOX_HEIGHT;

    if (type == WEATHER_RAIN)
    {
        weather_velocity.x = rain_wind_x + ((rain_random_move / 2) - random(rain_random_move));
        weather_velocity.y = rain_wind_y + ((rain_random_move / 2) - random(rain_random_move));
        weather_velocity.z = -rain_fallspeed;

        effect(weather_rain_particle, maxv(1, rain_density * time_step), nullvector, nullvector);
    }
    else if (type == WEATHER_SNOW)
    {
        weather_velocity.x = snow_wind_x + ((snow_random_move / 2) - random(snow_random_move));
        weather_velocity.y = snow_wind_y + ((snow_random_move / 2) - random(snow_random_move));
        weather_velocity.z = -snow_fallspeed;

        effect(weather_snow_particle, maxv(1, snow_density * time_step), nullvector, nullvector);
    }
}

void weather_pause_sound()
{
    snd_pause(weather_sound_handle);
}

void weather_resume_sound()
{
    snd_start(weather_sound_handle);
}

void weather_stop_sound()
{
    if (!snd_playing(weather_sound_handle))
    {
        return;
    }

    weather_sound_volume = 0;
    snd_stop(weather_sound_handle);
}

void weather_play_sound(int type)
{
    if (type == WEATHER_CLEAR)
    {
        weather_stop_sound();
        return;
    }

    if (snd_playing(weather_sound_handle))
    {
        weather_sound_volume = 0;
        snd_stop(weather_sound_handle);
    }

    if (type == WEATHER_RAIN)
    {
        weather_sound_handle = snd_loop(weather_rain_ogg, 0, 0);
    }
    else if (type == WEATHER_SNOW)
    {
        weather_sound_handle = snd_loop(weather_snow_ogg, 0, 0);
    }

    while (weather_sound_volume < weather_sound_volume_target)
    {
        if (!snd_playing(weather_sound_handle))
        {
            break;
        }

        weather_sound_volume += weather_sound_volume_fade_speed_factor * time_step;
        weather_sound_volume = clamp(weather_sound_volume, 0, weather_sound_volume_target);
        snd_tune(weather_sound_handle, weather_sound_volume, 0, 0);
        wait(1);
    }
}