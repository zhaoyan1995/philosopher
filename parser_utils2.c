/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanzhao <yanzhao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:58:36 by yanzhao           #+#    #+#             */
/*   Updated: 2025/12/01 22:58:38 by yanzhao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

long long	fill_result_long_long(char *argv)
{
	long long	result;
	int			i;

	i = 0;
	result = 0;
	while (argv[i])
	{
		result = result * 10 + (argv[i] - '0');
		i++;
	}
	return (result);
}

bool	safe_atoll(char *argv, long long *output)
{
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
	*output = fill_result_long_long(argv);
	return (true);
}
