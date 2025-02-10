#ifndef _EVENT_QUEUE_H
#define _EVENT_QUEUE_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#pragma once

#define MAX_EVENTS 100

typedef enum 
{
    EVENT_NONE,
    EVENT_KEYBOARD,
    EVENT_MOUSEMOVE,
    EVENT_WINDOW_UPDATE,
} EventType;

typedef struct 
{
    EventType type;
    void* data; // Can store additional data (e.g., keycode, mouse position)
} Event;

static Event event_queue[MAX_EVENTS];

bool is_event_queue_empty();
void push_event(Event event);
bool pop_event(Event *event);

#endif