/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 02:02:08 by marvin            #+#    #+#             */
/*   Updated: 2021/11/07 02:02:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static inline t_status	ft_sleep(t_philo *philo)
{
	U_INT	time;

	if (print_status(philo->id, PRINT_SLEEP, SIZE_SLEEP_MSG, \
	philo->box) == FAIL)
		return (FAIL);
	if (philo->box->time_to_die < philo->box->time_to_eat + \
	philo->box->time_to_sleep)
		time = philo->box->time_to_die - philo->box->time_to_eat;
	else
		time = philo->box->time_to_sleep;
	usleep(1000 * time);
	return (SUCCESS);
}

static inline int	eat(t_philo *philo)
{
	if (print_status(philo->id, PRINT_EAT, SIZE_EAT_MSG, philo->box) == FAIL)
	{
		sem_post(philo->box->forks);
		sem_post(philo->box->forks);
		return (FAIL);
	}
	philo->start_eat = find_time();
	if (philo->box->time_to_die <= philo->box->time_to_eat)
		usleep(1000 * philo->box->time_to_die);
	else
		usleep(1000 * philo->box->time_to_eat);
	sem_post(philo->box->forks);
	sem_post(philo->box->forks);
	if (philo->box->count_of_eat > 0)
		philo->dinner++;
	return (SUCCESS);
}

static inline int	take_fork(t_philo *philo)
{
	sem_wait(philo->box->table);
	sem_wait(philo->box->forks);
	if (print_status(philo->id, PRINT_FORK, SIZE_FORK_MSG, \
					 philo->box) == FAIL)
	{
		sem_post(philo->box->forks);
		sem_post(philo->box->table);
		return (FAIL);
	}
	sem_wait(philo->box->forks);
	sem_post(philo->box->table);
	if (print_status(philo->id, PRINT_FORK, SIZE_FORK_MSG, \
					 philo->box) == FAIL)
	{
		sem_post(philo->box->forks);
		sem_post(philo->box->forks);
		return (FAIL);
	}
	return (SUCCESS);
}

static inline t_status	check_num_exit(t_philo *philo, t_list *box)
{
	t_status	res;

	if (box->count_of_eat == false || box->count_of_eat != \
	philo->dinner)
	{
		sem_wait(box->printing);
		printf("\x1b[31m%llu %d died\n\x1b[0m", \
			   find_time() - box->start_time, philo->id + 1);
		res = FAIL;
	}
	else
		res = SUCCESS;
	clean_all(box);
	return (res);
}

t_status	philo_life(t_philo *philo, t_list *box)
{
	philo->start_eat = find_time();
	while (1)
	{
		if (take_fork(philo) == FAIL)
			break ;
		if (eat(philo) == FAIL)
			break ;
		if (ft_sleep(philo) == FAIL)
			break ;
		if (philo->dinner == philo->box->count_of_eat && \
		philo->box->count_of_eat > 0)
			break ;
		if (print_status(philo->id, PRINT_THINK, \
		SIZE_THINK_MSG, philo->box) == FAIL)
			break ;
	}
	exit (check_num_exit(philo, box));
}
