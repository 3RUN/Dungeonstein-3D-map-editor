
void shaders_initialize()
{
    mtl_solid = mtl_create();
    effect_load(mtl_solid, "mtl_solid.fx");

    mtl_two_sided = mtl_create();
    effect_load(mtl_two_sided, "mtl_two_sided.fx");
}

void shaders_destroy()
{
    if (mtl_solid)
    {
        effect_load(mtl_solid, NULL);
        ptr_remove(mtl_solid);
    }

    if (mtl_two_sided)
    {
        effect_load(mtl_two_sided, NULL);
        ptr_remove(mtl_two_sided);
    }
}

void shaders_update()
{
    mtl_solid->skill1 = floatv(shader_level_ambient);
    mtl_solid->skill2 = floatv(shader_angle_surface_darken);

    mtl_two_sided->skill1 = floatv(shader_level_ambient);
    mtl_two_sided->skill2 = floatv(shader_angle_surface_darken);
}