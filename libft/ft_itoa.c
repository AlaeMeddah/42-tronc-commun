/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:43:41 by almeddah          #+#    #+#             */
/*   Updated: 2024/10/16 17:11:07 by alae             ###   ########.fr       */
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

static int	itoa_2(int nbr, int size, char **result)
{
	if (nbr == -2147483648)
	{
		if (!itoa_2(nbr / 10, size + 1, result))
			return (0);
		ft_strcat_char(*result, '0' + ft_abs(nbr % 10));
		return (1);
	}
	if (ft_abs(nbr) >= 10)
		if (!itoa_2(nbr / 10, size + 1, result))
			return (0);
	if (ft_abs(nbr) < 10)
	{
		if (nbr < 0)
			size++;
		*result = malloc(sizeof(char) * (size + 1));
		if (!(*result))
			return (0);
		(*result)[0] = '\0';
		if (nbr < 0)
			ft_strcat_char(*result, '-');
	}
	ft_strcat_char(*result, '0' + (ft_abs(nbr) % 10));
	return (1);
}

char	*ft_itoa(int n)
{
	char	*result;

	if (!itoa_2(n, 1, &result))
		return (0);
	return (result);
}
