/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:43:19 by seoson            #+#    #+#             */
/*   Updated: 2023/10/12 15:04:13 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_data_philo(t_data *data, t_philo *philo)
{
	free(philo);
	free(data->fork);
	free(data->last_eat_time);
}

void	free_mutex_fork(int index, t_data *data)
{
	while (index >= 0)
	{
		pthread_mutex_destroy(&data->fork[index]);
		index--;
	}
	pthread_mutex_destroy(&data->fin_flag);
	pthread_mutex_destroy(&data->fork_print);
}

void	free_mutex_last_eat_time(int index, t_data *data)
{
	free_mutex_fork(data->argv_info.philo_num - 1, data);
	while (index >= 0)
	{
		pthread_mutex_destroy(&data->last_eat_time[index]);
		index--;
	}
}
