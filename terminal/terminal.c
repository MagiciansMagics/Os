#include "./terminal.h"

extern char currentdirpath[MAX_PATH_LENGTH];

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
        print("    touch <filename>            - Makes a new file\n");
        print("    rm    <filename>            - Removes selected file\n");
        print("    cat   <filename>            - Prints data of the selected file\n");
        print("    find  <filename>            - Finds selected file\n");
        print("    mkdir <dir name>            - Makes a directory\n");
        print("    rmdir <dir name>            - Removes selected directory\n");
        print("    cd    <dir name>            - Change directory\n");
        print("    ls                          - Prints current directory\n");
        print("    lscpu                       - Prints your cpu info\n");
    }
    else if (strcmp(args[0], "clear") == 0)
    {
        set_print_x_pos(0);
        set_print_y_pos(0);
        clear_screen(rgba_to_hex(0, 0, 0, 255));
    }
    else if (strcmp(args[0], "touch") == 0)
    {
        if (args_count < 2)
        {
            print("\nMissing filename");
        }
        else
        {
            create_file(args[1]);
        }
    }
    else if (strcmp(args[0], "rm") == 0)
    {
        if (args_count < 2)
        {
            print("\nMissing filename");
        }
        else
        {
            remove_file(args[1]);
        }
    }
    else if (strcmp(args[0], "edit") == 0)
    {
        if (args_count < 3)
        {
            print("\nMissing filename or data");
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
            print("\nMissing filename");
        }
        else
        {
            cat_file(args[1]);
        }
    }
    else if (strcmp(args[0], "find") == 0)
    {
        if (args_count < 2)
        {
            print("\nMissing filename");
        }
        else
        {
            find_file(args[1]);
        }
    }
    else if (strcmp(args[0], "mkdir") == 0)
    {
        if (args_count < 2)
        {
            print("\nMissing directory name");
        }
        else
        {
            create_directory(args[1]);
        }
    }
    else if (strcmp(args[0], "rmdir") == 0)
    {
        if (args_count < 2)
        {
            print("\nMissing directory name");
        }
        else
        {
            remove_directory(args[1]);
        }
    }
    else if (strcmp(args[0], "cd") == 0)
    {
        if (args_count < 2)
        {
            print("\nMissing directory name");
        }
        else
        {
            change_directory(args[1]);
        }
    }
    else if (strcmp(args[0], "ls") == 0)
    {
        list_current_dir();
    }
    else if (strcmp(args[0], "lscpu") == 0)
    {
        char vendor[13];
        get_cpu_vendor(vendor);
        print("\n\nCpu info:\n");
        print("    Cpu vendor: %s\n", vendor);
    }

    memset(command, 0, sizeof(command));

    print("\n%s: ", currentdirpath);
}