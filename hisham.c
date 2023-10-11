#include "sh.h"
/**
 *  * _putfd - function tht writes the character d to  fd
 *   * @d:  character to be printed
 *    * @fd:  filedescriptor to write to or modify
 *     *
 *      * Return: On success 1.
 *       * On error, -1 is returned, and errno is returned.
 */
int _putfd(char d, int fd)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (d == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(fd, buf, j);
		j = 0;
	}
	if (d != BUF_FLUSH)
		buf[j++] = d;
	return (1);
}
