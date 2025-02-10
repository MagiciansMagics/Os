#include "./event_handler.h"
#include "../graphics/font/print.h"

void process_event(Event *event, EventType event_type)
{
    switch (event_type)
    {
        case EVENT_NONE:
            break;
        case EVENT_KEYBOARD:
        {
            char* text_buffer = (char*) event->data;
            // here handle some way of making sure when is what for the keyboard to send data etc
            print("\n");
            break;
        }
        case EVENT_MOUSEMOVE:
            // draw it another position etc
            break;
        case EVENT_WINDOW_UPDATE:
            // simply swap buffers as this is requested
            break;
    }
}

void process_pending_events(void (*event_handler)(Event *, EventType))
{
    Event current_event;

    while (!is_event_queue_empty())
    {
        if (pop_event(&current_event))
        {
            process_event(&current_event, current_event.type);
        }
    }
}