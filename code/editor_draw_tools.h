#ifndef _EDITOR_DRAW_TOOLS_H_
#define _EDITOR_DRAW_TOOLS_H_

var mouse_resume_drawing = true; // used to prevent drawing when 'top bar' menu is used

var mouse_draw_timer = 0;
var mouse_draw_cooldown = 0.01;
var mouse_draw_once = false;

var mouse_erase_timer = 0;
var mouse_erase_cooldown = 0.01;
var mouse_erase_once = false;

var rotate_cell_once = false;

STRING *current_tool_str = "Editing tool: none;";

int is_cell_allowed_rotation(int type, int asset);

void editor_draw_cell(Episode *episode, Cell *to, Cell *from);

void editor_erase_cell(Cell *cell);

void editor_pick_tool(Cell *to, Cell *from);

void editor_draw_tools_update(Episode *episode, Cell *drawing_cell);

#endif