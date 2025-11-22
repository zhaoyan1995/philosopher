#include "philo.h"

bool    is_all_zero(char *argv)
{
	int     i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] != '0')
			return (false);
		i++;
	}
	return (true);
}

int	is_digit_argv(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] == ' ' || argv[i] == '\t')
		i++;
	if (argv[i] == '+')
		i++;
	if (!argv[i])
		return (0);
	while (argv[i])
	{
		if (argv[i] < '0' || argv[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_argv(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_digit_argv(argv[i]))
			return (0);
		i++;
	}
	return (1);
}
