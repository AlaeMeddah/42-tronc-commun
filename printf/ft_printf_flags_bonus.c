/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flags_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 13:32:04 by almeddah          #+#    #+#             */
/*   Updated: 2024/11/21 18:12:42 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	is_in(char c, char *s)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

void	ft_reset_flags(t_flags *flags)
{
	(*flags).left_justify = 0;
	(*flags).sign = 0;
	(*flags).zero_padded = 0;
	(*flags).space = 0;
	(*flags).min_width = 0;
	(*flags).precision = -1;
	(*flags).form = 0;
	(*flags).format_identifier = '\0';
}

void	ft_eval_flags(const char *format, t_flags *flags, int *i)
{
	while (is_in(format[*i], "-+ #0"))
	{
		if (format[*i] == '-')
			(*flags).left_justify = 1;
		if (format[*i] == '+')
			(*flags).sign = 1;
		if (format[*i] == ' ')
			(*flags).space = 1;
		if (format[*i] == '#')
			(*flags).form = 1;
		if (format[*i] == '0')
			(*flags).zero_padded = 1;
		(*i)++;
	}
	if (ft_isdigit(format[*i]))
		(*flags).min_width = ft_atoi(format + *i);
	while (ft_isdigit(format[*i]))
		(*i)++;
	if (format[*i] == '.')
	{
		(*flags).precision = ft_atoi(format + ++(*i));
		while (ft_isdigit(format[*i]))
			(*i)++;
	}
	(*flags).format_identifier = format[*i];
}
