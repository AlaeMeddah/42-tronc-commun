#ifndef PHILO_H
# define PHILO_H

# include "libft/libft.h"
# include "pthread.h"

typedef struct s_data
{
	int				nb_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_eat;
	int				*forks;
	pthread_mutex_t	lock;
}					t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	t_data			*data;
	// status;
	// last eat;
}					t_philo;

#endif