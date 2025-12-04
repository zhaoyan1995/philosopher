/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanzhao <yanzhao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:18:04 by yanzhao           #+#    #+#             */
/*   Updated: 2025/12/04 00:13:17 by yanzhao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	all_ate_enough(t_data *data)
{
	int	i;
	int	eaten_times;

	if (data->nb_of_eat == -1)
		return (false);
	i = 0;
	while (i < data->nb_of_philo)
	{
		eaten_times = mutex_read_nb_of_eaten(&data->philo[i]);
		if (eaten_times != data->nb_of_eat)
			return (false);
		i++;
	}
	mutex_update_end_of_program(data);
	return (true);
}

void	*monitor(void *arg)
{
	t_data		*data;
	long long	last_meal_time;
	int			i;

	data = (t_data *)arg;
	while (!mutex_read_all_threads_ready(data) && !data->end_of_program)
		usleep(100);
	while (!mutex_is_end(data))
	{
		i = -1;
		while (i++, i < data->nb_of_philo && !mutex_is_end(data))
		{
			last_meal_time = mutex_read_last_meal_time(&data->philo[i]);
			if (current_time_ms() - last_meal_time > data->time_to_die)
			{
				mutex_update_end_of_program(data);
				safe_print_die(&data->philo[i], "died");
				return (NULL);
			}
		}
		if (all_ate_enough(data))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}
