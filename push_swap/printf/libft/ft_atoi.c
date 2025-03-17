/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ameddah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:09:26 by ameddah           #+#    #+#             */
/*   Updated: 2023/11/24 09:50:02 by ameddah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*del_space(const char *str)
{
	while (*str && (*str == ' ' || (*str >= 9 && *str <= 13)))
	{
		str++;
	}
	return (str);
}

long	ft_atoi(const char *str)
{
	long	x;
	int		sign;

	x = 0;
	sign = 1;
	str = del_space(str);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && (*str >= '0' && *str <= '9'))
	{
		if (x > (LONG_MAX - (*str - '0')) / 10)
			return (LONG_MAX);
		x = x * 10 + (*str - '0');
		str++;
	}
	x = x * sign;
	return (x);
}
