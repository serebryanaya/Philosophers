/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_check_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveeta <pveeta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 01:22:05 by marvin            #+#    #+#             */
/*   Updated: 2021/11/21 18:40:24 by pveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static inline t_status	init_sem_and_philo(t_list *box)
{
	U_INT	i;

	i = 0;
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/table");
	box->forks = sem_open("/forks", O_CREAT, S_IRWXU, box->num_philo);
	box->printing = sem_open("/print", O_CREAT, S_IRWXU, 1);
	box->table = sem_open("/table", O_CREAT, S_IRWXU, 1);
	if (box->table == SEM_FAILED || box->forks == SEM_FAILED \
		|| box->printing == SEM_FAILED)
	{
		printf("Error: problems in open semafores\n");
		return (FAIL);
	}
	box->flag_dead = false;
	while (i < box->num_philo)
	{	
		box->philo[i].id = i;
		box->philo[i].start_eat = box->start_time;
		box->philo[i].box = box;
		box->ph_exit[i] = -1;
		box->philo[i++].dinner = 0;
	}
	return (SUCCESS);
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
		{
			printf("Too less time for eating!\n");
			return (FAIL);
		}
		if (box->count_of_eat == 0)
			return (FAIL);
	}
	else
		box->count_of_eat = 0;
	box->flag_dead = false;
	return (SUCCESS);
}

t_status	box_allocation(t_list *box)
{
	box->philo = (t_philo *)malloc(sizeof(t_philo) * box->num_philo);
	box->ph_pid = (pid_t *)malloc(sizeof(pid_t) * box->num_philo);
	box->ph_exit = (int *)malloc(sizeof(int) * box->num_philo);
	if (!box->philo || !box->ph_pid || !box->ph_exit)
	{
		printf("\x1b[36mError: problems in memory allocation\x1b[0m\n");
		return (FAIL);
	}
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
	{
		printf("\x1b[36mError: unproper digit\x1b[0m\n");
		return (FAIL);
	}
	box->start_time = find_time();
	if (check_argv(box, argv) == FAIL || box_allocation(box) == FAIL)
		return (FAIL);
	if (init_sem_and_philo(box) == FAIL)
		return (FAIL + clean_all(box));
	return (SUCCESS);
}
