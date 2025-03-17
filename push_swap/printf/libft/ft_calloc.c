/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ameddah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:11:33 by ameddah           #+#    #+#             */
/*   Updated: 2023/11/24 09:44:22 by ameddah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;

	if (nmemb == 0 || size == 0)
	{
		result = malloc(0);
		if (result != NULL)
			*((char *)result) = 0;
	}
	else
	{
		result = malloc(nmemb * size);
		if (result != NULL)
			ft_memset(result, 0, nmemb * size);
	}
	return (result);
}
