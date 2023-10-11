#include "sh.h"

/**
 * input_buf - function to buffers chained commands
 * @info: struct
 * @buff: address of buffer
 * @length: len var
 * Return: bytes
 */
ssize_t input_buf(info_t *info, char **buff, size_t *length)
{
	ssize_t k = 0;
	size_t length_p = 0;

	if (!*length)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sign_handle);
#if U_GETLINE
		k = getline(buff, &length_p, stdin);
#else
		k = _getline(info, buff, &length_p);
#endif
		if (k > 0)
		{
			if ((*buff)[k - 1] == '\n')
			{
				(*buff)[k - 1] = '\0';
				k--;
			}
			info->count_line = 1;
			rm_comments(*buff);
			build_his_t(info, *buff, info->history_line_number++);
			*length = k;
			info->command_buffer = buff;
		}
	}
	return (k);
}

/**
 * get_input - gets a line without the newline
 * @info: struct 
 * Return: number of bytes 
 */
ssize_t get_input(info_t *info)
{
	static char *command_buf; 
	static size_t buf_pos, chain_pos, buf_len;
	ssize_t bytes_read = 0;
	char **arg_ptr = &(info->arguments), *cmd_ptr;

	_putchar(BUF_CLEAR);
	bytes_read = input_buf(info, &command_buf, &buf_len);

	if (bytes_read == -1) 
		return (-1);

	if (buf_len) 
	{
		chain_pos = buf_pos; 
		cmd_ptr = command_buf + buf_pos; 
		ck_chain(info, command_buf, &chain_pos, buf_pos, buf_len);
		while (chain_pos < buf_len)
		{
			if (ischain(info, command_buf, &chain_pos))
				break;
			chain_pos++;
		}

		buf_pos = chain_pos + 1; 
		if (buf_pos >= buf_len) 
		{
			buf_pos = buf_len = 0; 
			info->command_type = C_NORM;
		}

		*arg_ptr = cmd_ptr; 
		return (_strlen(cmd_ptr)); 
	}

	*arg_ptr = command_buf;
	return (bytes_read);
}

/**
 * read_buf - reads a buffer
 * @info: struct containing argumrnts
 * @buff: buffer
 * @x: size
 * Return: z
 */
ssize_t read_buf(info_t *info, char *buff, size_t *x)
{
	ssize_t z = 0;

	if (*x)
		return (0);
	z = read(info->input_fd, buff, R_BUF);

	if (z >= 0)
		*x = z;
	return (z);
}

/**
 * _getline - function thst gets the next line of input
 * @info: struct
 * @ptr: pointer to buffer address
 * @length: size 
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buffer[R_BUF];
	static size_t position, buffer_length;
	size_t k;
	ssize_t read_result = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (position == buffer_length)
		position = buffer_length = 0;

	read_result = read_buf(info, buffer, &buffer_length);
	if (read_result == -1 || (read_result == 0 && buffer_length == 0))
		return (-1);

	c = _strchr(buffer + position, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : buffer_length;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) 
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buffer + position, k - position);
	else
		_strncpy(new_p, buffer + position, k - position + 1);

	s += k - position;
	position = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

