/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ameddah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:17:06 by ameddah           #+#    #+#             */
/*   Updated: 2023/11/27 15:30:55 by ameddah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (*s1 && i < n)
	{
		if ((unsigned char)*s1 < (unsigned char)*s2)
			return (-1);
		else if ((unsigned char)*s1 > (unsigned char)*s2)
			return (1);
		s1++;
		s2++;
		i++;
	}
	if (*s1 != *s2 && i < n)
		return (-1);
	return (0);
}
