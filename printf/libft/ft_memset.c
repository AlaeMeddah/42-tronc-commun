/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:52:42 by almeddah          #+#    #+#             */
/*   Updated: 2024/10/17 12:37:46 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*s_;
	unsigned char	c_;
	size_t			i;

	i = 0;
	c_ = (unsigned char)c;
	s_ = (unsigned char *)s;
	while (i < n)
	{
		s_[i] = c_;
		i++;
	}
	return (s);
}
