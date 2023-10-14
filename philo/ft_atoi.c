/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:29:20 by seoson            #+#    #+#             */
/*   Updated: 2023/10/11 17:21:43 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	jump_blank(const char *nptr)
{
	int	i;

	i = 0;
	while ((nptr[i] == 32 || ((nptr[i] >= 9 && nptr[i] <= 13))))
		i++;
	while (nptr[i])
	{
		if (nptr[i] == '-')
			return (0);
		else if (nptr[i] == '+')
			return (0);
		else
			break ;
		i++;
	}
	return (i);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sum;

	sum = 0;
	i = jump_blank(nptr);
	while (nptr && nptr[i])
	{
		if (nptr[i] >= '0' && nptr[i] <= '9')
				sum = sum * 10 + (nptr[i] - 48);
		else
			return (-1);
		i++;
	}
	return (sum);
}
