/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveeta <pveeta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 16:40:15 by pveeta            #+#    #+#             */
/*   Updated: 2021/11/21 17:57:00 by pveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline void	my_join(t_list *box, U_INT num, U_INT i)
{
	while (i < num)
	{
		pthread_join(box->philo[i].thread_num, NULL);
		i++;
	}
}

static inline int	create_threads(t_list *box, U_INT num, U_INT i)
{
	while (i < num)
	{
		if (pthread_create(&box->philo[i].thread_num, NULL, \
		philo_life, &box->philo[i]) != SUCCESS)
		{
			pthread_mutex_lock(&box->death);
			box->flag_dead = true;
			pthread_mutex_unlock(&box->death);
			my_join(box, i, 0);
			return (ft_exit("Error: problems in thread's creation"));
		}
		i += 2;
	}
	return (SUCCESS);
}

static inline t_status	who_finished2(t_list *box, U_INT *i, U_INT *finish_meal)
{
	if (box->flag_dead == false && box->count_of_eat > 0 && \
	*finish_meal < box->num_philo)
	{
		pthread_mutex_lock(&box->philo[*i].mutex);
		if (box->philo[*i].dinner == box->count_of_eat)
			(*finish_meal)++;
		pthread_mutex_unlock(&box->philo[*i].mutex);
		if (*finish_meal != box->num_philo && ++(*i) == box->num_philo)
		{
			*i = 0;
			*finish_meal = 0;
		}
		if (*finish_meal == box->num_philo)
			return (FAIL);
	}
	return (SUCCESS);
}

static inline void	who_finished(t_list *box, U_INT i, U_INT finish_meal)
{
	while (1)
	{
		pthread_mutex_lock(&box->death);
		if (find_time() - box->philo[i].start_eat > \
		box->time_to_die && box->flag_dead == false)
		{
			box->flag_dead = true;
			pthread_mutex_unlock(&box->death);
			printf("\x1b[31m%llu %d died\x1b[0m\n", find_time() \
			- box->start_time, box->philo[i].id + 1);
			return ;
		}
		pthread_mutex_unlock(&box->death);
		if (who_finished2(box, &i, &finish_meal) == FAIL)
			return ;
	}
}

t_status	create_simulation(void *arg)
{
	t_list		*box;

	box = (t_list *)arg;
	box->start_time = find_time();
	if (create_threads(box, box->num_philo, 0) == FAIL)
		return (FAIL);
	usleep(10);
	if (create_threads(box, box->num_philo, 1) == FAIL)
		return (FAIL);
	who_finished(box, 0, 0);
	my_join(box, box->num_philo, 0);
	return (SUCCESS);
}
