#ifndef _ENGINE_KEY_BIND_H_
#define _ENGINE_KEY_BIND_H_

// scancodes
#define SCANCODE_NONE -1
#define SCANCODE_MOUSE_LEFT 280
#define SCANCODE_MOUSE_RIGHT 281
#define SCANCODE_MOUSE_MIDDLE 282
#define SCANCODE_ENTER 28
#define SCANCODE_ESC 1
#define SCANCODE_DELETE 83

// words to filter input
STRING *mouse_left_str = "mouse_left";
STRING *mouse_right_str = "mouse_right";
STRING *mouse_middle_str = "mouse_middle";

// function to check for specific input keys and return their scancodes!
var engine_key_return_scancode_from_letter(STRING *key);

// return a letter from the given scancode
// this can be used for saving input from the game options
STRING *engine_key_return_letter_from_scancode(var scancode);

#endif