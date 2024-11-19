/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:30:35 by ameddah           #+#    #+#             */
/*   Updated: 2024/11/19 18:09:45 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// static size_t	count_size(long nb)
// {
// 	size_t	size;

// 	size = 0;
// 	if (nb < 0)
// 	{
// 		nb = nb * (-1);
// 		size = 1;
// 	}
// 	if (nb == 0)
// 		size = 1;
// 	else
// 	{
// 		while (nb)
// 		{
// 			nb = nb / 10;
// 			size++;
// 		}
// 	}
// 	return (size);
// }

// static char	*ft_itoa(int n)
// {
// 	size_t	size;
// 	long	nb;
// 	char	*str;
// 	int		is_negative;

// 	size = count_size((long) n);
// 	str = (char *) malloc(sizeof(char) * (size + 1));
// 	if (str == NULL)
// 		return (NULL);
// 	nb = (long) n;
// 	is_negative = 0;
// 	if (nb < 0)
// 	{
// 		nb = nb * (-1);
// 		str[0] = '-';
// 		is_negative = 1;
// 	}
// 	str[size] = '\0';
// 	while (size > (size_t) is_negative)
// 	{
// 		str[size - 1] = nb % 10 + '0';
// 		nb = nb / 10;
// 		size--;
// 	}
// 	return (str);
// }

char	*ft_flags_sign_space(char *num, t_flags flags)
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

int	ft_print_nbr(int n, t_flags flags)
{
	int		i;
	int		j;
	int		y;
	int		len;
	char	*num;

	i = 0;
	j = 0;
	y = 0;
	num = ft_flags_sign_space(ft_itoa(n), flags);
	// printf("%s\n", ft_itoa(n));
	// printf("%s\n", num);
	len = ft_strlen(num);
	if (flags.precision >= len)
	{
		if (*num == '-' || *num == '+' || *num == ' ')
			flags.precision += 1;
		y = flags.precision - len;
		len = flags.precision;
	}
	if (flags.min_width > len && !flags.left_justify && !(flags.zero_padded
			&& flags.precision == -1))
		i += ft_padding(flags, len, ' ');
	if (*num == '-' || *num == '+' || *num == ' ')
	{
		i = +ft_print_char(*num);
		j = 1;
	}
	if (flags.min_width > len && !flags.left_justify && flags.zero_padded
		&& flags.precision == -1)
		i += ft_padding(flags, len, '0');
	while (y-- != 0)
		i += ft_print_char('0');
	i += ft_print_str(num + j);
	if (flags.min_width > len && flags.left_justify)
		i += ft_padding(flags, len, ' ');
	free(num);
	return (i);
}
