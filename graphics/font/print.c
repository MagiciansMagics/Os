#include "./print.h"
#include "../draw/draw.h"
#include "./font.h"

int print_cursor_x = 0;
int print_cursor_y = 0;
uint32_t print_color = 0xFFC8C8C8;

const uint8_t* get_char_bitmap(char c)
{
    if (c >= 1 && c <= 255)
    {
        return &default_font[(c) * 32];
    }
    return NULL;
}

void put_char(char c, uint32_t color)
{
    if (c == '\n')
    {
        print_cursor_y += 16;
        print_cursor_x = 0;
        return;
    }

    const uint8_t* bitmap = get_char_bitmap(c);
    if (!bitmap) return;

    for (uint16_t row = 0; row < 16; row++)
    {
        uint8_t row_data1 = bitmap[row * 2];
        uint8_t row_data2 = bitmap[row * 2 + 1];

        for (uint16_t col = 0; col < 12; col++)
        {
            uint16_t bit = 0;
            if (col < 8)
            {
                bit = (row_data1 >> (7 - col)) & 1;
            }
            else
            {
                bit = (row_data2 >> (15 - col)) & 1;
            }

            if (bit == 1)
            {
                if ((print_cursor_x + col) < WSCREEN && (print_cursor_y + row) < HSCREEN)
                {
                    draw_pixel(print_cursor_x + col, print_cursor_y + row, color);
                }
            }
        }
    }

    print_cursor_x += 12;
}

void print(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    char buffer[32];

    while (*fmt)
    {
        if (*fmt == '%')
        {
            fmt++;          // just skips the %, nothing important.

            switch (*fmt)
            {
                case 'd':           // integer
                {
                    int num = va_arg(args, int);
                    itoa(num, buffer, 10);
                    for (char* p = buffer; *p; p++)
                    {
                        put_char(*p, print_color);
                    }
                    break;
                }
                case 'x':
                {
                    int num = va_arg(args, int);
                    itoa(num, buffer, 16);  // Convert integer to hex string
                    for (char* p = buffer; *p; p++)
                    {
                        put_char(*p, print_color);
                    }
                    break;
                }
                default:          // used % but not allowed type
                    break;
            }
        }
        else
        {
            put_char(*fmt, print_color);
        }

        fmt++;
    }

    va_end(args);
}