#include "./event_handler.h"
#include "../graphics/font/print.h"

extern int event_count;

int process_event()
{
    return 0;
}

int handle_keyboard_events(Event* queue, int index)
{
    switch (queue[index].subtype)
    {
        case KEYBOARD_NONE:
            break;

        case KEYBOARD_TYPE: // pressed a normal character
        {
            if (queue[index].data)
            {
                char character = ((char*)queue[index].data)[0];
                print("%c", character);
            }  
            break;
        }

        case KEYBOARD_PRESSED: // pressing down shift etc
            break;

        case KEYBOARD_RELEASED: // released from buttons such as shift etc
            break;

        case KEYBOARD_ENTER:
        {
            print("\n");
            break;
        }
    }
    return 0;
}

void handle_events()
{
    Event* queue = return_event_queue();

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
        }
    }
}