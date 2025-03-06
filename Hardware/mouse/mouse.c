#include "./mouse.h"
#include "./cursor.h"
#include "../../event_handler/event_queue.h"

uint8_t mousePacket[4];
int mouse_x_pos, mouse_y_pos = -30;

int mouse_prev_x_pos, mouse_prev_y_pos, mouse_m1_pressed = 0;

uint8_t mouseData;
uint8_t mouseCycle;

int mouse_pos_holder[4] = {};
uint32_t background_buffer[HCURSOR * WCURSOR];

void save_cursor_buffer(int mouse_x, int mouse_y)
{
    for (int h = 0; h < HCURSOR; h++)
    {
        for (int w = 0; w < WCURSOR; w++)
        {
            background_buffer[h * WCURSOR + w] = return_pixel_color(mouse_x + w, mouse_y + h);
        }
    }
}

void clear_mouse_trails(int prev_mouse_x, int prev_mouse_y)
{
    for (int h = 0; h < HCURSOR; h++)
    {
        for (int w = 0; w < WCURSOR; w++)
        {
            draw_pixel(prev_mouse_x + w, prev_mouse_y + h, background_buffer[h * WCURSOR + w]);
        }
    }
}

void draw_mouse(int mouse_x, int mouse_y, uint32_t color)
{
    for (int h = 0; h < HCURSOR; h++)
    {
        for (int w = 0; w < WCURSOR; w++)
        {
            draw_pixel(mouse_x + w, mouse_y + h, color);
        }
    }
}

void MouseHandler()
{
    uint8_t mouseData = inb(0x60);

    if (mouseCycle == 0 && !(mouseData & 0x08))
    {
        return;
    }

    mousePacket[mouseCycle++] = mouseData;

    if (mouseCycle == 3)
    {
        mouseCycle = 0;

        mouse_m1_pressed = (mousePacket[0] & 0x1);

        int deltaX = (int)((char)mousePacket[1]);
        int deltaY = (int)((char)mousePacket[2]);

        mouse_prev_x_pos = mouse_x_pos;
        mouse_prev_y_pos = mouse_y_pos;

        mouse_x_pos += deltaX;
        mouse_y_pos -= deltaY;

        mouse_x_pos = (mouse_x_pos < 0) ? 0 : ((mouse_x_pos > WSCREEN - 16) ? WSCREEN - 16 : mouse_x_pos);
        mouse_y_pos = (mouse_y_pos < 0) ? 0 : ((mouse_y_pos > HSCREEN - 16) ? HSCREEN - 16 : mouse_y_pos);

        mouse_pos_holder[0] = mouse_x_pos;
        mouse_pos_holder[1] = mouse_y_pos;
        mouse_pos_holder[2] = mouse_prev_x_pos;
        mouse_pos_holder[3] = mouse_prev_y_pos;

        Event event = {EVENT_MOUSE, MOUSE_MOVED, (void*)mouse_pos_holder};

        add_event(event);
    }
}

void init_mouse()
{
    outb(0x64, 0xA7); //Disable auxiliary PS/2 Device
    outb(0x64, 0xA8); //Enable Mouse

    while (inb(0x64) & 1)
    {
        inb(0x60);
    }

    irq_install_handler(12, &MouseHandler);

    outb(0x64, 0x20);              //Request config byte
    uint8_t status = (inb(0x60) | 2); //Enable mouse interrupts
    outb(0x64, 0x60);              //Define byte config
    outb(0x60, status);

    outb(0x64, 0xD4); //Sends command to PS/2 Device
    outb(0x60, 0xF4); //Enable mouse data streaming
}