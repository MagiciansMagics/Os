#ifndef _EVENT_HANDLER_H
#define _EVENT_HANDLER_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "./event_queue.h"

#pragma once

void process_event(Event *event, EventType event_type);
void process_pending_events(void (*event_handler)(Event *, EventType));

#endif