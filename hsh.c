#include "sh.h"

/**
 * hsh - main loop.
 * @info: the paramete.
 * @av: the argument.
 * Return: 0 or 1 or NULL.
 */
int hsh(info_t *info, char **av)
{
	ssize_t size = 0;
	int bltin_return = 0;

	while (size != -1 && bltin_return != -2)
	{
		info_clear(info);
		if (interactive(info))
			_puts("my_Queen_Esra$ ");
		_eputchar(BUF_CLEAR);
		size = get_input(info);
		if (size != -1)
		{
			info_set(info, av);
			bltin_return = fd_builtin(info);
			if (bltin_return == -1)
				fd_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		info_free(info, 0);
	}
	wr_history(info);
	info_free(info, 1);
	if (!interactive(info) && info->return_status)
		exit(info->return_status);
	if (bltin_return == -2)
	{
		if (info->exit_code == -1)
			exit(info->return_status);
		exit(info->exit_code);
	}
	return (bltin_return);
}
