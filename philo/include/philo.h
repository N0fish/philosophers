/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:13:01 by algultse          #+#    #+#             */
/*   Updated: 2024/04/23 13:44:38 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include "ft_malloc.h"

typedef enum e_state {
	THINKING,
	EATING,
	SLEEPING,
	DEAD,
}			t_state;

typedef struct s_philo {
	time_t			eat_time;
	enum e_state	state;
	int				num;
	struct s_data	*data;
	struct s_philo	*prev;
	struct s_philo	*next;
	int				eat_nb;
	int				first_fork;
	int				second_fork;
	bool			left_fork_used;
	bool			right_fork_used;
}				t_philo;

typedef struct s_data {
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*log;
	pthread_mutex_t	*ded;
	t_malloc		*m;	
	int				nb_pl;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_nb;
	time_t			begin_time;
	t_philo			*philo;
	bool			is_over;
}				t_data;

/* check */
bool	check_input(int argc, char **argv);
bool	check_int_max(int argc, char **argv);

/* init */
int		init_data(t_data **data, int argc, char **argv);

/* utils */
void	free_data(t_data *data);
void	error_philo(char *str, int fd);
time_t	now_ll(void);
long	ft_atoi_long(const char *str);
void	time_sleep(int ms);

/* philo */
t_philo	*new_philo(t_data *data, int num);
void	*main_philo(void *arg);
void	*spy_philo(void *arg);

/* philo_state */
bool	is_game_over(t_data *data);
bool	is_starving(t_philo *philo, int time_to_die);
bool	has_eaten_max(t_philo *philo);
void	*next_state_action(t_philo *philo);

/* philo_action */
void	speak(t_philo *philo, char *msg);
void	*eating(t_philo *philo);
void	*thinking(t_philo *philo);
void	*sleeping(t_philo *philo);
void	death(t_philo *philo);

#endif