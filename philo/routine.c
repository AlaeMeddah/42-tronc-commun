/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:35:22 by almeddah          #+#    #+#             */
/*   Updated: 2025/03/25 12:31:43 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking_2(int *hold_fork1, t_data *data, t_philo *philo)
{
	*hold_fork1 = 1;
	data->forks_status[philo->id] = 1;
}

int	thinking(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->forks[philo->id]);
	printf("%ld philo %d picked up fork %d\n", get_time_in_ms(data->start),
		philo->id, philo->id);
	pthread_mutex_lock(&data->forks[philo->fork_2]);
	printf("%ld philo %d picked up fork %d\n", get_time_in_ms(data->start),
		philo->id, philo->fork_2);
	return (1);
}

int	eating(t_philo *philo, t_data *data)
{
	gettimeofday(&philo->last_eat, NULL);
	printf("%ld philo %d started eating\n", get_time_in_ms(data->start),
		philo->id);
	while (get_time_in_ms(philo->last_eat) < data->time_eat)
	{
		if (check_death(*philo))
			data->died = 1;
		if (data->died || data->finished == data->nb_philos)
			return (0);
		usleep(50);
	}
	printf("%ld philo %d finished eating\n", get_time_in_ms(data->start),
		philo->id);
	philo->nb_eaten++;
	pthread_mutex_unlock(&data->forks[philo->id]);
	printf("%ld philo %d put down fork %d\n", get_time_in_ms(data->start),
		philo->id, philo->id);
	pthread_mutex_unlock(&data->forks[philo->fork_2]);
	printf("%ld philo %d put down fork %d\n", get_time_in_ms(data->start),
		philo->id, philo->fork_2);
	data->forks_status[philo->id] = 0;
	data->forks_status[philo->fork_2] = 0;
	return (1);
}

int	sleeping(t_philo *philo, t_data *data)
{
	printf("%ld philo %d started sleeping\n", get_time_in_ms(data->start),
		philo->id);
	while (get_time_in_ms(philo->last_eat) < data->time_eat + data->time_sleep)
	{
		if (check_death(*philo))
			data->died = 1;
		if (data->died || data->finished == data->nb_philos)
			return (0);
		usleep(50);
	}
	printf("%ld philo %d started thinking\n", get_time_in_ms(data->start),
		philo->id);
	return (1);
}
