#include "sh.h"

/**
 * is_delimiter - print true if character is a delimeter
 * @d:  char to be check
 * @delim:  delimeter
 * Return: 1 or 0.
 */
int is_delimiter(char d, char *delim)
{
	int i = 0;

	while (delim[i] != '\0')
	{

		if (d == delim[i])
		{
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 *_isalpha - print true if a character is alphabetic
 *@d: char to input
 *Return: 1 or 0.
 */

int _isalpha(int d)
{
	if ((d >= 65 && d <= 90) || (d >= 97 && d <= 122))
		return (1);
	else
		return (0);
}
