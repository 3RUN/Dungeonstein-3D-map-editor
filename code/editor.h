#ifndef _EDITOR_H_
#define _EDITOR_H_

#define EDITOR_BUTTON_HEIGHT 24
#define EDITOR_COMBOBOX_WIDTH 340

void editor_switch_state_to(int state);

void editor_switch_popup_to(int state);

#include "editor_input.h"
#include "editor_popups.h"
#include "editor_start.h"
#include "map_draw.h"
#include "editor_general.h"
#include "editor.c"
#endif