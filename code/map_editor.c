
void map_editor_initialize()
{
    map_editor_ui_initialize();
}

void map_editor_start(Episode *e)
{
    map_editor_ui_refresh(e);
}

void map_editor_reset(Episode *e)
{
    map_editor_ui_reset(e);
}

void map_editor_destroy()
{
    map_editor_ui_destroy();
}

void map_editor_update(Episode *e)
{
    if (!e)
    {
        return;
    }

    imgui_start_imode();

    map_editor_side_menu(e);
    map_editor_top_menu_bar(e);
    editor_cell_tooltip(e);

    imgui_end_imode();
}