#include "./filesystem.h"
#include "../Include/string.h"

FileSystem* fs = (FileSystem*)FILESYSTEM_BASE_ADDR;

directory* currentdirectory;

char currentdirpath[MAX_PATH_LENGTH];

void init_filesystem()
{
    strncpy(fs->root.dirname, "root", MAX_NAME);

    fs->root.parent = NULL;

    strncpy(currentdirpath, "/root", MAX_PATH_LENGTH);

    for (int i = 0; i < MAX_FILES; i++)
    {
        memset(fs->root.sub_files[i].filename, 0, MAX_NAME);
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

int create_file(char* name, int flags)
{
    if (strlen(name) >= MAX_NAME) return FILESYSTEM_ERR_FILENAME_TOO_LONG;

    for (int i = 0; i < MAX_SUB_DIRS; i++)
    {
        if (strcmp(currentdirectory->sub_dirs[i]->dirname, name) == 0)
        {
            return FILESYSTEM_ERR_DIR_EXIST;
        }
    }

    int index = -1;

    for (int i = 0; i < MAX_FILES; i++)
    {
        if (currentdirectory->sub_files[i].filename[0] == '\0')
        {
            index = i;
            break;
        }
    }

    if (index == -2)
    {
        return FILESYSTEM_ERR_MAX_FILES_REACHED;
    }

    strncpy(currentdirectory->sub_files[index].filename, name, MAX_NAME);
    currentdirectory->sub_files[index].size = 0;
    currentdirectory->sub_files[index].data = NULL;
    currentdirectory->sub_files[index].file_permission = FILE_READ_WRITE;

    return 0;
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

int edit_file(char* name, char* data)
{
    if (strlen(name) >= MAX_NAME) return FILESYSTEM_ERR_FILENAME_TOO_LONG;
    if (strlen(data) == 0) return FILESYSTEM_ERR_NO_DATA;

    for (int i = 0; i < MAX_SUB_DIRS; i++)
    {
        if (strcmp(currentdirectory->sub_dirs[i]->dirname, name) == 0)
        {
            return FILESYSTEM_ERR_PERMISSION_WRITE;
        }
    }

    uint32_t length = strlen(data);

    for (int i = 0; i < MAX_FILES; i++)
    {
        if (strcmp(currentdirectory->sub_files[i].filename, name) == 0 && currentdirectory->sub_files[i].file_permission == FILE_READ_WRITE || 
        currentdirectory->sub_files[i].file_permission == FILE_WRITE_ONLY)
        {
            if (currentdirectory->sub_files[i].data != NULL)
            {
                DeallocateMemory(currentdirectory->sub_files[i].data);
                currentdirectory->sub_files[i].data = NULL;
                memset(&currentdirectory->sub_files[i].size, 0, sizeof(currentdirectory->sub_files[i].size));
            }

            currentdirectory->sub_files[i].size = length;

            currentdirectory->sub_files[i].data = AllocateMemory(currentdirectory->sub_files[i].size);
            if (currentdirectory->sub_files[i].data == NULL) return FILESYSTEM_ERR_FAILED_TO_WRITE;

            memcpy(currentdirectory->sub_files[i].data, data, length);

            return 0;
        }
    }

    return FILESYSTEM_ERR_FILE_NOT_FOUND;
}

int cat_file(char* name)
{
    if (strlen(name) >= MAX_NAME) return FILESYSTEM_ERR_FILENAME_TOO_LONG;

    for (int i = 0; i < MAX_SUB_DIRS; i++)
    {
        if (strcmp(currentdirectory->sub_dirs[i]->dirname, name) == 0)
        {
            return FILESYSTEM_ERR_PERMISSION_READ;
        }
    }

    for (int i = 0; i < MAX_FILES; i++)
    {
        if (strcmp(currentdirectory->sub_files[i].filename, name) == 0 && currentdirectory->sub_files[i].file_permission == FILE_READ_WRITE ||
        currentdirectory->sub_files[i].file_permission == FILE_READ_ONLY)
        {
            if (currentdirectory->sub_files[i].data == NULL || currentdirectory->sub_files[i].size == 0)
            {
                return FILESYSTEM_ERR_FAILED_TO_READ;
            }

            char* content = (char*)AllocateMemory(currentdirectory->sub_files[i].size + 1);
            if (content == NULL) return FILESYSTEM_ERR_FAILED_TO_READ;

            memcpy(content, currentdirectory->sub_files[i].data, currentdirectory->sub_files[i].size);
            content[currentdirectory->sub_files[i].size] = '\0';

            print("\n%s", content);

            DeallocateMemory(content);

            return 0;
        }
    }

    return FILESYSTEM_ERR_FILE_NOT_FOUND;
}

// dir

int create_directory(char* dname, int permissions)
{
    if (strlen(dname) >= MAX_NAME) return FILESYSTEM_ERR_DIRNAME_TOO_LONG;

    for (int i = 0; i < MAX_SUB_DIRS; i++)
    {
        if (currentdirectory->sub_dirs[i] != NULL &&
            strcmp(currentdirectory->sub_dirs[i]->dirname, dname) == 0)
        {
            return FILESYSTEM_ERR_DIR_EXIST;
        }
    }

    for (int i = 0; i < MAX_SUB_DIRS; i++)
    {
        if (currentdirectory->sub_dirs[i] == NULL)
        {
            directory* new_dir = (directory*)AllocateMemory(sizeof(directory));
            if (!new_dir) return FILESYSTEM_ERR_COMMON_ERROR;

            memset(new_dir, 0, sizeof(directory));

            strncpy(new_dir->dirname, dname, MAX_NAME);

            new_dir->parent = currentdirectory;

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
            DeallocateMemory(currentdirectory->sub_dirs[i]);
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
        if (currentdirectory->parent != NULL)
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

// find and list

int find_file_loop(char* name, directory* dir, char* path) 
{
    for (int i = 0; i < MAX_FILES; i++) {
        if (dir->sub_files[i].filename[0] != '\0' && strcmp(dir->sub_files[i].filename, name) == 0) {
            print("\nFile found: /root%s/%s", path, dir->sub_files[i].filename);
            return 0;
        }
    }

    for (int i = 0; i < MAX_SUB_DIRS; i++) 
    {
        if (dir->sub_dirs[i] != NULL) {
            char new_path[MAX_NAME * 2];
            strncpy(new_path, path, MAX_NAME * 2);
            strncat(new_path, "/", MAX_NAME * 2 - strlen(new_path) - 1);
            strncat(new_path, dir->sub_dirs[i]->dirname, MAX_NAME * 2 - strlen(new_path) - 1);
            
            int result = find_file_loop(name, dir->sub_dirs[i], new_path);
            if (result >= 0) {
                return 0;
            }
        }
    }
    
    return FILESYSTEM_ERR_FILE_NOT_FOUND;
}

int find_file(char* name)
{
    if (strlen(name) >= MAX_NAME) {
        return FILESYSTEM_ERR_FILENAME_TOO_LONG;
    }
    
    char initial_path[MAX_NAME] = "";
    return find_file_loop(name, &fs->root, initial_path);
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
                print("- Size    %d\n", currentdirectory->sub_files[i].size);
            }
        }
    }
}