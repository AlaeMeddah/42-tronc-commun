/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ameddah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:30:31 by ameddah           #+#    #+#             */
/*   Updated: 2024/03/10 21:27:45 by ameddah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_hex_len(unsigned	int n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		len++;
		n = n / 16;
	}
	return (len);
}

int	ft_print_hex(unsigned int n, const char format)
{
	static char	lower[] = "0123456789abcdef";
	static char	upper[] = "0123456789ABCDEF";

	if (n == 0)
		return (ft_print_char('0'));
	if (n >= 16)
		ft_print_hex(n / 16, format);
	if (format == 'x')
		ft_print_char(lower[n % 16]);
	else
		ft_print_char(upper[n % 16]);
	return (ft_hex_len(n));
}
