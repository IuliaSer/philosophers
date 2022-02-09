/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iserzhan <iserzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 18:16:00 by iserzhan          #+#    #+#             */
/*   Updated: 2021/01/22 12:29:48 by iserzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_for_death(t_phil *phil)
{
	uint64_t	now;

	now = gettime();
	if ((!phil->eating) &&
		(now > (phil->last_meal + phil->data->time_to_die)))
	{
		sem_wait(phil->data->write_lock);
		g_alive = 0;
		ft_putnbr_fd(gettime() - phil->data->start, 1);
		write(1, " ", 1);
		ft_putnbr_fd(phil->id + 1, 1);
		write(1, " died\n", 6);
		return (1);
	}
	return (0);
}

void		*check_state(void *arg)
{
	t_phil			*phil;
	unsigned int	i;
	unsigned int	count;

	phil = (t_phil *)arg;
	while (1)
	{
		i = 0;
		count = 0;
		while (i < phil->data->num_of_phil)
		{
			if (check_for_death(phil))
				exit(1);
			if (phil->data->times_to_eat)
			{
				if (phil[i].full == 1)
					exit(2);
			}
			i++;
		}
	}
}
