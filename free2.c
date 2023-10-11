#include "sh.h"

/**
 * free_ptr - frees a pointer.
 * @p: address.
 * Return: 1 or 0.
 */
int free_ptr(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}

/**
 * free_str -  frees a string.
 * @pptr: to be freed string
 * Return: Void.
 */
void free_str(char **pptr)
{
	char **A = pptr;

	if (!pptr)
		return;
	for (; *pptr; pptr++)
	{
		free(*pptr);
	};
	free(A);
}

/**
 * free_list - function that frees all nodes of a list
 * @head_ptr: address of pointer to head node
 * Return: nothing
 */
void free_list(list_t **head_ptr)
{
	list_t *curr_node, *next_node;

	if (!head_ptr || !*head_ptr)
		return;
	curr_node = *head_ptr;
	while (curr_node != NULL)
	{
		next_node = curr_node->next;
		free(curr_node->str);
		free(curr_node);
		curr_node = next_node;
	}
	*head_ptr = NULL;
}
