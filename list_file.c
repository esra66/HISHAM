#include "sh.h"


/**
 * list_len - function that prints a length of list
 * @head: first node
 * Return: counter
 */
size_t list_len(const list_t *head)
{
	size_t counter = 0;
	const list_t *curr_node = head;

	for (; curr_node != NULL; curr_node = curr_node->next)
	{
		counter++;
	}

	return (counter);
}

/**
 * conv_list_to_str - function that converts a linked list to a string array
 * @head: first node
 * Return: string array
 */
char **conv_list_to_str(list_t *head)
{
	list_t *current = head;
	size_t count = list_len(head), idx, j;
	char **strings;
	char *string;

	if (!head || !count)
		return (NULL);
	strings = malloc(sizeof(char *) * (count + 1));
	if (!strings)
		return (NULL);
	for (idx = 0; current; current = current->next, idx++)
	{
		string = malloc(_strlen(current->str) + 1);
		if (!string)
		{
			for (j = 0; j < idx; j++)
				free(strings[j]);
			free(strings);
			return (NULL);
		}

		string = _strcpy(string, current->str);
		strings[idx] = string;
	}
	strings[idx] = NULL;
	return (strings);
}
