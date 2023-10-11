#include "sh.h"

/**
 * fd_cmd - find command in PATH.
 * @info: parameter.
 * Return: void.
 */
void fd_cmd(info_t *info)
{
	char *path1 = NULL;
	int i, j;

	info->command_path = info->argument_list[0];

	if (info->count_line == 1)
	{
		info->error_count++;
		info->count_line = 0;
	}

	for (i = 0, j = 0; info->arguments[i]; i++)

		if (!is_delimiter(info->arguments[i], " \t\n"))
			j++;

	if (!j)
		return;

	path1 = fd_path(info, _getenv(info, "PATH="), info->argument_list[0]);

	if (path1)
	{
		info->command_path = path1;
		cmd_fork(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argument_list[0][0] == '/') &&
				is_command(info, info->argument_list[0]))
			cmd_fork(info);

		else if (*(info->arguments) != '\n')
		{
			info->return_status = 127;
			print_err(info, "not found\n");
		}
	}
}

/**
 * cmd_fork - forks command.
 * @info: parameter.
 * Return: void
 */
void cmd_fork(info_t *info)
{
	pid_t child;

	child = fork();

	if (child == -1)
	{

		perror("Error:");
		return;
	}
	if (child == 0)
	{
		if (execve(info->command_path, info->argument_list, get_environ(info)) == -1)
		{
			info_free(info, 1);

			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->return_status));

		if (WIFEXITED(info->return_status))
		{
			info->return_status = WEXITSTATUS(info->return_status);

			if (info->return_status == 126)
				print_err(info, "Permission access denied\n");
		}
	}
}

/**
 * is_command - determine file if executable.
 * @info: struct.
 * @path1: path.
 * Return: 1 or 0.
 */
int is_command(info_t *info, char *path1)
{
	struct stat thstatus;

	(void)info;
	if (!path1 || stat(path1, &thstatus))
		return (0);

	if (thstatus.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
