/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:31:00 by seoson            #+#    #+#             */
/*   Updated: 2023/10/14 16:20:52 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_dining(t_data *data, t_philo *philo)
{
	int	index;

	index = 0;
	while (index < data->argv_info.philo_num)
	{
		if (pthread_create(&philo[index].thread, NULL, (void *)dining, \
			(void *)&philo[index]))
		{
			free_mutex_last_eat_time(data->argv_info.philo_num - 1, data);
			free_data_philo(data, philo);
			printf("Error: Thread create failed\n");
			return (ERROR);
		}
		index++;
	}
	return (SUCCESS);
}

void	*dining(t_philo *philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	pthread_mutex_lock(&philo->data->last_eat_time[philo->id]);
	philo->last_eat_time = get_current_time(philo->data);
	pthread_mutex_unlock(&philo->data->last_eat_time[philo->id]);
	if (philo->id % 2 == 1)
		usleep(odd_sleep(philo));
	while (1)
	{
		if (pick_eat(philo) == ERROR)
			break ;
		pthread_mutex_lock(&philo->data->fin_flag);
		if (philo->data->fin_count == philo->data->argv_info.philo_num)
		{
			pthread_mutex_unlock(&philo->data->fin_flag);
			break ;
		}
		pthread_mutex_unlock(&philo->data->fin_flag);
		if (sleep_think(philo) == ERROR)
			break ;
		usleep(100);
	}
	return (NULL);
}

long	odd_sleep(t_philo *philo)
{
	long	temp;

	if (philo->data->argv_info.time_eat * 2 > philo->data->argv_info.time_die)
		temp = philo->data->argv_info.time_die / 2;
	else
		temp = philo->data->argv_info.time_eat / 2;
	if (temp == 0)
		temp = 1;
	return (temp * 1000);
}

void	monitoring(t_data *data, t_philo *philo)
{
	int		index;

	index = 0;
	while (index < data->argv_info.philo_num)
	{
		pthread_mutex_lock(&data->fin_flag);
		if (data->fin_count == data->argv_info.philo_num)
			break ;
		pthread_mutex_unlock(&data->fin_flag);
		pthread_mutex_lock(&philo[index].data->last_eat_time[index]);
		if (get_current_time(philo->data) - philo[index].last_eat_time \
			> data->argv_info.time_die)
		{
			pthread_mutex_unlock(&philo[index].data->last_eat_time[index]);
			print_dead(&philo[index]);
			return ;
		}
		pthread_mutex_unlock(&philo[index].data->last_eat_time[index]);
		if (index == data->argv_info.philo_num - 1)
			index = 0;
		else
			index = (index % data->argv_info.philo_num) + 1;
	}
	pthread_mutex_unlock(&data->fin_flag);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	t_philo	*philo;

	if (check_argument(argc, argv, &data.argv_info) == ERROR)
		return (ERROR);
	philo = (t_philo *)malloc(sizeof(t_philo) * data.argv_info.philo_num);
	if (!philo)
	{
		printf("Error: Philo malloc failed\n");
		return (ERROR);
	}
	if (init_data(&data, philo) == ERROR)
		return (ERROR);
	if (init_philo(&data, philo) == ERROR)
		return (ERROR);
	if (start_dining(&data, philo) == ERROR)
		return (ERROR);
	usleep(100);
	monitoring(&data, philo);
	if (thread_join(&data, philo) == ERROR)
		return (ERROR);
	free_mutex_last_eat_time(philo->data->argv_info.philo_num - 1, \
				philo->data);
	free_data_philo(philo->data, philo);
	return (SUCCESS);
}
