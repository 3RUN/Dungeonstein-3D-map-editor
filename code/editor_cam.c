
void camera_movement(var grid_height, var grid_size)
{
    if (mouse_middle && is_allowed_to_draw_map() == true)
    {
        VECTOR vtemp;
        vec_set(&vtemp, &mouse_dir3d);
        vec_scale(&vtemp, -fsin(camera->tilt, camera->skill_y) / vtemp.z);
        vec_add(&vtemp, &vec_mouse_3d);
        vec_set(&camera->x, &vtemp);

        vec_camera_center.x = camera->x + fcos(camera->pan, camera->skill_x);
        vec_camera_center.y = camera->y + fsin(camera->pan, camera->skill_x);
        vec_camera_center.z = grid_height;

        GetCursorPos(&mouse_pos_PL);
    }
    else
    {
        VECTOR vtemp;
        vec_set(&vtemp, &mouse_dir3d);

        if (vtemp.z < 0)
        {
            vec_scale(&vtemp, fsin(camera->tilt, camera->skill_y) / vtemp.z);
            vec_add(&vtemp, &camera->x);
            vtemp.z = grid_height;
            vec_set(&vec_mouse_3d, &vtemp);

            vec_mouse_on_grid.x = integer((vec_mouse_3d.x + (sign(vec_mouse_3d.x) * (grid_size / 2))) / grid_size);
            vec_mouse_on_grid.y = integer((vec_mouse_3d.y + (sign(vec_mouse_3d.y) * (grid_size / 2))) / grid_size);
            vec_mouse_on_grid.z = grid_height / grid_size;
        }

        if (mickey.z && is_allowed_to_draw_map() == true)
        {
            var ntemp = camera->skill_y;
            camera->skill_y += mickey.z * 0.2;
            camera->skill_y = clamp(camera->skill_y, 256, camera->skill_y);
            ntemp = camera->skill_y / ntemp;
            vec_sub(&vec_camera_center, &vec_mouse_3d);
            vec_scale(&vec_camera_center, ntemp);
            vec_add(&vec_camera_center, &vec_mouse_3d);
            camera->skill_x = fcos(camera->tilt, camera->skill_y);
            camera->x = vec_camera_center.x - fcos(camera->pan, camera->skill_x);
            camera->y = vec_camera_center.y - fsin(camera->pan, camera->skill_x);
            camera->z = vec_camera_center.z - fsin(camera->tilt, camera->skill_y);
        }

        GetCursorPos(&mouse_pos_PL);
    }
}

void camera_initialize()
{
    vec_set(&vec_grid_center, vector((MAP_WIDTH / 2) * MAP_CELL_SIZE, -(MAP_HEIGHT / 2) * MAP_CELL_SIZE, 0));
    vec_set(&vec_camera_center, &vec_grid_center);

    camera->arc = 90;
    vec_set(&camera->pan, vector(90, -90, 0));
    vec_set(&sky_color.blue, BACKGROUND_COLOR);

    camera->skill_y = 1024; // initial camera height
    camera->skill_x = fcos(camera->tilt, camera->skill_y);

    camera->x = vec_camera_center.x - fcos(camera->pan, camera->skill_x);
    camera->y = vec_camera_center.y - fsin(camera->pan, camera->skill_x);
    camera->z = vec_camera_center.z - fsin(camera->tilt, camera->skill_y);
}

void camera_update()
{
    camera_movement(vec_grid_center.z, MAP_CELL_SIZE);
}