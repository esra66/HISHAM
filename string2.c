#include "sh.h"

/**
 * **strtow - splits a string into words.
 * @string: input string.
 * @deli: delimeter.
 * Return: a pointer.
 */

char **strtow(char *string, char *deli)
{
	int z, k, l, t, words_count = 0;
	char **A;

	if (string == NULL || string[0] == 0)
		return (NULL);
	if (!deli)
		deli = " ";
	for (z = 0; string[z] != '\0'; z++)
		if (!is_delimiter(string[z], deli) && (is_delimiter(string[z + 1],
						deli) || !string[z + 1]))
			words_count++;

	if (words_count == 0)
		return (NULL);
	A = malloc((1 + words_count) * sizeof(char *));
	if (!A)
		return (NULL);
	for (z = 0, k = 0; k < words_count; k++)
	{
		while (is_delimiter(string[z], deli))
			z++;
		l = 0;
		while (!is_delimiter(string[z + l], deli) && string[z + l])
			l++;
		A[k] = malloc((l + 1) * sizeof(char));
		if (!A[k])
		{
			for (l = 0; l < k; l++)
				free(A[l]);
			free(A);
			return (NULL);
		}
		for (t = 0; t < l; t++)
			A[k][t] = string[z++];
		A[k][t] = 0;
	}
	A[k] = NULL;
	return (A);
}

/**
 * **strtow2 - splits a string into words.
 * @string: string.
 * @deli: delimeter.
 * Return: a pointer.
 */
char **strtow2(char *string, char deli)
{
	int z, k, l, t, words_count = 0;
	char **A;

	if (string == NULL || string[0] == 0)
		return (NULL);
	for (z = 0; string[z] != '\0'; z++)
		if ((string[z] != deli && string[z + 1] == deli) ||
				(string[z] != deli && !string[z + 1]) || string[z + 1] == deli)
			words_count++;
	if (words_count == 0)
		return (NULL);
	A = malloc((1 + words_count) * sizeof(char *));
	if (!A)
		return (NULL);
	for (z = 0, k = 0; k < words_count; k++)
	{
		while (string[z] == deli && string[z] != deli)
			z++;
		l = 0;
		while (string[z + l] != deli && string[z + l] && string[z + l] != deli)
			l++;
		A[k] = malloc((l + 1) * sizeof(char));
		if (!A[k])
		{
			for (l = 0; l < k; l++)
				free(A[l]);
			free(A);
			return (NULL);
		}
		for (t = 0; t < l; t++)
			A[k][t] = string[z++];
		A[k][t] = 0;
	}
	A[k] = NULL;
	return (A);
}
