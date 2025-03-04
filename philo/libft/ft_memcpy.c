/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:22:08 by almeddah          #+#    #+#             */
/*   Updated: 2024/10/17 12:37:31 by almeddah         ###   ########.fr       */
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
