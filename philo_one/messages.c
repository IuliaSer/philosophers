/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iserzhan <iserzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:56:23 by iserzhan          #+#    #+#             */
/*   Updated: 2021/01/17 18:13:20 by iserzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	write_message(t_phil *phil, char *str)
{
	pthread_mutex_lock(&phil->data->write_lock);
	ft_putnbr_fd(gettime() - phil->data->start, 1);
	write(1, " ", 1);
	ft_putnbr_fd(phil->id + 1, 1);
	write(1, str, ft_strlen(str));
	pthread_mutex_unlock(&phil->data->write_lock);
}

int		write_error(char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}
