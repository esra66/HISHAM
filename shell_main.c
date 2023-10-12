#include "sh.h"

/**
 * main - entry point
 * @ac: arg count.
 * @av: arg vector.
 * Return:  0 or 1 or NULL.
 */
int main(int ac, char **av)
{
	info_t info[] = { INIT_INFO };

	(void)ac;

	pop_env_list(info);
	re_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
