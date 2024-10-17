/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:50:17 by almeddah          #+#    #+#             */
/*   Updated: 2024/10/17 12:38:14 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	i;
	size_t	j;

	j = 0;
	if (!*to_find)
		return ((char *)str);
	if (!n)
		return (0);
	while (str[j] && j < n)
	{
		i = 0;
		while (str[j + i] == to_find[i] && to_find[i] && j + i < n)
			i++;
		if (!to_find[i])
			return ((char *)(str + j));
		j++;
	}
	return (0);
}
