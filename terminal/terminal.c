#include "./terminal.h"

extern int print_cursor_x;
extern int print_cursor_y;

#define MAX_ARGS 10

void parse_command_arguments(char* command, char* args[], int* args_count)
{
    *args_count = 0;

    while (*command)
    {
        while (*command == ' ') command++;

        if (*command == '\0') break;

        if (*args_count < MAX_ARGS)
        {
            args[*args_count] = command;
            (*args_count)++;
        }

        while (*command && *command != ' ') command++;

        if (*command) 
        {
            *command = '\0';
            command++;
        }
    }
}

void handle_terminal_cmd(char* command)
{
    if (!command || *command == '\0') return;

    char* args[MAX_ARGS];
    int args_count = 0;
    parse_command_arguments(command, args, &args_count);

    if (args_count == 0) return;

    if (strcmp(args[0], "help") == 0)
    {
        put_string("\n\nAvailable commands: \n",                                        rgba_to_hex(0, 255, 0, 255));
        put_string("    help                        - Displays all commands\n",         rgba_to_hex(0, 255, 0, 255));
        put_string("    clear                       - Clears the screen\n",             rgba_to_hex(0, 255, 0, 255));
        put_string("    touch <filename>            - Creates an empty file\n",         rgba_to_hex(0, 255, 0, 255));
        put_string("    rm    <filename>            - Deletes selected file\n",         rgba_to_hex(0, 255, 0, 255));
        put_string("    edit  <filename> <data>     - Edits the files data\n",          rgba_to_hex(0, 255, 0, 255));
        put_string("    ls                          - Displays all files\n",            rgba_to_hex(0, 255, 0, 255));
    }
    else if (strcmp(args[0], "clear") == 0)
    {
        print_cursor_x = 0;
        print_cursor_y = 0;
        clear_screen(rgba_to_hex(0, 0, 0, 255));
    }
    else if (strcmp(args[0], "touch") == 0)
    {
        if (args_count < 2)
        {
            put_string("\nError: Missing filename", rgba_to_hex(255, 0, 0, 255));
        }
        else
        {
            create_file(args[1], DEFAULT_FILE_SIZE);
        }
    }
    else if (strcmp(args[0], "ls") == 0)
    {
        list_all_files();
    }
    else if (strcmp(args[0], "edit") == 0)
    {
        if (args_count < 3)
        {
            put_string("\nError: Missing filename or data", rgba_to_hex(255, 0, 0, 255));
        }
        else
        {
            edit_file(args[1], args[2]);
        }
    }
    else if (strcmp(args[0], "cat") == 0)
    {
        if (args_count < 2)
        {
            put_string("\nError: Missing filename", rgba_to_hex(255, 0, 0, 255));
        }
        else
        {
            cat_file(args[1]);
        }
    }
    else if (strcmp(args[0], "rm") == 0)
    {
        if (args_count < 2)
        {
            put_string("\nError: Missing filename", rgba_to_hex(255, 0, 0, 255));
        }
        else
        {
            delete_file(args[1]);
        }
    }

    memset(command, 0, sizeof(command));

    print("\nCommand: ");
}