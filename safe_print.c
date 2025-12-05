/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanzhao <yanzhao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:40:10 by yanzhao           #+#    #+#             */
/*   Updated: 2025/12/05 01:16:34 by yanzhao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_print(t_philo *philo, char *message)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->data->print_mutex);
	timestamp = current_time_ms() - philo->data->start_time;
	if (mutex_is_end(philo->data) == false)
		printf("%lld %d %s\n", timestamp, philo->id, message);
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
