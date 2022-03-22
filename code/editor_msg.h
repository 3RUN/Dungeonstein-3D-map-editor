#ifndef _EDITOR_MSG_H_
#define _EDITOR_MSG_H_

#define MAX_MESSAGES 5
#define MESSAGE_FADE_SPEED 3
#define MESSAGES_LAYER 998
#define MESSAGES_ALPHA 75

TEXT *message_txt = NULL;

SOUND *beep_ogg = "beep.ogg";

var beep_volume = 50;
var message_timer[MAX_MESSAGES];

void messages_show();

void messages_hide();

void messages_reset();

void messages_initialize();

void messages_destroy();

void messages_update();

void message_add(STRING *msg);

#endif