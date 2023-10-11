#include "sh.h"

/**
 * ischain - test is a chain delimeter.
 * @info: struct.
 * @buff: buffer.
 * @ptr: address.
 * Return: 1 or 0.
 */
int ischain(info_t *info, char *buff, size_t *ptr)
{
	size_t A = *ptr;

	if (buff[A] == '|' && buff[A + 1] == '|')
	{
		buff[A] = 0;
		A++;
		info->command_type = C_OR;
	}
	else if (buff[A] == '&' && buff[A + 1] == '&')
	{
		buff[A] = 0;
		A++;
		info->command_type = C_AND;
	}
	else if (buff[A] == ';')
	{
		buff[A] = 0;
		info->command_type = C_CHAIN;
	}
	else
		return (0);
	*ptr = A;
	return (1);
}

/**
 * ck_chain - checks chain.
 * @info:  struct.
 * @buff: buffer.
 * @ptr: address.
 * @k: position start.
 * @length: length.
 * Return: Void
 */
void ck_chain(info_t *info, char *buff, size_t *ptr, size_t k, size_t length)
{
	size_t l = *ptr;

	if (info->command_type == C_AND)
	{
		if (info->return_status)
		{
			buff[k] = 0;
			l = length;
		}
	}
	if (info->command_type == C_OR)
	{
		if (!info->return_status)
		{
			buff[k] = 0;
			l = length;
		}
	}

	*ptr = l;
}


