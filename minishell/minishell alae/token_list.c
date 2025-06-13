/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:17:00 by alae              #+#    #+#             */
/*   Updated: 2025/06/13 09:37:08 by alae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_new_list(char **data, int *i, int j)
{
	int		l;
	char	**new_data;

	*i += 10;
	new_data = malloc(sizeof(char *) * (*i));
	if (!new_data)
	{
		printf("new data allocation error\n");
		free_char_list(data);
		return (NULL);
	}
	l = 0;
	while (l <= j)
	{
		new_data[l] = data[l];
		l++;
	}
	free(data);
	return (new_data);
}

int	quoted_token(char **prompt, int k, char **data, int j)
{
	int	x;

	x = 0;
	if ((*prompt)[k] == '\'' || (*prompt)[k] == '"')
	{
		x = nb_quoted_char(*prompt + k);
		if (!x)
		{
			printf("unclosed quote\n");
			data[j] = NULL;
			free_char_list(data);
			return (-1);
		}
	}
	return (x);
}

int	parse_prompt(char **prompt, char **data, int j)
{
	int	k;

	k = 0;
	while (**prompt && ft_isspace(**prompt))
		(*prompt)++;
	if (**prompt == '|')
		k++;
	else if (**prompt == '>' || **prompt == '<')
	{
		k++;
		if (*(*prompt + 1) == **prompt)
			k++;
	}
	else
	{
		while ((*prompt)[k] && !ft_isspace((*prompt)[k]) && (*prompt)[k] != '|'
			&& (*prompt)[k] != '<' && (*prompt)[k] != '>')
			k += quoted_token(prompt, k, data, j) + 1;
	}
	return (k);
}

int	copy_to_list(char **prompt, int k, int j, char **data)
{
	if (k)
	{
		data[j] = ft_strncpy(*prompt, k);
		if (!data[j])
		{
			free_char_list(data);
			return (-1);
		}
		j++;
	}
	*prompt += k;
	data[j] = NULL;
	return (j);
}

char	**create_token_list(char *prompt)
{
	char	**data;
	int		i;
	int		j;
	int		k;

	i = 10;
	j = 0;
	data = malloc(sizeof(char *) * i);
	if (!data)
	{
		printf("data allocation error\n");
		return (NULL);
	}
	while (*prompt)
	{
		if (j >= i - 1)
			data = create_new_list(data, &i, j);
		k = parse_prompt(&prompt, data, j);
		if (k == -1)
			return (NULL);
		j = copy_to_list(&prompt, k, j, data);
		if (j == -1)
			return (NULL);
	}
	return (data);
}
