/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:07:05 by algultse          #+#    #+#             */
/*   Updated: 2024/04/23 14:22:50 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_starving(t_philo *philo, int time_to_die)
{
	return ((int)(now_ll() - philo->eat_time) >= time_to_die);
}

bool	has_eaten_max(t_philo *philo)
{
	bool	res;

	pthread_mutex_lock(philo->data->ded);
	if (philo->data->must_eat_nb != -1 && \
			philo->eat_nb >= philo->data->must_eat_nb)
		res = true;
	else
		res = false;
	pthread_mutex_unlock(philo->data->ded);
	return (res);
}

bool	is_game_over(t_data *data)
{
	t_philo	*philo;
	bool	all_eaten;

	if (!data)
		return (true);
	philo = data->philo;
	all_eaten = true;
	while (philo)
	{
		if (!has_eaten_max(philo))
		{
			all_eaten = false;
			if (is_starving(philo, data->time_to_die))
			{
				death(philo);
				return (true);
			}
		}
		philo = philo->next;
	}
	return (all_eaten);
}

void	*next_state_action(t_philo *philo)
{
	if (philo->state != DEAD && philo->state == THINKING)
		return (eating);
	else if (philo->state != DEAD && philo->state == EATING)
		return (sleeping);
	else if (philo->state != DEAD && philo->state == SLEEPING)
		return (thinking);
	return (NULL);
}
