/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:38:02 by almeddah          #+#    #+#             */
/*   Updated: 2025/03/17 11:45:34 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("wrong number of arguments");
		return (0);
	}
	i = 0;
	while (++i < argc)
	{
		if (!ft_isnum(argv[i]))
		{
			printf("wrong format of arguments");
			return (0);
		}
	}
	return (1);
}
