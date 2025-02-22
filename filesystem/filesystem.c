#include "./filesystem.h"
#include "../Include/string.h"

FileSystem* fs = (FileSystem*)FILESYSTEM_BASE_ADDR;

directory* currentdirectory;

char currentdirpath[MAX_PATH_LENGTH];

void init_filesystem()
{
    if (fs == NULL) 
    {
        fs = (FileSystem*)AllocateMemory(sizeof(FileSystem));
        if (fs == NULL) 
        {
            return;
        }
    }

    memset(&fs, 0, sizeof(FileSystem));

    strncpy(fs->root.dirname, "root", MAX_NAME);
    fs->root.parent = NULL;

    strncpy(currentdirpath, "/root", MAX_PATH_LENGTH);

    for (int i = 0; i < MAX_FILES; i++)
    {
        fs->root.sub_files[i].filename[0] = '\0';
        fs->root.sub_files[i].size = 0;
        fs->root.sub_files[i].data = NULL;
        fs->root.sub_files[i].file_permission = FILE_READ_WRITE;
    }

    for (int i = 0; i < MAX_SUB_DIRS; i++)
    {
        fs->root.sub_dirs[i] = NULL;
    }

    currentdirectory = &fs->root;
}

int create_file(char* name)
{
    if (strlen(name) >= MAX_NAME) return FILESYSTEM_ERR_FILENAME_TOO_LONG;

    bool q = false;

    for (int i = 0; i < MAX_SUB_DIRS; i++)
    {
        if (strcmp(currentdirectory->sub_dirs[i]->dirname, name) == 0)
        {
            q = true;
            return FILESYSTEM_ERR_DIR_EXIST;
        }
    }

    if (!q)
    {
        for (int i = 0; i < MAX_FILES; i++)
        {
            if (strcmp(currentdirectory->sub_files[i].filename, name) != 0)
            {
                strncpy(currentdirectory->sub_files[i].filename, name, MAX_NAME);
                currentdirectory->sub_files[i].data = NULL;
                currentdirectory->sub_files[i].size = 0;
                currentdirectory->sub_files[i].file_permission = FILE_READ_WRITE;
                return 0;
            }
        }
    }

    return FILESYSTEM_ERR_FILE_EXIST;
}

int remove_file(char* name)
{
    if (strlen(name) >= MAX_NAME) return FILESYSTEM_ERR_FILENAME_TOO_LONG;

    bool q = false;

    for (int i = 0; i < MAX_SUB_DIRS; i++)
    {
        if (strcmp(currentdirectory->sub_dirs[i]->dirname, name) == 0)
        {
            q = true;
        }
    }

    if (!q)
    {
        for (int i = 0; i < MAX_FILES; i++)
        {
            if (strcmp(currentdirectory->sub_files[i].filename, name) == 0)
            {
                memset(currentdirectory->sub_files[i].filename, 0, sizeof(currentdirectory->sub_files[i].filename));

                if (currentdirectory->sub_files[i].data != NULL)
                {
                    DeallocateMemory(currentdirectory->sub_files[i].data);
                    currentdirectory->sub_files[i].data = NULL;
                }

                currentdirectory->sub_files[i].size = 0;
                currentdirectory->sub_files[i].file_permission = FILE_DEAD;
                return 0;
            }
        }
    }

    return FILESYSTEM_ERR_FILE_NOT_FOUND;
}

int create_directory(char* dname)
{
    if (strlen(dname) >= MAX_NAME) return FILESYSTEM_ERR_DIRNAME_TOO_LONG;

    for (int i = 0; i < MAX_SUB_DIRS; i++)
    {
        if (currentdirectory->sub_dirs[i] == NULL)
        {
            directory* new_dir = (directory*)AllocateMemory(sizeof(directory));
            if (!new_dir) return FILESYSTEM_ERR_COMMON_ERROR;

            memset(new_dir, 0, sizeof(directory));

            strncpy(new_dir->dirname, dname, MAX_NAME);

            currentdirectory->sub_dirs[i] = new_dir;

            return 0;
        }
    }

    return FILESYSTEM_ERR_MAX_DIRS_REACHED;
}

int remove_directory(char* dname)
{
    if (strlen(dname) >= MAX_NAME) return FILESYSTEM_ERR_DIRNAME_TOO_LONG;

    for (int i = 0; i < MAX_SUB_DIRS; i++)
    {
        if (currentdirectory->sub_dirs[i] != NULL && strcmp(currentdirectory->sub_dirs[i]->dirname, dname) == 0)
        {
            currentdirectory->sub_dirs[i] = NULL;           // lazy asf way

            return 0;
        }
    }
    return FILESYSTEM_ERR_DIR_NOT_FOUND;
}


int change_directory(char* dirname)
{
    if (strlen(dirname) >= MAX_NAME) return FILESYSTEM_ERR_DIRNAME_TOO_LONG;

    if (strcmp(dirname, "..") == 0)
    {
        if (currentdirectory->parent != NULL || currentdirectory->parent == &fs->root)
        {
            currentdirectory = currentdirectory->parent;

            char* lastSlash = strrchr(currentdirpath, '/');
            if (lastSlash != NULL)
                *lastSlash = '\0';

            if (strlen(currentdirpath) == 0)
                strncpy(currentdirpath, "/", MAX_PATH_LENGTH);


            return 0;
        }

        return FILESYSTEM_ERR_DIR_NOT_FOUND;
    }

    for (int i = 0; i < MAX_SUB_DIRS; i++)
    {
        if (currentdirectory->sub_dirs[i] != NULL && strcmp(currentdirectory->sub_dirs[i]->dirname, dirname) == 0)
        {
            currentdirectory = currentdirectory->sub_dirs[i];
            strncat(currentdirpath, "/", MAX_PATH_LENGTH - strlen(currentdirpath) - 1);
            strncat(currentdirpath, dirname, MAX_PATH_LENGTH - strlen(currentdirpath) - 1);

            return 0;
        }
    }

    return FILESYSTEM_ERR_DIR_NOT_FOUND;
}

void list_current_dir()
{
    bool hasDirectories = false;
    bool hasFiles = false;

    for (int i = 0; i < MAX_SUB_DIRS; i++)
    {
        if (currentdirectory->sub_dirs[i] != NULL && currentdirectory->sub_dirs[i]->dirname[0] != '\0')
        {
            hasDirectories = true;
            break;
        }
    }

    for (int i = 0; i < MAX_FILES; i++)
    {
        if (currentdirectory->sub_files[i].filename[0] != '\0')
        {
            hasFiles = true;
            break;
        }
    }

    if (hasDirectories)
    {
        print("\n\n[Directorys]\n");

        for (int i = 0; i < MAX_SUB_DIRS; i++)
        {
            if (currentdirectory->sub_dirs[i] != NULL && currentdirectory->sub_dirs[i]->dirname[0] != '\0')
            {
                print("%s", currentdirectory->sub_dirs[i]->dirname);
                set_print_x_pos(600);
                print("<DIR>\n");
            }
        }
    }

    if (hasFiles)
    {
        print("\n\n[Files]\n");

        for (int i = 0; i < MAX_FILES; i++)
        {
            if (currentdirectory->sub_files[i].filename[0] != '\0')
            {
                print("%s", currentdirectory->sub_files[i].filename);
                set_print_x_pos(600);
                print("<FILE>\n");
            }
        }
    }
}