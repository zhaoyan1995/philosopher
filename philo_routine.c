/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanzhao <yanzhao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:40:10 by yanzhao           #+#    #+#             */
/*   Updated: 2025/12/01 22:40:12 by yanzhao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_print(t_philo *philo, char *message)
{
	long long	timestamp;
	bool		is_end;

	timestamp = current_time_ms() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->end_mutex);
	is_end = philo->data->end_of_program;
	if (is_end == false)
		printf("%lld %d %s\n", timestamp, philo->id, message);
	pthread_mutex_unlock(&philo->data->end_mutex);
	pthread_mutex_unlock(&philo->data->print_mutex);	
}

void	smart_sleep(long long duration, t_philo *philo)
{
	long long	start;

	start = current_time_ms();
	while (current_time_ms() - start < duration)
	{
		if (mutex_is_end(philo->data))
			return ;
		usleep(500);
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

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!mutex_read_all_threads_ready(philo->data))
		usleep(100);
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		if (!eating(philo))
			break ;
		if (mutex_is_end(philo->data))
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
