#ifndef _MAP_FUNCS_H_
#define _MAP_FUNCS_H_

#define OBJECT_BBOX_ALPHA 15
#define SECRET_WALL_ALPHA 75

STRING *decor_mdl = "decor.mdl";

STRING *bbox_npc_mdl = "bbox_npc.mdl";
STRING *bbox_props_mdl = "bbox_props.mdl";
STRING *bbox_cell_mdl = "bbox_cell.mdl";
STRING *bbox_door_mdl = "bbox_door.mdl";
STRING *bbox_switch_mdl = "bbox_switch.mdl";

STRING *secret_wall_mdl = "secret_wall.mdl";
STRING *teleport_in_frame_mdl = "teleport_frame.mdl";
STRING *teleport_in_mdl = "teleport.mdl";

var water_amplitude = 50;
var water_speed = 1;
var water_modulation = 1500;

var teleport_amplitude = 105;
var teleport_speed = 0.5;
var teleport_modulation = 950;

// event_frame
void object_event_frame();

// events
void player_controller();

void level_finish();

void trigger_zone();

void object_spawn_point();

void secret_wall();

void teleport_in();

void teleport_out();

// props
void props_sprite();

void props_bbox();

void props_passable_bbox();

void props_light();

void props_light_sprite();

void props_column();

void props_barrel();

void props_table();

void props_vase();

void props_door();

void props_gate();

void props_ceiling_support();

void props_window();

void props_decor_on_wall();

void props_switch();

// items
void item_key_blue();

void item_key_red();

void item_key_yellow();

void item_health_bonus();

void item_medkit_small();

void item_medkit_big();

void item_ammo_bullets_small();

void item_ammo_bullets_big();

void item_ammo_shells_small();

void item_ammo_shells_big();

void item_ammo_rockets_small();

void item_ammo_rockets_big();

void item_treasure();

void item_powerup_map();

void item_powerup_suit();

void item_powerup_chicken();

void item_powerup_lantern();

void item_powerup_mushroom();

void item_weapon_pistol();

void item_weapon_shotgun();

void item_weapon_chaingun();

void item_weapon_rocketlauncher();

// enemies
void enemy_bat();

void enemy_boxer();

void enemy_bum();

void enemy_mage();

void enemy_human_pistol();

void enemy_human_shotgun();

void enemy_skeleton();

void enemy_slime_fire();

void enemy_slime_ice();

void enemy_zombie();

// bosses
void boss_human_chaingun();

void boss_human_rocketlauncher();

void boss_slime_toxic();

void boss_megaeye();

#include "map_funcs.c"
#endif