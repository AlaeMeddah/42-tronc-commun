/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:30:38 by ameddah           #+#    #+#             */
/*   Updated: 2024/11/19 18:08:35 by almeddah         ###   ########.fr       */
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

int	to_hex(unsigned long long n, int size, char **ptr, char *base)
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

int	ft_print_hex(unsigned int n, t_flags flags)
{
	int			i;
	int			y;
	int			len;
	char		*hex;
	char		*format;
	static char	lower[] = "0123456789abcdef";
	static char	upper[] = "0123456789ABCDEF";

	if (flags.format_identifier == 'x')
	{
		if (!to_hex(n, 1, &hex, lower))
			return (0);
		format = "0x";
	}
	else
	{
		if (!to_hex(n, 1, &hex, upper))
			return (0);
		format = "0X";
	}
	i = 0;
	y = 0;
	len = ft_strlen(hex);
	if (flags.precision > len)
	{
		y = flags.precision - len;
		len = flags.precision;
	}
	if (flags.form)
		len += 2;
	if (flags.min_width > len && !flags.left_justify)
	{
		if (flags.zero_padded && flags.precision == -1)
			i += ft_padding(flags, len, '0');
		else
			i += ft_padding(flags, len, ' ');
	}
	if (flags.form)
		i += ft_print_str(format);
	while (y-- != 0)
		i += ft_print_char('0');
	i += ft_print_str(hex);
	if (flags.min_width > len && flags.left_justify)
		i += ft_padding(flags, len, ' ');
	free(hex);
	return (i);
}
