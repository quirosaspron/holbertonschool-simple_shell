#include "simple_shell.h"
char *pathfinder(char *cmd)
{
    struct stat buf;
    char *path = NULL;
    char *path_tokens = NULL;
    char *path_array[100] = {NULL};
    char *s2 = cmd;
    char *new_path = NULL;
    int i, j;

    if (stat(cmd, &buf) == 0)
    {
        if (!S_ISDIR(buf.st_mode))
            return (_strdup(cmd));
    }

    path = _strdup(_getenv("PATH"));
    if (path == NULL)
        return (NULL);

    path_tokens = strtok(path, ":");

    new_path = malloc(sizeof(char) * (strlen(path) + strlen(cmd) + 2));
    if (new_path == NULL)
    {
        free(path);
        return (NULL);
    }

    i = 0;
    while (path_tokens != NULL)
    {
        path_array[i++] = path_tokens;
        path_tokens = strtok(NULL, ":");
    }
    path_array[i] = NULL;

    for (j = 0; path_array[j] != NULL; j++)
    {
        strcpy(new_path, path_array[j]);
        strcat(new_path, "/");
        strcat(new_path, s2);

        if (stat(new_path, &buf) == 0)
        {
            if (!S_ISDIR(buf.st_mode))
            {
                free(path);
                return new_path;
            }
        }
        else
        {
            new_path[0] = '\0';
        }
    }

    free(path);
    free(new_path);
    return NULL;
}
