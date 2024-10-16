/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:56:34 by almeddah          #+#    #+#             */
/*   Updated: 2024/10/14 15:58:03 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	bzero(void *s, size_t n)
{
	unsigned char	*s_;
	size_t			i;

	i = 0;
	s_ = (unsigned char *)s;
	while (i < n)
	{
		s_[i] = '0';
		i++;
	}
	return (s);
}
