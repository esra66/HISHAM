#include "sh.h"

/**
 * get_environ - copy of the environ
 * @info: Struct
 * Return: 0
 */
char **get_environ(info_t *info)
{
	if (!info->modified_environment || info->environment_changed)
	{
		info->modified_environment = conv_list_to_str(info->environment);
		info->environment_changed = 0;
	}

	return (info->modified_environment);
}

/**
 * _unsetenv - Remove environment variables
 * @info: Struct
 * @var: string env var.
 * Return: 1 or 0.
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node;
	char *x;
	size_t y;

	if (!info->environment || !var)
		return (0);

	for (node = info->environment, y = 0; node; node = node->next, y++)
	{
		x = starts_with(node->str, var);

		if (x && *x == '=')
		{
			info->environment_changed = delete_node_at_index(&(info->environment), y);
			node = info->environment;
			y = 0;
		}
	}

	return (info->environment_changed);
}


/**
 * _setenv - function that Initialize or modify new environ var.
 * @info: Struct
 * @var:  string environment variable.
 * @value: environment variable value of string environment variable.
 * Return: 0.
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *new_str = NULL;
	list_t *current_node;
	char *z;

	if (!var || !value)
		return (0);

	new_str = malloc(_strlen(var) + _strlen(value) + 2);
	if (!new_str)
		return (1);
	_strcpy(new_str, var);
	_strcat(new_str, "=");
	_strcat(new_str, value);
	current_node = info->environment;

	for (; current_node; current_node = current_node->next)
	{
		z = starts_with(current_node->str, var);
		if (z && *z == '=')
		{
			free(current_node->str);
			current_node->str = new_str;
			info->environment_changed = 1;
			return (0);
		}
	}

	add_node_end(&(info->environment), new_str, 0);
	free(new_str);
	info->environment_changed = 1;
	return (0);
}
