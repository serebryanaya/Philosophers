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

#include "philo_bonus.h"

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
	if (box->philo)
		free(box->philo);
	if (box->ph_pid)
		free(box->ph_pid);
	if (box->ph_exit)
		free(box->ph_exit);
	if (box->forks)
		sem_close(box->forks);
	if (box->table)
		sem_close(box->table);
	if (box->printing)
		sem_close(box->printing);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/table");
	if (box)
		free(box);
	return (SUCCESS);
}
