#ifndef _GUI_H_
#define _GUI_H_

#include <stdint.h>
#include "../graphics/draw/draw.h"
#include "../graphics/screen/screen.h"

#pragma once

#define MAX_GUI_OBJECTS 258

typedef struct Style
{
    uint32_t background_color;
} Style;

typedef struct Frame
{
    char* name;
    int width;
    int height;
    int x;
    int y;
    int prev_x;
    int prev_y;
    Style style;
} Frame;

typedef enum
{
    ELEMENT_FRAME,
} GUI_ElementType;

typedef struct GUI_Element
{
    GUI_ElementType type;
    union
    {
        Frame frame;
    };
} GUI_Element;

#endif