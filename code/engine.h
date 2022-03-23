#ifndef _ENGINE_H_
#define _ENGINE_H_

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

BMAP *mouse_tga = "mouse.tga";

int autolock_mouse_locked = false;

float get_hsv_from_color(float value);

float get_color_from_hsv(float value);

void change_color_from_hsv(COLOR *color, float color_red, float color_green, float color_blue);

var engine_key_return_scancode_from_letter(STRING *key);

void engine_key_return_letter_from_scancode(STRING **out_letter, int scancode);

void mouse_set_position(VECTOR *pos);

void mouse_get_position(VECTOR *out);

void mouse_set_map(BMAP *new_mouse_map);

void mouse_enable(int is_mouse_centered);

void mouse_disable();

void mouse_lock_in_window();

void engine_set_resolution_from_id(int id, int display_mode);

void engine_apply_video_settings();

void engine_initialize();

#endif