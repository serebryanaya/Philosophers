/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standart.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 01:21:50 by marvin            #+#    #+#             */
/*   Updated: 2021/11/07 01:21:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	modif_atoi(char *s, int *flag, int i, long number)
{
	int	sign;

	if (*flag != 0)
		return (0);
	while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-')
		sign = -1;
	else
		sign = 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i] != 0 && *flag != -1)
	{
		if (s[i] < '0' || s[i] > '9')
			*flag = -1;
		while (s[i] >= '0' && s[i] <= '9' && *flag != -1)
		{
			number = 10 * number + (s[i++] - '0');
			if ((number > 2147483647 && sign == 1) || sign == -1)
				*flag = -1;
		}
	}
	return (sign * number);
}

UL_INT	find_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		printf("Can't find current time!\n");
		return (FAIL);
	}
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

t_status	clean_all(t_list *box)
{
	U_INT	i;

	if (box->forks)
	{
		i = 0;
		while (i < box->num_philo)
			pthread_mutex_destroy(&box->forks[i++]);
		free(box->forks);
	}
	if (box->philo)
	{
		i = 0;
		while (i < box->num_philo)
			pthread_mutex_destroy(&box->philo[i++].mutex);
		free(box->philo);
	}
	pthread_mutex_destroy(&box->printing);
	pthread_mutex_destroy(&box->death);
	return (SUCCESS);
}
