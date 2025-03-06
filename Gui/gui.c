#include "./gui.h"

GUI_Element gui_objects[MAX_GUI_OBJECTS];
int gui_object_count = 0;

void add_frame(const char* name, int x, int y, int width, int height, uint32_t bg_color)
{
    if (gui_object_count >= MAX_GUI_OBJECTS)
        return;

    GUI_Element* element = &gui_objects[gui_object_count++];
    element->type = ELEMENT_FRAME;
    element->frame.name = (char*)name;
    element->frame.x = x;
    element->frame.y = y;
    element->frame.width = width;
    element->frame.height = height;
    element->frame.prev_x = x;
    element->frame.prev_y = y;
    element->frame.style.background_color = bg_color;
}

void render_frame(const char* name)
{
    for (int i = 0; i < gui_object_count; i++)
    {
        if (strcmp(name, gui_objects[i].frame.name) == 0 && gui_objects->type == ELEMENT_FRAME)
        {
            draw_rectangular(gui_objects[i].frame.x, gui_objects[i].frame.y, gui_objects[i].frame.width, gui_objects[i].frame.height, gui_objects[i].frame.style.background_color);
        }
    }
}