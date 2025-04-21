/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:27:05 by almeddah          #+#    #+#             */
/*   Updated: 2025/04/21 17:13:50 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_token	*create_token(int n)
// {
// 	t_token	*new_token;

// 	new_token = malloc(sizeof(t_token));
// 	if (!new_token)
// 		return (0);
// 	new_token->cmd_number = n;
// 	new_token->cmd = NULL;
// 	new_token->args = NULL;
// 	new_token->infile = NULL;
// 	new_token->outfile = NULL;
// 	new_token->next = NULL;
// 	return (new_token);
// }

// t_token	*create_token_list(char **data)
// {
// 	t_token *token_list;
// 	t_token *new_token;
// 	int cmd_nb = 1;

// 	token_list = NULL;

// }

char	*ft_strncpy(char *src, int n)
{
	int		i;
	char	*dest;

	i = 0;
	dest = malloc(sizeof(char) * (n + 1));
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**create_data(char *prompt)
{
	char	**data;
	int		i;
	int		k;

	i = 0;
	k = 0;
	data = malloc(sizeof(char *) * 20);
	while (*prompt)
	{
		k = 0;
		while (*prompt && ft_isspace(*prompt))
			prompt++;
		if (*prompt == '\'' || *prompt == '"')
		{
			k++;
			while (prompt[k] != *prompt)
			{
				if (!prompt[k])
				{
					printf("unclosed quote\n");
					return (NULL);
				}
				k++;
			}
			k++;
		}
		else if (*prompt == '|')
			k++;
		else
		{
			while (prompt[k] && !ft_isspace(prompt[k]) && prompt[k] != '|'
				&& prompt[k] != '\'' && prompt[k] != '"')
				k++;
		}
		data[i] = ft_strncpy(prompt, k);
		prompt += k;
		i++;
	}
	data[i] = NULL;
	return (data);
}

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	char	**data;
	int		i;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		prompt = readline("$> ");
		if (!prompt)
			break ;
		if (*prompt)
		{
			add_history(prompt);
			data = create_data(prompt);
			if (!data)
				return (0);
		}
		i = 0;
		while (data[i])
		{
			printf("%s\n", data[i]);
			free(data[i]);
			i++;
		}
		free(data);
		free(prompt);
	}
	return (0);
}
