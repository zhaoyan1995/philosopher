/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanzhao <yanzhao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 19:15:20 by yanzhao           #+#    #+#             */
/*   Updated: 2025/12/05 01:18:37 by yanzhao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_constant_data(int argc, char **argv, t_data *data)
{
	if (!safe_atoi(argv[1], &data->nb_of_philo))
		return (0);
	if (!safe_atoll(argv[2], &data->time_to_die))
		return (0);
	if (!safe_atoll(argv[3], &data->time_to_eat))
		return (0);
	if (!safe_atoll(argv[4], &data->time_to_sleep))
		return (0);
	if (argc == 6)
	{
		if (!safe_atoi(argv[5], &data->nb_of_eat))
			return (0);
	}
	else
		data->nb_of_eat = -1;
	return (1);
}

int	init_data(int argc, char **argv, t_data *data)
{
	if (!init_constant_data(argc, argv, data))
		return (0);
	if (data->nb_of_philo <= 0)
		return (0);
	if (data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0 || data->nb_of_eat == 0)
		return (0);
	if (data->nb_of_philo % 2 != 0)
		data->time_to_think = 2 * data->time_to_eat - data->time_to_sleep;
	else
		data->time_to_think = 0;
	if (data->time_to_think < 0)
		data->time_to_think = 0;
	else
		data->time_to_think *= 0.42;
	data->end_of_program = false;
	data->all_threads_ready = false;
	return (1);
}

int	alloc_data(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->nb_of_philo);
	if (!data->philo)
		return (0);
	data->philo_th = malloc(sizeof(pthread_t) * data->nb_of_philo);
	if (!data->philo_th)
		return (free(data->philo), 0);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_of_philo);
	if (!data->fork)
		return (free(data->philo), free(data->philo_th), 0);
	return (1);
}
