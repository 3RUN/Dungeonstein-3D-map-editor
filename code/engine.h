#ifndef _ENGINE_H_
#define _ENGINE_H_

BMAP *mouse_tga = "mouse.tga";

int autolock_mouse_locked = false;

void mouse_set_position(VECTOR *pos);

VECTOR *mouse_get_position();

void mouse_enable(int is_mouse_centered);

void mouse_disable();

void mouse_lock_in_window();

void engine_set_resolution_from_id(int id, int display_mode);

void engine_apply_settings();

void engine_initialize();

#endif