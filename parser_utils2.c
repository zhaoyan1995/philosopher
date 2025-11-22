#include "philo.h"

bool	is_llong_overflow(char *argv)
{
	int	i;

	if (ft_strlen(argv) < ft_strlen(LL_MAX_STR))
		return (false);
	if (ft_strlen(argv) > ft_strlen(LL_MAX_STR))
		return (true);
	i = 0;
	while (argv[i])
	{
		if (argv[i] > LL_MAX_STR[i])
			return (true);
		i++;
	} 
	return (false);
}

bool	safe_atoll(char *argv, long long *output)
{
	int	i;
	long long	result;

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
	if (is_llong_overflow(argv))
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
