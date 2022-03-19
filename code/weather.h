#ifndef _WEATHER_H_
#define _WEATHER_H_

#define WEATHER_SEEDBOX_LENGTH 320
#define WEATHER_SEEDBOX_WIDTH 320
#define WEATHER_SEEDBOX_HEIGHT 96

#define WEATHER_PARTICLE_Z_LIMIT -16
#define WEATHER_PARTICLE_Z_OFFSET 0.1

VECTOR weather_seedbox;
VECTOR weather_velocity;

var rain_density = 115;
var rain_wind_x = 0;
var rain_wind_y = 0;
var rain_random_move = 0;
var rain_fallspeed = 10;
var rain_size = 8;
var rain_random_size = 4;
var rain_alpha = 75;
var rain_random_alpha = 10;

var rain_splash_density = 3;
var rain_splash_spread = 2;
var rain_splash_size = 0.5;
var rain_splash_random_size = 0.25;
var rain_splash_gravity = 2;
var rain_splash_vel_z = 2;
var rain_splash_random_vel_z = 0.5;
var rain_splash_alpha = 25;
var rain_splash_random_alpha = 10;
var rain_splash_fadeout_speed = 5;

var snow_density = 75;
var snow_wind_x = 0;
var snow_wind_y = 0;
var snow_random_move = 2;
var snow_fallspeed = 5;
var snow_size = 0.75;
var snow_random_size = 0.5;
var snow_alpha = 75;
var snow_random_alpha = 10;

var snow_splash_size = 0.75;
var snow_splash_random_size = 0.5;
var snow_splash_alpha = 30;
var snow_splash_random_alpha = 10;
var snow_splash_fadeout_speed = 2.5;

BMAP *weather_rain_tga = "weather_rain.tga";
BMAP *weather_snow_tga = "weather_snow.tga";

var weather_sound_handle = 0;
var weather_sound_volume = 0;
var weather_sound_volume_target = 25;
var weather_sound_volume_fade_speed_factor = 4;

SOUND *weather_rain_ogg = "rain.ogg";
SOUND *weather_snow_ogg = "snow.ogg";

void vec_randomize(VECTOR *vec, var range);

void weather_impact_particle_event(PARTICLE *p);

void weather_rain_splash_particle(PARTICLE *p);

void weather_snow_impact_particle(PARTICLE *p);

void weather_particle_event(PARTICLE *p);

void weather_rain_particle(PARTICLE *p);

void weather_snow_particle(PARTICLE *p);

void weather_update(int type);

void weather_pause_sound();

void weather_resume_sound();

void weather_stop_sound();

void weather_play_sound(int type);

#endif