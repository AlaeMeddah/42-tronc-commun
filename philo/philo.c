/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:59:20 by almeddah          #+#    #+#             */
/*   Updated: 2025/08/11 17:47:43 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fork_assignement(t_philo *philo, t_data *data)
{
	philo->fork_1 = min((philo->id) - 1, philo->id % data->nb_philos);
	philo->fork_2 = max((philo->id) - 1, philo->id % data->nb_philos);
	return ;
}

int	routine_order(t_philo *philo, t_data *data)
{
	if (!thinking(philo, data))
		return (0);
	if (!eating(philo, data))
		return (0);
	if (!sleeping(philo, data))
		return (0);
	return (1);
}

void	*multiple_philos(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	pthread_mutex_lock(&data->lock);
	printf("%ld philo %d started thinking\n", get_time_in_ms(data->start),
		philo->id);
	pthread_mutex_unlock(&data->lock);
	fork_assignement(philo, data);
	while (1)
	{
		if (!routine_order(philo, data))
			return (NULL);
		pthread_mutex_lock(&data->lock);
		if (data->end_simu)
		{
			pthread_mutex_unlock(&data->lock);
			return (NULL);
		}
		pthread_mutex_unlock(&data->lock);
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
	pthread_mutex_lock(&data->forks[(philo->id) - 1]);
	printf("%ld philo %d picked up fork %d\n", get_time_in_ms(data->start),
		philo->id, (philo->id) - 1);
	pthread_mutex_unlock(&data->forks[(philo->id) - 1]);
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
