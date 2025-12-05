/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_value_mutex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanzhao <yanzhao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 21:18:35 by yanzhao           #+#    #+#             */
/*   Updated: 2025/12/01 21:18:38 by yanzhao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//routine
bool	mutex_read_all_threads_ready(t_data *data)
{
	bool	all_threads_ready;

	pthread_mutex_lock(&data->ready_mutex);
	all_threads_ready = data->all_threads_ready;
	pthread_mutex_unlock(&data->ready_mutex);
	return (all_threads_ready);
}

//routine
bool	mutex_is_end(t_data *data)
{
	bool	end_of_program;

	pthread_mutex_lock(&data->end_mutex);
	end_of_program = data->end_of_program;
	pthread_mutex_unlock(&data->end_mutex);
	return (end_of_program);
}

//monitor
int	mutex_read_nb_of_eaten(t_philo *philo)
{
	int	nb_of_meal;

	pthread_mutex_lock(&philo->meal_lock);
	nb_of_meal = philo->nb_of_meal;
	pthread_mutex_unlock(&philo->meal_lock);
	return (nb_of_meal);
}

//monitor
long long	mutex_read_last_meal_time(t_philo *philo)
{
	long long	last_meal_time;

	pthread_mutex_lock(&philo->meal_lock);
	last_meal_time = philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_lock);
	return (last_meal_time);
}
