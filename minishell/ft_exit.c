/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhpham <minhpham@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 00:43:16 by minhpham          #+#    #+#             */
/*   Updated: 2025/07/03 15:45:02 by minhpham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long	ft_atol(const char *str)
{
	long	res;
	int		sign;
	int		i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

int	ft_exit(char **args, int in_fork)
{
	long	code;

	if (!args[1])
	{
		if (!in_fork)
			write(2, "exit\n", 5);
		exit(0);
	}
	if (!is_numeric(args[1]))
	{
		if (!in_fork)
			write(2, "exit\n", 5);
		write(2, "exit: ", 7);
		write(2, args[1], ft_strlen(args[1]));
		write(2, ": numeric argument required\n", 29);
		exit(2);
	}
	if (args[2])
	{
		if (!in_fork)
			write(2, "exit\n", 5);
		write(2, "exit: too many arguments\n", 26);
		return (1);
	}
	code = ft_atol(args[1]);
	if (!in_fork)
		write(2, "exit\n", 5);
	exit((unsigned char)code);
}
