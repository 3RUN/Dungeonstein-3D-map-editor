#ifndef _LIGHTSTYLE_H_
#define _LIGHTSTYLE_H_

STRING *light_factor_str = "abcdefghijklmnopqrstuvwxyz";

// styles
STRING *lightstyle_none_str = "z";
STRING *lightstyle_flicker_str = "mmamammmmammamamaaamammma";
STRING *lightstyle_pulse_str = "abcdefghijklmnopqrrqponmlkjihgfedcba";
STRING *lightstyle_strobe_str = "mamamamamama";
STRING *lightstyle_candle_str = "mmmaaammmaaammmabcdefaaaammmmabcdefmmmaaaa";

STRING *global_style_str = "bcdefghijklmnopqrrqponmlkjihgfedcb";

var flicker_light_factor = 0;
var pulse_light_factor = 0;
var strobe_light_factor = 0;
var candle_light_factor = 0;
var global_light_factor = 0;

int light_get_id(STRING *character);

void flicker_lightstyle();

void pulse_lightstyle();

void strobe_lightstyle();

void candle_lightstyle();

void global_lightstyle();

void lightstyles();

#include "lightstyle.c"
#endif