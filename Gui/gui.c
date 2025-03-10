#include "./gui.h"

GUI_Element *root_gui_element = NULL;

GUI_Element* find_gui_element(int x_pos, int y_pos)
{
    static GUI_Element* current = NULL;

    if (root_gui_element == NULL)
        return NULL;

    for (int i = 0; i < root_gui_element->children_count; i++)
    {
        current = root_gui_element->children[i];

        if (current->type == ELEMENT_NONE) return NULL;

        if (x_pos >= current->x && x_pos < (current->x + current->width) && y_pos >= current->y && y_pos < (current->y + current->height))
        {
            if (current->focus == 3)
            {
                return current;
            }
            else if (current->focus == 2)
            {
                return current;
            }
            else if (current->focus == 1)
            {
                return current;
            }
            else
            {
                return current;
            }
        }
    }

    return NULL;
}

void save_buffer(GUI_Element* object, uint32_t *buffer)
{
    for (int y = 0; y < object->height; y++)
    {
        for (int x = 0; x < object->width; x++)
        {
            buffer[y * object->width + x] = return_pixel_color(object->x + x, object->y + y);
        }
    }
}

void undraw_buffer(GUI_Element* object, uint32_t *buffer)
{
    for (int y = 0; y < object->height; y++)
    {
        for (int x = 0; x < object->width; x++)
        {
            draw_pixel(x + object->prev_x, y + object->prev_y, buffer[y * object->width + x]);
        }
    }
}

void handle_gui_dragging(int mouse_x, int mouse_y, int prev_mouse_x, int prev_mouse_y)
{
    GUI_Element* object = find_gui_element(mouse_x, mouse_y);

    if (object == NULL)
        return;

    int mouse_dx = mouse_x - prev_mouse_x;
    int mouse_dy = mouse_y - prev_mouse_y;

    uint32_t frame_backbuffer[object->width * object->height];

    object->prev_x = object->x;
    object->prev_y = object->y;

    object->x += mouse_dx;
    object->y += mouse_dy;

    undraw_buffer(object, frame_backbuffer);
    save_buffer(object, frame_backbuffer);
    draw_rectangular(object->x, object->y, object->width, object->height, object->style.background_color);
}

void add_frame(GUI_Element* parent, const char* name, int x, int y, int width, int height, int focus, uint32_t bg_color)
{
    if (!parent || strlen(name) == 0)
        return;

    GUI_Element* new_frame = (GUI_Element*)AllocateMemory(sizeof(GUI_Element));
    if (new_frame == NULL)
        return;

    if (parent->children_count > MAX_CHILDREN_COUNT)
        return;

    new_frame->type = ELEMENT_FRAME;
    new_frame->parent = parent;

    memset(new_frame->name, 0, sizeof(new_frame->name));
    strncpy(new_frame->name, name, strlen(name));
    new_frame->x = x;
    new_frame->y = y;
    new_frame->width = width;
    new_frame->height = height;
    new_frame->prev_x = x;
    new_frame->prev_y = y;
    new_frame->focus = focus;
    new_frame->style.background_color = bg_color;
    new_frame->children_count = 0;

    parent->children[parent->children_count] = new_frame;
    parent->children_count++;

    draw_rectangular(new_frame->x, new_frame->y, new_frame->width, new_frame->height, new_frame->style.background_color);
}

void init_gui()
{
    root_gui_element = (GUI_Element*)AllocateMemory(sizeof(GUI_Element));

    if (root_gui_element == NULL)
        return;

    root_gui_element->type = ELEMENT_NONE;
    root_gui_element->parent = NULL;
    root_gui_element->children_count = 0;
    root_gui_element->x = 0;
    root_gui_element->y = 0;
    root_gui_element->height = 0;
    root_gui_element->width = 0;
    root_gui_element->focus = 0;

    for (int i = 0; i < MAX_CHILDREN_COUNT; i++)
    {
        memset(root_gui_element->children[i], 0, sizeof(root_gui_element->children[i]));

        root_gui_element->children[i] = NULL;
    }

    add_frame(root_gui_element, "test", 0,0, 200, 200, 3, rgba_to_hex(255,255,255,255));

    memset(root_gui_element->name, 0, sizeof(root_gui_element->name));
}