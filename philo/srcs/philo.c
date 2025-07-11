/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:20:52 by algultse          #+#    #+#             */
/*   Updated: 2024/04/23 14:31:13 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*new_philo(t_data *data, int num)
{
	t_philo	*philo;

	philo = (t_philo *)ft_malloc(data->m, sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->num = num;
	philo->data = data;
	philo->eat_nb = 0;
	philo->state = THINKING;
	philo->prev = NULL;
	philo->next = NULL;
	philo->first_fork = philo->num;
	philo->second_fork = philo->num - 1;
	if (philo->num == 1)
		philo->second_fork = philo->data->nb_pl;
	philo->eat_time = now_ll();
	philo->left_fork_used = false;
	philo->right_fork_used = false;
	return (philo);
}

// ce thread va exister un nombre num_philo de fois
void	*main_philo(void *arg)
{
	t_philo	*philo;
	void	(*action)(t_philo*);

	philo = (t_philo *)arg;
	if (!philo)
		return (NULL);
	if (!(philo->num & 1))
		usleep(philo->data->time_to_eat / 5 * 1000);
	while (true)
	{
		pthread_mutex_lock(philo->data->ded);
		action = next_state_action(philo);
		if (philo->data->is_over || action == NULL)
		{
			pthread_mutex_unlock(philo->data->ded);
			break ;
		}
		pthread_mutex_unlock(philo->data->ded);
		action(philo);
	}
	if (philo->left_fork_used && philo->right_fork_used)
		pthread_mutex_unlock(&philo->data->forks[philo->second_fork - 1]);
	if (philo->left_fork_used)
		pthread_mutex_unlock(&philo->data->forks[philo->first_fork - 1]);
	return (NULL);
}

// ce thread va exister qu'une seule fois
void	*spy_philo(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	if (!data)
		return (NULL);
	while (!is_game_over(data))
		;
	pthread_mutex_lock(data->ded);
	if (data->nb_pl == 1)
	{
		pthread_mutex_unlock(&data->philo->data->forks[data->philo->first_fork \
			- 1]);
		data->philo->left_fork_used = false;
	}
	data->is_over = true;
	pthread_mutex_unlock(data->ded);
	return (NULL);
}
