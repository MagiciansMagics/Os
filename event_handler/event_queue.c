#include "./event_queue.h"

size_t event_count = 0;

bool is_event_queue_empty()
{
    return event_count != 0;
}

void push_event(Event event)
{
    if (event_count < MAX_EVENTS)
    {
        event_queue[event_count++] = event;
    }
}

bool pop_event(Event *event)
{
    if (event_count == 0)
    {
        return false;
    }

    *event = event_queue[0];

    for (size_t i = 1; i < event_count; i++)
    {
        event_queue[i - 1] = event_queue[i];
    }

    event_count--;
    return true;
}