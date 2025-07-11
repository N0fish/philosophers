/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:35:47 by algultse          #+#    #+#             */
/*   Updated: 2024/04/16 13:32:48 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philo_list(t_data *data)
{
	t_philo	*philo;
	t_philo	*tmp;
	t_philo	*start;
	int		n;

	if (!data)
		return (NULL);
	n = 1;
	philo = new_philo(data, n);
	if (!philo)
		return (NULL);
	start = philo;
	while (++n <= data->nb_pl)
	{
		tmp = new_philo(data, n);
		if (!tmp)
			return (NULL);
		tmp->prev = philo;
		philo->next = tmp;
		philo = tmp;
	}
	return (start);
}

pthread_mutex_t	*init_forks(t_data *data)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = (pthread_mutex_t *)ft_malloc(\
		data->m, data->nb_pl * sizeof(pthread_mutex_t));
	if (!forks)
		return (NULL);
	i = 0;
	while (i < data->nb_pl)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

bool	init_locks(t_data *data)
{
	data->log = (pthread_mutex_t *)ft_malloc(data->m, sizeof(pthread_mutex_t));
	if (!data->log)
		return (false);
	pthread_mutex_init(data->log, NULL);
	data->ded = (pthread_mutex_t *)ft_malloc(data->m, sizeof(pthread_mutex_t));
	if (!data->ded)
		return (false);
	pthread_mutex_init(data->ded, NULL);
	return (true);
}

void	init_args_values(t_data *data, int argc, char **argv)
{
	data->nb_pl = (int)ft_atoi_long(argv[1]);
	data->time_to_die = (int)ft_atoi_long(argv[2]);
	data->time_to_eat = (int)ft_atoi_long(argv[3]);
	data->time_to_sleep = (int)ft_atoi_long(argv[4]);
	data->begin_time = now_ll();
	data->must_eat_nb = -1;
	if (argc == 6)
		data->must_eat_nb = (int)ft_atoi_long(argv[5]);
	data->is_over = false;
}

int	init_data(t_data **data, int argc, char **argv)
{
	t_malloc	*mallocs;

	mallocs = init_malloc();
	if (!mallocs)
		return (error_philo("Error mallocs\n", 2), EXIT_FAILURE);
	*data = (t_data *)ft_malloc(mallocs, sizeof(t_data));
	if (!*data)
		return (error_philo("Error malloc data\n", 2), EXIT_FAILURE);
	(*data)->m = mallocs;
	init_args_values(*data, argc, argv);
	if (!init_locks(*data))
		return (error_philo("Error init locks\n", 2), EXIT_FAILURE);
	(*data)->philo = init_philo_list(*data);
	if (!(*data)->philo)
		return (error_philo("Error init philo\n", 2), EXIT_FAILURE);
	(*data)->forks = init_forks(*data);
	if (!(*data)->forks)
		return (error_philo("Error init forks\n", 2), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
