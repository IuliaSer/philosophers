/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iserzhan <iserzhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:04:30 by iserzhan          #+#    #+#             */
/*   Updated: 2021/01/13 16:07:31 by iserzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int			ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int			ft_atoi(const char *str)
{
	int				b;
	long long int	res;

	res = 0;
	b = 1;
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	if ((*str == '-'))
		b = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= 48 && *str <= 57)
	{
		if (res > ((res * 10) + (*str - '0')) && b == 1)
			return (-1);
		else if (res > ((res * 10) + (*str - '0')) && b == -1)
			return (0);
		else
			res = (res * 10) + (*str - '0');
		str++;
	}
	return (res * b);
}

static void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

static void	ft_putstr_fd(char *s, int fd)
{
	int		i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void		ft_putnbr_fd(int n, int fd)
{
	int min;

	min = -2147483648;
	if (n < 0 && n != min)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n == min)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
		ft_putchar_fd(n + '0', fd);
}
