#include "philo.h"

bool	even_philo_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (mutex_is_end(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (true);
	}
	safe_print(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	if (mutex_is_end(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (true);
	}
	safe_print(philo, "has taken a fork");
	return (false);
}

bool	odd_philo_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (mutex_is_end(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (true);
	}
	safe_print(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	if (mutex_is_end(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (true);
	}
	safe_print(philo, "has taken a fork");
	return (false);
}

bool	take_forks(t_philo *philo)
{
	if (mutex_is_end(philo))
		return (true);
	if (philo->id % 2 == 0)
	{
		if (even_philo_take_forks(philo))
			return (true);
	}
	else if (philo->id % 2 == 1)
	{
		if (odd_philo_take_forks(philo))
			return (true);
	}		
	return (false);
}

void	put_down_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else if (philo->id % 2 == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}
