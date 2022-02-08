/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 01:36:43 by marvin            #+#    #+#             */
/*   Updated: 2021/11/07 01:36:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline int	check_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

int	check_argv(t_list *box, char **argv)
{
	if (box->num_philo < 1 || box->time_to_die < 0 || \
	box->time_to_eat < 0 || box->time_to_sleep < 0)
		return (ft_exit("This arguments are too big or too less!"));
	if (check_number(argv[1]) == FAIL || \
	check_number(argv[2]) == FAIL || check_number(argv[3]) == FAIL || \
	check_number(argv[4]) == FAIL || (argv[5] != NULL && \
	check_number(argv[5]) == FAIL))
		return (ft_exit("Unproper arguments"));
	if (box->time_to_die < 60 || box->time_to_eat < 60 || \
	box->time_to_sleep < 60)
	{
		printf("\x1b[36mError: time is less than 60 ms\x1b[0m\n");
		return (FAIL);
	}
	return (SUCCESS);
}

t_status	ft_exit(char *message)
{
	printf("%s\n", message);
	return (FAIL);
}

void	*ft_exit2(char *message)
{
	printf("%s\n", message);
	return (NULL);
}
