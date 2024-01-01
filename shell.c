#include "shell.h"

/**
 * Handles the signal when Ctrl+C is pressed.
 * @param sig_num: Integer representing the signal number.
 */
void sig_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		_puts("\n#cisfun$ ");
	}
}

/**
 * Handles the End of File condition.
 * @param len: Return value of the getline function.
 * @param buff: Buffer used for input.
 */
void _EOF(int len, char *buff)
{
	(void)buff;
	if (len == -1)
	{
		if (isatty(STDIN_FILENO))
		{
			_puts("\n");
			free(buff);
		}
		exit(0);
	}
}

/**
 * Checks if the program is running in a terminal and displays the prompt.
 */
void _isatty(void)
{
	if (isatty(STDIN_FILENO))
	{
		_puts("#cisfun$ ");
	}
}

/**
 * Shell main function.
 * @return 0 on success.
 */
int main(void)
{
	ssize_t len = 0;
	char *buff = NULL, *value, *pathname, **arv;
	size_t size = 0;
	list_path *head = NULL;
	void (*f)(char **);
	signal(SIGINT, sig_handler);

	/** Main loop for the shell*/
	while (len != EOF)
	{
		// Display prompt if running in a terminal
		_isatty();
		len = getline(&buff, &size, stdin);
		_EOF(len, buff);
		arv = splitstring(buff, " \n");
		if (!arv || !arv[0])
		{
			execute(arv);
		}
		else
		{
			value = _getenv("PATH");
			head = linkpath(value);
			pathname = _which(arv[0], head);
			f = checkbuild(arv);

			if (f)
			{
				free(buff);
				f(arv);
			}
			else if (!pathname)
			{
				execute(arv);
			}
			else if (pathname)
			{
				free(arv[0]);
				arv[0] = pathname;
				execute(arv);
			}
		}
	}

	// Free allocated memory before exiting
	free_list(head);
	freearv(arv);
	free(buff);

	return 0;
}
