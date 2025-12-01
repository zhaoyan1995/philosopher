#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>
#include <string.h>

#define INT_MAX_STR "2147483647"
#define LL_MAX_STR "9223372036854775807"

typedef	struct	s_data	t_data;
typedef	struct	s_philo	t_philo;

typedef	struct	s_data
{
	int	nb_of_philo;
	int	nb_of_eat;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;
	long long	time_to_think;
	long long	start_time;
	bool	all_threads_ready;
	bool	end_of_program;
	t_philo *philo;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	ready_mutex;
	pthread_mutex_t	end_mutex;
	pthread_mutex_t	*fork;
	pthread_t	*philo_th;
	pthread_t	monitor_th;
}	t_data;

typedef	struct	s_philo
{
	int	id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_lock;
	int	nb_of_meal;
	int	left_fork_id;
	int	right_fork_id;
	long long 	last_meal_time;
	t_data	*data;
}	t_philo;

//parser.c
int	is_digit_argv(char *argv);
int	check_argv(int argc, char **argv);
bool	is_all_zero(char *argv);

//parser_utils.c
int	ft_strlen(char *str);
bool	is_int_overflow(char *argv);
bool	safe_atoi(char *argv, int *output);

//parser_utils2.c
bool	safe_atoll(char *argv, long long *output);
bool	is_llong_overflow(char *argv);

//init_data.c
int		init_data(int argc, char **argv, t_data *data);
int		alloc_data(t_data *data);

//init_mutex.c
void	init_all_mutex(t_data *data);

//init_philo_struct.c
void	assign_fork_to_philo(t_data *data, int i);
void	init_single_philo(t_data *data);
void	init_philo(t_data *data);

//create_threads.c
int		create_philo_thread(t_data *data);
int		create_all_thread(t_data *data);
int		join_all_thread(t_data *data);

//philo_routine.c
void	*solo_philo_routine(void *arg);
void	*routine(void *arg);
void	smart_sleep(long long duration, t_philo *philo);
void    safe_print(t_philo *philo, char *message);

//philo_eating.c
bool	even_philo_take_forks(t_philo *philo);
bool	odd_philo_take_forks(t_philo *philo);
bool	take_forks(t_philo *philo);
void	put_down_forks(t_philo *philo);

//monitor.c
void	*monitor(void *arg);

//get_time.c
long long	current_time_ms(void);

//check_end_of_program.c
bool	mutex_is_end(t_data *data);
void	mutex_update_last_meal_time(t_philo *philo);
void	mutex_update_end_of_program(t_data *data);
long long	mutex_read_last_meal_time(t_philo *philo);
int	mutex_read_nb_of_eaten(t_philo *philo);
void	mutex_update_ready_mutex(t_data *data);
bool	mutex_read_all_threads_ready(t_data *data);

//clean_up_data.c
void	destroy_data(t_data *data);
void	destroy_mutex(t_data *data);

#endif
