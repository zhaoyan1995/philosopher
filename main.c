#include "philo.h"

void	ft_put_str(char *str, int fd)
{
	int	len_str;

	len_str = ft_strlen(str);
	if (len_str == 0)
		return ;
	write(fd, str, len_str);
}

void	destroy_data(t_data *data)
{
	free(data->philo);
	free(data->philo_th);
	free(data->fork);
}

void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		pthread_mutex_destroy(&data->fork[i]);
		pthread_mutex_destroy(&data->philo[i].meal_lock);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->end_mutex);
}

void	print_data(t_philo *philo)
{
	printf("philo id = %d\n", philo->id);
	printf("philo's left fork %d\n", philo->left_fork_id);
	printf("philo's right fork %d\n", philo->right_fork_id);
	printf("last meal time = %lld\n", philo->last_meal_time);
}

void	safe_print(t_philo *philo, char *message)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->data->print_mutex);
	timestamp = current_time_ms() - philo->data->start_time;
	if (!philo->data->end_of_program)
		printf("%lld %d %s\n", timestamp, philo->id, message);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	safe_print_die(t_philo *philo, char *message)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->data->print_mutex);
	timestamp = current_time_ms() - philo->data->start_time;
	if (philo->data->end_of_program)
		printf("%lld %d %s\n", timestamp, philo->id, message);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

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

bool	all_ate_enough(t_data *data)
{
	int	i;
	int	eaten_times;

	if (data->nb_of_eat == -1)
		return (false);
	i = 0;
	while (i < data->nb_of_philo)
	{
		eaten_times = mutex_read_nb_of_eaten(&data->philo[i]);
		if (eaten_times != data->nb_of_eat)
			return (false) ;
		i++;
	}
	mutex_update_end_of_program(data);
	return (true);
}

void	*monitor(void *arg)
{
	t_data	*data;
	long long	last_meal_time;
	int	i;

	data = (t_data *)arg;
	if (data->nb_of_philo == 1)
	{
		i = 0;
		usleep(data->time_to_die * 1000);
		pthread_mutex_lock(&data->end_mutex);
		data->end_of_program = true;
		pthread_mutex_unlock(&data->end_mutex);
		safe_print_die(&data->philo[i], "died");
		return (NULL);
	}
	while (!data->end_of_program)
	{
		i = 0;
		while (i < data->nb_of_philo)
		{
			last_meal_time = mutex_read_last_meal_time(&data->philo[i]);
			if (current_time_ms() - last_meal_time > data->time_to_die)
			{
				mutex_update_end_of_program(data);
				safe_print_die(&data->philo[i], "died");
				return (NULL);
			}
			i++;
		}
		if (all_ate_enough(data))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}

int	create_all_thread(t_data *data)
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

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
	{
		ft_put_str("Usage: ./philo num_philo time_to_die time_to_eat time_to_sleep [num_must_eat]\n", 2);
		return (1);
	}
	if (!check_argv(argc, argv))
		return (printf("invalid arguments!\n"), 1);
	memset(&data, 0, sizeof(t_data));
	if (!init_data(argc, argv, &data))
		return (printf("invalid arguments here!\n"), 1);
	if (!alloc_data(&data))
		return (1);
	init_all_mutex(&data);
	init_philo(&data);
	if (!create_all_thread(&data))
		return (destroy_mutex(&data), destroy_data(&data), 1);
	join_all_thread(&data);
	destroy_mutex(&data);
	destroy_data(&data);
	return (0);
}
