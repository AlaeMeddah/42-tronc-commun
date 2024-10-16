/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:29:11 by almeddah          #+#    #+#             */
/*   Updated: 2024/10/14 15:36:28 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_;
	unsigned char	*src_;
	size_t			i;

	src_ = (unsigned char *)src;
	dest_ = (unsigned char *)dest;
	if (dest > src)
	{
		while (n--)
			*(dest_ + n) = *(src_ + n);
	}
	else
	{
		i = 0;
		while (i < n)
		{
			*(dest_ + i) = *(src_ + i);
			i++;
		}
	}
	return (dest);
}
