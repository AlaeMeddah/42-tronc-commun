/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:24:38 by almeddah          #+#    #+#             */
/*   Updated: 2025/08/11 16:46:08 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, int argc, char **argv)
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
	if (!data->nb_philos || !data->time_die || !data->nb_eat)
	{
		printf("Error with arg value");
		return (0);
	}
	return (1);
}

void	init_philo(t_philo *philo, t_data *data, int i)
{
	philo->id = i + 1;
	philo->nb_eaten = 0;
	philo->last_eat = data->start;
	philo->data = data;
}

int	min(int i, int j)
{
	if (i <= j)
		return (i);
	return (j);
}

int	max(int i, int j)
{
	if (i >= j)
		return (i);
	return (j);
}
