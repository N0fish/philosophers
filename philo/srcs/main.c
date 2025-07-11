/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:13:08 by algultse          #+#    #+#             */
/*   Updated: 2024/04/23 13:46:25 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_start(t_data *data)
{
	t_philo	*philo;
	int		i;

	data->threads = ft_malloc(data->m, sizeof(pthread_t) * (data->nb_pl + 1));
	if (!data->threads)
		return ;
	i = 0;
	philo = data->philo;
	while (i < data->nb_pl)
	{
		if (!philo \
		|| pthread_create(&data->threads[i], NULL, &main_philo, philo))
			return ;
		philo = philo->next;
		i++;
	}
	if (pthread_create(&data->threads[i], NULL, &spy_philo, data))
		return ;
	i = 0;
	while (i <= data->nb_pl)
	{
		if (pthread_join(data->threads[i], NULL))
			return ;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int		exit_code;

	if (argc - 1 != 4 && argc - 1 != 5)
		return (error_philo("Usage: ./philo <philosophers> <time to die> <time to eat> <time to sleep> [times each philosopher must eat]\
		\n", 2), EXIT_FAILURE);
	if (!check_input(argc, argv))
		return (error_philo("Error other than digits\n", 2), EXIT_FAILURE);
	if (!check_int_max(argc, argv))
		return (error_philo("Error int range\n", 2), EXIT_FAILURE);
	exit_code = init_data(&data, argc, argv);
	if (exit_code == EXIT_SUCCESS)
		philo_start(data);
	free_data(data);
	return (exit_code);
}
