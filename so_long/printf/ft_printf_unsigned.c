/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:30:41 by ameddah           #+#    #+#             */
/*   Updated: 2024/11/21 17:30:36 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	count_size_(unsigned long nb)
{
	size_t	size;

	size = 0;
	if (nb == 0)
		size = 1;
	else
	{
		while (nb)
		{
			nb = nb / 10;
			size++;
		}
	}
	return (size);
}

static char	*ft_uitoa(unsigned int n)
{
	size_t			size;
	unsigned long	nb;
	char			*str;

	size = count_size_((unsigned long)n);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	nb = (unsigned long)n;
	str[size] = '\0';
	while (size > 0)
	{
		str[size - 1] = nb % 10 + '0';
		nb = nb / 10;
		size--;
	}
	return (str);
}

static int	ft_print_unsigned_2(t_flags flags, int *len)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	if (flags.precision > *len)
	{
		y = flags.precision - *len;
		*len = flags.precision;
	}
	if (flags.min_width > *len && !flags.left_justify)
	{
		if (flags.zero_padded && flags.precision == -1)
			i += ft_padding(flags, *len, '0');
		else
			i += ft_padding(flags, *len, ' ');
	}
	while (y-- != 0)
		i += ft_print_char('0');
	return (i);
}

int	ft_print_unsigned(unsigned int n, t_flags flags)
{
	int		i;
	int		len;
	char	*num;

	i = 0;
	if (n == 0 && flags.precision == 0)
		num = ft_strdup("");
	else
		num = ft_uitoa(n);
	len = ft_strlen(num);
	i += ft_print_unsigned_2(flags, &len);
	i += ft_print_str(num);
	if (flags.min_width > len && flags.left_justify)
		i += ft_padding(flags, len, ' ');
	free(num);
	return (i);
}
