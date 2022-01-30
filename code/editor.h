#ifndef _EDITOR_H_
#define _EDITOR_H_

#define STATE_NEW 0
#define STATE_EPISODE 1
#define STATE_EDITOR 2
#define STATE_TEST 3

int editor_state = STATE_NEW;
int editor_old_state = STATE_NEW;

void editor_switch_state_to(int state);

void editor_create_tooltip(STRING *tooltip);

void editor_help_maker(char *desc);

#endif