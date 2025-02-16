#include "./terminal.h"

extern int print_cursor_x;
extern int print_cursor_y;

void handle_terminal_cmd(char* command)
{
    if (!command) return;

    if (strcmp(command, "help") == 0)
    {
        put_string("\n\nAvailable commands: \n",                                    rgba_to_hex(0, 255, 0, 255));
        put_string("    help                    - Displays all commands\n",         rgba_to_hex(0, 255, 0, 255));
        put_string("    clear                   - Clears the screen\n",             rgba_to_hex(0, 255, 0, 255));
    }
    else if (strcmp(command, "clear") == 0)
    {
        print_cursor_x = 0;
        print_cursor_y = 0;
        clear_screen(rgba_to_hex(0, 0, 0, 255));
    }

    print("\nCommand: ");
}