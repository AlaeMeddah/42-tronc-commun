/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ameddah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:30:38 by ameddah           #+#    #+#             */
/*   Updated: 2024/03/12 14:06:15 by ameddah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_ptr(unsigned long long n)
{
	int			i;
	static char	base[] = "0123456789abcdef";

	if (n == 0)
		return (ft_print_str("(nil)"));
	i = 0;
	if (n >= 16)
		i += ft_print_ptr(n / 16);
	i += ft_print_char(base[n % 16]);
	return (i);
}
