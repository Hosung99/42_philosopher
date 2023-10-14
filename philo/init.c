/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:36:49 by seoson            #+#    #+#             */
/*   Updated: 2023/10/14 13:16:50 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	atoi_argv(t_argv *argv_info, int argc, char *argv[])
{
	argv_info->philo_num = ft_atoi(argv[1]);
	argv_info->time_die = ft_atoi(argv[2]);
	argv_info->time_eat = ft_atoi(argv[3]);
	argv_info->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		argv_info->must_eat = ft_atoi(argv[5]);
	else
		argv_info->must_eat = -1;
}

int	check_argument(int argc, char *argv[], t_argv *argv_info)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (ERROR);
	}
	if (argc == 6 && ft_atoi(argv[5]) < 1)
	{
		printf("Error: Wrong argument\n");
		return (ERROR);
	}
	atoi_argv(argv_info, argc, argv);
	if (argv_info->philo_num < 1 || argv_info->time_die <= 0
		|| argv_info->time_eat <= 0 || argv_info->time_sleep <= 0)
	{
		printf("Error: Wrong argument\n");
		return (ERROR);
	}
	return (SUCCESS);
}

int	init_philo(t_data *data, t_philo *philo)
{
	int	index;

	index = 0;
	if (init_mutex(data) == ERROR)
	{
		free_data_philo(data, philo);
		return (ERROR);
	}
	while (index < data->argv_info.philo_num)
	{
		philo[index].data = data;
		philo[index].id = index;
		philo[index].r_fork = index;
		philo[index].eat_count = 0;
		if (index == 0)
			philo[index].l_fork = data->argv_info.philo_num - 1;
		else
			philo[index].l_fork = index - 1;
		if (data->argv_info.philo_num == 1)
			philo[index].l_fork = 0;
		index++;
	}
	return (SUCCESS);
}

int	init_mutex(t_data *data)
{
	int	index;

	index = 0;
	while (index < data->argv_info.philo_num)
	{
		if (pthread_mutex_init(&data->fork[index], NULL) != 0)
		{
			free_mutex_fork(index, data);
			printf("Error: Mutex init failed\n");
			return (ERROR);
		}
		if (pthread_mutex_init(&data->last_eat_time[index], NULL) != 0)
		{
			free_mutex_last_eat_time(index, data);
			printf("Error: Mutex init failed\n");
			return (ERROR);
		}
		index++;
	}
	return (SUCCESS);
}

int	init_data(t_data *data, t_philo *philo)
{
	struct timeval	time;

	if (malloc_data(data, philo) == ERROR)
		return (ERROR);
	if (pthread_mutex_init(&data->fin_flag, NULL) != 0)
	{
		free_data_philo(data, philo);
		printf("Error: Mutex init failed\n");
		return (ERROR);
	}
	if (pthread_mutex_init(&data->fork_print, NULL) != 0)
	{
		free_data_philo(data, philo);
		pthread_mutex_destroy(&data->fin_flag);
		printf("Error: Mutex init failed\n");
		return (ERROR);
	}
	gettimeofday(&time, NULL);
	data->print_status = ALIVE;
	data->start_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	data->fin_count = 0;
	return (SUCCESS);
}
