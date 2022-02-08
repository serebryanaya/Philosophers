/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveeta <pveeta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 01:20:33 by marvin            #+#    #+#             */
/*   Updated: 2021/11/23 12:58:15 by pveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline t_status	one_philo(t_list *box)
{
	printf("\x1b[36m%d %d has taken a fork\x1b[0m\n", 0, box->num_philo);
	usleep(1000 * box->time_to_die);
	printf("\x1b[31m%u %d died\x1b[0m\n", box->time_to_die + 1, box->num_philo);
	clean_all(box);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_list		box;
	pthread_t	monitor;
	int			check;

	if (argc != 5 && argc != 6)
		return (ft_exit("Error: unproper count of arguments"));
	if (init_struct(&box, argv) == FAIL)
		return (FAIL);
	if (box.num_philo == 1)
		return (one_philo(&box));
	if (pthread_create(&monitor, NULL, (void *)&create_simulation, \
	(void *)&box) != SUCCESS)
		return (clean_all(&box) + ft_exit("Error: can't create the thread"));
	pthread_join(monitor, (void **)&check);
	if (check == SUCCESS)
	{
		if (box.flag_dead == false)
			printf("\n\x1b[33mHappy end: all members ate for %u times.\x1b[0m\n", \
			box.count_of_eat);
		if (box.flag_dead == true)
			printf("\n\x1b[31mSo sad: a philosopher died\x1b[0m\n");
	}
	return (clean_all(&box));
}
