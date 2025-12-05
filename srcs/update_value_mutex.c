/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end_of_program.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanzhao <yanzhao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 21:18:35 by yanzhao           #+#    #+#             */
/*   Updated: 2025/12/01 21:18:38 by yanzhao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//create_thread
void	mutex_update_ready_mutex(t_data *data)
{
	pthread_mutex_lock(&data->ready_mutex);
	data->all_threads_ready = true;
	pthread_mutex_unlock(&data->ready_mutex);
}

//routine
void	mutex_update_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = current_time_ms();
	philo->nb_of_meal += 1;
	pthread_mutex_unlock(&philo->meal_lock);
}

//monitor
void	mutex_update_end_of_program(t_data *data)
{
	pthread_mutex_lock(&data->end_mutex);
	data->end_of_program = true;
	pthread_mutex_unlock(&data->end_mutex);
}
