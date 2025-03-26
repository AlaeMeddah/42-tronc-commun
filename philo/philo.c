/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:59:20 by almeddah          #+#    #+#             */
/*   Updated: 2025/03/26 13:11:56 by almeddah         ###   ########.fr       */
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
		usleep(25);
	return ;
}

void	print_function(char *str, t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->lock);
	if (!data->end_simu)
		printf(str, get_time_in_ms(data->start), philo->id);
	pthread_mutex_unlock(&data->lock);
	return ;
}

void	*philo_function(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	print_function("%ld philo %d started thinking\n", data, philo);
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
