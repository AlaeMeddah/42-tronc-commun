/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:29:11 by almeddah          #+#    #+#             */
/*   Updated: 2024/10/16 17:06:32 by alae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_;
	unsigned char	*src_;
	size_t			i;

	if (dest == NULL && src == NULL)
		return (NULL);
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
