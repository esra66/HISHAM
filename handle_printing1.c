#include "sh.h"

/**
 * _myhistory - displays history.
 * @info: Structure containing potential arguments.
 *  Return: 0.
 */
int _myhistory(info_t *info)
{
	print_list(info->command_history);
	return (0);
}


/**
 * print_err - prints an error.
 * @info: struct.
 * @err_st: error string.
 * Return: 0 or -1.
 */
void print_err(info_t *info, char *err_st)
{
	_eputs(info->program_name);
	_eputs(": ");
	print_deci(info->error_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argument_list[0]);
	_eputs(": ");
	_eputs(err_st);
}


/**
 * print_deci - prints decimal.
 * @input: input.
 * @f_desc: file descriptor.
 * Return: char counter.
 */
int print_deci(int input, int f_desc)
{
	int (*__putchar)(char) = _putchar;
	int j, counter = 0;
	unsigned int _abs_, curr;

	if (f_desc == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		counter++;
	}
	else
		_abs_ = input;
	curr = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			__putchar('0' + curr / j);
			counter++;
		}
		curr %= j;
	}
	__putchar('0' + curr);
	counter++;

	return (counter);
}


/**
 * rm_comments - replaces instance of '#' with null.
 * @buffer: address.
 * Return: Always 0;
 */
void rm_comments(char *buffer)
{
	int i = 0;

	while (buffer[i] != '\0')
	{
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
		i++;
	}
}

/**
 * fd_path - finds command in PATH.
 * @info: struct.
 * @str_path: PATH.
 * @comd: command to be found.
 * Return: PATH or NULL.
 */
char *fd_path(info_t *info, char *str_path, char *comd)
{
	int k = 0, current = 0;
	char *pth;

	if (!str_path)
		return (NULL);
	if ((_strlen(comd) > 2) && starts_with(comd, "./"))
	{
		if (is_command(info, comd))
			return (comd);
	}
	while (1)
	{
		if (!str_path[k] || str_path[k] == ':')
		{
			pth = duplicate_ch(str_path, current, k);
			if (!*pth)
				_strcat(pth, comd);
			else
			{
				_strcat(pth, "/");
				_strcat(pth, comd);
			}
			if (is_command(info, pth))
				return (pth);
			if (!str_path[k])
				break;
			current = k;
		}
		k++;
	}
	return (NULL);
}
