#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

bool	is_int_overflow(char *argv)
{
	int	i;

	if (ft_strlen(argv) < ft_strlen(INT_MAX_STR))
		return (false);
	if (ft_strlen(argv) > ft_strlen(INT_MAX_STR))
		return (true);
	i = 0;
	while (argv[i])
	{
		if (argv[i] > INT_MAX_STR[i])
			return (true);
		i++;
	} 
	return (false);
}

bool	safe_atoi(char *argv, int *output)
{
	int	i;
	int	result;

	while (*argv == ' ')
		argv++;
	if (*argv == '-')
		return (false);
	if (*argv == '+')
		argv++;
	if (is_all_zero(argv))
	{
		*output = 0;
		return (true);
	}
	while (*argv == '0')
		argv++;
	if (*argv == '\0')
		return (false);
	if (is_int_overflow(argv))
		return (false);
	i = 0;
	result = 0;
	while (argv[i])
	{
		result = result  * 10 + (argv[i] - '0');
		i++;
	}
	*output = result;
	return (true);
}
