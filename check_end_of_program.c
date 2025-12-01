#include "philo.h"

//create_thread
void	mutex_update_ready_mutex(t_data *data)
{
	pthread_mutex_lock(&data->ready_mutex);
	data->all_threads_ready = true;
	pthread_mutex_unlock(&data->ready_mutex);
}

//routine
bool	mutex_read_all_threads_ready(t_data *data)
{
	bool	all_threads_ready;

	pthread_mutex_lock(&data->ready_mutex);
	all_threads_ready = data->all_threads_ready;
	pthread_mutex_unlock(&data->ready_mutex);
	return (all_threads_ready);
}

//routine
bool	mutex_is_end(t_data *data)
{
	bool	end_of_program;

	pthread_mutex_lock(&data->end_mutex);
	end_of_program = data->end_of_program;
	pthread_mutex_unlock(&data->end_mutex);
	return (end_of_program);
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
int	mutex_read_nb_of_eaten(t_philo *philo)
{
	int	nb_of_meal;

	pthread_mutex_lock(&philo->meal_lock);
	nb_of_meal = philo->nb_of_meal;
	pthread_mutex_unlock(&philo->meal_lock);
	return (nb_of_meal);
}

//monitor
void	mutex_update_end_of_program(t_data *data)
{
	pthread_mutex_lock(&data->end_mutex);
	data->end_of_program = true;
	pthread_mutex_unlock(&data->end_mutex);
}

//monitor
long long mutex_read_last_meal_time(t_philo *philo)
{
	long long	last_meal_time;

	pthread_mutex_lock(&philo->meal_lock);
 	last_meal_time = philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_lock);
	return (last_meal_time);
}
