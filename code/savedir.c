
BOOL DirectoryExists(char *szPath)
{
    DWORD dwAttrib = GetFileAttributes(szPath);
    return (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

void set_savedir()
{
    char *documents_path[MAX_PATH]; // MAX_PATH = 260 characters

    // if we are using windows Vista and above ?
    // then use SHGetFolderPath instead of SHGetSpecialFolderPath
    if (sys_winversion >= 6)
    {
        SHGetFolderPath(NULL, CSIDL_PERSONAL, 0, NULL, documents_path);
    }
    else
    {
        SHGetSpecialFolderPath(NULL, documents_path, CSIDL_PERSONAL, FALSE);
    }

    str_cpy(save_dir, _str(documents_path));
    str_cat(save_dir, "\\");
    str_cat(save_dir, project_name_str);
    str_cat(save_dir, "\\");

    if (!DirectoryExists(_chr(save_dir)))
    {
        CreateDirectory(_chr(save_dir), NULL);
    }

    // also make sure to create 'episodes' subfolder in save_dir
    STRING *subfolder_str = "";
    str_cpy(subfolder_str, save_dir);
    str_cat(subfolder_str, "\\episodes");

    if (!DirectoryExists(_chr(subfolder_str)))
    {
        CreateDirectory(_chr(subfolder_str), NULL);
    }
}