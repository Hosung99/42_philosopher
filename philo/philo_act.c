/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_act.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:57:24 by seoson            #+#    #+#             */
/*   Updated: 2023/10/14 17:30:08 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pick_eat(t_philo *philo)
{
	if (pick(philo) == ERROR)
		return (ERROR);
	if (eat(philo) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	pick(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->r_fork]);
	if (print_state(philo, "has taken a fork") == ERROR \
		|| philo->data->argv_info.philo_num == 1)
	{
		pthread_mutex_unlock(&philo->data->fork[philo->r_fork]);
		return (ERROR);
	}
	pthread_mutex_lock(&philo->data->fork[philo->l_fork]);
	if (print_state(philo, "has taken a fork") == ERROR)
	{
		pthread_mutex_unlock(&philo->data->fork[philo->l_fork]);
		pthread_mutex_unlock(&philo->data->fork[philo->r_fork]);
		return (ERROR);
	}
	return (SUCCESS);
}

int	eat(t_philo *philo)
{
	if (print_state(philo, "is eating") == ERROR)
	{
		pthread_mutex_unlock(&philo->data->fork[philo->l_fork]);
		pthread_mutex_unlock(&philo->data->fork[philo->r_fork]);
		return (ERROR);
	}
	philo->eat_count++;
	if (philo->eat_count == philo->data->argv_info.must_eat)
	{
		pthread_mutex_lock(&philo->data->fin_flag);
		philo->data->fin_count++;
		pthread_mutex_unlock(&philo->data->fin_flag);
	}
	pthread_mutex_lock(&philo->data->last_eat_time[philo->id]);
	philo->last_eat_time = get_current_time(philo->data);
	pthread_mutex_unlock(&philo->data->last_eat_time[philo->id]);
	if (sleep_tight(philo, philo->data->argv_info.time_eat) == ERROR)
	{
		pthread_mutex_unlock(&philo->data->fork[philo->l_fork]);
		pthread_mutex_unlock(&philo->data->fork[philo->r_fork]);
		return (ERROR);
	}
	pthread_mutex_unlock(&philo->data->fork[philo->l_fork]);
	pthread_mutex_unlock(&philo->data->fork[philo->r_fork]);
	return (SUCCESS);
}

int	sleep_think(t_philo *philo)
{
	if (print_state(philo, "is sleeping") == ERROR)
		return (ERROR);
	if (sleep_tight(philo, philo->data->argv_info.time_sleep) == ERROR)
		return (ERROR);
	if (print_state(philo, "is thinking") == ERROR)
		return (ERROR);
	usleep(100);
	return (SUCCESS);
}

int	sleep_tight(t_philo *philo, int time)
{
	long	start_time;

	start_time = get_current_time(philo->data);
	while (philo->data->argv_info.time_eat != 0 && \
		get_current_time(philo->data) - start_time < time)
	{
		pthread_mutex_lock(&philo->data->fork_print);
		if (philo->data->print_status == DIE)
		{
			pthread_mutex_unlock(&philo->data->fork_print);
			return (ERROR);
		}
		pthread_mutex_unlock(&philo->data->fork_print);
		usleep(200);
	}
	return (SUCCESS);
}
