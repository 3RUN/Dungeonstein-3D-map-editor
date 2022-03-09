
void game_build_info_initialize()
{
    game_build_info_reset();
}

void game_build_info_reset()
{
    is_level_finish_found = false;
    is_player_position_found = false;
}

void game_build_info_update(Episode *episode)
{
    if (!episode)
    {
        return;
    }

    STRING *temp_str = "";
    str_cpy(temp_str, "Start position found: ");
    if (is_player_position_found == true)
    {
        str_cat(temp_str, "true;");
    }
    else
    {
        str_cat(temp_str, "false;");
    }

    str_cat(temp_str, "\nFinish position found: ");
    if (is_level_finish_found == true)
    {
        str_cat(temp_str, "true;");
    }
    else
    {
        str_cat(temp_str, "false;");
    }

    draw_text(temp_str, 10, 10, COLOR_WHITE);
}