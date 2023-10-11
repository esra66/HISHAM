#include "sh.h"

/**
 * node_starts_with - function that returns node
 * @nd: address.
 * @pre: string.
 * @ch: next character.
 * Return: node or null.
 */
list_t *node_starts_with(list_t *nd, char *pre, char ch)
{
	char *A = NULL;

	for (; nd; nd = nd->next)
	{
		A = starts_with(nd->str, pre);
		if (A && ((ch == -1) || (*A == ch)))
			return (nd);
	}
	return (NULL);
}

/**
 * get_node_index - gets index of a node.
 * @h: address.
 * @nd: pointer.
 * Return: index or -1.
 */
ssize_t get_node_index(list_t *h, list_t *nd)
{
	size_t len = 0;

	for (len = 0; h; h = h->next, len++)
	{
		if (h == nd)
			return (len);
	}
	return (-1);
}
