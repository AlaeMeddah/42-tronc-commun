/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:59:20 by almeddah          #+#    #+#             */
/*   Updated: 2025/03/26 15:34:16 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fork_assignement(t_philo *philo, t_data *data)
{
	if (philo->id == data->nb_philos)
		philo->fork_2 = 1;
	else
		philo->fork_2 = philo->id + 1;
	if (philo->id % 2 == 0)
		usleep(100);
	return ;
}

void	*multiple_philos(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	printf("%ld philo %d started thinking\n", get_time_in_ms(data->start),
		philo->id);
	fork_assignement(philo, data);
	while (1)
	{
		if (!thinking(philo, data))
			return (NULL);
		if (!eating(philo, data))
			return (NULL);
		if (!sleeping(philo, data))
			return (NULL);
		if (data->end_simu)
			return (NULL);
	}
	return (NULL);
}

void	*lone_philo(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	printf("%ld philo %d started thinking\n", get_time_in_ms(data->start),
		philo->id);
	pthread_mutex_lock(&data->forks[philo->id]);
	printf("%ld philo %d picked up fork %d\n", get_time_in_ms(data->start),
		philo->id, philo->id);
	return (NULL);
}

int	philo_creation(t_data *data, t_philo **philos)
{
	int		i;
	void	*(*philo_function)(void *);

	philo_function = lone_philo;
	if (data->nb_philos != 1)
		philo_function = multiple_philos;
	i = -1;
	gettimeofday(&data->start, NULL);
	while (++i < data->nb_philos)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
		{
			perror("Memory allocation for philosopher failed");
			return (0);
		}
		init_philo(philos[i], data, i);
		if (pthread_create(&philos[i]->thread, NULL, philo_function,
				philos[i]) != 0)
		{
			perror("Failed to create philo");
			return (0);
		}
	}
	return (1);
}
