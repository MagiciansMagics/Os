#include "./keyboard.h"
#include "../../graphics/font/print.h"
#include "../../event_handler/event_handler.h"
#include "../../Include/string.h"

extern int print_cursor_x;
extern int print_cursor_y;

bool allowed_input = true;

bool shift = false;
bool caps = false;
bool winpressed = false;

char text_buffer[MAX_TEXT_SIZE];
int text_length = 0;

const char* lowercase[] = {
    " ", " ", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
    "-", "=", "\b", " ", "q", "w", "e", "r", "t", "y", "u", "i",
    "o", "p", "[", "]", "\n", " ", "a", "s", "d", "f", "g", "h",
    "j", "k", "l", ";", "'", "`", " ", "\\", "z", "x", "c", "v",
    "b", "n", "m", ",", ".", "/", " ", "*", " ", " "
};

const char* uppercase[] = {
    " ", " ", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")",
    "_", "+", "\b", " ", "Q", "W", "E", "R", "T", "Y", "U", "I",
    "O", "P", "{", "}", "\n", " ", "A", "S", "D", "F", "G", "H",
    "J", "K", "L", ":", "\"", "~", " ", "|", "Z", "X", "C", "V",
    "B", "N", "M", "<", ">", "?", " ", " ", " ", " "
};

void clear_last_char(uint32_t color)
{
    print_cursor_x -= 12;

    for (int y = 0; y < 16; y++)
    {
        for (int x = 0; x < 12; x++)
        {
            draw_pixel(print_cursor_x + x, print_cursor_y + y, color);
        }
    }
}

void KeyboardHandler()
{
    uint8_t scan = inb(0x60);

    uint8_t isPress = !(scan & 0x80);
    scan &= 0x7F;

    if (allowed_input)
    {
        switch (scan)
        {
            case 42:  // Left Shift
            case 54:  // Right Shift
                shift = isPress;
                break;

            case 58:  // Caps Lock
                if (isPress) 
                    caps = !caps; 
                break;

            case 0x1C:  // Enter    
            {
                if (isPress)
                {
                    Event event = {EVENT_KEYBOARD, KEYBOARD_ENTER, &text_buffer};
                    add_event(event);
                    text_length = 0; 
                }
                break;
            }

            case 0x5B:  // Left Windows Key
            case 0x5C:  // Right Windows Key
                winpressed = isPress;
                break;

            case 0x0E:          // backspace
            {
                if (isPress)
                {
                    if (text_length == 0) return;
                    text_length--;
                    text_buffer[text_length] = '\0';
                    clear_last_char(rgba_to_hex(0, 0, 0, 255));
                }
                break;
            }

            case 0x53:              // delete
            {
                if (isPress)
                {
                    if (text_length == 0) return;
                    text_length--;
                    text_buffer[text_length] = '\0';
                    clear_last_char(rgba_to_hex(0, 0, 0, 255));
                }
                break;
            }

            default:
                if (isPress && scan < sizeof(lowercase) / sizeof(lowercase[0])) 
                {
                    if (text_length < MAX_TEXT_SIZE - 1)
                    {
                        char character;
                        
                        if (shift || caps)
                        {
                            character = uppercase[scan][0];
                        }
                        else
                        {
                            character = lowercase[scan][0];
                        }

                        text_buffer[text_length] = character;
                        text_length++;
                        text_buffer[text_length] = '\0';

                        Event event = {EVENT_KEYBOARD, KEYBOARD_TYPE, &character};
                        add_event(event);
                    }
                }
                break;
        }
    }
}

void InitKeyboard()
{
    irq_install_handler(0x01, &KeyboardHandler);
}