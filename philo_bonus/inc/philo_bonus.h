/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveeta <pveeta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 01:21:22 by marvin            #+#    #+#             */
/*   Updated: 2021/11/21 14:51:01 by pveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <semaphore.h>
# include <stdio.h>

# define SUCCESS		0
# define FAIL			1
# define PRINT_FORK		"\x1b[36m has taken a fork\n\x1b[0m"
# define SIZE_FORK_MSG	28
# define PRINT_EAT		"\x1b[33m is eating\n\x1b[0m"
# define SIZE_EAT_MSG	21
# define PRINT_SLEEP	"\x1b[32m is sleeping\n\x1b[0m"
# define SIZE_SLEEP_MSG	23
# define PRINT_THINK	"\x1b[35m is thinking\n\x1b[0m"
# define SIZE_THINK_MSG	23
# define PRINT_DEATH	"\x1b[31m died\n\x1b[0m"
# define SIZE_DEATH_MSG	16
# define MAX_SIZE		100

# define U_INT			unsigned int
# define UL_INT			unsigned long long int

typedef enum e_status
{
	false,
	true,
}	t_status;

struct	s_philo;

typedef struct s_list
{
	U_INT			num_philo;
	U_INT			time_to_die;
	U_INT			time_to_eat;
	U_INT			time_to_sleep;
	U_INT			count_of_eat;
	UL_INT			start_time;
	t_status		flag_dead;
	sem_t			*forks;
	sem_t			*printing;
	sem_t			*table;
	struct s_philo	*philo;
	pid_t			*ph_pid;
	int				*ph_exit;
}	t_list;

typedef struct s_philo
{
	U_INT			id;
	UL_INT			start_eat;
	U_INT			dinner;
	t_list			*box;
}	t_philo;

long		modif_atoi(char *s, int *flag, int i, long number);
t_status	init_struct(t_list *box, char **argv);
t_status	print_status(U_INT n_philo, char *status, U_INT size, t_list *box);
t_status	philo_life(t_philo *philo, t_list *box);
UL_INT		find_time(void);
int			check_argv(t_list *box, char **argv);
t_status	clean_all(t_list *box);

#endif
