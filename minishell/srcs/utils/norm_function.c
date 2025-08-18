/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 20:30:25 by alae              #+#    #+#             */
/*   Updated: 2025/08/18 20:37:05 by alae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	norm_function1(char **str, int *d_quote, char **result)
{
	if (**str == '\'' && !*d_quote)
	{
		(*str)++;
		while (**str != '\'')
			*(*result)++ = *(*str)++;
		(*str)++;
	}
	else if (**str == '"')
	{
		if (!*d_quote)
			*d_quote = 1;
		else
			*d_quote = 0;
		(*str)++;
	}
}

void	norm_function2(char **str, int *i, int *d_quote)
{
	if (**str != '"')
		(*i)++;
	else
	{
		if (!*d_quote)
			*d_quote = 1;
		else
			*d_quote = 0;
	}
	(*str)++;
}

void	norm_function3(int *i, char **str, t_data data)
{
	char	*expanded;
	int		j;

	j = 0;
	expanded = expand_variable(*str, data, &j);
	(*i) += ft_strlen(expanded);
	if (*((*str) + 1) == '?')
		free(expanded);
	(*str) += j;
}
