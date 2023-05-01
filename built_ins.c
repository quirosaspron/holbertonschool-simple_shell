#include "simple_shell.h"
/**
 * _printenv - prints environment like printenv
 *
 * Return: 0
 */
int _printenv(void)
{
	char *s = environ[0];
	int i = 0;

	while (s)
	{
		write(1, s, _strlen(s));
		write(1, "\n", 1);
		s = environ[++i];
	}
	return (0);
}

/**
 * _str_n_cmp - lexicographically compares not more than count chars
 * from two strings and returns an integer based on the result.
 * @s1: first string
 * @s2: second string to compare to first string
 * @n: count of the comparison between s1 and s2
 * Return: <0 if s1 is less than s2, 0 for equal, >0 if s1 is greater than s2
 * Description: Src code file like GNU C library
 */
int _str_n_cmp(char *s1, char *s2, int n)
{
	char c1, c2;

	while (n--)
	{
		c1 = *s1++;
		c2 = *s2++;
		if (c1 == '\0' || c1 != c2)
			return (c1 > c2 ? 1 : (c1 < c2 ? -1 : 0));
	}
				return (0);
}
/**
 * _getenv - prints environment like getenv
 * @var: environ variable
 *
 * Return: 0
 */
char *_getenv(char *var)
{
	int i = 0;

	for (i = 0; environ[i]; i++)
	{
		if (_str_n_cmp(environ[i], var, _strlen(var)) == 0)
			return (&environ[i][_strlen(var)]);
	}
	return (NULL);
}
/**
 * env_list - create a linked list of the environment variables
 * @env: the environment variables
 * Return: pointer to the head of the linked list
 */
env_t *env_list(char **env)
{
	env_t *head, *node, *temp;
	char *path_value = NULL;

	head = NULL;
	while (*env)
	{
		node = malloc(sizeof(env_t));
		if (node == NULL)
			exit(1);
		node->name = _strdup(*env);
		node->next = NULL;
		if (head == NULL)
			head = node;
		else
			temp->next = node;
		temp = node;

		if (_strncmp(*env, "PATH=", 5) == 0)
			_unsetenv(&head, *env);
		if (_strncmp(*env, "PATH1=", 6) == 0)
			_unsetenv(&head, *env);
	}
	path_value = _strcat("PATH1=", "/bin");
	_setenv(&head, path_value);

	return (head);
}
