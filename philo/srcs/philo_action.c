/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:20:45 by algultse          #+#    #+#             */
/*   Updated: 2024/04/23 13:48:53 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	speak(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->data->log);
	if (philo->state != DEAD && !philo->data->is_over)
		printf("%ld %d %s\n", now_ll() - philo->data->begin_time, \
			philo->num, msg);
	pthread_mutex_unlock(philo->data->log);
}

void	*eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->first_fork - 1]);
	speak(philo, "has taken a fork");
	pthread_mutex_lock(philo->data->ded);
	philo->left_fork_used = true;
	pthread_mutex_unlock(philo->data->ded);
	pthread_mutex_lock(&philo->data->forks[philo->second_fork - 1]);
	speak(philo, "has taken a fork");
	speak(philo, "is eating");
	pthread_mutex_lock(philo->data->ded);
	philo->right_fork_used = true;
	philo->state = EATING;
	philo->eat_time = now_ll();
	pthread_mutex_unlock(philo->data->ded);
	time_sleep(philo->data->time_to_eat);
	pthread_mutex_lock(philo->data->ded);
	philo->eat_nb++;
	pthread_mutex_unlock(philo->data->ded);
	pthread_mutex_unlock(&philo->data->forks[philo->second_fork - 1]);
	pthread_mutex_lock(philo->data->ded);
	philo->right_fork_used = false;
	pthread_mutex_unlock(philo->data->ded);
	pthread_mutex_unlock(&philo->data->forks[philo->first_fork - 1]);
	pthread_mutex_lock(philo->data->ded);
	philo->left_fork_used = false;
	return (pthread_mutex_unlock(philo->data->ded), NULL);
}

void	*thinking(t_philo *philo)
{
	pthread_mutex_lock(philo->data->ded);
	if (philo->state != SLEEPING || philo->data->is_over)
	{
		pthread_mutex_unlock(philo->data->ded);
		return (NULL);
	}
	philo->state = THINKING;
	pthread_mutex_unlock(philo->data->ded);
	speak(philo, "is thinking");
	return (NULL);
}

void	*sleeping(t_philo *philo)
{
	pthread_mutex_lock(philo->data->ded);
	if (philo->state != EATING || philo->data->is_over)
	{
		pthread_mutex_unlock(philo->data->ded);
		return (NULL);
	}
	philo->state = SLEEPING;
	pthread_mutex_unlock(philo->data->ded);
	speak(philo, "is sleeping");
	time_sleep(philo->data->time_to_sleep);
	return (NULL);
}

void	death(t_philo *philo)
{
	speak(philo, "died");
	pthread_mutex_lock(philo->data->ded);
	philo->state = DEAD;
	philo->data->is_over = true;
	pthread_mutex_unlock(philo->data->ded);
}
