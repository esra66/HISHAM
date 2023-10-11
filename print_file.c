#include"sh.h"


/**
 * print_list_str - function that prints only the str element
 * @x: pointer to first node
 * Return: size of list
 */
size_t print_list_str(const list_t *x)
{
	size_t count = 0;

	while (x != NULL)
	{
		if (x->str != NULL)
		{
			_puts(x->str);
			_puts("\n");
		}
		else
		{
			_puts("(nil)");
			_puts("\n");
		}
		x = x->next;
		count++;
	}
	return (count);
}

/**
 * print_list - prints linked list elements.
 * @header: header.
 * Return: size.
 */
size_t print_list(const list_t *header)
{
	size_t len = 0;

	for (; header; header = header->next, len++)
	{
		_puts(conv_num(header->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(header->str ? header->str : "(nil)");
		_puts("\n");
	}
	return (len);
}

