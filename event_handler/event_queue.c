#include "./event_queue.h"
#include "../Include/malloc.h"
#include "../graphics/font/print.h"

int event_count = 0;

Event* event_queue = NULL; // Use NULL instead of nullptr

#define EVENT_QUEUE_FULL (event_count >= MAX_EVENTS)
#define EVENT_QUEUE_EMPTY (event_count == 0)

int init_event_queue()
{
    if (event_queue != NULL)
    {
        DeallocateMemory(event_queue);
        event_queue = NULL;
    }

    event_queue = (Event*)AllocateMemory(MAX_EVENTS * sizeof(Event));

    if (event_queue == NULL)
    {
        print("Failed to allocate memory for event queue\n");
        return 1;
    }

    event_count = 0;
    return 0;
}

int add_event(Event event)
{
    if (EVENT_QUEUE_FULL)
        return 1;
    event_queue[event_count] = event;
    event_count++;
    return 0;
}

int remove_event(int index)
{
    if (EVENT_QUEUE_EMPTY)
        return 1;

    if (index < 0 || index >= event_count)
        return 1;

    for (int i = index; i < event_count - 1; i++)
    {
        event_queue[i] = event_queue[i + 1];
    }

    event_count--;

    return 0;
}

int clear_event_queue()
{
    if (EVENT_QUEUE_EMPTY)
        return 1;

    while (event_count > 0)
    {
        int a = remove_event(0);

        if (a)
            return 1;
    }

    return 0;
}

Event* return_event_queue()
{
    return event_queue;
}