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
    EVENT_MOUSE,
    EVENT_WINDOW,
} EventType;

typedef enum
{
    KEYBOARD_TYPE,
    KEYBOARD_PRESSED,
    KEYBOARD_RELEASED,
    KEYBOARD_ENTER,
    KEYBOARD_FILE_EDITING,
} KeyboardEventType;

typedef enum
{
    MOUSE_CLICKED,
    MOUSE_SCROLLED
} MouseEventType;

typedef enum
{
    WINDOW_UPDATE
} WindowEventType;

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