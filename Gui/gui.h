#ifndef _GUI_H_
#define _GUI_H_

#include <stdint.h>
#include <stddef.h>
#include "../Include/string.h"
#include "../Include/malloc.h"
#include "../graphics/draw/draw.h"

#pragma once

#define MAX_CHILDREN_COUNT 50

typedef struct Style
{
    uint32_t background_color;
} Style;

typedef struct Frame
{
    bool dragable;
} Frame;

typedef enum
{
    ELEMENT_NONE,
    ELEMENT_FRAME,
} GUI_ElementType;

typedef struct GUI_Element
{
    GUI_ElementType type;
    struct GUI_Element* children[MAX_CHILDREN_COUNT];
    struct GUI_Element* parent;
    int children_count;
    char* name;
    int width;
    int height;
    int x;
    int y;
    int prev_x;
    int prev_y;
    int focus;
    Style style;
    union
    {
        Frame frame;
    };
} GUI_Element;

void init_gui();
void add_frame(GUI_Element* parent, const char* name, int x, int y, int width, int height, int focus, uint32_t bg_color);
void handle_gui_dragging(int mouse_x, int mouse_y, int prev_mouse_x, int prev_mouse_y);
void delete_frame(GUI_Element* object, uint32_t *frame);
void save_frame_data(GUI_Element* object, uint32_t *frame);

#endif