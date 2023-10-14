#include "sh.h"

/**
 * add_node - adds a node to the start
 * @head: address of pointer to head
 * @str: string field of node
 * @num: node index
 * Return: pointer to new head
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head = malloc(sizeof(list_t));

	if (!new_head)
		return (NULL);
	new_head->num = num;
	new_head->str = NULL;
	new_head->next = *head;
	if (str)
	{
		new_head->str = _strdup(str);

		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - adds a node to the end
 * @head: address of pointer to head
 * @str: string field of node
 * @num: node index
 * Return: pointer to new tail
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node = malloc(sizeof(list_t));
	list_t *node;

	if (!new_node)
		return (NULL);
	new_node->num = num;
	new_node->str = NULL;
	new_node->next = NULL;
	if (str)
	{
		new_node->str = _strdup(str);

		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		node = *head;

		while (node->next != NULL)
			node = node->next;
		node->next = new_node;
	}
	return (new_node);
}

/**
 * delete_node_at_index - function that deletes node at index
 * @head: address of pointer to first node
 * @index: index of node to delete
 * Return: 1 on success or 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int counter = 0;

	if (!head || !*head)
		return (0);
	if (index == 0)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node != NULL)
	{
		if (counter == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		counter++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}
