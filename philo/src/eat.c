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

#include "philo.h"

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
		pthread_mutex_unlock(&philo->box->forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->box->forks[philo->r_fork]);
		return (FAIL);
	}
	philo->start_eat = find_time();
	if (philo->box->time_to_die <= philo->box->time_to_eat)
		usleep(1000 * philo->box->time_to_die);
	else
		usleep(1000 * philo->box->time_to_eat);
	pthread_mutex_unlock(&philo->box->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->box->forks[philo->r_fork]);
	if (philo->box->count_of_eat > 0)
		philo->dinner++;
	return (SUCCESS);
}

static inline int	take_fork(t_philo *philo)
{
	if (philo->box->num_philo % 2 == 1)
		usleep(100);
	pthread_mutex_lock(&philo->box->forks[philo->l_fork]);
	if (print_status(philo->id, PRINT_FORK, SIZE_FORK_MSG, philo->box) == FAIL)
	{
		pthread_mutex_unlock(&philo->box->forks[philo->l_fork]);
		return (FAIL);
	}
	pthread_mutex_lock(&philo->box->forks[philo->r_fork]);
	if (print_status(philo->id, PRINT_FORK, SIZE_FORK_MSG, philo->box) == FAIL)
	{
		pthread_mutex_unlock(&philo->box->forks[philo->l_fork]);
		pthread_mutex_unlock(&philo->box->forks[philo->r_fork]);
		return (FAIL);
	}
	return (SUCCESS);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
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
		if (find_time() - philo->start_eat < \
		philo->box->time_to_die * 8 / 10)
			usleep(1000);
	}
	return (NULL);
}
