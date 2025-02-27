#include "./event_handler.h"
#include "../graphics/font/print.h"
#include "../Include/string.h"

extern int event_count;

int is_event_queue_empty()
{
    return event_count == 0;
}

int handle_keyboard_events(Event* queue, int index)
{
    switch (queue[index].subtype)
    {
        case KEYBOARD_TYPE: // pressed a normal character
        {
            if (queue[index].data)
            {
                char character = ((char*)queue[index].data)[0];
                print("%c", character);
            }  
            break;
        }
        
        case KEYBOARD_ENTER:
        {
            char* cmd = (char*)queue[index].data;
            handle_terminal_cmd(cmd);
            break;
        }

        default:                // unknown subtype
            break;
    }
    return 0;
}

int handle_mouse_events(Event* queue, int index)
{
    switch (queue[index].subtype)
    {
        case MOUSE_MOVED:
        {
            int* mouse_ptr = (int*)queue[index].data;
            if (mouse_ptr)
            {
                undraw_mouse(mouse_ptr[2], mouse_ptr[3]); // Remove old cursor position
                draw_mouse(mouse_ptr[0], mouse_ptr[1], rgba_to_hex(255, 255, 255, 255)); // Draw new position
            }
            break;
        }

        case MOUSE_CLICKED:
        {
            // here make it handle if its currently over a gui and pressing etc.
            break;
        }
    }
}

int handle_window_events(Event* queue, int index)
{
    switch(queue[index].subtype)
    {
        case WINDOW_UPDATE:
        {
            break;
        }
    }
}

void handle_events()
{
    if (is_event_queue_empty()) return;

    Event* queue = return_event_queue();

    if (!queue) return;

    for (int i = 0; i < event_count; i++)
    {
        switch (queue[i].type)
        {
            case EVENT_NONE:
            {
                remove_event(i);
                break; // simply do nothing as it says
            }

            case EVENT_KEYBOARD:
            {
                handle_keyboard_events(queue, i);
                remove_event(i);
                break;
            }

            case EVENT_MOUSE:
            {
                handle_mouse_events(queue, i);
                remove_event(i);
                break;
            }

            default:            // unknown event
            {
                remove_event(i);
                break;
            }
        }
    }
}