/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:04:03 by almeddah          #+#    #+#             */
/*   Updated: 2024/11/21 18:13:00 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

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

	if (!str && (flags.precision >= (int)ft_strlen("(null)")
			|| flags.precision == -1))
		return (ft_print_str_flags("(null)", flags));
	else if (!str)
		return (ft_print_str_flags("", flags));
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
		ft_print_char(str[y++]);
	if (flags.min_width > len && flags.left_justify)
		i += ft_padding(flags, len, ' ');
	return (i + y);
}
