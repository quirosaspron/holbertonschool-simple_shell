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
 * _unsetenv - remove an environment variable
 * @env: pointer to the environment variable array
 * @name: name of the variable to unset
 */
void _unsetenv(char ***env, char *name)
{
    int i, j;
    char **temp;

    if (*env == NULL || name == NULL)
        return;

    /* Find the variable in the environment variable array */
    for (i = 0; (*env)[i] != NULL; i++)
    {
        if (_strncmp((*env)[i], name, _strlen(name)) == 0 && (*env)[i][_strlen(name)] == '=')
        {
            /* Shift the remaining variables to fill the gap */
            for (j = i; (*env)[j] != NULL; j++)
                (*env)[j] = (*env)[j + 1];

            /* Resize the environment variable array */
            temp = realloc(*env, sizeof(char *) * (j));
            if (temp == NULL)
                return;

            *env = temp;
            break;
        }
    }
}

/**
 * _setenv - set or update an environment variable
 * @env: pointer to the environment variable array
 * @name: name of the variable to set or update
 * @value: value to assign to the variable
 */
void _setenv(char ***env, char *name, char *value)
{
    int i;
    char *var, *new_var;

    if (*env == NULL || name == NULL || value == NULL)
        return;

    /* Update the value if the variable already exists */
    for (i = 0; (*env)[i] != NULL; i++)
    {
        if (_strncmp((*env)[i], name, _strlen(name)) == 0 && (*env)[i][_strlen(name)] == '=')
        {
            var = (*env)[i];
            new_var = malloc(sizeof(char) * (_strlen(name) + _strlen(value) + 2));
            if (new_var == NULL)
                return;

            _strcpy(new_var, name);
            _strcat(new_var, "=");
            _strcat(new_var, value);
            (*env)[i] = new_var;
            free(var);
            return;
        }
    }

    /* If variable does not exist, create a new entry */
    var = malloc(sizeof(char) * (_strlen(name) + _strlen(value) + 2));
    if (var == NULL)
        return;

    _strcpy(var, name);
    _strcat(var, "=");
    _strcat(var, value);

    /* Count the number of environment variables */
    for (i = 0; (*env)[i] != NULL; i++)
        ;

    /* Resize the environment variable array */
    *env = realloc(*env, sizeof(char *) * (i + 2));
    if (*env == NULL)
    {
        free(var);
        return;
    }

    (*env)[i] = var;
    (*env)[i + 1] = NULL;
}
