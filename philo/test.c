#include "libft/libft.h"
#include "pthread.h"
#include "stdio.h"
#include <unistd.h>

#define NUM_PHILOSOPHERS 3

typedef struct s_data
{
	int				nb_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_eat;
	pthread_mutex_t	*forks;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	pthread_t		thread;
	t_data			*data;
}					t_philo;

void	*philo_function(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	int		fork_1;
	int		fork_2;
	int		temp;

	philo = (t_philo *)arg;
	data = philo->data;
	fork_1 = philo->id - 1;
	fork_2 = philo->id % NUM_PHILOSOPHERS;
	// To avoid deadlock, pick the lowest numbered fork first
	if (fork_1 > fork_2)
	{
		temp = fork_1;
		fork_1 = fork_2;
		fork_2 = temp;
	}
	while (philo->eat_count < data->nb_eat || data->nb_eat == -1)
	{
		printf("Philosopher %d is thinking\n", philo->id);
		// Pick up forks (mutex lock)
		pthread_mutex_lock(&data->forks[fork_1]);
		printf("Philosopher %d picked up fork %d\n", philo->id, fork_1);
		pthread_mutex_lock(&data->forks[fork_2]);
		printf("Philosopher %d picked up fork %d\n", philo->id, fork_2);
		// Eating
		printf("Philosopher %d is eating\n", philo->id);
		usleep(data->time_eat); // Simulate eating (time in microseconds)
		philo->eat_count++;
		printf("Philosopher %d finished eating. Total meals: %d\n", philo->id,
			philo->eat_count);
		// Put down forks (mutex unlock)
		pthread_mutex_unlock(&data->forks[fork_1]);
		printf("Philosopher %d put down fork %d\n", philo->id, fork_1);
		pthread_mutex_unlock(&data->forks[fork_2]);
		printf("Philosopher %d put down fork %d\n", philo->id, fork_2);
		// Sleep after eating
		printf("Philosopher %d is sleeping\n", philo->id);
		usleep(data->time_sleep); // Simulate sleeping (time in microseconds)
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	int		i;
	t_data	data;
	t_philo	*philos[NUM_PHILOSOPHERS];

	if (argc < 5 || argc > 6)
		return (0);
	// Parse arguments (check if they are numeric)
	i = 0;
	while (++i < argc)
	{
		if (!ft_isnum(argv[i]))
			return (0);
	}
	// Initialize data structure
	data.nb_philos = ft_atoi(argv[1]);
	data.time_die = ft_atoi(argv[2]);
	data.time_eat = ft_atoi(argv[3]);
	data.time_sleep = ft_atoi(argv[4]);
	data.nb_eat = (argc == 6) ? ft_atoi(argv[5]) : -1;
	// Allocate memory for forks and initialize mutexes
	data.forks = malloc(data.nb_philos * sizeof(pthread_mutex_t));
	if (!data.forks)
	{
		perror("Memory allocation failed");
		return (EXIT_FAILURE);
	}
	for (i = 0; i < data.nb_philos; i++)
		pthread_mutex_init(&data.forks[i], NULL);
	// Allocate memory for philosophers and create threads
	for (i = 0; i < data.nb_philos; i++)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
		{
			perror("Memory allocation for philosopher failed");
			return (EXIT_FAILURE);
		}
		philos[i]->id = i + 1;
		philos[i]->eat_count = 0;
		philos[i]->data = &data;
		if (pthread_create(&philos[i]->thread, NULL, philo_function,
				philos[i]) != 0)
		{
			perror("Failed to create thread");
			return (EXIT_FAILURE);
		}
	}
	// Join threads
	for (i = 0; i < data.nb_philos; i++)
	{
		if (pthread_join(philos[i]->thread, NULL) != 0)
		{
			perror("Failed to join thread");
			return (EXIT_FAILURE);
		}
		free(philos[i]);
	}
	// Clean up and destroy mutexes
	for (i = 0; i < data.nb_philos; i++)
		pthread_mutex_destroy(&data.forks[i]);
	free(data.forks);
	return (0);
}
