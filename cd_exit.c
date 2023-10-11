#include "sh.h"

/**
 * _myexit - function that used to exit
 * @info: Structure  Used to maintain constant function prototype.
 *  Return: exits with exit status
 */
int _myexit(info_t *info)
{
	int check_exit;

	if (info->argument_list[1])
	{
		check_exit = _atoierr(info->argument_list[1]);
		if (check_exit == -1)
		{
			info->return_status = 2;
			print_err(info, "Illegal number: ");
			_eputs(info->argument_list[1]);
			_eputchar('\n');
			return (1);
		}
		info->exit_code = _atoierr(info->argument_list[1]);
		return (-2);
	}
	info->exit_code = -1;
	return (-2);
}

/**
 * _mycd - function that changes current directory
 * @info: Structure used to maintain constant function prototype.
 *  Return: 0
 */
int _mycd(info_t *info)
{
	char *x, *dir, buff[1024];
	int cd_ret;

	x = getcwd(buff, 1024);
	if (!x)
		_puts("TODO: >>getcwd failure msg here<<\n");
	if (!info->argument_list[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			cd_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			cd_ret = chdir(dir);
	}
	else if (_strcmp(info->argument_list[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(x);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		cd_ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		cd_ret = chdir(info->argument_list[1]);

	if (cd_ret == -1)
	{
		print_err(info, "can't cd to ");
		_eputs(info->argument_list[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buff, 1024));
	}
	return (0);
}
