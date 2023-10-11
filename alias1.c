#include "sh.h"

/**
 * unset_alias - removes alias.
 * @info: struct .
 * @st: alias to be removed.
 * Return: 0 or 1 .
 */
int unset_alias(info_t *info, char *st)
{
	char *equal_pos;
	int r, index;

	equal_pos = _strchr(st, '=');

	if (!equal_pos)
		return (1);

	index = get_node_index(info->command_aliases,
			node_starts_with(info->command_aliases, st, -1));

	if (index == -1)
		return (1);

	r = delete_node_at_index(&(info->command_aliases), index);
	return (r);
}

/**
 * set_alias - sets alias to string.
 * @info: struct.
 * @st1: alias.
 * Return: 0 or 1.
 */
int set_alias(info_t *info, char *st1)
{
	char *x;

	x = _strchr(st1, '=');
	if (!x)
		return (1);
	if (!*++x)
		return (unset_alias(info, st1));

	unset_alias(info, st1);
	return (add_node_end(&(info->command_aliases), st1, 0) == NULL);
}

/**
 * print_alias - prints an alias .
 * @nd1: node.
 * Return: 0 or 1.
 */
int print_alias(list_t *nd1)
{
	char *A = NULL, *B = NULL;

	if (nd1)
	{
		A = _strchr(nd1->str, '=');
		for (B = nd1->str; B <= A; B++)
			_putchar(*B);
		_putchar('\'');
		_puts(A + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - function that copies the alias in builtin
 * @info: Structure tht has potential arguments.maintains
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *A = NULL;
	list_t *nd2 = NULL;

	if (info->argument_count == 1)
	{
		nd2 = info->command_aliases;
		while (nd2)
		{
			print_alias(nd2);
			nd2 = nd2->next;
		}
		return (0);
	}
	for (i = 1; info->argument_list[i]; i++)
	{
		A = _strchr(info->argument_list[i], '=');
		if (A)
			set_alias(info, info->argument_list[i]);
		else
			print_alias(node_starts_with(info->command_aliases,
						info->argument_list[i], '='));
	}

	return (0);
}
