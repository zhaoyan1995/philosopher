/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo_thread.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanzhao <yanzhao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 19:48:13 by yanzhao           #+#    #+#             */
/*   Updated: 2025/11/29 19:48:41 by yanzhao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philo_thread(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->nb_of_philo)
	{
		if (pthread_create(&data->philo_th[i], NULL, &routine, &data->philo[i]) != 0)
		{
			j = 0;
			while (j < i)
			{
				pthread_join(data->philo_th[j], NULL);
				j++;
			}
			return (0);
		}
		i++;
	}
	return (1);
}

int	create_all_thread(t_data *data)
{
	int	j;

	if (!create_philo_thread(data))
		return (0);
	if (pthread_create(&data->monitor_th, NULL, &monitor, data) != 0)
	{
		j = 0;
		while (j < data->nb_of_philo)
		{
			pthread_join(data->philo_th[j], NULL);
			j++;
		}
		return (0);
	}
	return (1);
}

int	join_all_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		pthread_join(data->philo_th[i], NULL);
		i++;
	}
	pthread_join(data->monitor_th, NULL);
	return (1);
}
