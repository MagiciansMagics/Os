#ifndef _EVENT_QUEUE_H
#define _EVENT_QUEUE_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#pragma once

#define MAX_EVENTS 100
#define NOEVENT 0

typedef enum 
{
    EVENT_NONE,
    EVENT_KEYBOARD,
    EVENT_MOUSEMOVE,
    EVENT_WINDOW_UPDATE,
} EventType;

typedef enum
{
    KEYBOARD_NONE,
    KEYBOARD_TYPE,
    KEYBOARD_PRESSED,
    KEYBOARD_RELEASED,
    KEYBOARD_ENTER
} KeyboardEventType;

typedef enum
{
    MOUSE_NONE,
    MOUSE_MOVED,
    MOUSE_CLICKED,
    MOUSE_RELEASED,
    MOUSE_SCROLLED
} MouseEventType;

typedef struct 
{
    EventType type;
    int subtype; // Use this for specific event details (keyboard/mouse/etc.)
    void* data;  // Can store additional event-specific data
} Event;

int init_event_queue();
int add_event(Event event);
int remove_event(int index);
int clear_event_queue();
Event* return_event_queue();

#endif