/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iserzhan <iserzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:07:49 by iserzhan          #+#    #+#             */
/*   Updated: 2021/01/17 17:54:19 by iserzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

uint64_t	gettime(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void		count_meals(t_phil *phil)
{
	if (phil->data->times_to_eat)
	{
		phil->has_eaten++;
		if (phil->data->times_to_eat == phil->has_eaten)
			phil->full = 1;
	}
}
