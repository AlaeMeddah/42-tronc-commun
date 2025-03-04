#include "libft/libft.h"
#include "pthread.h"
#include "stdio.h"
#include "sys/time.h"

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
	int				nb_eaten;
	struct timeval	last_eat;
	struct timeval	current_time;
	pthread_t		thread;
	t_data			*data;
}					t_philo;

void	*philo_function(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	int		fork_2;
	long	elapsed_sec;
	long	elapsed_usec;

	philo = (t_philo *)arg;
	data = philo->data;
	philo->nb_eaten = 0;
	printf("philo %d started thinking\n", philo->id);
	gettimeofday(&philo->last_eat, NULL);
	if (philo->id == data->nb_philos)
		fork_2 = 1;
	else
		fork_2 = philo->id + 1;
	while (1)
	{
		while (1)
		{
			gettimeofday(&philo->current_time, NULL);
			elapsed_sec = philo->current_time.tv_sec - philo->last_eat.tv_sec;
			elapsed_usec = philo->current_time.tv_usec
				- philo->last_eat.tv_usec;
			if (elapsed_usec < 0)
			{
				elapsed_usec += 1000000;
				elapsed_sec--;
			}
			if (elapsed_sec * 1000000 + elapsed_usec >= data->time_die)
			{
				printf("philo %d died\n", philo->id);
				return (NULL);
			}
			if (pthread_mutex_trylock(&data->forks[philo->id]) == 0)
			{
				if (pthread_mutex_trylock(&data->forks[fork_2]) == 0)
					break ;
				else
					pthread_mutex_unlock(&data->forks[philo->id]);
			}
		}
		printf("philo %d started eating using forks %d et %d\n", philo->id,
			philo->id, fork_2);
		gettimeofday(&philo->last_eat, NULL);
		usleep(data->time_eat);
		philo->nb_eaten++;
		printf("philo %d finished eating using forks %d et %d\n", philo->id,
			philo->id, fork_2);
		pthread_mutex_unlock(&data->forks[philo->id]);
		pthread_mutex_unlock(&data->forks[fork_2]);
		if (philo->nb_eaten == data->nb_eat)
		{
			printf("philo %d has finished simulation\n", philo->id);
			return (NULL);
		}
		printf("philo %d started sleeping\n", philo->id);
		usleep(data->time_sleep);
		printf("philo %d started thinking\n", philo->id);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	int		i;
	t_data	data;
	t_philo	**philos;

	if (argc < 5 || argc > 6)
		return (0);
	i = 0;
	while (++i < argc)
	{
		if (!ft_isnum(argv[i]))
			return (0);
	}
	data.nb_philos = ft_atoi(argv[1]);
	data.time_die = ft_atoi(argv[2]);
	data.time_eat = ft_atoi(argv[3]);
	data.time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data.nb_eat = ft_atoi(argv[5]);
	else
		data.nb_eat = -1;
	philos = malloc(data.nb_philos * sizeof(t_philo *));
	if (!philos)
	{
		perror("Memory allocation failed");
		return (EXIT_FAILURE);
	}
	data.forks = malloc((data.nb_philos + 1) * sizeof(pthread_mutex_t));
	if (!data.forks)
	{
		perror("Memory allocation failed");
		free(philos);
		return (EXIT_FAILURE);
	}
	i = -1;
	while (++i < data.nb_philos + 1)
		pthread_mutex_init(&data.forks[i], NULL);
	i = -1;
	while (++i < data.nb_philos)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
		{
			perror("Memory allocation for philosopher failed");
			free(philos);
			free(data.forks);
			return (EXIT_FAILURE);
		}
		philos[i]->id = i + 1;
		philos[i]->data = &data;
		if (pthread_create(&philos[i]->thread, NULL, &philo_function,
				philos[i]) != 0)
		{
			perror("Failed to create thread");
			free(philos);
			free(data.forks);
			return (EXIT_FAILURE);
		}
	}
	i = -1;
	while (++i < data.nb_philos)
	{
		if (pthread_join(philos[i]->thread, NULL) != 0)
		{
			perror("Failed to create thread");
			free(philos);
			free(data.forks);
			return (EXIT_FAILURE);
		}
	}
	for (i = 0; i < data.nb_philos + 1; i++)
	{
		pthread_mutex_destroy(&data.forks[i]);
	}
	free(data.forks);
	for (i = 0; i < data.nb_philos; i++)
	{
		free(philos[i]);
	}
	free(philos);
	return (0);
}
