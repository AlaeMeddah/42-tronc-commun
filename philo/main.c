/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:40:30 by almeddah          #+#    #+#             */
/*   Updated: 2025/08/11 15:27:38 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_up(t_data *data, t_philo **philos)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->forks);
	i = -1;
	while (++i < data->nb_philos)
		free(philos[i]);
	free(philos);
	return ;
}

int	mem_alloc(t_data *data, t_philo ***philos)
{
	*philos = malloc(data->nb_philos * sizeof(t_philo *));
	data->forks = malloc((data->nb_philos) * sizeof(pthread_mutex_t));
	if (!(*philos) || !data->forks)
	{
		perror("Memory allocation failed");
		return (0);
	}
	return (1);
}

void	mutex_init(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
		pthread_mutex_init(&data->forks[i], NULL);
	pthread_mutex_init(&data->lock, NULL);
	return ;
}

int	thread_join(t_data *data, t_philo **philos, pthread_t *monitor)
{
	int	i;

	i = -1;
	if (pthread_join(*monitor, NULL) != 0)
	{
		perror("Failed to join monitor");
		return (0);
	}
	while (++i < data->nb_philos)
	{
		if (pthread_join(philos[i]->thread, NULL) != 0)
		{
			perror("Failed to join philo");
			return (0);
		}
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		**philos;
	pthread_t	monitor;

	if (!check_args(argc, argv))
		return (0);
	if (!init_data(&data, argc, argv))
		return (0);
	if (!mem_alloc(&data, &philos))
		return (0);
	mutex_init(&data);
	if (!philo_creation(&data, philos))
		return (0);
	if (!monitor_creation(&monitor, philos))
		return (0);
	if (!thread_join(&data, philos, &monitor))
		return (0);
	clean_up(&data, philos);
	return (0);
}
