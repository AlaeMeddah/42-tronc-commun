/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:08:46 by almeddah          #+#    #+#             */
/*   Updated: 2025/08/18 20:39:27 by alae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variable(char *str, t_data data, int *i)
{
	int	j;
	int	k;

	j = 0;
	str++;
	if (str[j] == '?')
	{
		*i += 2;
		return (ft_itoa(data.exit_code));
	}
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
		j++;
	*i += j + 1;
	if (!j)
		return ("$");
	if (j)
	{
		k = -1;
		while (data.envp[++k])
		{
			if (!ft_strncmp(data.envp[k], str, j) && data.envp[k][j] == '=')
				return (data.envp[k] + j + 1);
		}
	}
	return ("");
}

int	expanded_token_size(char *str, t_data data)
{
	int	i;
	int	d_quote;

	d_quote = 0;
	i = 0;
	while (*str)
	{
		if (*str == '\'' && !d_quote)
		{
			i += nb_quoted_char(str) - 1;
			str += nb_quoted_char(str) + 1;
		}
		else if (*str == '$')
			norm_function3(&i, &str, data);
		else
			norm_function2(&str, &i, &d_quote);
	}
	return (i);
}

void	test(char *result, char *str, t_data data)
{
	char	*expanded;
	int		x;
	int		d_quote;
	int		y;

	d_quote = 0;
	while (*str)
	{
		if ((*str == '\'' && !d_quote) || *str == '"')
			norm_function1(&str, &d_quote, &result);
		else if (*str == '$')
		{
			x = 0;
			y = 0;
			expanded = expand_variable(str, data, &x);
			while (expanded[y])
				*result++ = expanded[y++];
			if (*(str + 1) == '?')
				free(expanded);
			str += x;
		}
		else
			*result++ = *str++;
	}
}

char	*expand_token(char *str, t_data data)
{
	char	*result;
	int		size;

	size = expanded_token_size(str, data);
	if (!size)
		return (NULL);
	result = malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	test(result, str, data);
	result[size] = '\0';
	return (result);
}
