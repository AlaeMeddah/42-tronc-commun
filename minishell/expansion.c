/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:08:46 by almeddah          #+#    #+#             */
/*   Updated: 2025/06/13 18:09:40 by almeddah         ###   ########.fr       */
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
	int	j;

	i = 0;
	while (*str)
	{
		if (*str == '\'')
		{
			i += nb_quoted_char(str) - 1;
			str += nb_quoted_char(str) + 1;
		}
		else if (*str == '$')
		{
			j = 0;
			i += ft_strlen(expand_variable(str, data, &j));
			str += j;
		}
		else
		{
			if (*str != '"')
				i++;
			str++;
		}
	}
	return (i);
}

void	test(char *result, char *str, t_data data)
{
	char	*expanded;
	int		x;

	while (*str)
	{
		if (*str == '\'')
		{
			str++;
			while (*str != '\'')
				*result++ = *str++;
			str++;
		}
		else if (*str == '"')
			str++;
		else if (*str == '$')
		{
			x = 0;
			expanded = expand_variable(str, data, &x);
			while (*expanded)
				*result++ = *expanded++;
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
	result = malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	test(result, str, data);
	result[size] = '\0';
	return (result);
}
