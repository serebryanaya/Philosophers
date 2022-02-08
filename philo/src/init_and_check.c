/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveeta <pveeta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 01:22:05 by marvin            #+#    #+#             */
/*   Updated: 2021/11/21 18:40:03 by pveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline t_status	init_mutex(t_list *box)
{
	U_INT	i;

	if (pthread_mutex_init(&box->printing, NULL) != SUCCESS || \
	pthread_mutex_init(&box->death, NULL) != SUCCESS)
		return (ft_exit("Error: problems in mutex initialization"));
	box->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
	* box->num_philo);
	if (box->forks == NULL)
		return (ft_exit("Error: problems in memory allocation"));
	i = 0;
	while (i < box->num_philo)
	{
		if (pthread_mutex_init(&box->forks[i], NULL) != SUCCESS)
			return (ft_exit("Error: problems in mutex initialization"));
		i++;
	}
	return (SUCCESS);
}

static inline void	num_fork(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		if (philo->id == philo->box->num_philo - 1)
			philo->l_fork = 0;
		else
			philo->l_fork = philo->id + 1;
		philo->r_fork = philo->id;
	}
	else
	{
		philo->l_fork = philo->id;
		if (philo->id == philo->box->num_philo - 1)
			philo->r_fork = 0;
		else
			philo->r_fork = philo->id + 1;
	}
}

static inline t_philo	*init_philo(t_list *box, t_philo *philo)
{
	U_INT	i;

	i = 0;
	if (init_mutex(box) == FAIL)
		return (NULL);
	while (i < box->num_philo)
	{
		philo[i].id = i;
		philo[i].start_eat = box->start_time;
		philo[i].box = box;
		philo[i].dinner = 0;
		philo[i].thread_num = 0;
		num_fork(&philo[i]);
		if (pthread_mutex_init(&box->philo[i].mutex, NULL) != SUCCESS)
			return (ft_exit2("Error: problems in mutex initialization"));
		i++;
	}
	return (box->philo);
}

static inline t_status	init_struct2(t_list *box, char **argv, int *flag)
{
	if (*flag != 0)
		return (FAIL);
	box->time_to_die = (U_INT)modif_atoi(argv[2], flag, 0, 0);
	box->time_to_eat = (U_INT)modif_atoi(argv[3], flag, 0, 0);
	box->time_to_sleep = (U_INT)modif_atoi(argv[4], flag, 0, 0);
	if (argv[5])
	{
		box->count_of_eat = (U_INT)modif_atoi(argv[5], flag, 0, 0);
		if (box->count_of_eat < 0)
			return (ft_exit("Too less time for eating!"));
		if (box->count_of_eat == 0)
			return (FAIL);
	}
	else
		box->count_of_eat = 0;
	box->flag_dead = false;
	return (SUCCESS);
}

t_status	init_struct(t_list *box, char **argv)
{
	int	flag;

	flag = 0;
	box->num_philo = (U_INT)modif_atoi(argv[1], &flag, 0, 0);
	if (box->num_philo > 200)
	{
		printf("\x1b[36mError: more than 200 philosophers\x1b[0m\n");
		return (FAIL);
	}
	if (init_struct2(box, argv, &flag) == FAIL)
		return (FAIL);
	if (flag != 0)
		return (ft_exit("Error: unproper digits"));
	box->start_time = find_time();
	if (check_argv(box, argv) == FAIL)
		return (FAIL);
	box->philo = (t_philo *)malloc(sizeof(t_philo) * box->num_philo);
	if (box->philo == NULL)
		return (ft_exit("Error: problems in memory allocation"));
	if (init_philo(box, box->philo) == NULL)
	{
		free(box->philo);
		return (FAIL);
	}
	return (SUCCESS);
}
