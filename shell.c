#include "shell.h"
/*
 * main - it is a shell
 * Retun: void
 **/

void main()
{
	size_t n = 10;
        char *buffer = NULL;
	char cmd[];
	char *token;
	/*Create argv*/

        printf("#myshell$");
        getline(&buffer, &n, stdin);
	token = strtok(str, " ");        
	/*input tokens into argv*/
	/*Create a child process */
	/* The child process will execve from the parameters in argv */
	/*We will wait for the child to finish so we can print and start again */

        free(buffer);
        return (0);
	
}
