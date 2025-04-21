/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:27:05 by almeddah          #+#    #+#             */
/*   Updated: 2025/04/21 18:39:43 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_input_redirect	*create_input_redirect(char *str1, char *str2)
{
	t_input_redirect	*new_redir;

	if (!str2)
		return (NULL);
	new_redir = malloc(sizeof(t_input_redirect));
	if (!new_redir)
		return (NULL);
	new_redir->file = NULL;
	new_redir->delim = NULL;
	if (!ft_strncmp(str1, "<", 2))
		new_redir->file = ft_strdup(str2);
	else
		new_redir->delim = ft_strdup(str2);
	new_redir->next = NULL;
	return (new_redir);
}

t_output_redirect	*create_output_redirect(char *str1, char *str2)
{
	t_output_redirect	*new_redir;

	if (!str2)
		return (NULL);
	new_redir = malloc(sizeof(t_output_redirect));
	if (!new_redir)
		return (NULL);
	new_redir->file = ft_strdup(str2);
	new_redir->append = 0;
	if (!ft_strncmp(str1, ">>", 2))
		new_redir->append = 1;
	new_redir->next = NULL;
	return (new_redir);
}

t_command	*create_command(void)
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_command));
	if (!new_command)
		return (0);
	return (new_command);
}

t_command	*create_command_list(char **data)
{
	t_command	*command_list;
	t_command	*new_command;

	command_list = NULL;
}

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
