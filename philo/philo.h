/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:35:15 by almeddah          #+#    #+#             */
/*   Updated: 2025/03/17 11:46:54 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "pthread.h"
# include "stdio.h"
# include "sys/time.h"
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_data
{
	int				nb_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_eat;
	int				died;
	int				finished;
	struct timeval	start;
	pthread_mutex_t	*forks;
	int				*forks_status;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				fork_2;
	int				nb_eaten;
	struct timeval	last_eat;
	pthread_t		thread;
	t_data			*data;
}					t_philo;

int					thinking(t_philo *philo, t_data *data);
int					eating(t_philo *philo, t_data *data);
int					sleeping(t_philo *philo, t_data *data);
int					ft_isnum(char *str);
int					ft_atoi(const char *str);
time_t				get_time_in_ms(struct timeval start);
int					check_death(t_philo philo);
int					check_finished(t_philo *philo, t_data *data);
int					check_args(int argc, char **argv);

#endif