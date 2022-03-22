#ifndef _EDITOR_ASSET_PARAMS_H_
#define _EDITOR_ASSET_PARAMS_H_

// WALLS
// * "flas" is telling wether it's a secret wall (true) or not (false)
// * "event_type" is holding activation type (0 - interaction (default), 1 - trigger zone or 2 - switch)
// * "event_id" is holding id of a trigger zone or switch (range: 0...MAX_ID_RANGE)

// PROPS
// * "event_type" is holding activation type (0 - interaction (default), 1 - trigger zone or 2 - switch) 
//    or type of a key (0 - blue, 1 - red, 2 - yellow) for locked doors
//    or 0 - none (default), 1 - interaction, 2 - trigger zone or 3 - switch for fences
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
// * "temp_skill" is used 0/1/2 - wait/wait deaf/patrol behaviour

// BOSSES
// * "flag" is checking whether boss should drop an item on death (true) or not (false)
// * "event_type" is holding item id to be dropper (0/1/2 - keys blue/red/yellow, 3/4 - medkits small/big)

#define MAX_ID_RANGE 999

void asset_params_activation_type(Cell *cell);

void asset_params_id(Cell *cell);

void asset_params_wall_params(Cell *cell, int asset);

void asset_params_props_params(Cell *cell, int asset);

void asset_params_events_params(Cell *cell, int asset);

void asset_params_enemies_params(Cell *cell, int asset);

void asset_params_bosses_params(Cell *cell, int asset);

void asset_params_obj_params_update(Cell *cell, int type, int asset);

#endif