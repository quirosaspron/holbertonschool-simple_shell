#include "simple_shell.h"
/**
 * main - print prompt, handle EOF, read file_stream
 * @argc: arg count (not needed)
 * @argv: argv for command
 * Return: Always 0.
 */
int main(int argc, char *argv[])
{
    char *s = NULL;
    size_t buffer_size = 0;
    ssize_t file_stream = 0;
    char *name;
    int return_status = 0;
    int cmd_return_status;
    
    (void)argc;
    name = argv[0];

    while (1)
    {
        if (isatty(STDIN_FILENO) == 1)
            write(1, "$ ", 2);
        file_stream = getline(&s, &buffer_size, stdin);
        if (file_stream == -1)
        {
            if (isatty(STDIN_FILENO) == 1)
                write(1, "\n", 1);
            break;
        }

        if (s[file_stream - 1] == '\n')
            s[file_stream - 1] = '\0';
        if (*s == '\0')
            continue;
        cmd_return_status = cmd_read(s, file_stream, name);
        if (cmd_return_status == 2)
        {
            return_status = 0;
            break;
        }
        else if (cmd_return_status != 0)
        {
            return_status = cmd_return_status;
        }
    }
    free(s);
    s = NULL;
    return (return_status);
}


/**
 * cmd_read - handles command line and tokenizes it
 * @s: string
 * @file_stream: getline input
 * @name: name
 * Return: 0
 */
int cmd_read(char *s, size_t __attribute__((unused))file_stream, char *name)
{
        char *token = NULL;
        char *cmd_arr[100];
        int i;

        if (_strcmp(s, "exit") == 0)
                return (2);
        if (_strcmp(s, "env") == 0)
                return (_printenv());

        while (*s == ' ')
                s++;

        if (*s == '\0')
                return (0);

        token = strtok(s, " "), i = 0;
        while (token)
        {
                cmd_arr[i++] = token;
                token = strtok(NULL, " ");
        }
        cmd_arr[i] = NULL;
        return (call_command(cmd_arr, name));
}
/**
 * print_not_found - prints when cmd is not found in path
 * @cmd: a string provided by the stdin
 * @name: name
 */
void print_not_found(char *cmd, char *name)
{
        write(2, name, _strlen(name));
        write(2, ": 1: ", 5);
        write(2, cmd, _strlen(cmd));
        write(2, ": not found\n", 12);
}
/**
 * call_command - calls cmd, forks, execve
 * @cmd_arr: a string provided by the stdin
 * @name: name
 * Return: 0
 */
int call_command(char *cmd_arr[], char *name)
{
    char *cmd = cmd_arr[0];
    char *exe_path_str = pathfinder(cmd);
    pid_t is_child;
    int status = 0;

    if (exe_path_str == NULL && _strcmp(cmd_arr[0], "exit") != 0)
    {
        dprintf(STDERR_FILENO, "%s: 1: %s: not found\n", name, cmd);
        status = 127;
    }
    else
    {
        is_child = fork();
        if (is_child < 0)
        {
            perror("Error:");
            status = -1;
        }
        else if (is_child > 0)
        {
            wait(&status);
	    if (WIFEXITED(status))
            {
                status = WEXITSTATUS(status);
                if (status != 0)
                {
                    if (_strcmp(cmd_arr[0], "exit") == 0 && cmd_arr[1] == NULL)
                        status = 2;
                }
            }
        }
        else if (is_child == 0)
        {
            (execve(exe_path_str, cmd_arr, environ));
            perror("Error:");
            exit(127);
        }
        free(exe_path_str);
    }

    return status;
}
