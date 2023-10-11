#include "sh.h"


/**
 * _eputs - prints a string.
 * @st: printed string.
 * Return: Void.
 */
void _eputs(char *st)
{
	int i = 0;

	if (!st)
		return;

	for (i = 0; st[i] != '\0'; i++)
		_eputchar(st[i]);
}



/**
 * _eputchar - writes the char d to stderr
 * @ch: char
 * Return: On success 1 or -1.
 */
int _eputchar(char ch)
{
	static int i;
	static char buff[W_BUF];

	if (ch == BUF_CLEAR || i >= W_BUF)
	{
		write(2, buff, i);
		i = 0;
	}
	if (ch != BUF_CLEAR)
		buff[i++] = ch;
	return (1);
}






/**
 * _putfd - writes character .
 * @ch: printed character.
 * @f_des: file descriptor.
 * Return: 1 or -1.
 */
int _putfd(char ch, int f_des)
{
	static int i;
	static char buff[W_BUF];

	if (ch == BUF_CLEAR || i >= W_BUF)
	{
		write(f_des, buff, i);
		i = 0;
	}
	if (ch != BUF_CLEAR)
		buff[i++] = ch;
	return (1);
}

/**
 * _putsfd - prints string.
 * @st: printed string.
 * @f_desc: file descriptor.
 * Return: number of chars.i
 */
int _putsfd(char *st, int f_desc)
{
	int i = 0, j;

	if (!st)
		return (0);

	for (j = 0; st[j] != '\0'; j++)
	{
		i += _putfd(st[j], f_desc);
	}
	return (i);
}
