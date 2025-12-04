/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanzhao <yanzhao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:40:10 by yanzhao           #+#    #+#             */
/*   Updated: 2025/12/04 00:11:46 by yanzhao          ###   ########.fr       */
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

void	safe_print_die(t_philo *philo, char *message)
{
	long long	timestamp;

	timestamp = current_time_ms() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d %s\n", timestamp, philo->id, message);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
