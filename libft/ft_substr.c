/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:49:18 by almeddah          #+#    #+#             */
/*   Updated: 2024/10/16 11:48:56 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	len_s;
	char	*result;

	i = 0;
	len_s = ft_strlen(s);
	if (start > len_s)
		len = 0;
	else if (len > len_s - start)
		len = len_s - start;
	result = malloc(len + 1);
	if (!result)
		return (0);
	while ((s + start)[i] && i < len)
	{
		result[i] = (s + start)[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
