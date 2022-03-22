
// checks if given directory exists or not
BOOL DirectoryExists(char *szPath)
{
    DWORD dwAttrib = GetFileAttributes(_chr(szPath));
    return (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

// returns the full path to your game folder (which is in your PC's documents folder)
STRING *get_savedir_folder()
{
    return save_dir;
}

// this function will create game's folder in documents folder
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

    // set new save directory
    str_cpy(save_dir, _str(documents_path));
    str_cat(save_dir, "\\");
    str_cat(save_dir, project_name_str);
    str_cat(save_dir, "\\");

    // check if directory exists or not
    // and if it doesn't, create it !
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