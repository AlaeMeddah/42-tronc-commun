/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:35:22 by almeddah          #+#    #+#             */
/*   Updated: 2025/08/11 16:43:12 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_function(char *str, t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->lock);
	if (!data->end_simu)
		printf(str, get_time_in_ms(data->start), philo->id);
	pthread_mutex_unlock(&data->lock);
	return ;
}

int	thinking(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->forks[philo->fork_1]);
	pthread_mutex_lock(&data->lock);
	if (!data->end_simu)
		printf("%ld philo %d picked up fork %d\n", get_time_in_ms(data->start),
			philo->id, philo->fork_1);
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
	pthread_mutex_lock(&data->lock);
	if (!data->end_simu)
		printf("%ld philo %d started eating\n", get_time_in_ms(data->start),
			philo->id);
	philo->nb_eaten++;
	if (philo->nb_eaten == data->nb_eat)
	{
		data->finished++;
		if (data->finished == data->nb_philos)
			data->end_simu = 1;
	}
	pthread_mutex_unlock(&data->lock);
	while (get_time_in_ms(philo->last_eat) < data->time_eat)
		usleep(50);
	pthread_mutex_unlock(&data->forks[philo->fork_2]);
	pthread_mutex_unlock(&data->forks[philo->fork_1]);
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
