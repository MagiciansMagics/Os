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
#define MAX_NAME                            50
#define MAX_FILES                           15
#define MAX_SUB_DIRS                        10

#define MAX_PATH_LENGTH                     (MAX_SUB_DIRS * MAX_NAME + MAX_SUB_DIRS + MAX_NAME)

typedef enum
{
    FILESYSTEM_ERR_FILENAME_TOO_LONG = -1,
    FILESYSTEM_ERR_DIRNAME_TOO_LONG = -2,
    FILESYSTEM_ERR_FILE_NOT_FOUND = -3,
    FILESYSTEM_ERR_DIR_NOT_FOUND = -4,
    FILESYSTEM_ERR_DOESNT_EXIST = -5,                           // just a geneneral error if something doesnt exist in the file system
    FILESYSTEM_ERR_DIR_EXIST = -6,
    FILESYSTEM_ERR_FILE_EXIST = -7,
    FILESYSTEM_ERR_MAX_DIRS_REACHED = -8,
    FILESYSTEM_ERR_MAX_FILES_REACHED = -9,
    FILESYSTEM_ERR_COMMON_ERROR = -10,
    FILESYSTEM_ERR_NO_DATA = -11,
    FILESYSTEM_ERR_PERMISSION_WRITE = -12,
    FILESYSTEM_ERR_PERMISSION_READ = -13,
    FILESYSTEM_ERR_FAILED_TO_WRITE = -14,
    FILESYSTEM_ERR_FAILED_TO_READ = -15,
} FileSystemError;

typedef enum
{
    FILE_DEAD = 0,         // only used when deleting a file etc 
    FILE_READ_ONLY = 1,    // File is read-only
    FILE_WRITE_ONLY = 2,   // File is write-only
    FILE_READ_WRITE = 3,   // File is both readable and writable
    FILE_HIDDEN = 4,       // File is hidden
} FilePermissions;

typedef struct
{
    char filename[MAX_NAME];
    uint32_t size;
    uint8_t* data;
    FilePermissions file_permission;
} FileHeader;

typedef struct directory directory;

struct directory
{
    char dirname[MAX_NAME];

    FileHeader sub_files[MAX_FILES];

    directory* sub_dirs[MAX_SUB_DIRS];
    directory* parent;
};

typedef struct
{
    directory root;
    directory* currentdir;
} FileSystem;

void init_filesystem();
int create_file(char* name, int flags);
int remove_file(char* name);
int edit_file(char* name, char* data);
int cat_file(char* name);
int find_file(char* name);
int create_directory(char* name, int permissions);
int remove_directory(char* dname);
int change_directory(char* dirname);
void list_current_dir();

#endif