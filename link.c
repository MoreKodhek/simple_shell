#include "shell.h"

/**
 * _getenv - Gets the value of the global variable.
 * @name: Name of the global variable.
 * Return: String of value.
 */
char *_getenv(const char *name)
{
	if (!name)
		return (0);

	for (int i = 0; environ[i]; i++)
	{
		int j = 0;

		if (name[j] == environ[i][j])
		{
			while (name[j] && name[j] == environ[i][j])
				j++;

			if (name[j] == '\0')
				return (environ[i] + j + 1);
		}
	}

	return (0);
}

/**
 * add_node_end - Adds a new node at the end of a list.
 * @head: Pointer to pointer to our linked list.
 * @str: Pointer to string in the previous first node.
 * Return: Address of the new element/node.
 */
list_path *add_node_end(list_path **head, char *str)
{
	if (!head || !str)
		return (0);

	list_path *new = malloc(sizeof(list_path));

	if (!new)
		return (0);

	new->dir = str;
	new->p = NULL;

	if (!*head)
		*head = new;
	else
	{
		list_path *tmp = *head;

		while (tmp->p)
			tmp = tmp->p;

		tmp->p = new;
	}

	return (*head);
}

/**
 * linkpath - Creates a linked list for path directories.
 * @path: String of path value.
 * Return: Pointer to the created linked list.
 */
list_path *linkpath(char *path)
{
	list_path *head = NULL;
	char *token;
	char *cpath = _strdup(path);

	token = strtok(cpath, ":");
	while (token)
	{
		head = add_node_end(&head, token);
		token = strtok(NULL, ":");
	}

	return (head);
}

/**
 * _which - Finds the pathname of a filename.
 * @filename: Name of the file or command.
 * @head: Head of the linked list of path directories.
 * Return: Pathname of the filename or NULL if no match.
 */
char *_which(char *filename, list_path *head)
{
	struct stat st;
	char *string;
	list_path *tmp = head;

	while (tmp)
	{
		string = concat_all(tmp->dir, "/", filename);
		if (stat(string, &st) == 0)
			return (string);

		free(string);
		tmp = tmp->p;
	}

	return (0);
}

/**
 * free_list - Frees a linked list.
 * @head: Pointer to our linked list.
 */
void free_list(list_path *head)
{
	while (head)
	{
		list_path *storage = head->p;

		free(head->dir);
		free(head);
		head = storage;
	}
}
