#ifndef _EDITOR_INPUT_H_
#define _EDITOR_INPUT_H_

#define INPUT_BOTTON_WIDTH 128
#define INPUT_BUTTON_HEIGHT 16

void input_remove_on_key_binding(var scancode);

void input_update_on_key_binding(var scancode, void *fnc);

void input_overwrite(char *input, STRING *bindkey);

void input_check_overwrite(STRING *bindkey);

void input_bind_key(char *input, STRING *input_entry, STRING *entry, STRING *bindkey);

void input_bind_new_key(STRING *entry, STRING *bindkey);

void input_remove_bind_key(STRING *entry);

void input_wait_for_binding(STRING *entry);

void input_add_keybinding(STRING *entry, STRING *input);

void shortcut_add_keybinding(STRING *entry, STRING *base_key, STRING *input);

#include "editor_input.c"
#endif