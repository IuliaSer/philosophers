/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iserzhan <iserzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:56:18 by iserzhan          #+#    #+#             */
/*   Updated: 2021/01/22 13:11:42 by iserzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		free_all(t_all *all)
{
	unsigned int i;

	i = 0;
	if (all->data->forks)
	{
		while (i < all->data->num_of_phil)
		{
			pthread_mutex_destroy(&all->data->forks[i]);
			i++;
		}
	}
	pthread_mutex_destroy(&all->data->write_lock);
	free(all->data->forks);
	if (all->phil)
		free(all->phil);
	all->phil = NULL;
}

static void	init_phil(t_phil *phil, t_data *data, int i)
{
	phil[i].data = data;
	phil[i].id = i;
	phil[i].l_fork = i;
	phil[i].r_fork = (i + 1) % data->num_of_phil;
	phil[i].last_meal = 0;
	phil[i].eating = 0;
	phil[i].has_eaten = 0;
	phil[i].full = 0;
	phil[i].tid = malloc(sizeof(pthread_t) * 100);
}

void		init_vars(char **argv, int argc, t_all *all)
{
	unsigned int i;

	i = 0;
	g_alive = 1;
	pthread_mutex_init(&all->data->write_lock, NULL);
	pthread_mutex_init(&all->data->death_lock, NULL);
	all->data->num_of_phil = ft_atoi(argv[1]);
	all->data->time_to_die = ft_atoi(argv[2]);
	all->data->time_to_eat = ft_atoi(argv[3]);
	all->data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		all->data->times_to_eat = ft_atoi(argv[5]);
	else
		all->data->times_to_eat = 0;
	all->phil = (t_phil *)malloc(sizeof(t_phil ) * all->data->num_of_phil);
	all->data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) *
		all->data->num_of_phil);
	while (i < all->data->num_of_phil)
	{
		pthread_mutex_init(&all->data->forks[i], NULL);
		i++;
	}
}

int			main(int argc, char **argv)
{
	t_all			all;
	t_phil			phil;
	t_data			data;
	unsigned int	i;

	i = 0;
	all.phil = &phil;
	all.data = &data;
	if (argc < 5 || argc > 6)
		return (write_error("wrong number of arguments\n"));
	init_vars(argv, argc, &all);
	if (all.data->num_of_phil > 200 || all.data->time_to_die < 60 ||
		all.data->time_to_sleep < 60)
		return (0);
	while (i < all.data->num_of_phil)
		init_phil(all.phil, all.data, i++);
	start_threads(&all);
	free_all(&all);
	return (0);
}
