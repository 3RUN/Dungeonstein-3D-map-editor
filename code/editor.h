#ifndef _EDITOR_H_
#define _EDITOR_H_

#define EDITOR_TOP_BAR_HEIGHT 16
#define EDITOR_SIDE_BAR_WIDTH 280

var editor_state = EDITOR_STATE_EDIT;
var editor_old_state = EDITOR_STATE_EDIT;

void editor_switch_state_to(var state);

#endif