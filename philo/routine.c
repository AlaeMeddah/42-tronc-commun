/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:35:22 by almeddah          #+#    #+#             */
/*   Updated: 2025/03/26 12:54:32 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thinking(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->forks[philo->id]);
	pthread_mutex_lock(&data->lock);
	if (!data->end_simu)
		printf("%ld philo %d picked up fork %d\n", get_time_in_ms(data->start),
			philo->id, philo->id);
	pthread_mutex_unlock(&data->lock);
	pthread_mutex_lock(&data->forks[philo->fork_2]);
	pthread_mutex_lock(&data->lock);
	if (!data->end_simu)
		printf("%ld philo %d picked up fork %d\n", get_time_in_ms(data->start),
			philo->id, philo->fork_2);
	pthread_mutex_unlock(&data->lock);
	return (1);
}

int	eating(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->lock);
	gettimeofday(&philo->last_eat, NULL);
	pthread_mutex_unlock(&data->lock);
	print_function("%ld philo %d started eating\n", data, philo);
	philo->nb_eaten++;
	if (philo->nb_eaten == data->nb_eat)
	{
		pthread_mutex_lock(&data->lock);
		data->finished++;
		pthread_mutex_unlock(&data->lock);
	}
	while (get_time_in_ms(philo->last_eat) < data->time_eat)
		usleep(50);
	pthread_mutex_unlock(&data->forks[philo->id]);
	pthread_mutex_unlock(&data->forks[philo->fork_2]);
	return (1);
}

int	sleeping(t_philo *philo, t_data *data)
{
	print_function("%ld philo %d started sleeping\n", data, philo);
	while (get_time_in_ms(philo->last_eat) < data->time_eat + data->time_sleep)
		usleep(50);
	print_function("%ld philo %d started thinking\n", data, philo);
	return (1);
}
