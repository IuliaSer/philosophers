/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iserzhan <iserzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:56:23 by iserzhan          #+#    #+#             */
/*   Updated: 2021/01/22 12:56:31 by iserzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	write_message(t_phil *phil, char *str)
{
	sem_wait(phil->data->write_lock);
	ft_putnbr_fd(gettime() - phil->data->start, 1);
	write(1, " ", 1);
	ft_putnbr_fd(phil->id + 1, 1);
	write(1, str, ft_strlen(str));
	g_alive ? sem_post(phil->data->write_lock) : 0;
}

int		write_error(char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}
