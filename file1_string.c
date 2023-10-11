#include"sh.h"

/**
 * _strlen - print length.
 * @str: string.
 * Return: length.
 */
int _strlen(char *str)
{
	int x = 0;

	if (str == NULL)
		return (0);

	while (*str != '\0')
	{
		x++;
		str++;
	}
	return (x);
}
/**
 * starts_with - check if string start with
 * @str: string.
 * @prefex: substring.
 * Return: Address.
 */
char *starts_with(const char *str, const char *prefex)
{
	while (*prefex != '\0')
	{
		if (*prefex  !=  *str)
		{
			return (NULL);
		}
		prefex++;
		str++;
	}
	return ((char *)str);
}

/**
 * _strcat - concatenates sour and dest.
 * @dest: dest.
 * @sour: sour.
 * Return: pointer.
 */
char *_strcat(char *dest, char *sour)
{
	int x = 0;
	int y = 0;

	while (dest[x] != '\0')
		x++;

	while (sour[y] != '\0')
	{
		dest[x] = sour[y];
		x++;
		y++;
	}
	dest[x] = '\0';
	return (dest);
}
/**
 * _strcmp -  compare two strings.
 * @st1: st1.
 * @st2: st2.
 * Return: the result.
 */
int _strcmp(char *st1, char *st2)
{
	int x = 0;

	while (st1[x] != '\0' && st2[x] != '\0' && st1[x] == st2[x])
	{
		x++;
	}

	if (st1[x] == st2[x])
	{
		return (0);
	}
	else if (st1[x] < st2[x])
	{
		return (-1);
	}
	else
	{
		return (1);
	}
}


