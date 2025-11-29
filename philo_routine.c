#include "philo.h"

void	safe_print(t_philo *philo, char *message)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->data->print_mutex);
	timestamp = current_time_ms() - philo->data->start_time;
	if (!philo->data->end_of_program)
		printf("%lld %d %s\n", timestamp, philo->id, message);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	smart_sleep(long long duration, t_philo *philo)
{
	long long	start;

	start = current_time_ms();
	while (current_time_ms() - start < duration)
	{
		if (mutex_is_end(philo))
			return ;
		usleep(500);
	}
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_of_philo == 1)
		return (NULL);
	while (1)
	{
		if (mutex_is_end(philo))
			break ;
		if (take_forks(philo))
			break ;
		mutex_update_last_meal_time(philo);
		if (mutex_is_end(philo))
		{
			put_down_forks(philo);
			break ;
		}
		safe_print(philo, "is eating");
		smart_sleep(philo->data->time_to_eat, philo);
		put_down_forks(philo);

		if (mutex_is_end(philo))
			break ;
		safe_print(philo, "is sleeping");
		smart_sleep(philo->data->time_to_sleep, philo);

		if (mutex_is_end(philo))
			break ;
		safe_print(philo, "is thinking");
	}
	return (NULL);
}
