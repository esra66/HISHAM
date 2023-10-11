#include "sh.h"

/**
 * get_hisfile - gets the history file
 * @info: struct
 * Return: history file with allocated string
 */
char *get_hisfile(info_t *info)
{
	char *buffer, *home_dir;
	size_t buffer_size;

	do {
		home_dir = _getenv(info, "HOME=");

		if (!home_dir)
			break;

		buffer_size = _strlen(home_dir) + _strlen(H_FILE) + 2;
		buffer = malloc(sizeof(char) * buffer_size);

		if (!buffer)
			break;

		buffer[0] = 0;
		_strcpy(buffer, home_dir);
		_strcat(buffer, "/");
		_strcat(buffer, H_FILE);
		return (buffer);
	} while (0);

	return (NULL);
}

/**
 * wr_history -  create or append file.
 * @info: struct
 * Return: 1 or -1
 */
int wr_history(info_t *info)
{
	ssize_t file_descriptor;
	char *filename = get_hisfile(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	file_descriptor = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (file_descriptor == -1)
		return (-1);

	for (node = info->command_history; node; node = node->next)
	{
		_putsfd(node->str, file_descriptor);
		_putfd('\n', file_descriptor);
	}
	_putfd(BUF_CLEAR, file_descriptor);
	close(file_descriptor);
	return (1);
}


/**
 * re_history - reads history from file
 * @info: struct
 * Return: history count or 0
 */
int re_history(info_t *info)
{
	int i, last_index = 0, line_count = 0;
	ssize_t d, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filenam = get_hisfile(info);

	if (!filenam)
		return (0);

	d = open(filenam, O_RDONLY);
	free(filenam);
	if (d == -1)
		return (0);
	if (!fstat(d, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(d, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(d);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_his_t(info, buf + last_index, line_count++);
			last_index = i + 1;
		}
	if (last_index != i)
		build_his_t(info, buf + last_index, line_count++);
	free(buf);
	info->history_line_number = line_count;
	while (info->history_line_number-- >= H_MAX)
		delete_node_at_index(&(info->command_history), 0);
	renum_his(info);
	return (info->history_line_number);
}

/**
 * build_his_t - adds entry to history linked list
 * @info: Struct
 * @buffer: buffer
 * @line_count: history linecount
 * Return: 0
 */
int build_his_t(info_t *info, char *buffer, int line_count)
{
	list_t *nod = NULL;

	if (info->command_history)
		nod = info->command_history;
	add_node_end(&nod, buffer, line_count);

	if (!info->command_history)
		info->command_history = nod;
	return (0);
}

/**
 * renum_his - renumbers ofhistory after changes
 * @info: Struct
 * Return: history counter
 */
int renum_his(info_t *info)
{
	list_t *node = info->command_history;
	int j = 0;

	while (node)
	{
		node->num = j++;
		node = node->next;
	}
	return (info->history_line_number = j);
}
