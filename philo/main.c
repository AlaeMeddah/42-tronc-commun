/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:40:30 by almeddah          #+#    #+#             */
/*   Updated: 2025/03/26 13:06:12 by almeddah         ###   ########.fr       */
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
		print_function("%ld philo %d died\n", philo->data, philo);
		return (1);
	}
	return (0);
}

int	check_finished(t_data *data)
{
	pthread_mutex_lock(&data->lock);
	if (data->finished == data->nb_philos)
	{
		pthread_mutex_unlock(&data->lock);
		return (1);
	}
	pthread_mutex_unlock(&data->lock);
	return (0);
}

void	set_data(t_data *data, int argc, char **argv)
{
	data->nb_philos = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	data->finished = 0;
	data->end_simu = 0;
	if (argc == 6)
		data->nb_eat = ft_atoi(argv[5]);
	else
		data->nb_eat = -1;
}

void	clean_up(t_data *data, t_philo **philos)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos + 1)
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
	data->forks = malloc((data->nb_philos + 1) * sizeof(pthread_mutex_t));
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
	while (++i < data->nb_philos + 1)
		pthread_mutex_init(&data->forks[i], NULL);
	pthread_mutex_init(&data->lock, NULL);
	return ;
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
			if (check_death(philos[i]) || check_finished(data))
			{
				pthread_mutex_lock(&data->lock);
				data->end_simu = 1;
				pthread_mutex_unlock(&data->lock);
			}
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

int	philo_creation(t_data *data, t_philo **philos)
{
	int	i;

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
		philos[i]->id = i + 1;
		philos[i]->nb_eaten = 0;
		philos[i]->last_eat = data->start;
		philos[i]->data = data;
		if (pthread_create(&philos[i]->thread, NULL, &philo_function,
				philos[i]) != 0)
		{
			perror("Failed to create philo");
			return (0);
		}
	}
	return (1);
}

int	thread_join(t_data *data, t_philo **philos, pthread_t *observer)
{
	int	i;

	i = -1;
	if (pthread_join(*observer, NULL) != 0)
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
	set_data(&data, argc, argv);
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
