#include "shell.h"

/**
 * splitstring - Splits a string and creates an array of pointers to words.
 * @str: The string to be split.
 * @delim: The delimiter.
 * Return: Array of pointers to words.
 */
char **splitstring(char *str, const char *delim)
{
	char **array = NULL, *token, *copy;
	size_t wn = 2; /* Initial size of the array */
	int i = 0;

	copy = _strdup(str);
	if (!copy || !(array = malloc(sizeof(char *) * wn)))
	{
		perror(_getenv("_"));
		return (NULL);
	}

	token = strtok(copy, delim);
	array[0] = _strdup(token);

	while ((token = strtok(NULL, delim)))
	{
		array = _realloc(array, sizeof(char *) * (wn - 1), sizeof(char *) * wn);
		array[i + 1] = _strdup(token);
		i++;
		wn++;
	}

	free(copy);
	return (array);
}

/**
 * execute - Executes a command.
 * @argv: Array of arguments.
 */
void execute(char **argv)
{
	int d, status;

	if (!argv || !argv[0])
		return;

	d = fork();
	if (d == -1)
	{
		perror(_getenv("_"));
		return;
	}

	if (d == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			perror(argv[0]);
			exit(EXIT_FAILURE);
		}
	}

	wait(&status);
}

/**
 * _realloc - Reallocates memory block.
 * @ptr: Previous pointer.
 * @old_size: Old size of the previous pointer.
 * @new_size: New size for the pointer.
 * Return: New resized pointer.
 */
void *_realloc(void *ptr, size_t old_size, size_t new_size)
{
	char *new, *old;
	size_t i;

	if (!ptr)
		return (malloc(new_size));

	if (new_size == old_size || (new_size == 0 && (free(ptr), 1)))
		return (ptr);

	new = malloc(new_size);
	old = ptr;

	if (!new)
		return (NULL);

	for (i = 0; i < (new_size < old_size ? new_size : old_size); i++)
		new[i] = old[i];

	free(ptr);

	if (new_size > old_size)
	{
		for (; i < new_size; i++)
			new[i] = '\0';
	}

	return (new);
}

/**
 * freearv - Frees the array of pointers arv.
 * @arv: Array of pointers.
 */
void freearv(char **arv)
{
	int i;

	if (!arv)
		return;

	for (i = 0; arv[i]; i++)
		free(arv[i]);

	free(arv);
}
