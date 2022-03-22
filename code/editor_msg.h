#ifndef _EDITOR_MSG_H_
#define _EDITOR_MSG_H_

#define MAX_MESSAGES 5
#define MESSAGES_LAYER 998
#define MESSAGES_ALPHA 100
#define MESSAGE_FADE_SPEED 2

PANEL *message_pan[MAX_MESSAGES];

FONT *message_font = "Arial#16";

STRING *message_str[MAX_MESSAGES];

SOUND *beep_ogg = "beep.ogg";

var snd_beep_volume = 50;
var messages_total = 0;

void messages_initialize();

void messages_destroy();

void messages_show();

void messages_hide();

void messages_reset();

void message_add(STRING *msg);

void messages_update();

#endif