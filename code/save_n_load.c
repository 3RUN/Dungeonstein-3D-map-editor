
int map_save()
{
    char *map_file = file_dialog_save("Save level", "*.map");

    key_pressed(-1);

    if (map_file == NULL)
    {
        return false;
    }

    return true;
}

int map_load()
{
    char *map_file = file_dialog("Load level", "*.map");

    key_pressed(-1);

    if (map_file == NULL)
    {
        return false;
    }

    return true;
}