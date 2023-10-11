#include "sh.h"

/**
 * _atoi - converts string to integer
 * @str: string
 * Return: 0 or converted number
 */

int _atoi(char *str)
{
	int index, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (index = 0; str[index] != '\0' && flag != 2; index++)
	{
		if (str[index] == '-')
			sign *= -1;

		if (str[index] >= '0' && str[index] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[index] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

/**
 * _atoierr - converts string to int.
 * @st: converted string
 * Return: 0 or -1.
 */
int _atoierr(char *st)
{
	int i = 0;
	unsigned long int res = 0;

	if (*st == '+')
		st++;

	while (st[i] != '\0')
	{
		if (st[i] >= '0' && st[i] <= '9')
		{
			res *= 10;
			res += (st[i] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
		i++;
	}
	return ((int)res);
}
