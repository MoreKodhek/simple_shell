#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "shell.h"

/**
 * _strdup - Duplicates a string.
 * @str: Pointer to a string.
 * Return: Pointer to the duplicated string.
 */
char *_strdup(const char *str)
{
	if (!str)
		return (0);

	size_t len = strlen(str);
	char *new_str = malloc(len + 1);

	if (!new_str)
		return (0);

	strcpy(new_str, str);
	return (new_str);
}

/**
 * concat_all - Concatenates three strings.
 * @name: First string.
 * @sep: Second string.
 * @value: Third string.
 * Return: Pointer to the new concatenated string.
 */
char *concat_all(const char *name, const char *sep, const char *value)
{
	size_t len_name = strlen(name);
	size_t len_sep = strlen(sep);
	size_t len_value = strlen(value);

	char *result = malloc(len_name + len_sep + len_value + 1);

	if (!result)
		return (0);

	/* Concatenate strings using sprintf for efficiency.*/
	sprintf(result, "%s%s%s", name, sep, value);

	return (result);
}

/**
 * _putchar - Writes the character c to stdout.
 * @c: The character to print.
 * Return: On success 1, on error -1 is returned,
 * and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _puts - Prints a string.
 * @str: Pointer to string.
 */
void _puts(const char *str)
{
	write(1, str, strlen(str));
}

/**
 * main - Shell
 * Return: 0 on success
 */

int main(void)
{
	char *str1 = "Hello";
	char *str2 = " ";
	char *str3 = "World";

	/* Test _strdup */
	char *duplicate = _strdup(str1);

	if (duplicate != NULL)
	{
		_puts("Duplicated string: ");
		_puts(duplicate);
		_putchar('\n');
		free(duplicate);
	}

	/* Test concat_all */
	char *result = concat_all(str1, str2, str3);

	if (result != NULL)
	{
		_puts("Concatenated string: ");
		_puts(result);
		_putchar('\n');
		free(result);
	}

	return (0);
}
