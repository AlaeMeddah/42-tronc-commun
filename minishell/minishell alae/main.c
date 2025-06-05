/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:27:05 by almeddah          #+#    #+#             */
/*   Updated: 2025/06/05 17:35:42 by alae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variable(char *data, char **envp, int *i)
{
	int	j;
	int	k;

	j = 0;
	data++;
	while (data[j] && (ft_isalnum(data[j]) || data[j] == '_'))
		j++;
	*i += j + 1;
	if (!j)
		return ("$");
	if (j)
	{
		k = 0;
		while (envp[k])
		{
			if (!ft_strncmp(envp[k], data, j) && envp[k][j] == '=')
				return (envp[k] + j + 1);
			k++;
		}
	}
	return ("");
}

int	expanded_token_size(char *data, char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (*data)
	{
		if (*data == '\'')
		{
			i += nb_quoted_char(data) - 1;
			data += nb_quoted_char(data) + 1;
		}
		else if (*data == '$')
		{
			j = 0;
			i += ft_strlen(expand_variable(data, envp, &j));
			data += j;
		}
		else
		{
			if (*data != '"')
				i++;
			data++;
		}
	}
	return (i);
}

void	test(char *result, char *data, char **envp)
{
	char	*expanded;
	int		x;

	while (*data)
	{
		if (*data == '\'')
		{
			data++;
			while (*data != '\'')
				*result++ = *data++;
			data++;
		}
		else if (*data == '"')
			data++;
		else if (*data == '$')
		{
			x = 0;
			expanded = expand_variable(data, envp, &x);
			while (*expanded)
				*result++ = *expanded++;
			data += x;
		}
		else
			*result++ = *data++;
	}
}

char	*expand_token(char *data, char **envp)
{
	char	*result;
	int		size;

	size = expanded_token_size(data, envp);
	result = malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	test(result, data, envp);
	result[size] = '\0';
	return (result);
}

t_command	*create_new_command(t_command *command_list, int i)
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_command));
	if (!new_command)
	{
		printf("command allocation error\n");
		free_command_list(command_list);
		return (NULL);
	}
	new_command->next = NULL;
	new_command->input_redirect = NULL;
	new_command->output_redirect = NULL;
	new_command->argv = malloc(sizeof(char *) * (i + 1));
	if (!new_command->argv)
	{
		printf("command arg allocation error\n");
		free_command_list(command_list);
		return (NULL);
	}
	return (new_command);
}

int	redirection_error(char **data, int i)
{
	if (!data[i + 1] || is_redirection(data[i + 1]) || !ft_strcmp(data[i + 1],
			"|"))
	{
		printf("redirection error\n");
		return (1);
	}
	return (0);
}

int	handle_new_command(char **data, char **envp, int *i, t_command *new_command)
{
	int	j;

	*i = 0;
	j = 0;
	while (data[*i] && ft_strcmp(data[*i], "|"))
	{
		if (is_redirection(data[*i]))
		{
			if (redirection_error(data, *i))
				return (0);
			else
			{
				if (!create_redirect(data, envp, *i, new_command))
					return (0);
			}
			*i += 2;
		}
		else
			new_command->argv[j++] = expand_token(data[(*i)++], envp);
	}
	new_command->argv[j] = NULL;
	return (1);
}

int	add_command_to_list(char **data, char **envp, int *i,
		t_command **command_list)
{
	t_command	*new_command;

	*i = 0;
	while (data[*i] && ft_strcmp(data[*i], "|"))
		(*i)++;
	new_command = create_new_command(*command_list, *i);
	if (!new_command)
		return (0);
	if (!handle_new_command(data, envp, i, new_command))
	{
		free_command_list(*command_list);
		return (0);
	}
	ft_add_back((void **)command_list, new_command);
	return (1);
}

void	*pipe_error(t_command *command_list)
{
	printf("pipe error\n");
	free_command_list(command_list);
	return (NULL);
}

t_command	*create_command_list(char **data, char **envp)
{
	t_command	*command_list;
	int			i;

	command_list = NULL;
	while (*data)
	{
		if (!ft_strcmp(*data, "|"))
			return (pipe_error(command_list));
		if (!add_command_to_list(data, envp, &i, &command_list))
			return (NULL);
		data += i;
		if (*data)
		{
			if (!ft_strcmp(*data, "|") && (!*(data + 1)))
				return (pipe_error(command_list));
			data++;
		}
	}
	return (command_list);
}

int	main(int argc, char **argv, char **envp)
{
	char		*prompt;
	char		**data;
	t_command	*cmd_list;

	(void)argc;
	(void)argv;
	while (1)
	{
		prompt = readline("$> ");
		if (!prompt)
			break ;
		if (*prompt)
		{
			add_history(prompt);
			data = create_data(prompt);
			if (data)
			{
				cmd_list = create_command_list(data, envp);
				free_char_list(data);
				if (cmd_list)
				{
					display_command_list(cmd_list);
					free_command_list(cmd_list);
				}
			}
		}
		free(prompt);
	}
	return (0);
}
