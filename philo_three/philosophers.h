/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iserzhan <iserzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 17:57:03 by iserzhan          #+#    #+#             */
/*   Updated: 2021/01/17 19:08:16 by iserzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

int g_alive;
int g_eaten;
int g_status;

typedef struct			s_data
{
	uint64_t			time_to_eat;
	uint64_t			time_to_sleep;
	uint64_t			time_to_die;
	uint64_t			start;
	unsigned int		times_to_eat;
	unsigned int		num_of_phil;
	sem_t				*forks;
	sem_t				*write_lock;
	sem_t				*death_lock;
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
	pid_t				pid;
	t_data				*data;
}						t_phil;

typedef struct			s_all
{
	t_phil				*phil;
	t_data				*data;
}						t_all;

int						main(int argc, char **argv);
void					start_threads(t_all *all);
void					write_message(t_phil *phil, char *str);
int						write_error(char *str);
int						ft_atoi(const char *str);
int						ft_strlen(char *str);
void					ft_putnbr_fd(int n, int fd);
uint64_t				gettime(void);
void					free_all(t_all	*all);
int						start_processes(t_all *all);
void					*check_state(void *arg);
void					count_meals(t_phil *phil);

#endif
