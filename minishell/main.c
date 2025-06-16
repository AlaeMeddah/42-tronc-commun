/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:27:05 by almeddah          #+#    #+#             */
/*   Updated: 2025/06/13 10:21:07 by alae             ###   ########.fr       */
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

int	handle_new_command(t_data data, int *i, t_command *new_command)
{
	int	j;

	*i = 0;
	j = 0;
	while (data.token_list[*i] && ft_strcmp(data.token_list[*i], "|"))
	{
		if (is_redirection(data.token_list[*i]))
		{
			if (redirection_error(data.token_list, *i))
				return (0);
			else
			{
				if (!create_redirect(data, *i, new_command))
					return (0);
			}
			*i += 2;
		}
		else
			new_command->argv[j++] = expand_token(data.token_list[(*i)++],
					data);
	}
	new_command->argv[j] = NULL;
	return (1);
}

int	add_command_to_list(t_data data, int *i, t_command **command_list)
{
	t_command	*new_command;

	*i = 0;
	while (data.token_list[*i] && ft_strcmp(data.token_list[*i], "|"))
		(*i)++;
	new_command = create_new_command(*command_list, *i);
	if (!new_command)
		return (0);
	if (!handle_new_command(data, i, new_command))
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

t_command	*create_command_list(t_data data)
{
	t_command	*command_list;
	int			i;

	command_list = NULL;
	while (*data.token_list)
	{
		if (!ft_strcmp(*data.token_list, "|"))
			return (pipe_error(command_list));
		if (!add_command_to_list(data, &i, &command_list))
			return (NULL);
		data.token_list += i;
		if (*data.token_list)
		{
			if (!ft_strcmp(*data.token_list, "|") && (!*(data.token_list + 1)))
				return (pipe_error(command_list));
			data.token_list++;
		}
	}
	return (command_list);
}

void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void)sig;
}

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = handle_sigquit;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	t_data	data;

	(void)argc;
	(void)argv;
	data.exit_code = 0;
	data.command_list = NULL;
	data.token_list = NULL;
	data.envp = envp;
	setup_signals();
	while (1)
	{
		prompt = readline("$> ");
		if (!prompt)
			break ;
		if (*prompt)
		{
			add_history(prompt);
			data.token_list = create_token_list(prompt);
			if (data.token_list)
			{
				data.command_list = create_command_list(data);
				free_char_list(data.token_list);
				if (data.command_list)
				{
					display_command_list(data.command_list);
					free_command_list(data.command_list);
				}
			}
		}
		free(prompt);
	}
	return (0);
}
