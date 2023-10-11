#include "sh.h"


/**
 * _strncpy - copies a string.
 * @dest: destination string.
 * @src: source string.
 * @n: number of characters to copy.
 * Return: pointer to the destination string.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i;
	char *result = dest;

	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}

	for (; i < n; i++)
	{
		dest[i] = '\0';
	}

	return (result);
}

/**
 * *_strncat - concatenates two strings
 * @des: first string
 * @src: second string
 * @n: num of bytes
 * Return: concat string
 */
char *_strncat(char *des, char *src, int n)
{
	int i, j;
	char *result = des;

	i = 0;

	while (des[i] != '\0')
		i++;

	for (j = 0; j < n && src[j] != '\0'; j++)
		des[i + j] = src[j];

	des[i + j] = '\0';

	return (result);
}

/**
 * *_strchr - locates a character in a string
 * @st: string
 * @c: character
 * Return: pointer to area of memory
 */
char *_strchr(char *st, char c)
{
	int i = 0;

	while (st[i] != '\0')
	{
		if (st[i] == c)
			return (&st[i]);
		i++;
	}

	return (NULL);
}
