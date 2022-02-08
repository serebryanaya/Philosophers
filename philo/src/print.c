/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveeta <pveeta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 15:30:53 by pveeta            #+#    #+#             */
/*   Updated: 2021/11/16 19:12:05 by pveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline U_INT	num_to_str(UL_INT time, char *str, U_INT count)
{
	U_INT	tmp;
	U_INT	divider;

	tmp = (U_INT)time;
	divider = 10;
	while (tmp % divider != tmp)
		divider = divider * 10;
	while (divider != 1)
	{
		divider = divider / 10;
		str[count] = tmp / divider + 48;
		tmp = tmp % divider;
		count++;
	}
	return (count);
}

t_status	print_status(U_INT n_philo, char *status, U_INT size, t_list *box)
{
	U_INT	count;
	U_INT	n;
	char	msg[MAX_SIZE];

	pthread_mutex_lock(&box->death);
	if (box->flag_dead == true)
	{
		pthread_mutex_unlock(&box->death);
		return (FAIL);
	}
	pthread_mutex_lock(&box->printing);
	count = num_to_str(find_time() - box->start_time, &msg[0], 0);
	msg[count++] = ' ';
	count = num_to_str(n_philo + 1, &msg[0], count);
	n = 0;
	while (n < size)
		msg[count++] = status[n++];
	write(1, msg, count - 1);
	pthread_mutex_unlock(&box->printing);
	pthread_mutex_unlock(&box->death);
	return (SUCCESS);
}
