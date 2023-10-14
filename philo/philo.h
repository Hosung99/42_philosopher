/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:26:28 by seoson            #+#    #+#             */
/*   Updated: 2023/10/12 17:59:19 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define SUCCESS 1
# define ERROR -1
# define DIE -2
# define ALIVE 2

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct s_argv
{
	int	philo_num;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	must_eat;
}	t_argv;

typedef struct s_data
{
	long			start_time;
	t_argv			argv_info;
	pthread_mutex_t	fin_flag;
	int				fin_count;
	pthread_mutex_t	fork_print;
	int				print_status;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*last_eat_time;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				l_fork;
	int				r_fork;
	int				eat_count;
	long			last_eat_time;
	pthread_t		thread;
	t_data			*data;
}	t_philo;

int		check_argument(int argc, char *argv[], t_argv *argv_info);
int		ft_atoi(const char *nptr);
int		init_data(t_data *data, t_philo *philo);
int		init_philo(t_data *data, t_philo *philo);
int		init_mutex(t_data *data);
int		start_dining(t_data *data, t_philo *philo);
int		malloc_data(t_data *data, t_philo *philo);
long	get_current_time(t_data *data);
void	*dining(t_philo *philo);
int		pick_eat(t_philo *philo);
int		pick(t_philo *philo);
int		eat(t_philo *philo);
long	odd_sleep(t_philo *philo);
int		sleep_think(t_philo *philo);
int		sleep_tight(t_philo *philo, int time);
int		print_state(t_philo *philo, char *str);
void	print_dead(t_philo *philo);
void	monitoring(t_data *data, t_philo *philo);
int		thread_join(t_data *data, t_philo *philo);
void	free_data_philo(t_data *data, t_philo *philo);
void	free_mutex_fork(int index, t_data *data);
void	free_mutex_last_eat_time(int index, t_data *data);

#endif
