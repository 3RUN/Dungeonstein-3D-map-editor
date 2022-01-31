
int episode_save()
{
    char *map_file = file_dialog_save("Save episode", "*.ep");

    key_pressed(-1);

    if (map_file == NULL)
    {
        return false;
    }

    return true;
}

int episode_load()
{
    char *map_file = file_dialog("Load episode", "*.ep");

    key_pressed(-1);

    if (map_file == NULL)
    {
        return false;
    }

    return true;
}