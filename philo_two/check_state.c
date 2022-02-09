/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iserzhan <iserzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 20:07:33 by iserzhan          #+#    #+#             */
/*   Updated: 2021/01/22 12:53:09 by iserzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_for_death(t_all *all, int i)
{
	uint64_t		now;

	now = gettime();
	if ((!all->phil[i].eating) &&
		(now > (all->phil[i].last_meal + all->data->time_to_die)))
	{
		sem_wait(all->phil[i].data->write_lock);
		g_alive = 0;
		ft_putnbr_fd(gettime() - all->phil->data->start, 1);
		write(1, " ", 1);
		ft_putnbr_fd(all->phil->id + 1, 1);
		write(1, " died\n", 6);
		return (1);
	}
	return (0);
}

static int	check_if_eatten_enough(t_all *all, unsigned int count)
{
	if (count == all->data->num_of_phil)
	{
		sem_wait(all->data->write_lock);
		write(1, "Philosophers has eaten enough\n", 30);
		return (1);
	}
	return (0);
}

void		*check_state(void *arg)
{
	t_all			*all;
	unsigned int	i;
	unsigned int	count;

	all = (t_all *)arg;
	while (1)
	{
		i = 0;
		count = 0;
		while (i < all->data->num_of_phil)
		{
			if (check_for_death(all, i))
				return ((void*)0);
			if (all->data->times_to_eat)
			{
				if (all->phil[i].full)
					count++;
				if (check_if_eatten_enough(all, count))
					return ((void*)0);
			}
			i++;
		}
	}
}
