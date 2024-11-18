/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:30:38 by ameddah           #+#    #+#             */
/*   Updated: 2024/11/18 16:35:32 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_strncat(char *dest, const char *src, unsigned int nb)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j] && j < nb)
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

int	ptr_to_str(unsigned long long n, int size, char **ptr)
{
	static char	base[] = "0123456789abcdef";

	if (n >= 16)
	{
		if (!ptr_to_str(n / 16, size + 1, ptr))
			return (0);
	}
	if (n < 16)
	{
		*ptr = malloc(sizeof(char) * (size + 1));
		if (!(*ptr))
			return (0);
		(*ptr)[0] = '\0';
	}
	ft_strncat(*ptr, &(base[n % 16]), 1);
	return (1);
}

int	ft_print_ptr(unsigned long long n, t_flags flags)
{
	int		i;
	char	*ptr;
	char	*result;

	if (n == 0)
		return (ft_print_str_flags("(nil)", flags));
	if (!ptr_to_str(n, 1, &ptr))
		return (0);
	result = ft_strjoin("0x", ptr);
	free(ptr);
	i = ft_print_str_flags(result, flags);
	free(result);
	return (i);
}
