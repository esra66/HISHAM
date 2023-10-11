#include "sh.h"

/**
 *_memset - fills memory with a constant byte
 *@A: pointer.
 *@B: byte to be filled.
 *@C: number of bytes.
 *Return: pointer.
 */
char *_memset(char *A, char B, unsigned int C)
{
	unsigned int i = 0;

	while (i < C)
	{
		A[i] = B;
		i++;
	}
	return (A);
}

/**
 * _realloc - it reallocates a block of memory.
 * @ptr1: pointer .
 * @o_size: prev block size.
 * @n_size: new block size.
 * Return: pointer.
 */
void *_realloc(void *ptr1, unsigned int o_size, unsigned int n_size)
{
	char *pp;

	if (!ptr1)
		return (malloc(n_size));
	if (!n_size)
		return (free(ptr1), NULL);
	if (n_size == o_size)
		return (ptr1);

	pp = malloc(n_size);
	if (!pp)
		return (NULL);

	o_size = o_size < n_size ? o_size : n_size;
	while (o_size--)
		pp[o_size] = ((char *)ptr1)[o_size];
	free(ptr1);
	return (pp);
}
