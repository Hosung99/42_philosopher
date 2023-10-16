/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:33:57 by seoson            #+#    #+#             */
/*   Updated: 2023/10/14 15:12:14 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thread_join(t_data *data, t_philo *philo)
{
	int	index;

	index = 0;
	while (index < data->argv_info.philo_num)
	{
		if (pthread_join(philo[index].thread, NULL))
		{
			free_mutex_last_eat_time(philo->data->argv_info.philo_num - 1, \
				philo->data);
			free_data_philo(philo->data, philo);
			return (ERROR);
		}
		index++;
	}
	return (SUCCESS);
}

long	get_current_time(t_data *data)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000 - data->start_time);
}

int	malloc_data(t_data *data, t_philo *philo)
{
	data->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
		* (data->argv_info.philo_num));
	if (!data->fork)
	{
		free(philo);
		printf("Error: Fork Mutex malloc failed\n");
		return (ERROR);
	}
	data->last_eat_time = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
		* (data->argv_info.philo_num));
	if (!data->last_eat_time)
	{
		free(philo);
		free(data->fork);
		printf("Error: Last Eat Time Mutex malloc failed\n");
		return (ERROR);
	}
	return (SUCCESS);
}

int	print_state(t_philo *philo, char *str)
{
	struct timeval	time;

	pthread_mutex_lock(&philo->data->fork_print);
	gettimeofday(&time, NULL);
	if (philo->data->print_status == DIE)
	{
		pthread_mutex_unlock(&philo->data->fork_print);
		return (ERROR);
	}
	printf("%ld %d %s\n", time.tv_sec * 1000 + time.tv_usec \
		/ 1000 - philo->data->start_time, philo->id + 1, str);
	pthread_mutex_unlock(&philo->data->fork_print);
	return (SUCCESS);
}

void	print_dead(t_philo *philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	pthread_mutex_lock(&philo->data->fork_print);
	if (philo->data->print_status == DIE)
	{
		pthread_mutex_unlock(&philo->data->fork_print);
		return ;
	}
	philo->data->print_status = DIE;
	printf("%ld %d %s\n", time.tv_sec * 1000 + time.tv_usec / \
		1000 - philo->data->start_time, philo->id + 1, "died");
	pthread_mutex_unlock(&philo->data->fork_print);
}
