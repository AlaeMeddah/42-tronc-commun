/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:22:08 by almeddah          #+#    #+#             */
/*   Updated: 2024/10/16 17:06:06 by alae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_;
	unsigned char	*src_;
	size_t			i;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	src_ = (unsigned char *)src;
	dest_ = (unsigned char *)dest;
	while (i < n)
	{
		dest_[i] = src_[i];
		i++;
	}
	return (dest);
}
