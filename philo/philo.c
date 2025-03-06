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
	int				died;
	int				finished;
	struct timeval	start;
	pthread_mutex_t	*forks;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				fork_2;
	int				nb_eaten;
	struct timeval	last_eat;
	pthread_t		thread;
	t_data			*data;
}					t_philo;

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

int	check_death(t_philo philo)
{
	struct timeval	time;
	long			elapsed_sec;
	long			elapsed_usec;

	gettimeofday(&time, NULL);
	elapsed_sec = time.tv_sec - philo.last_eat.tv_sec;
	elapsed_usec = time.tv_usec - philo.last_eat.tv_usec;
	if (elapsed_usec < 0)
	{
		elapsed_usec += 1000000;
		elapsed_sec--;
	}
	if (elapsed_sec * 1000 + elapsed_usec / 1000 >= philo.data->time_die)
	{
		printf("%ld philo %d died\n", get_time_in_ms(philo.data->start),
			philo.id);
		return (1);
	}
	return (0);
}

int	check_finished(t_philo *philo, t_data *data)
{
	if (philo->nb_eaten == data->nb_eat)
	{
		data->finished++;
		printf("%ld philo %d has finished simulation\n",
			get_time_in_ms(data->start), philo->id);
		if (data->finished == data->nb_philos)
			return (1);
	}
	return (0);
}

int	thinking(t_philo *philo, t_data *data)
{
	while (1)
	{
		if (check_death(*philo))
			data->died = 1;
		if (data->died || data->finished == data->nb_philos)
			return (0);
		if (pthread_mutex_trylock(&data->forks[philo->id]) == 0)
		{
			if (pthread_mutex_trylock(&data->forks[philo->fork_2]) == 0)
				break ;
			else
				pthread_mutex_unlock(&data->forks[philo->id]);
		}
		usleep(1000);
	}
	return (1);
}

int	eating(t_philo *philo, t_data *data)
{
	int	i;

	gettimeofday(&philo->last_eat, NULL);
	printf("%ld philo %d started eating using forks %d et %d\n",
		get_time_in_ms(data->start), philo->id, philo->id, philo->fork_2);
	i = -1;
	while (++i < data->time_eat)
	{
		usleep(1000);
		if (check_death(*philo))
			data->died = 1;
		if (data->died || data->finished == data->nb_philos)
			return (0);
	}
	printf("%ld philo %d finished eating using forks %d et %d\n",
		get_time_in_ms(data->start), philo->id, philo->id, philo->fork_2);
	philo->nb_eaten++;
	pthread_mutex_unlock(&data->forks[philo->id]);
	pthread_mutex_unlock(&data->forks[philo->fork_2]);
	return (1);
}

int	sleeping(t_philo *philo, t_data *data)
{
	int	i;

	printf("%ld philo %d started sleeping\n", get_time_in_ms(data->start),
		philo->id);
	i = -1;
	while (++i < data->time_sleep)
	{
		usleep(1000);
		if (check_death(*philo))
			data->died = 1;
		if (data->died || data->finished == data->nb_philos)
			return (0);
	}
	printf("%ld philo %d started thinking\n", get_time_in_ms(data->start),
		philo->id);
	return (1);
}

void	*philo_function(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	philo->nb_eaten = 0;
	printf("%ld philo %d started thinking\n", get_time_in_ms(data->start),
		philo->id);
	philo->last_eat = data->start;
	if (philo->id == data->nb_philos)
		philo->fork_2 = 1;
	else
		philo->fork_2 = philo->id + 1;
	while (1)
	{
		if (!thinking(philo, data))
			return (NULL);
		if (!eating(philo, data))
			return (NULL);
		if (check_finished(philo, data))
			return (NULL);
		if (!sleeping(philo, data))
			return (NULL);
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
	data.died = 0;
	data.finished = 0;
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
	gettimeofday(&data.start, NULL);
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
