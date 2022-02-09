/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_philosophers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iserzhan <iserzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:56:12 by iserzhan          #+#    #+#             */
/*   Updated: 2021/01/17 20:04:40 by iserzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	count_meals(t_phil *phil)
{
	if (phil->data->times_to_eat)
	{
		phil->has_eaten++;
		if (phil->data->times_to_eat == phil->has_eaten)
			phil->full = 1;
	}
}

static void	eating(t_phil *phil)
{
	uint64_t start;
	uint64_t finish;

	sem_wait(phil->data->forks);
	write_message(phil, " has taken a fork\n");
	sem_wait(phil->data->forks);
	write_message(phil, " has taken a fork\n");
	phil->eating = 1;
	write_message(phil, " is eating\n");
	start = gettime();
	finish = start;
	phil->last_meal = gettime();
	while ((finish - start) < phil->data->time_to_eat)
	{
		usleep(1);
		finish = gettime();
	}
	count_meals(phil);
	phil->eating = 0;
	sem_post(phil->data->forks);
	sem_post(phil->data->forks);
}

static void	sleeping(t_phil *phil)
{
	write_message(phil, " is sleeping\n");
	usleep(phil->data->time_to_sleep * 1000);
}

static void	*action(void *arg)
{
	t_phil		*phil;

	phil = (t_phil *)arg;
	phil->last_meal = gettime();
	while (g_alive)
	{
		eating(phil);
		sleeping(phil);
		write_message(phil, " is thinking\n");
	}
	return ((void*)0);
}

void		start_threads(t_all *all)
{
	unsigned int	i;
	pthread_t		tid;

	i = 0;
	all->data->start = gettime();
	while (i < all->data->num_of_phil)
	{
		pthread_create(all->phil[i].tid, NULL, action, (void *)&all->phil[i]);
		usleep(100);
		i++;
	}
	pthread_create(&tid, NULL, &check_state, (void *)all);
	pthread_join(tid, NULL);
	usleep(10000);
	i = 0;
	while (i < all->data->num_of_phil)
	{
		pthread_detach(*all->phil[i].tid);
		i++;
	}
}
