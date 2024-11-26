/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:30:35 by ameddah           #+#    #+#             */
/*   Updated: 2024/11/21 18:12:53 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static char	*ft_flags_sign_space(char *num, t_flags flags)
{
	char	*result;

	if ((flags.sign || flags.space) && *num != '-')
	{
		if (flags.sign)
		{
			result = ft_strjoin("+", num);
			free(num);
		}
		else
		{
			result = ft_strjoin(" ", num);
			free(num);
		}
	}
	else
		result = num;
	return (result);
}

static int	ft_print_nbr_2(char *num, t_flags *flags, int *len)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	if ((*flags).precision >= *len)
	{
		if (*num == '-' || *num == '+' || *num == ' ')
			(*flags).precision += 1;
		y = (*flags).precision - *len;
		*len = (*flags).precision;
	}
	if ((*flags).min_width > *len && !(*flags).left_justify
		&& !((*flags).zero_padded && (*flags).precision == -1))
		i += ft_padding((*flags), *len, ' ');
	if (*num == '-' || *num == '+' || *num == ' ')
		i = +ft_print_char(*num);
	if ((*flags).min_width > *len && !(*flags).left_justify
		&& (*flags).zero_padded && (*flags).precision == -1)
		i += ft_padding((*flags), *len, '0');
	while (y-- != 0)
		i += ft_print_char('0');
	return (i);
}

int	ft_print_nbr(int n, t_flags flags)
{
	int		i;
	int		len;
	char	*num;

	i = 0;
	if (n == 0 && flags.precision == 0)
		num = ft_strdup("");
	else
		num = ft_flags_sign_space(ft_itoa(n), flags);
	len = ft_strlen(num);
	i += ft_print_nbr_2(num, &flags, &len);
	if (*num == '-' || *num == '+' || *num == ' ')
		i += ft_print_str(num + 1);
	else
		i += ft_print_str(num);
	if (flags.min_width > len && flags.left_justify)
		i += ft_padding(flags, len, ' ');
	free(num);
	return (i);
}
