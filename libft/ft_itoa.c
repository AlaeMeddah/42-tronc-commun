/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:43:41 by almeddah          #+#    #+#             */
/*   Updated: 2024/10/16 13:24:27 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_abs(int nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}

static char	*ft_strcat_char(char *dest, char c)
{
	unsigned int	i;

	i = 0;
	while (dest[i])
		i++;
	dest[i] = c;
	dest[i + 1] = '\0';
	return (dest);
}

static void	itoa_2(int nbr, int size, char **result)
{
	int	i;

	if (nbr == -2147483648)
	{
		itoa_2(nbr / 10, size + 1, result);
		ft_strcat_char(*result, '0' + ft_abs(nbr % 10));
		return ;
	}
	if (ft_abs(nbr) >= 10)
		itoa_2(nbr / 10, size + 1, result);
	if (ft_abs(nbr) < 10)
	{
		if (nbr < 0)
			size++;
		*result = malloc(sizeof(char) * (size + 1));
		(*result)[0] = '\0';
		if (nbr < 0)
			ft_strcat_char(*result, '-');
	}
	ft_strcat_char(*result, '0' + (ft_abs(nbr) % 10));
}

char	*ft_itoa(int n)
{
	char	*result;

	itoa_2(n, 1, &result);
	return (result);
}
