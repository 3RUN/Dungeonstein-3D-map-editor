
int episode_save(STRING *file_name, Episode *e)
{
    if (!e)
    {
        return false;
    }

    STRING *temp_str = "#256";
    str_cpy(temp_str, "episodes\\");
    str_cat(temp_str, file_name);
    path_make_absolute(temp_str); // add 'save_dir' full path (in documents folder)

    void *returned_buffer = file_save(temp_str, e, sizeof(Episode));
    if (returned_buffer == NULL)
    {
        return false;
    }

    return true;
}

int episode_load(STRING *file_name, Episode *e)
{
    if (!e)
    {
        return false;
    }

    STRING *temp_str = "#256";
    str_cpy(temp_str, "episodes\\");
    str_cat(temp_str, file_name);
    path_make_absolute(temp_str); // add 'save_dir' full path (in documents folder)

    if (!file_exists(temp_str))
    {
        return false;
    }

    long _size = 0;
    void *buffer = file_load(temp_str, NULL, &_size);
    memcpy(e, buffer, sizeof(Episode));
    void *returned_buffer = file_load(NULL, buffer, &_size);
    if (returned_buffer == NULL)
    {
        return false;
    }

    return true;
}