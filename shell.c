#include "shell.h"
/**
 * main - it is a shell
 * Retun: void
 */

int main(void)
{
	size_t n = 10;
	char *buffer = NULL;
	char *token;
	char *argv[10];
	int argc = 0;
	int val;
	pid_t pid;

	while (1)
	{
		printf("#myshell$ ");
		if (getline(&buffer, &n,stdin) == -1)
		{
			printf("Error reading input\n");
			perror("Error");
			return (1);
		}
		token = strtok(buffer, " \n");
		while (token != NULL)
		{
			argv[argc++] = token;
			token = strtok(NULL, " \n");
		}
		argv[argc] = NULL;
		if (argc > 0)
		{
			pid = fork();
			if (pid == -1)
			{
				printf("Error\n");
				return 1;
			}
			else if (pid == 0)
			{
				val = execve(argv[0], argv, NULL );
				if (val == -1)
				{
					perror("Error");
				}	
				return (1);
			}
			else
			{
				wait(NULL);
			}
		}
		argc = 0;
	}

	free(buffer);
	return (0);
}
