/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:57:22 by algultse          #+#    #+#             */
/*   Updated: 2024/04/23 14:32:46 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_data(t_data *data)
{
	pthread_mutex_destroy(data->log);
	pthread_mutex_destroy(data->ded);
	if (!data)
		return ;
	ft_free_all(data->m);
}

void	error_philo(char *str, int fd)
{
	if (!str)
		str = "(null)";
	while (*str)
	{
		write (fd, str, 1);
		str++;
	}
}

time_t	now_ll(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	return ((long long)(tv.tv_sec)*1000 + (long long)(tv.tv_usec) / 1000);
}

long	ft_atoi_long(const char *str)
{
	long long	res;
	int			sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		if (sign == 1 && res > LONG_MAX)
			return (LONG_MAX);
		if (sign == -1 && (-res < LONG_MIN))
			return (LONG_MIN);
		str++;
	}
	return (sign * res);
}

// oblige de faire ca car usleep, qui fonctionne en microseconds,
// fait de la merde sur les grands nombres, par exemple 100 milliseconds
// (100 milliseconds == 100 000 microseconds)
void	time_sleep(int ms)
{
	time_t	n;

	n = now_ll();
	while (now_ll() - n <= ms)
		usleep(100);
}
