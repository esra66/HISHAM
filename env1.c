#include "sh.h"

/**
 * _myenv - prints the current environment.
 * @info: Struct.
 * Return: 0.
 */
int _myenv(info_t *info)
{
	print_list_str(info->environment);
	return (0);
}

/**
 * _getenv - gets environ variable.
 * @info: Struct.
 * @var_nam: var name.
 * Return: value.
 */
char *_getenv(info_t *info, const char *var_nam)
{
	list_t *nd1 = info->environment;
	char *A;

	for (; nd1 != NULL; nd1 = nd1->next)
	{
		A = starts_with(nd1->str, var_nam);
		if (A && *A)
		{
			return (A);
		}
	}

	return (NULL);
}

/**
 * _mysetenv - Initialize new environment.
 * @info: Struct.
 *  Return: 0.
 */
int _mysetenv(info_t *info)
{
	if (info->argument_count != 3)
	{
		_eputs("WRONG ARGUMENTS\n");
		return (1);
	}
	if (_setenv(info, info->argument_list[1], info->argument_list[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Removes an env variable.
 * @info: Struct.
 *  Return: 0.
 */
int _myunsetenv(info_t *info)
{
	int i = 1;

	if (info->argument_count == 1)
	{
		_eputs("FEW ARGUMENTS\n");
		return (1);
	}
	while (i <= info->argument_count)
	{
		_unsetenv(info, info->argument_list[i]);
		i++;
	}

	return (0);
}

/**
 * pop_env_list - populates environmnt linked list.
 * @info: Struct.
 * Return: 0.
 */
int pop_env_list(info_t *info)
{
	list_t *nd = NULL;
	size_t i = 0;

	while (environ[i] != NULL)
	{
		add_node_end(&nd, environ[i], 0);
		i++;
	}
	info->environment = nd;
	return (0);
}
