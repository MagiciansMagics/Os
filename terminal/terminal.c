#include "./terminal.h"

extern int print_cursor_x;
extern int print_cursor_y;
extern uint32_t print_color;

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
        print("\n\nAvailable commands: \n");
        print("    help                        - Displays all commands\n");
        print("    clear                       - Clears the screen\n");
        print("    touch <filename>            - Creates an empty file\n");
        print("    rm    <filename>            - Deletes selected file\n");
        print("    edit  <filename> <data>     - Edits the files data\n");
        print("    ls                          - Displays all files\n");
        print("    lscpu                       - Prints your cpu info\n");
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
            print("\nError: Missing filename");
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
            print("\nError: Missing filename or data");
        }
        else
        {
            size_t total_length = 0;
            for (int i = 2; i < args_count; i++)
            {
                total_length += strlen(args[i]) + 1;
            }

            char *full_data = (char *)AllocateMemory(total_length);
            if (!full_data)
            {
                return;
            }


            full_data[0] = '\0';
            for (int i = 2; i < args_count; i++)
            {
                strcat(full_data, args[i]);
                if (i < args_count - 1)
                    strcat(full_data, " ");
            }

            edit_file(args[1], full_data);
            DeallocateMemory(full_data);
        }
    }
    else if (strcmp(args[0], "cat") == 0)
    {
        if (args_count < 2)
        {
            print("\nError: Missing filename");
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
            print("\nError: Missing filename");
        }
        else
        {
            delete_file(args[1]);
        }
    }
    else if (strcmp(args[0], "lscpu") == 0)
    {
        char vendor[13];
        get_cpu_vendor(vendor);
        print("\n\nCpu info:\n");
        print("    Cpu vendor: %s\n\n", vendor);
    }

    memset(command, 0, sizeof(command));

    print("\nCommand: ");
}