/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:30:38 by ameddah           #+#    #+#             */
/*   Updated: 2024/11/21 18:12:48 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	to_hex(unsigned long long n, int size, char **ptr, char *base)
{
	if (n >= 16)
	{
		if (!to_hex(n / 16, size + 1, ptr, base))
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
	int			i;
	char		*ptr;
	char		*result;
	static char	base[] = "0123456789abcdef";

	if (n == 0)
		return (ft_print_str_flags("(nil)", flags));
	if (!to_hex(n, 1, &ptr, base))
		return (0);
	result = ft_strjoin("0x", ptr);
	free(ptr);
	i = ft_print_str_flags(result, flags);
	free(result);
	return (i);
}

static char	*ft_print_hex_2(unsigned int n, t_flags flags, char **format)
{
	char		*hex;
	static char	lower[] = "0123456789abcdef";
	static char	upper[] = "0123456789ABCDEF";

	if (n == 0 && flags.precision == 0)
		hex = ft_strdup("");
	else
	{
		if (flags.format_identifier == 'x')
		{
			if (!to_hex(n, 1, &hex, lower))
				return (0);
			*format = "0x";
		}
		else
		{
			if (!to_hex(n, 1, &hex, upper))
				return (0);
			*format = "0X";
		}
	}
	return (hex);
}

int	ft_print_hex_3(t_flags flags, int *len, char *format, unsigned int n)
{
	int	i;

	i = 0;
	if (flags.form)
		*len += 2;
	if (flags.min_width > *len && !flags.left_justify)
	{
		if (flags.zero_padded && flags.precision == -1)
			i += ft_padding(flags, *len, '0');
		else
			i += ft_padding(flags, *len, ' ');
	}
	if (flags.form && n != 0)
		i += ft_print_str(format);
	return (i);
}

int	ft_print_hex(unsigned int n, t_flags flags)
{
	int		i;
	int		y;
	int		len;
	char	*hex;
	char	*format;

	i = 0;
	y = 0;
	hex = ft_print_hex_2(n, flags, &format);
	len = ft_strlen(hex);
	if (flags.precision > len)
	{
		y = flags.precision - len;
		len = flags.precision;
	}
	i += ft_print_hex_3(flags, &len, format, n);
	while (y-- != 0)
		i += ft_print_char('0');
	i += ft_print_str(hex);
	if (flags.min_width > len && flags.left_justify)
		i += ft_padding(flags, len, ' ');
	free(hex);
	return (i);
}
