/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanzhao <yanzhao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 19:06:01 by yanzhao           #+#    #+#             */
/*   Updated: 2025/11/29 23:24:47 by yanzhao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_fork_to_philo(t_data *data, int i)
{
	if (data->philo[i].id == data->nb_of_philo)
	{
		data->philo[i].left_fork = &data->fork[data->nb_of_philo - 1];
		data->philo[i].left_fork_id = data->nb_of_philo;
		data->philo[i].right_fork = &data->fork[0];
		data->philo[i].right_fork_id = 1;
	}
	else
	{
		data->philo[i].left_fork = &data->fork[i];
		data->philo[i].left_fork_id = data->philo[i].id;
		data->philo[i].right_fork = &data->fork[i + 1];
		data->philo[i].right_fork_id = data->philo[i].id + 1;
	}
}

void	init_single_philo(t_data *data)
{
	data->philo[0].id = 1;
	data->philo[0].left_fork = &data->fork[0];
	data->philo[0].left_fork_id = data->nb_of_philo;
	data->philo[0].right_fork = &data->fork[0];
	data->philo[0].right_fork_id = data->nb_of_philo;
	data->philo[0].nb_of_meal = 0;
	data->philo[0].data = data;
}

void	init_philo(t_data *data)
{
	int	i;

	if (data->nb_of_philo == 1)
		init_single_philo(data);
	else
	{
		i = 0;
		while (i < data->nb_of_philo)
		{
			data->philo[i].id = i + 1;
			assign_fork_to_philo(data, i);
			data->philo[i].nb_of_meal = 0;
			data->philo[i].data = data;
			i++;
		}
	}
}
