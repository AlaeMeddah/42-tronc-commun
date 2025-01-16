/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ameddah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:30:44 by ameddah           #+#    #+#             */
/*   Updated: 2024/04/08 16:03:30 by ameddah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_print_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_print_str("(null)"));
	while (str[i])
	{
		ft_print_char(str[i]);
		i++;
	}
	return (i);
}

int	ft_eval_format(va_list args, const char format)
{
	int					nb_char;
	unsigned long long	n;

	nb_char = 0;
	if (format == 'c')
		nb_char += ft_print_char(va_arg(args, int));
	else if (format == 's')
		nb_char += ft_print_str(va_arg(args, char *));
	else if (format == 'p')
	{
		n = va_arg(args, unsigned long long);
		if (n != 0)
			nb_char += ft_print_str("0x");
		nb_char += ft_print_ptr(n);
	}
	else if (format == 'd' || format == 'i')
		nb_char += ft_print_nbr(va_arg(args, int));
	else if (format == 'u')
		nb_char += ft_print_unsigned(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		nb_char += ft_print_hex(va_arg(args, unsigned int), format);
	else if (format == '%')
		nb_char += ft_print_char('%');
	return (nb_char);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		nb_char;
	va_list	args;

	va_start(args, format);
	i = -1;
	nb_char = 0;
	while (format[++i])
	{
		if (format[i] == '%')
		{
			nb_char += ft_eval_format(args, format[i + 1]);
			i++;
		}
		else
			nb_char += ft_print_char(format[i]);
	}
	va_end(args);
	return (nb_char);
}
