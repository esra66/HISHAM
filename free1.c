#include "sh.h"

/**
 * info_clear - initializes info_t struct
 * @info: struct
 * Return: void.
 */
void info_clear(info_t *info)
{
	info->arguments = NULL;
	info->argument_list = NULL;
	info->command_path = NULL;
	info->argument_count = 0;
}

/**
 * info_set - initializes info_t struct
 * @info: struct
 * @av: the vector of argument
 * Return: void.
 */
void info_set(info_t *info, char **av)
{
	int i;
	char **arg_list;

	info->program_name = av[0];

	if (info->arguments)
	{
		arg_list = strtow(info->arguments, " \t");
		if (!arg_list)
		{
			arg_list = malloc(sizeof(char *) * 2);
			if (arg_list)
			{
				arg_list[0] = _strdup(info->arguments);
				arg_list[1] = NULL;
			}
		}

		for (i = 0; arg_list && arg_list[i]; i++)
			;

		info->argument_count = i;
		info->argument_list = arg_list;

		rep_alias(info);
		rep_vars(info);
	}
}

/**
 * info_free - frees info_t struct
 * @info: struct
 * @free_all: freeing all if true
 * Return: void
 */
void info_free(info_t *info, int free_all)
{
	free_str(info->argument_list);
	info->argument_list = NULL;
	info->command_path = NULL;
	if (free_all)
	{
		if (!info->command_buffer)
			free(info->arguments);
		if (info->environment)
			free_list(&(info->environment));
		if (info->command_history)
			free_list(&(info->command_history));
		if (info->command_aliases)
			free_list(&(info->command_aliases));
		free_str(info->modified_environment);
		info->modified_environment = NULL;
		free_ptr((void **)info->command_buffer);
		if (info->input_fd > 2)
			close(info->input_fd);
		_putchar(BUF_CLEAR);
	}
}


