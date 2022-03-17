
// function to check for specific input keys and return their scancodes!
int engine_key_return_scancode_from_letter(STRING *key)
{
    // nothing in the string ?
    if (key == NULL || str_len(key) <= 0)
    {
        diag("\nERROR! Can't return a scancode! Nothing in the key string!");
        return SCANCODE_NONE;
    }

    str_lwr(key); // convert key into lowercase string

    // check if it's 'none'
    if (str_cmpi(key, input_none_str))
    {
        return SCANCODE_NONE;
    }

    // expand with additional keys if needed
    if (str_cmpi(key, mouse_left_str))
    {
        return SCANCODE_MOUSE_LEFT;
    }
    else if (str_cmpi(key, mouse_right_str))
    {
        return SCANCODE_MOUSE_RIGHT;
    }
    else if (str_cmpi(key, mouse_middle_str))
    {
        return SCANCODE_MOUSE_MIDDLE;
    }

    // check if the given key can return a proper scancode
    int temp_scancode = key_for_str(key);
    if (temp_scancode > 0)
    {
        return temp_scancode;
    }

    // if nothing worked correctly, then return -1
    diag("\nERROR! Can't return a scancode from key: ");
    diag(key);
    diag(". No scancode was found!");

    return SCANCODE_NONE;
}

// return a letter from the given scancode
// this can be used for saving input from the game options
STRING *engine_key_return_letter_from_scancode(int scancode)
{
    // check if scancode is correct
    // correct range is from SCANCODE_ESC to SCANCODE_MOUSE_MIDDLE
    if (scancode <= 0 || scancode > SCANCODE_MOUSE_MIDDLE)
    {
        diag("\nERROR! Given scancode: ");
        diag(str_for_num(NULL, scancode));
        diag("is out of range!");

        return "";
    }

    STRING *tmp_str = "#16";
    str_for_key(tmp_str, scancode);

    switch (scancode)
    {
    case SCANCODE_MOUSE_LEFT:
        str_cpy(tmp_str, mouse_left_str);
        break;

    case SCANCODE_MOUSE_RIGHT:
        str_cpy(tmp_str, mouse_right_str);
        break;

    case SCANCODE_MOUSE_MIDDLE:
        str_cpy(tmp_str, mouse_middle_str);
        break;

    default:
        break;
    }

    return tmp_str;
}