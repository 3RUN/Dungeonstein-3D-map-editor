
void shaders_update()
{
    mtl_solid->skill1 = floatv(shader_level_ambient);
    mtl_solid->skill2 = floatv(shader_angle_surface_darken);

    mtl_two_sided->skill1 = floatv(shader_level_ambient);
    mtl_two_sided->skill2 = floatv(shader_angle_surface_darken);
}