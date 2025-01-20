/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:03:06 by almeddah          #+#    #+#             */
/*   Updated: 2024/10/17 12:37:19 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_;
	unsigned char	c_;
	size_t			i;

	i = 0;
	c_ = (unsigned char)c;
	s_ = (unsigned char *)s;
	while (i < n)
	{
		if (s_[i] == c_)
			return ((void *)(s_ + i));
		i++;
	}
	return (0);
}
