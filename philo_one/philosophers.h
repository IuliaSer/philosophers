/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iserzhan <iserzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 20:16:11 by iserzhan          #+#    #+#             */
/*   Updated: 2021/01/19 12:06:52 by iserzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

int		g_alive;
int		g_eaten;

typedef struct			s_data
{
	uint64_t			time_to_eat;
	uint64_t			time_to_sleep;
	uint64_t			time_to_die;
	uint64_t			start;
	unsigned int		times_to_eat;
	unsigned int		num_of_phil;
	pthread_mutex_t		*forks;
	pthread_mutex_t		write_lock;
	pthread_mutex_t		death_lock;
}						t_data;

typedef struct			s_phil
{
	int					id;
	int					l_fork;
	int					r_fork;
	int					full;
	unsigned int		has_eaten;
	uint64_t			last_meal;
	int					eating;
	pthread_t			*tid;
	t_data				*data;
}						t_phil;

typedef struct			s_all
{
	t_phil				*phil;
	t_data				*data;
}						t_all;

int						main(int argc, char **argv);
void					*start_threads(t_all *all);
void					write_message(t_phil *phil, char *str);
int						write_error(char *str);
int						ft_atoi(const char *str);
int						ft_strlen(char *str);
void					ft_putnbr_fd(int n, int fd);
uint64_t				gettime(void);
void					free_all(t_all	*all);
void					*check_state(void *arg);

#endif
