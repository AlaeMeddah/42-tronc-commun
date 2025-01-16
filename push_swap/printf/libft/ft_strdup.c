/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ameddah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:15:10 by ameddah           #+#    #+#             */
/*   Updated: 2023/11/22 10:15:15 by ameddah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	char	*dest_;

	dest_ = dest;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (dest_);
}

char	*ft_strdup(const char *src)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(src);
	new_str = (char *)malloc(len + 1);
	if (new_str != NULL)
	{
		ft_strcpy(new_str, src);
	}
	return (new_str);
}
