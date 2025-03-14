#ifndef _EVENT_HANDLER_H
#define _EVENT_HANDLER_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "./event_queue.h"
#include "../filesystem/filesystem.h"
#include "../Hardware/mouse/mouse.h"
#include "../graphics/screen/screen.h"
#include "../Gui/gui.h"

#pragma once

void handle_events();

#endif