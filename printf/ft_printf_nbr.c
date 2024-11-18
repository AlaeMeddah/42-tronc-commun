/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:30:35 by ameddah           #+#    #+#             */
/*   Updated: 2024/11/18 16:48:58 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// static size_t	count_size(long nb)
// {
// 	size_t	size;

// 	size = 0;
// 	if (nb < 0)
// 	{
// 		nb = nb * (-1);
// 		size = 1;
// 	}
// 	if (nb == 0)
// 		size = 1;
// 	else
// 	{
// 		while (nb)
// 		{
// 			nb = nb / 10;
// 			size++;
// 		}
// 	}
// 	return (size);
// }

// static char	*ft_itoa(int n)
// {
// 	size_t	size;
// 	long	nb;
// 	char	*str;
// 	int		is_negative;

// 	size = count_size((long) n);
// 	str = (char *) malloc(sizeof(char) * (size + 1));
// 	if (str == NULL)
// 		return (NULL);
// 	nb = (long) n;
// 	is_negative = 0;
// 	if (nb < 0)
// 	{
// 		nb = nb * (-1);
// 		str[0] = '-';
// 		is_negative = 1;
// 	}
// 	str[size] = '\0';
// 	while (size > (size_t) is_negative)
// 	{
// 		str[size - 1] = nb % 10 + '0';
// 		nb = nb / 10;
// 		size--;
// 	}
// 	return (str);
// }

int	ft_print_nbr(int n)
{
	int		i;
	char	*num;

	i = 0;
	num = ft_itoa(n);
	i = ft_print_str(num);
	free(num);
	return (i);
}
