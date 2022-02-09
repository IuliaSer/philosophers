/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_philosophers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iserzhan <iserzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:56:12 by iserzhan          #+#    #+#             */
/*   Updated: 2021/01/22 12:06:21 by iserzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void		eating(t_phil *phil)
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

static void		sleeping(t_phil *phil)
{
	write_message(phil, " is sleeping\n");
	usleep(phil->data->time_to_sleep * 1000);
}

static int		action(t_phil *phil)
{
	pthread_t tid;

	phil->last_meal = gettime();
	pthread_create(&tid, NULL, &check_state, phil);
	pthread_detach(tid);
	if (!g_alive)
		return (1);
	while (g_alive)
	{
		g_alive ? eating(phil) : exit(1);
		g_alive ? sleeping(phil) : exit(1);
		g_alive ? write_message(phil, " is thinking\n") : exit(1);
	}
	return (1);
}

void			wait_processes(t_all *all)
{
	unsigned int	i;
	unsigned int	j;
	int				status;

	i = 0;
	j = 0;
	while (waitpid(-1, &status, 0) && j++ < all->data->num_of_phil)
	{
		g_status = WEXITSTATUS(status);
		if (g_status == 1)
		{
			i = 0;
			while (i < all->data->num_of_phil)
			{
				kill(all->phil[i].pid, SIGKILL);
				i++;
			}
			exit(0);
		}
	}
}

int				start_processes(t_all *all)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	all->data->start = gettime();
	while (i < all->data->num_of_phil)
	{
		all->phil[i].pid = fork();
		if (all->phil[i].pid < 0)
		{
			printf("error: fork failed\n");
			return (1);
		}
		else if (all->phil[i].pid == 0)
		{
			if (action(&all->phil[i]))
				exit(1);
		}
		usleep(100);
		i++;
	}
	wait_processes(all);
	return (0);
}
