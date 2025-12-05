/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanzhao <yanzhao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:40:10 by yanzhao           #+#    #+#             */
/*   Updated: 2025/12/05 01:54:13 by yanzhao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*void	smart_sleep(long long duration, t_philo *philo)
{
	long long	start;
	long long	escape;
	long long	remain;

	if (duration == 0)
		return ;
	start = current_time_ms();
	while (current_time_ms() - start < duration)
	{
		if (mutex_is_end(philo->data))
			return ;
		escape = current_time_ms() - start ;
		remain = duration - escape;
		if (remain > 1000)
			usleep(remain / 2);
		else
			while (current_time_ms() - start < duration)
				;
	}
}*/

void	smart_sleep(long long duration, t_philo *philo)
{
	long long	start;
	long long	now;

	start = current_time_ms();
	while (1)
	{
		if (mutex_is_end(philo->data))
			return ;
		now = current_time_ms();
		if (now - start >= duration)
			break;
		usleep(200);
	}
}

void	*solo_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!mutex_read_all_threads_ready(philo->data))
		usleep(100);
	pthread_mutex_lock(philo->right_fork);
	if (mutex_is_end(philo->data))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (NULL);
	}
	safe_print(philo, "has taken a fork");
	while (1)
	{
		if (mutex_is_end(philo->data))
		{
			pthread_mutex_unlock(philo->right_fork);
			break ;
		}
		usleep(500);
	}
	return (NULL);
}

int	eating(t_philo *philo)
{
	if (mutex_read_nb_of_eaten(philo) == philo->data->nb_of_eat)
		return (0);
	if (mutex_is_end(philo->data))
		return (0);
	if (take_forks(philo))
		return (0);
	mutex_update_last_meal_time(philo);
	if (mutex_is_end(philo->data))
	{
		put_down_forks(philo);
		return (0);
	}
	safe_print(philo, "is eating");
	smart_sleep(philo->data->time_to_eat, philo);
	put_down_forks(philo);
	return (1);
}

void	prepare_routine(t_philo *philo)
{
	while (!mutex_read_all_threads_ready(philo->data))
		usleep(100);
	if (philo->data->nb_of_philo % 2 == 0)
	{
		if (philo->id % 2 == 0)
			usleep(300);
	}
	else
	{
		if (philo->id % 2 == 0)
			smart_sleep(philo->data->time_to_think, philo);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	prepare_routine(philo);
	philo->last_meal_time = mutex_read_last_meal_time(philo);
	while (1)
	{
		if (!eating(philo))
			break ;
		safe_print(philo, "is sleeping");
		smart_sleep(philo->data->time_to_sleep, philo);
		if (mutex_is_end(philo->data))
			break ;
		safe_print(philo, "is thinking");
		smart_sleep(philo->data->time_to_think, philo);
	}
	return (NULL);
}
