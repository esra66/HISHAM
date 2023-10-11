#include "sh.h"

/**
 * _strcpy - function that copies the string
 * @dest: destination string
 * @sour: source string
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *sour)
{
	int w;

	for (w = 0; sour[w] != '\0'; w++)
		dest[w] = sour[w];
	dest[w] = '\0';
	return (dest);
}

/**
 * _strdup - duplicates the string in memory.
 * @st: string to be duplicate.
 * Return: pointer to the duplicated string, or NULL if str is NULL.
 */
char *_strdup(const char *st)
{
	char *dup;
	int i = 0;
	int length = 0;

	if (st == NULL)
		return (NULL);
	while (st[length] != '\0')
		length++;

	dup = malloc((length + 1) * sizeof(char));
	if (dup == NULL)
	{
		return (NULL);
	}

	for (i = 0; i <= length; i++)
		dup[i] = st[i];
	return (dup);
}

/**
* _puts - function that prints a string to stdout
* @st: string to print
* Return: void
*/
void _puts(char *st)
{
	int z;

	for (z = 0; st[z] != '\0'; z++)
		_putchar(st[z]);
}

/**
 * _putchar - function that writes c character to stdout
 * @c: character to print
 * Return: 1 or -1.
 */
int _putchar(char c)
{
	static char buf[W_BUF];
	static int k;

	if (c == BUF_CLEAR || k >= W_BUF)
	{
		write(1, buf, k);
		k = 0;
	}
	if (c != BUF_CLEAR)
		buf[k++] = c;
	return (1);
}
