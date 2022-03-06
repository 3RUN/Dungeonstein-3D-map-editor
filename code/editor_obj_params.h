#ifndef _EDITOR_OBJ_PARAMS_H_
#define _EDITOR_OBJ_PARAMS_H_

// WALLS
// * "flas" is telling wether it's a secret wall (true) or not (false)
// * "event_type" is holding activation type (0 - interaction (default), 1 - trigger zone or 0 - switch)
// * "event_id" is holding id of a trigger zone or switch (range: 0...MAX_ID_RANGE)

// PROPS
// * "event_type" is holding activation type (0 - interaction (default), 1 - trigger zone or 2 - switch) or type of a key (0 - blue, 1 - red, 2 - yellow) for locked doors
// * "event_id" is holding id of a trigger zone or switch (range: 0...MAX_ID_RANGE)

// TRIGGER ZONE EVENT
// * "event_id" is holding id of this trigger zone (range: 0...MAX_ID_RANGE)

// SPAWN OBJECT EVENT
// * "flag" is holding what kind of object should be spawn (0 - item, 1 - weapon, 2 - enemy, 3 - boss)
// * "event_type" is holding activation type (0 - on creation (default), 1 - trigger zone or 2 - switch)
// * "event_id" is holding id of a trigger zone or switch (range: 0...MAX_ID_RANGE)
// * "temp_skill" is holding id of the object to be spawn
// list of IDs used for objects to be spawn
// ITEMS: 0/1/2 - keys blue/red/yellow and 4/5 - medkits small/big
// WEAPONS: 0 - ammo box, 1/2 - pistol weapon/ammo, 3/4 - shotgun weapon/ammo, 5/6 - smg weapon/ammo, 7/8 - machinegun weapon/ammo, 9/10 - rocketlauncher weapon/ammo
// ENEMIES: 0 - rat, 1 - dog, 2/3 - guard pistol/shotgun, 4 - soldier smg, 5 - suicide bomber, 6 - zombie and 7/8 - support machinegun/rocketlauncher
// BOSSES: 0/1/2 - uber soldier/officer/mutant, 3 - mecha soldier and 4 - demon

// ENEMIES
// * "flag" is checking whether enemy should drop an item on death (true) or not (false)
// * "event_type" is holding item id to be dropper (0/1/2 - keys blue/red/yellow, 3/4 - medkits small/big or 5/6 - ammo/weapon that enemy is held)

// BOSSES
// * "flag" is checking whether boss should drop an item on death (true) or not (false)
// * "event_type" is holding item id to be dropper (0/1/2 - keys blue/red/yellow, 3/4 - medkits small/big)

#define MAX_ID_RANGE 999

STRING *params_none_str = "Parameters: none";

STRING *params_is_secret_wall_str = "is_secret_wall";
STRING *params_activation_str = "Activation";
STRING *params_activation_type_interaction_str = "Interaction";
STRING *params_activation_type_on_creation_str = "On creation";
STRING *params_activation_type_trigger_zone_str = "Trigger zone - id";
STRING *params_activation_type_switch_str = "Switch - id";
STRING *params_activation_id_str = "Id:";
STRING *params_activation_id_decrease_str = "Id Decrease";
STRING *params_activation_id_increase_str = "Id Increase";

STRING *params_key_type_str = "Key type:";
STRING *params_key_type_blue_str = "Blue";
STRING *params_key_type_red_str = "Red";
STRING *params_key_type_yellow_str = "Yellow";

STRING *params_drop_item_str = "Drop item";
STRING *params_drop_item_key_blue_str = "Key blue";
STRING *params_drop_item_key_red_str = "Key red";
STRING *params_drop_item_key_yellow_str = "Key yellow";
STRING *params_drop_item_small_medkit_str = "Small medkit";
STRING *params_drop_item_big_medkit_str = "Bit medkit";
STRING *params_drop_item_ammo_str = "Ammo";
STRING *params_drop_item_weapon_str = "Weapon";

STRING *params_spawn_object_category_str = "Category";
STRING *params_spawn_object_type_str = "Type";
STRING *params_spawn_object_type_item_str = "Item";
STRING *params_spawn_object_type_weapon_str = "Weapon";
STRING *params_spawn_object_type_enemy_str = "Enemy";
STRING *params_spawn_object_type_boss_str = "Boss";

STRING *params_spawn_object_ammo_big_str = "Ammo box";
STRING *params_spawn_object_weapon_pistol_str = "Pistol weapon";
STRING *params_spawn_object_ammo_pistol_str = "Pistol ammo";
STRING *params_spawn_object_weapon_shotgun_str = "Shotgun weapon";
STRING *params_spawn_object_ammo_shotgun_str = "Shotgun ammo";
STRING *params_spawn_object_weapon_smg_str = "SMG weapon";
STRING *params_spawn_object_ammo_smg_str = "SMG ammo";
STRING *params_spawn_object_weapon_machinegun_str = "Machinegun weapon";
STRING *params_spawn_object_ammo_machinegun_str = "Machinegun ammo";
STRING *params_spawn_object_weapon_rocketlauncher_str = "Rocketlauncher weapon";
STRING *params_spawn_object_ammo_rocketlauncher_str = "Rocketlauncher ammo";

STRING *params_spawn_object_enemy_rat_str = "Rat";
STRING *params_spawn_object_enemy_dog_str = "Dog";
STRING *params_spawn_object_enemy_guard_pistol_str = "Guard pistol";
STRING *params_spawn_object_enemy_guard_shotgun_str = "Guard shotgun";
STRING *params_spawn_object_enemy_soldier_smg_str = "Soldier SMG";
STRING *params_spawn_object_enemy_suicide_bomber_str = "Suicide bomber";
STRING *params_spawn_object_enemy_zombie_str = "Zombie";
STRING *params_spawn_object_enemy_support_machinegun_str = "Support machinegun";
STRING *params_spawn_object_enemy_support_rocketlauncher_str = "Support rocketlauncher";

STRING *params_spawn_object_boss_uber_soldier_str = "Uber soldier";
STRING *params_spawn_object_boss_uber_officer_str = "Uber officer";
STRING *params_spawn_object_boss_uber_mutant_str = "Uber mutant";
STRING *params_spawn_object_boss_mecha_soldier_str = "Mecha soldier";
STRING *params_spawn_object_boss_demon_str = "Demon";

void editor_activation_type(Cell *cell);

void editor_id(Cell *cell);

void editor_wall_params(Cell *cell, int index);

void editor_props_params(Cell *cell, int index);

void editor_events_params(Cell *cell, int index);

void editor_enemies_params(Cell *cell, int index);

void editor_bosses_params(Cell *cell, int index);

void editor_obj_params_update(Cell *cell, int type, int index);

#endif