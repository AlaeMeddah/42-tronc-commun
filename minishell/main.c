/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:27:05 by almeddah          #+#    #+#             */
/*   Updated: 2025/04/23 14:49:19 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	*ft_last(void *list)
{
	t_list	*node;

	node = (t_list *)list;
	if (node)
	{
		while (node->next)
			node = node->next;
	}
	return ((void *)node);
}

void	ft_add_back(void **list, void *new)
{
	t_list	*last;

	if (new)
	{
		if (*list == NULL)
			*list = new;
		else
		{
			last = (t_list *)ft_last(*list);
			last->next = (t_list *)new;
		}
	}
}

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
	if (!ft_strcmp(str1, "<"))
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
	if (!ft_strcmp(str1, ">>"))
		new_redir->append = 1;
	new_redir->next = NULL;
	return (new_redir);
}

t_command	*create_command_list(char **data)
{
	t_command	*command_list;
	t_command	*new_command;
	int			i;
	int			j;

	command_list = NULL;
	while (*data)
	{
		if (!ft_strcmp(*data, "|"))
			return (NULL);
		i = 0;
		while (data[i] && ft_strcmp(data[i], "|") != 0)
			i++;
		new_command = malloc(sizeof(t_command));
		if (!new_command)
			return (0);
		new_command->next = NULL;
		new_command->input_redirect = NULL;
		new_command->output_redirect = NULL;
		new_command->argv = malloc(sizeof(char *) * (i + 1));
		i = 0;
		j = 0;
		while (data[i] && ft_strcmp(data[i], "|") != 0)
		{
			if (!ft_strcmp(data[i], "<") || !ft_strcmp(data[i], "<<"))
			{
				if (!data[i + 1])
					return (NULL);
				else
					ft_add_back((void **)&(new_command->input_redirect),
						create_input_redirect(data[i], data[i + 1]));
				i += 2;
			}
			else if (!ft_strcmp(data[i], ">") || !ft_strcmp(data[i], ">>"))
			{
				if (!data[i + 1])
					return (NULL);
				else
					ft_add_back((void **)&(new_command->output_redirect),
						create_output_redirect(data[i], data[i + 1]));
				i += 2;
			}
			else
			{
				new_command->argv[j] = ft_strdup(data[i]);
				j++;
				i++;
			}
		}
		new_command->argv[j] = NULL;
		ft_add_back((void **)&command_list, new_command);
		data += i;
		if (*data)
			data++;
	}
	return (command_list);
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

void	display_input_redirects(t_input_redirect *input_redirect)
{
	while (input_redirect)
	{
		if (input_redirect->delim)
			printf("<< %s ", input_redirect->delim);
		else
			printf("< %s ", input_redirect->file);
		input_redirect = input_redirect->next;
	}
}

void	display_output_redirects(t_output_redirect *output_redirect)
{
	while (output_redirect)
	{
		if (output_redirect->append)
			printf(">> %s ", output_redirect->file);
		else
			printf("> %s ", output_redirect->file);
		output_redirect = output_redirect->next;
	}
}

void	display_command(t_command *cmd)
{
	int	i;

	if (!cmd)
	{
		printf("No command\n");
		return ;
	}
	// Display input redirects
	display_input_redirects(cmd->input_redirect);
	// Display output redirects
	display_output_redirects(cmd->output_redirect);
	// Display arguments
	if (cmd->argv)
	{
		i = 0;
		while (cmd->argv[i])
		{
			printf("%s ", cmd->argv[i]);
			i++;
		}
	}
	printf("\n");
}

void	display_command_list(t_command *cmd_list)
{
	while (cmd_list)
	{
		display_command(cmd_list);
		cmd_list = cmd_list->next;
	}
}

#include <stdlib.h>

void	free_input_redirect(t_input_redirect *input_redirect)
{
	t_input_redirect	*tmp;

	while (input_redirect)
	{
		tmp = input_redirect;
		if (input_redirect->file)
			free(input_redirect->file);
		if (input_redirect->delim)
			free(input_redirect->delim);
		input_redirect = input_redirect->next;
		free(tmp);
	}
}

void	free_output_redirect(t_output_redirect *output_redirect)
{
	t_output_redirect	*tmp;

	while (output_redirect)
	{
		tmp = output_redirect;
		if (output_redirect->file)
			free(output_redirect->file);
		output_redirect = output_redirect->next;
		free(tmp);
	}
}

void	free_command(t_command *cmd)
{
	int	i;

	if (cmd)
	{
		if (cmd->argv)
		{
			i = 0;
			while (cmd->argv[i])
			{
				free(cmd->argv[i]);
				i++;
			}
			free(cmd->argv);
		}
		free_input_redirect(cmd->input_redirect);
		free_output_redirect(cmd->output_redirect);
		free(cmd);
	}
}

void	free_command_list(t_command *cmd_list)
{
	t_command	*tmp;

	while (cmd_list)
	{
		tmp = cmd_list;
		cmd_list = cmd_list->next;
		free_command(tmp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*prompt;
	char		**data;
	t_command	*cmd_list;
	int			i;

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
			cmd_list = create_command_list(data);
			i = 0;
			while (data[i])
			{
				// printf("%s\n", data[i]);
				free(data[i]);
				i++;
			}
			free(data);
			if (!cmd_list)
				return (0);
			display_command_list(cmd_list);
			free_command_list(cmd_list);
		}
		free(prompt);
	}
	return (0);
}
