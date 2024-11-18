/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:30:49 by ameddah           #+#    #+#             */
/*   Updated: 2024/11/18 17:02:32 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include "stdarg.h"
# include <limits.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_flags
{
	int		left_justify;
	int		sign;
	int		zero_padded;
	int		space;
	int		min_width;
	int		precision;
	int		form;
	char	format_identifier;
}			t_flags;

int			ft_printf(const char *format, ...);
int			ft_eval_format(va_list args, t_flags flags);
int			ft_print_char(int c);
int			ft_print_str(char *str);
int			ft_print_str_flags(char *str, t_flags flags);
int			ft_print_nbr(int n);
int			ft_print_unsigned(unsigned int n);
int			ft_print_hex(unsigned int n, const char format);
int			ft_print_ptr(unsigned long long n, t_flags flags);
void		ft_eval_flags(const char *format, t_flags *flags, int *i);
void		ft_reset_flags(t_flags *flags);

#endif
