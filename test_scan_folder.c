
TEXT *tDir = {
    strings = 9999;
flags = SHOW;
}

void test_scan_folder()
{
    STRING *temp_str = "#256";
    str_cpy(temp_str, "episodes\\*.dat");
    path_make_absolute(temp_str); // add 'save_dir' full path (in documents folder)

    int found = txt_for_dir(tDir, temp_str);
    //cprintf0(str_for_num(NULL, found));
}