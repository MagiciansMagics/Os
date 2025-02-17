#include "./filesystem.h"
#include "../Include/string.h"

FileSystem* fs = (FileSystem*)FILESYSTEM_BASE_ADDR;

int files_count = 0;

extern uint32_t print_color;
extern int print_cursor_x;
extern int print_cursor_y;

void init_filesystem()
{
    for (size_t i = 0; i < MAX_FILES; i++) 
    {
        fs->files[i].filename[0] = '\0';
        fs->files[i].size = 0;
    }
}

int create_file(const char* name, uint32_t size)
{
    if (size >= MAX_FILE_SIZE) return FILESYSTEM_ERR_INVALID_SIZE;
    if (strlen(name) >= MAXFILENAME) return FILESYSTEM_ERR_FILENAME_TOO_LONG;

    for (size_t i = 0; i < MAX_FILES; i++) 
    {
        if (fs->files[i].filename[0] == '\0') 
        {
            strncpy(fs->files[i].filename, name, MAXFILENAME - 1);
            fs->files[i].filename[MAXFILENAME - 1] = '\0';
            fs->files[i].file_permission = FILE_READ_WRITE;                 // file is generally always read and write until changed
            fs->files[i].size = size;
            fs->files[i].data = NULL;
            files_count++;
            return 0;
        }
    }

    return FILESYSTEM_ERR_NO_SPACE_LEFT;
}

int edit_file(const char* file_name, const char* data)
{
    if (!file_name) return FILESYSTEM_ERR_DOESNT_EXIST;
    if (!data) return FILESYSTEM_ERR_INVALID_SIZE;

    uint32_t data_length = strlen(data);

    for (int i = 0; i < files_count; i++)
    {
        if (strcmp(fs->files[i].filename, file_name) == 0 &&
            (fs->files[i].file_permission == FILE_WRITE_ONLY || 
             fs->files[i].file_permission == FILE_READ_WRITE))
        {
            if (fs->files[i].data)
            {
                memset(fs->files[i].data, 0, fs->files[i].size);
                DeallocateMemory(fs->files[i].data);
            }
            fs->files[i].size = data_length;

            fs->files[i].data = AllocateMemory(fs->files[i].size);
            if (!fs->files[i].data) return FILESYSTEM_ERR_FAILED_TO_WRITE;

            memcpy(fs->files[i].data, data, data_length);

            return 0;
        }
    }

    return FILESYSTEM_ERR_DOESNT_EXIST;
}

int delete_file(const char* file_name)
{
    if (!file_name) return FILESYSTEM_ERR_DOESNT_EXIST;

    for (int i = 0; i < files_count; i++)
    {
        if (strcmp(fs->files[i].filename, file_name) == 0)
        {
            memset(fs->files[i].filename, 0, MAXFILENAME);

            if (fs->files[i].data)
            {
                DeallocateMemory(fs->files[i].data);
                fs->files[i].data = NULL;
            }

            fs->files[i].size = 0x00000000;
            fs->files[i].file_permission = 0;

            for (int j = i; j < files_count - 1; j++)
            {
                fs->files[j] = fs->files[j + 1];
            }

            files_count--;

            return 0;
        }
    }

    return FILESYSTEM_ERR_DOESNT_EXIST;
}

int cat_file(const char* file_name)
{
    if (!file_name) return FILESYSTEM_ERR_DOESNT_EXIST;

    for (int i = 0; i < files_count; i++)
    {
        if (strcmp(fs->files[i].filename, file_name) == 0)
        {
            if (fs->files[i].file_permission == FILE_WRITE_ONLY)
                return FILESYSTEM_ERR_PERMISSION_DENIED;

            if (!fs->files[i].data || fs->files[i].size == 0)
                return FILESYSTEM_ERR_INVALID_SIZE;

            char* content = (char*)AllocateMemory(fs->files[i].size + 1);
            if (!content) return FILESYSTEM_ERR_FAILED_TO_WRITE;

            memcpy(content, fs->files[i].data, fs->files[i].size);
            content[fs->files[i].size] = '\0';

            print_color = rgba_to_hex(0, 255, 0, 255);
            print("\n%s", content);
            print_color = 0xFFC8C8C8;

            return 0;
        }
    }

    return FILESYSTEM_ERR_DOESNT_EXIST;
}

void list_all_files()
{
    if (!fs) return;
    if (files_count == 0) { put_string("\nNo files found", rgba_to_hex(255, 0, 0, 255)); return; }
    print_color = rgba_to_hex(0, 255, 0, 255);
    print("\n\nAll files:\n");
    for (int i = 0; i < files_count; i++)
    {
        if (fs->files[i].filename[0] != '\0')
        {
            print("    %s          - Size: %u\n", fs->files[i].filename, fs->files[i].size);
        }
    }
    print_color = 0xFFC8C8C8;
}