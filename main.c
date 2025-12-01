#include "philo.h"

void	ft_put_str(char *str, int fd)
{
	int	len_str;

	len_str = ft_strlen(str);
	if (len_str == 0)
		return ;
	write(fd, str, len_str);
}

//debug
void	print_data(t_philo *philo)
{
	printf("philo id = %d\n", philo->id);
	printf("philo's left fork %d\n", philo->left_fork_id);
	printf("philo's right fork %d\n", philo->right_fork_id);
	printf("last meal time = %lld\n", philo->last_meal_time);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 5 && argc != 6)
	{
		ft_put_str("Usage: ./philo num_philo time_to_die time_to_eat time_to_sleep [num_must_eat]\n", 2);
		return (1);
	}
	if (!check_argv(argc, argv))
		return (ft_put_str("invalid arguments!\n", 2), 1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	memset(data, 0, sizeof(t_data));
	if (!init_data(argc, argv, data))
		return (ft_put_str("invalid arguments!\n", 2), free(data), 1);
	if (!alloc_data(data))
		return (free(data), 1);
	init_all_mutex(data);
	init_philo(data);
	if (!create_all_thread(data))
		return (destroy_mutex(data), destroy_data(data), 1);
	join_all_thread(data);
	destroy_mutex(data);
	destroy_data(data);
	return (0);
}
