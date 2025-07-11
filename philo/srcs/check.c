/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:17:18 by algultse          #+#    #+#             */
/*   Updated: 2024/04/16 13:30:27 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
		if (!*s++)
			return (false);
	return ((char *)s);
}

bool	check_number(char *str)
{
	if (!*str)
		return (false);
	while (*str)
	{
		if (!ft_strchr("0123456789", *str))
			return (false);
		str++;
	}
	return (true);
}

bool	check_input(int argc, char **argv)
{
	int	i;

	if (!argv)
		return (false);
	i = 1;
	while (argv[i] && i < argc)
	{
		if (!check_number(argv[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	check_int_max(int argc, char **argv)
{
	long	nb;
	int		i;

	if (!argv)
		return (false);
	i = 1;
	while (argv[i] && i < argc)
	{
		nb = ft_atoi_long(argv[i]);
		if (i == 1)
			if (nb == 0 || nb > 200)
				return (false);
		if (nb > INT_MAX || nb < INT_MIN)
			return (false);
		i++;
	}
	return (true);
}
