#include "philo.h"

int	init_data(int argc, char **argv, t_data *data)
{
	if (!safe_atoi(argv[1], &data->nb_of_philo))
		return (0);
	if (!safe_atoll(argv[2], &data->time_to_die))
		return (0);
	if (!safe_atoll(argv[3], &data->time_to_eat))
		return (0);
	if (!safe_atoll(argv[4], &data->time_to_sleep))
		return (0);
	if (argc == 6)	
	{
		if (!safe_atoi(argv[5], &data->nb_of_eat))
			return (0);
	}
	else	
		data->nb_of_eat = -1;
	if (data->nb_of_philo <= 0)
		return (0);
	if (data->time_to_die <= 0 || data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		return (0);
	data->end_of_program = false;
	return (1);
}

int	alloc_data(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->nb_of_philo);
	if (!data->philo)
		return (0);
	data->philo_th = malloc(sizeof(pthread_t) * data->nb_of_philo);
	if (!data->philo_th)
		return (free(data->philo), 0);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_of_philo);
	if (!data->fork)
		return (free(data->philo), free(data->philo_th), 0);
	return (1);
}

void	init_all_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->monitor_mutex, NULL);
}

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		data->philo[i].id = i;
		if (i == data->nb_of_philo - 1)
		{
			data->philo[i].left_fork = &data->fork[data->nb_of_philo - 1];
			data->philo[i].left_fork_id = data->nb_of_philo - 1;
			data->philo[i].right_fork = &data->fork[0];
			data->philo[i].right_fork_id = 0;
		}
		else
		{
			data->philo[i].left_fork = &data->fork[i];
			data->philo[i].left_fork_id = i;
			data->philo[i].right_fork = &data->fork[i + 1];
			data->philo[i].right_fork_id = i + 1;
		}
		data->philo[i].last_meal_time = current_time_ms();
		data->philo[i].data = data;
		i++;
	}
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
		i++;
	}
	pthread_mutex_destroy(&data->monitor_mutex);
}

void	print_data(t_philo *philo)
{
	printf("philo id = %d\n", philo->id);
	printf("philo's left fork %d\n", philo->left_fork_id);
	printf("philo's right fork %d\n", philo->right_fork_id);
	printf("last meal time = %lld\n", philo->last_meal_time);
}

void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	print_data(philo);
	return (NULL);
}

void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	if (data->end_of_program == false)	
		printf("end of the program is false\n");
	else
		printf("end of the program is true\n");
	return (NULL);
}

int	create_all_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		if (pthread_create(&data->philo_th[i], NULL, &routine, &data->philo[i]) != 0)
			return (0);
		i++;
	}
	if (pthread_create(&data->monitor_th, NULL, &monitor, &data) != 0)
		return (0);
	return (1);
}

int	join_all_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		if (pthread_join(data->philo_th[i], NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_join(data->monitor_th, NULL) != 0)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo num_philo time_to_die time_to_eat time_to_sleep [num_must_eat]\n");		
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
	if (!join_all_thread(&data))
		return (destroy_mutex(&data), destroy_data(&data), 1);
	destroy_mutex(&data);
	destroy_data(&data);
	return (0);
}
