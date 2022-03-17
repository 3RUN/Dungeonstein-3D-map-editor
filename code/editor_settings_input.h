#ifndef _EDITOR_SETTINGS_INPUT_H_
#define _EDITOR_SETTINGS_INPUT_H_

#define INPUT_BOTTON_WIDTH 128
#define INPUT_BUTTON_HEIGHT 16

void editor_input_overwrite(char *input, STRING *bindkey);

void editor_input_check_overwrite(STRING *bindkey);

void editor_input_bind_key(char *input, STRING *input_entry, STRING *entry, STRING *bindkey);

void editor_input_bind_new_key(STRING *entry, STRING *bindkey);

void editor_input_remove_bind_key(STRING *entry);

void editor_input_wait_for_binding(STRING *entry);

void editor_input_add_keybinding(STRING *entry, STRING *input);

void editor_shortcut_add_keybinding(STRING *entry, STRING *base_key, STRING *input);

#endif