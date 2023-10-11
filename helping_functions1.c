#include "sh.h"
/**
 * interactive - prints true if shell is in interactive mode.
 * @info: address of struct.
 * Return: 1 or 0.
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->input_fd <= 2);
}

/**
 * sign_handle - blocks ctrl copy
 * @sig_num: the number of signal
 * Return: void
 */
void sign_handle(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_CLEAR);
}

/**
 * conv_num - converts a num.
 * @numb: number.
 * @base: base.
 * @flag: flags.
 * Return: string.
 */
char *conv_num(long int numb, int base, int flag)
{
	static char *array;
	static char buff[50];
	char sign = 0;
	char *ptr;
	unsigned long A = numb;

	if (!(flag & CONV_TO_UNSIGNED) && numb < 0)
	{
		A = -numb;
		sign = '-';

	}
	array = flag & CONV_TO_LOW ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buff[49];
	*ptr = '\0';

	while (A != 0)
	{
		*--ptr = array[A % base];
		A /= base;
	}

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * fd_builtin - finds a biltin cmd.
 * @info: parameter.
 * Return: -1, 0 , 1 or -2.
 */
int fd_builtin(info_t *info)
{
	int A, biltin_return = -1;
	builtin_t biltin_arr[] = {
		{"alias", _myalias},
		{"setenv", _mysetenv},
		{"cd", _mycd},
		{"env", _myenv},
		{"exit", _myexit},
		{"unsetenv", _myunsetenv},
		{"history", _myhistory},
		{NULL, NULL}};

	for (A = 0; biltin_arr[A].type; A++)
		if (_strcmp(info->argument_list[0], biltin_arr[A].type) == 0)
		{
			info->error_count++;
			biltin_return = biltin_arr[A].func(info);
			break;
		}
	return (biltin_return);
}


/**
 * duplicate_ch - duplicate set of chars.
 * @str_path: PATH.
 * @start1: start.
 * @stop2: stop.
 * Return: pointer.
 */
char *duplicate_ch(char *str_path, int start1, int stop2)
{
	static char buff[1024];
	int l = 0, k = 0;

	for (k = 0, l = start1; l < stop2; l++)
		if (str_path[l] != ':')
			buff[k++] = str_path[l];
	buff[k] = 0;
	return (buff);
}
