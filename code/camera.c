
void camera_initialize()
{
    camera->arc = CAMERA_ARC;
    vec_set(&camera->x, vector(0, 0, MAP_CELL_SIZE / 2));
    vec_set(&camera->pan, vector(0, 0, 0));
}

void camera_load_config(Config *config)
{
    if (!config)
    {
        return;
    }

    scancode_cam_forward = engine_key_return_scancode_from_letter(config->input_forward);
    scancode_cam_backward = engine_key_return_scancode_from_letter(config->input_backward);
    scancode_cam_strafe_left = engine_key_return_scancode_from_letter(config->input_strafe_left);
    scancode_cam_strafe_right = engine_key_return_scancode_from_letter(config->input_strafe_right);
    scancode_cam_fly_up = engine_key_return_scancode_from_letter(config->input_fly_up);
    scancode_cam_fly_down = engine_key_return_scancode_from_letter(config->input_fly_down);
    scancode_cam_run = engine_key_return_scancode_from_letter(config->input_run);
    scancode_cam_rotate = engine_key_return_scancode_from_letter(config->input_rotate_camera);
}

void camera_auto_resize()
{
    if (editor_state == EDITOR_STATE_EDIT)
    {
        camera->pos_x = 0;
        camera->pos_y = (EDITOR_TOP_BAR_HEIGHT * config_saved.font_scale);
        camera->size_x = screen_size.x;
        camera->size_y = screen_size.y - (EDITOR_TOP_BAR_HEIGHT * config_saved.font_scale);
    }
    else
    {
        camera->pos_x = 0;
        camera->pos_y = 0;
        camera->size_x = screen_size.x;
        camera->size_y = screen_size.y;
    }
}

void camera_update_fog()
{
    if (is_map_settings_visible == true)
    {
        camera->fog_end = map_settings.fog_end;
        camera->fog_start = map_settings.fog_start;

        camera->clip_near = 0.1;
        camera->clip_far = camera->fog_end * 1.25;

        fog_color = 4;
        change_color_from_hsv(&d3d_fogcolor4, map_settings.fog_color[0], map_settings.fog_color[1], map_settings.fog_color[2]);
        vec_set(&sky_color, &d3d_fogcolor4);
    }
    else if (is_lights_on == true)
    {
        Map *active_map = map_get_active(&def_episode);

        camera->fog_end = active_map->fog_end;
        camera->fog_start = active_map->fog_start;

        camera->clip_near = 0.1;
        camera->clip_far = camera->fog_end * 1.25;

        fog_color = 4;
        change_color_from_hsv(&d3d_fogcolor4, active_map->fog_color[0], active_map->fog_color[1], active_map->fog_color[2]);
        vec_set(&sky_color, &d3d_fogcolor4);
    }
    else
    {
        camera->fog_end = FOG_MAX_END;
        camera->fog_start = FOG_MAX_END;

        camera->clip_near = 0.1;
        camera->clip_far = FOG_MAX_END * 1.25;

        fog_color = 4;
        change_color_from_hsv(&d3d_fogcolor4, config_current.background_color[0], config_current.background_color[1], config_current.background_color[2]);
        vec_set(&sky_color, &d3d_fogcolor4);
    }
}

void camera_fly()
{
    if (is_popup_opened == true || editor_state != EDITOR_STATE_EDIT)
    {
        return false;
    }

    if (key_cam_rotate)
    {
        camera->pan = cycle(camera->pan - mickey.x / 6.5 * config_saved.mouse_sensitivity, 0, 360);
        camera->tilt = clamp(camera->tilt - mickey.y / 6.5 * config_saved.mouse_sensitivity, -90, 90);
        camera->roll = 0;
    }

    VECTOR input;
    input.x = CAM_MOVE_SPEED * (key_cam_forward - key_cam_backward);
    input.y = CAM_MOVE_SPEED * (key_cam_strafe_left - key_cam_strafe_right);
    input.z = CAM_MOVE_SPEED * (key_cam_fly_up - key_cam_fly_down);

    if (key_cam_run)
    {
        input.x *= CAM_RUN_FACTOR;
        input.y *= CAM_RUN_FACTOR;
        input.z *= CAM_RUN_FACTOR;
    }
    vec_scale(&input, time_step);
    vec_rotate(&input, vector(camera->pan, 0, 0));
    vec_add(&camera->x, &input);
}

void camera_update()
{
    key_cam_forward = key_pressed(scancode_cam_forward);
    key_cam_backward = key_pressed(scancode_cam_backward);
    key_cam_strafe_left = key_pressed(scancode_cam_strafe_left);
    key_cam_strafe_right = key_pressed(scancode_cam_strafe_right);
    key_cam_fly_up = key_pressed(scancode_cam_fly_up);
    key_cam_fly_down = key_pressed(scancode_cam_fly_down);
    key_cam_run = key_pressed(scancode_cam_run);
    key_cam_rotate = key_pressed(scancode_cam_rotate);

    camera_update_fog();
    camera_auto_resize();
    camera_fly();
}