#ifndef _FILESYSTEM_H_
#define _FILESYSTEM_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "../Include/string.h"
#include "../graphics/font/print.h"
#include "../graphics/draw/draw.h"
#include "../Include/malloc.h"

#pragma once

#define MAX_FILE_SIZE                       2048
#define DEFAULT_FILE_SIZE                   0                       // if a file is made simply the size is technically zero
#define FILESYSTEM_BASE_ADDR                0x40000
#define MAXFILENAME                         50
#define MAX_FILES                           15

typedef enum
{
    FILESYSTEM_ERR_FILENAME_TOO_LONG = -1,
    FILESYSTEM_ERR_NO_SPACE_LEFT = -2,  
    FILESYSTEM_ERR_INVALID_SIZE = -3, 
    FILESYSTEM_ERR_DOESNT_EXIST = -4,
    FILESYSTEM_ERR_FAILED_TO_WRITE = -5,
    FILESYSTEM_ERR_PERMISSION_DENIED = -6,
} FileSystemError;

typedef enum
{
    FILE_READ_ONLY = 1,    // File is read-only
    FILE_WRITE_ONLY = 2,   // File is write-only
    FILE_READ_WRITE = 3,   // File is both readable and writable
    FILE_HIDDEN = 4,       // File is hidden
} FilePermissions;

typedef struct
{
    char filename[MAXFILENAME];
    uint32_t size;
    uint8_t* data;
    FilePermissions file_permission;
} FileHeader;

typedef struct
{
    FileHeader files[MAX_FILES];
} FileSystem;

void init_filesystem();
int create_file(const char* name, uint32_t size);
int delete_file(const char* file_name);
int edit_file(const char* file_name, const char* data);
int cat_file(const char* file_name);
void list_all_files();

#endif