#include "simple_shell.h"
/**
 * pathfinder - Find the path of a command in the PATH env variable
 * @cmd: The command to find
 * Return: The full path of the command if found, NULL otherwise
 */
char *pathfinder(char *cmd)
{
	struct stat buf;
	char *path, path_tokens, path_array[100], new_path;
	char *s2 = cmd;
	int i, j;

	if (stat(cmd, &buf) == 0)
	{
		if (!S_ISDIR(buf.st_mode))
			return (_strdup(cmd));
	}
	path = _strdup(_getenv("PATH"));
	path_tokens = strtok(path, ":");
	new_path = malloc(sizeof(char) * 100);
	i = 0;
	while (path_tokens != NULL)
	{
		path_array[i++] = path_tokens;
		path_tokens = strtok(NULL, ":");
	}
	path_array[i] = NULL;
	for (j = 0; path_array[j] != NULL; j++)
	{
		_strcpy(new_path, path_array[j]);
		_strcat(new_path, "/");
		_strcat(new_path, s2);
		_strcat(new_path, "\0");
		if (stat(new_path, &buf) == 0)
		{
			if (!S_ISDIR(buf.st_mode))
			{
				free(path);
				return (new_path);
			}
		}
		else
			new_path[0] = '\0';
	}
	free(path);
	free(new_path);
	return (NULL);
}
