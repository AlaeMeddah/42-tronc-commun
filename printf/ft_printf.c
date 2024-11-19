/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:30:44 by ameddah           #+#    #+#             */
/*   Updated: 2024/11/19 18:04:18 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_char(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_padding(t_flags flags, int len, char c)
{
	int	i;

	i = 0;
	while (len + i < flags.min_width)
		i += ft_print_char(c);
	return (i);
}

int	ft_print_char_flags(int c, t_flags flags)
{
	int	i;

	i = 0;
	if (flags.min_width > 1 && !flags.left_justify)
		i += ft_padding(flags, 1, ' ');
	i += ft_print_char(c);
	if (flags.min_width > 1 && flags.left_justify)
		i += ft_padding(flags, 1, ' ');
	return (i);
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

int	ft_print_str_flags(char *str, t_flags flags)
{
	int	i;
	int	y;
	int	len;

	if (!str)
		return (ft_print_str_flags("(null)", flags));
	i = 0;
	len = ft_strlen(str);
	if (flags.precision != -1 && flags.precision < len)
		len = flags.precision;
	if (flags.precision == -1)
		flags.precision = len;
	if (flags.min_width > len && !flags.left_justify)
		i += ft_padding(flags, len, ' ');
	y = 0;
	while (str[y] && y < flags.precision)
	{
		ft_print_char(str[y]);
		y++;
	}
	if (flags.min_width > len && flags.left_justify)
		i += ft_padding(flags, len, ' ');
	return (i + y);
}

int	ft_eval_format(va_list args, t_flags flags)
{
	int	nb_char;

	nb_char = 0;
	if (flags.format_identifier == 'c')
		nb_char += ft_print_char_flags(va_arg(args, int), flags);
	else if (flags.format_identifier == 's')
		nb_char += ft_print_str_flags(va_arg(args, char *), flags);
	else if (flags.format_identifier == 'p')
		nb_char += ft_print_ptr(va_arg(args, unsigned long long), flags);
	else if (flags.format_identifier == 'd' || flags.format_identifier == 'i')
		nb_char += ft_print_nbr(va_arg(args, int), flags);
	else if (flags.format_identifier == 'u')
		nb_char += ft_print_unsigned(va_arg(args, unsigned int), flags);
	else if (flags.format_identifier == 'x' || flags.format_identifier == 'X')
		nb_char += ft_print_hex(va_arg(args, unsigned int), flags);
	else if (flags.format_identifier == '%')
		nb_char += ft_print_char('%');
	return (nb_char);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		nb_char;
	va_list	args;
	t_flags	flags;

	va_start(args, format);
	i = -1;
	nb_char = 0;
	while (format[++i])
	{
		if (format[i] == '%')
		{
			i++;
			ft_reset_flags(&flags);
			ft_eval_flags(format, &flags, &i);
			nb_char += ft_eval_format(args, flags);
		}
		else
			nb_char += ft_print_char(format[i]);
	}
	va_end(args);
	return (nb_char);
}

// int	main(void)
// {
// 	ft_printf("%.0i\n", 0);
// 	ft_printf("%.i\n", 0);
// 	ft_printf("%5.0i\n", 0);
// 	ft_printf("%5.i\n", 0);
// 	ft_printf("%-5.0i\n", 0);
// 	ft_printf("%-5.i\n", 0);
// 	ft_printf("%.0d\n", 0);
// 	ft_printf("%.d\n", 0);
// 	ft_printf("%5.0d\n", 0);
// 	ft_printf("%5.d\n", 0);
// 	ft_printf("%-5.0d\n", 0);
// 	ft_printf("%-5.d\n", 0);
// 	ft_printf("%.0u\n", 0);
// 	ft_printf("%.u\n", 0);
// 	ft_printf("%5.0u\n", 0);
// 	return (0);
// }