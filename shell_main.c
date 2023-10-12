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
	int f_desc = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (f_desc)
			: "r" (f_desc));

	if (ac == 2)
	{
		f_desc = open(av[1], O_RDONLY);
		if (f_desc == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can not open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_CLEAR);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->input_fd = f_desc;
	}
	pop_env_list(info);
	re_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
