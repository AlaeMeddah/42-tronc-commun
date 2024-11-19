/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:30:49 by ameddah           #+#    #+#             */
/*   Updated: 2024/11/19 18:15:59 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include "limits.h"
# include "stdarg.h"
# include "stdint.h"
# include "stdio.h"
# include "stdlib.h"
# include "unistd.h"

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
int			ft_print_nbr(int n, t_flags flags);
int			ft_print_unsigned(unsigned int n, t_flags flags);
int			ft_print_hex(unsigned int n, t_flags flags);
int			ft_print_ptr(unsigned long long n, t_flags flags);
void		ft_eval_flags(const char *format, t_flags *flags, int *i);
void		ft_reset_flags(t_flags *flags);
int			is_in(char c, char *s);
int			ft_padding(t_flags flags, int len, char c);
#endif
