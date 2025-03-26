/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:09:46 by almeddah          #+#    #+#             */
/*   Updated: 2025/03/26 15:20:26 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time_in_ms(struct timeval start)
{
	struct timeval	time;
	long			elapsed_sec;
	long			elapsed_usec;

	gettimeofday(&time, NULL);
	elapsed_sec = time.tv_sec - start.tv_sec;
	elapsed_usec = time.tv_usec - start.tv_usec;
	if (elapsed_usec < 0)
	{
		elapsed_usec += 1000000;
		elapsed_sec--;
	}
	return ((elapsed_sec * 1000) + (elapsed_usec / 1000));
}

int	check_death(t_philo *philo)
{
	struct timeval	time;
	long			elapsed_sec;
	long			elapsed_usec;

	gettimeofday(&time, NULL);
	pthread_mutex_lock(&philo->data->lock);
	elapsed_sec = time.tv_sec - philo->last_eat.tv_sec;
	elapsed_usec = time.tv_usec - philo->last_eat.tv_usec;
	pthread_mutex_unlock(&philo->data->lock);
	if (elapsed_usec < 0)
	{
		elapsed_usec += 1000000;
		elapsed_sec--;
	}
	if (elapsed_sec * 1000 + elapsed_usec / 1000 >= philo->data->time_die)
	{
		pthread_mutex_lock(&philo->data->lock);
		philo->data->end_simu = 1;
		pthread_mutex_unlock(&philo->data->lock);
		printf("%ld philo %d died\n", get_time_in_ms(philo->data->start),
			philo->id);
		return (1);
	}
	return (0);
}

void	*monitor_function(void *args)
{
	t_philo	**philos;
	t_data	*data;
	int		i;

	philos = (t_philo **)args;
	data = (*philos)->data;
	while (1)
	{
		i = -1;
		while (++i < data->nb_philos)
		{
			check_death(philos[i]);
			if (data->end_simu)
				return (NULL);
		}
	}
	return (NULL);
}

int	monitor_creation(pthread_t *observer, t_philo **philos)
{
	if (pthread_create(observer, NULL, &monitor_function, philos) != 0)
	{
		perror("Failed to create monitor");
		return (0);
	}
	return (1);
}
