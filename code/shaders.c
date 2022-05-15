
void shaders_initialize()
{
    pp_view = view_create(-1);
    set(pp_view, PROCESS_TARGET);

    mtl_solid = mtl_create();
    mtl_solid->flags = AUTORELOAD;
    effect_load(mtl_solid, "mtl_solid.fx");

    mtl_water = mtl_create();
    mtl_water->flags = AUTORELOAD;
    effect_load(mtl_water, "mtl_water.fx");

    mtl_marker = mtl_create();
    mtl_marker->flags = AUTORELOAD;
    effect_load(mtl_marker, "mtl_marker.fx");

    mtl_night_sky = mtl_create();
    mtl_night_sky->flags = AUTORELOAD;
    mtl_night_sky->skin1 = bmap_create(SKYCUBE_TGA);
    bmap_to_cubemap(mtl_night_sky->skin1);
    effect_load(mtl_night_sky, "mtl_sky.fx");

    skycube_ent = ent_createlayer(SPHERE_MDL, SKY | SCENE | SHOW, 1);
    vec_set(&skycube_ent->x, &camera->x);
    vec_fill(&skycube_ent->scale_x, (camera->clip_far * 0.99) / 8);
    skycube_ent->material = mtl_night_sky;

    mtl_pp_screen = mtl_create();
    mtl_pp_screen->flags = AUTORELOAD;
    mtl_pp_screen->skin1 = mtl_dither_pcx;
    effect_load(mtl_pp_screen, "mtl_pp_screen.fx");
}

void shaders_destroy()
{
    if (pp_view)
    {
        pp_view->material = NULL;
        ptr_remove(pp_view);
        pp_view = NULL;
    }

    if (mtl_solid)
    {
        effect_load(mtl_solid, NULL);
        ptr_remove(mtl_solid);
        mtl_solid = NULL;
    }

    if (mtl_water)
    {
        effect_load(mtl_water, NULL);
        ptr_remove(mtl_water);
        mtl_water = NULL;
    }

    if (mtl_marker)
    {
        effect_load(mtl_marker, NULL);
        ptr_remove(mtl_marker);
        mtl_marker = NULL;
    }

    if (mtl_night_sky)
    {
        if (mtl_night_sky->skin1)
        {
            bmap_remove(mtl_night_sky->skin1);
            mtl_night_sky->skin1 = NULL;
        }

        effect_load(mtl_night_sky, NULL);
        ptr_remove(mtl_night_sky);
        mtl_night_sky = NULL;
    }

    safe_remove(skycube_ent);

    if (mtl_pp_screen)
    {
        mtl_pp_screen->skin1 = NULL;
        effect_load(mtl_pp_screen, NULL);
        ptr_remove(mtl_pp_screen);
        mtl_pp_screen = NULL;
    }

#ifdef PSX_DITHER
    camera->stage = NULL;
#endif
}

void shaders_show_sky()
{
    if (is(skycube_ent, INVISIBLE))
    {
        reset(skycube_ent, INVISIBLE);
    }
}

void shaders_hide_sky()
{
    if (!is(skycube_ent, INVISIBLE))
    {
        set(skycube_ent, INVISIBLE);
    }
}

void shaders_reset()
{
    if (!render_target_tga)
    {
        render_target_tga = bmap_createblack(2048, 2048, 32);
    }

    bmap_zbuffer(render_target_tga);

#ifdef PSX_DITHER
    pp_view->material = NULL;
    camera->stage = NULL;

    wait(1);

    pp_view->material = mtl_pp_screen;
    camera->stage = pp_view;
#endif
}

void shaders_update()
{
    mtl_solid->skill1 = floatv(shader_level_ambient);
    mtl_solid->skill2 = floatv(shader_vertex_snapping);
    mtl_solid->skill3 = floatv(shader_lighting_brightness);
    mtl_solid->skill4 = floatv(is_lights_on);

    mtl_water->skill1 = floatv(shader_level_ambient);
    mtl_water->skill2 = floatv(shader_vertex_snapping);
    mtl_water->skill3 = floatv(shader_lighting_brightness);
    mtl_water->skill4 = floatv(is_lights_on);

    mtl_marker->skill1 = floatv(shader_level_ambient);
    mtl_marker->skill2 = floatv(shader_vertex_snapping);

    mtl_night_sky->skill1 = floatv(shader_sky_fogginess);
    mtl_night_sky->skill2 = floatv(shader_vertex_snapping);

    if (skycube_ent)
    {
        if (is_lights_on == true || is_map_settings_visible == true)
        {
            shaders_show_sky();
        }
        else
        {
            shaders_hide_sky();
        }

        vec_set(&skycube_ent->x, &camera->x);
        vec_fill(&skycube_ent->scale_x, (camera->clip_far * 0.99) / 8);
    }
}