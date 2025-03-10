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
                //print("%c", character);
            }  
            break;
        }
        
        case KEYBOARD_ENTER:
        {
            char* cmd = (char*)queue[index].data;
            //handle_terminal_cmd(cmd);
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
        case MOUSE_CLICKED:
        {
            int* mouse_pos_ptr = (int*)queue[index].data;

            handle_gui_dragging(mouse_pos_ptr[0], mouse_pos_ptr[1], mouse_pos_ptr[2], mouse_pos_ptr[3]);
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