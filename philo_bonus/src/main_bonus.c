/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveeta <pveeta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 01:20:33 by marvin            #+#    #+#             */
/*   Updated: 2021/11/21 16:45:45 by pveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static inline void	ft_kill(t_list *box, U_INT num)
{
	while (num > 0)
	{
		kill(box->ph_pid[num - 1], SIGTERM);
		num--;
	}
}

static inline t_status	who_finished(t_list *box, U_INT i, U_INT finish_meal)
{
	while (box->flag_dead == false && finish_meal != box->num_philo)
	{
		waitpid(box->ph_pid[i], &box->ph_exit[i], WNOHANG);
		if (box->ph_exit[i] > 0)
		{
			ft_kill(box, box->num_philo);
			box->flag_dead = true;
			return (FAIL);
		}
		else if (box->ph_exit[i] == SUCCESS)
			finish_meal++;
		if (finish_meal != box->num_philo && i++ == box->num_philo - 1 \
			&& box->flag_dead == false)
		{
			i = 0;
			finish_meal = 0;
		}
		if (box->flag_dead == true)
			return (FAIL);
	}
	return (SUCCESS);
}

static inline t_status	create_simulation(t_list *box)
{
	U_INT		i;
	U_INT		n;
	pid_t		child;

	i = 0;
	n = 0;
	child = 0;
	box->start_time = find_time();
	while (i < box->num_philo)
	{
		child = fork();
		if (child < 0)
		{
			ft_kill(box, i + 1);
			printf("\x1b[31mError: can't create the child process\n\x1b[0m");
			return (FAIL);
		}
		if (child == 0)
			philo_life(&box->philo[i], box);
		box->ph_pid[i] = child;
		i++;
	}
	return (who_finished(box, 0, 0));
}

int	main(int argc, char **argv)
{
	t_list		*box;

	if (argc != 5 && argc != 6)
	{
		printf("Error: unproper count of arguments\n");
		return (FAIL);
	}
	box = malloc(sizeof(t_list));
	if (!box || init_struct(box, argv) == FAIL)
		return (FAIL);
	if (box->num_philo == 1)
	{
		printf("\x1b[36m%d %d has taken a fork\x1b[0m\n", 0, box->num_philo);
		usleep(1000 * box->time_to_die);
		printf("%d %d died\n", box->time_to_die + 1, box->num_philo);
		return (clean_all(box));
	}
	create_simulation(box);
	if (box->flag_dead == false)
		printf("\n\x1b[33mHappy end: %d ph. ate for %u times.\x1b[0m\n", \
		box->num_philo, box->count_of_eat);
	if (box->flag_dead == true)
		printf("\n\x1b[31mSo sad: a philosopher died\x1b[0m\n");
	ft_kill(box, box->num_philo);
	return (clean_all(box));
}
