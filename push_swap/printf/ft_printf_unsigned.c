/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ameddah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:30:41 by ameddah           #+#    #+#             */
/*   Updated: 2024/03/05 18:30:54 by ameddah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	count_size_(unsigned long nb)
{
	size_t	size;

	size = 0;
	if (nb == 0)
		size = 1;
	else
	{
		while (nb)
		{
			nb = nb / 10;
			size++;
		}
	}
	return (size);
}

static char	*ft_uitoa(unsigned int n)
{
	size_t			size;
	unsigned long	nb;
	char			*str;

	size = count_size_((unsigned long) n);
	str = (char *) malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	nb = (unsigned long) n;
	str[size] = '\0';
	while (size > 0)
	{
		str[size - 1] = nb % 10 + '0';
		nb = nb / 10;
		size--;
	}
	return (str);
}

int	ft_print_unsigned(unsigned int n)
{
	int		i;
	char	*num;

	i = 0;
	num = ft_uitoa(n);
	i = ft_print_str(num);
	free(num);
	return (i);
}
