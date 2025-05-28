/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:27:05 by almeddah          #+#    #+#             */
/*   Updated: 2025/05/28 13:23:35 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(char *str)
{
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, ">>"))
		return (1);
	if (!ft_strcmp(str, "<") || !ft_strcmp(str, "<<"))
		return (2);
	return (0);
}

// try to use variable expansion done for herdoc
int	expand_2(char *data, char **envp)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (*data)
	{
		if (*data == '\'')
		{
			i += nb_quoted_char(data) - 1;
			data += nb_quoted_char(data) + 1;
		}
		else if (*data == '"')
			data++;
		else if (*data == '$')
		{
			j = 0;
			data++;
			while (data[j] && data[j] != '\'' && data[j] != '"'
				&& data[j] != ' ')
				j++;
			if (j)
			{
				k = 0;
				while (envp[k])
				{
					if (!ft_strncmp(envp[k], data, j) && envp[k][j] == '=')
					{
						i += ft_strlen(envp[k] + j + 1);
						break ;
					}
					k++;
				}
			}
			data += j;
		}
		else
		{
			i++;
			data++;
		}
	}
	return (i);
}

// try to use variable expansion done for herdoc
char	*expand(char *data, char **envp)
{
	char	*result;
	char	*result_;
	int		j;
	int		k;
	int		l;

	result = malloc(sizeof(char) * (expand_2(data, envp) + 1));
	result_ = result;
	while (*data)
	{
		if (*data == '\'')
		{
			data++;
			while (*data != '\'')
			{
				*result = *data;
				data++;
				result++;
			}
			data++;
		}
		else if (*data == '"')
			data++;
		else if (*data == '$')
		{
			j = 0;
			data++;
			while (data[j] && data[j] != '\'' && data[j] != '"'
				&& data[j] != ' ')
				j++;
			if (j)
			{
				k = 0;
				while (envp[k])
				{
					if (!ft_strncmp(envp[k], data, j) && envp[k][j] == '=')
					{
						l = 1;
						while (envp[k][j + l])
						{
							*result = envp[k][j + l];
							result++;
							l++;
						}
						break ;
					}
					k++;
				}
			}
			data += j;
		}
		else
		{
			*result = *data;
			result++;
			data++;
		}
	}
	*result = '\0';
	return (result_);
}

t_command	*create_command_list(char **data, char **envp)
{
	t_command	*command_list;
	t_command	*new_command;
	void		*redirect;
	int			i;
	int			j;

	command_list = NULL;
	while (*data)
	{
		if (!ft_strcmp(*data, "|"))
		{
			printf("pipe error\n");
			free_command_list(command_list);
			return (NULL);
		}
		i = 0;
		while (data[i] && ft_strcmp(data[i], "|"))
			i++;
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
		i = 0;
		j = 0;
		while (data[i] && ft_strcmp(data[i], "|"))
		{
			if (is_redirection(data[i]))
			{
				if (!data[i + 1] || is_redirection(data[i + 1])
					|| !ft_strcmp(data[i + 1], "|"))
				{
					printf("redirection error\n");
					free_command_list(command_list);
					return (NULL);
				}
				else
				{
					if (is_redirection(data[i]) == 2)
					{
						redirect = create_input_redirect(data[i], data[i + 1],
								envp);
						if (!redirect)
						{
							free_command_list(command_list);
							return (NULL);
						}
						ft_add_back((void **)&(new_command->input_redirect),
							redirect);
					}
					if (is_redirection(data[i]) == 1)
					{
						redirect = create_output_redirect(data[i], data[i + 1]);
						if (!redirect)
						{
							free_command_list(command_list);
							return (NULL);
						}
						ft_add_back((void **)&(new_command->output_redirect),
							redirect);
					}
				}
				i += 2;
			}
			else
			{
				new_command->argv[j] = expand(data[i], envp);
				j++;
				i++;
			}
		}
		new_command->argv[j] = NULL;
		ft_add_back((void **)&command_list, new_command);
		data += i;
		if (*data)
		{
			if (!ft_strcmp(*data, "|") && (!*(data + 1)))
			{
				printf("pipe erreur\n");
				free_command_list(command_list);
				return (NULL);
			}
			data++;
		}
	}
	return (command_list);
}

char	**create_new_data(char **data, int *i, int j)
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
		{
			if ((*prompt)[k] == '\'' || (*prompt)[k] == '"')
			{
				if (!nb_quoted_char(*prompt + k))
				{
					printf("unclosed quote\n");
					data[j] = NULL;
					free_char_list(data);
					return (-1);
				}
				k += nb_quoted_char(*prompt + k);
			}
			k++;
		}
	}
	return (k);
}

int	copy_to_data(char **prompt, int k, int j, char **data)
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

char	**create_data(char *prompt)
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
			data = create_new_data(data, &i, j);
		k = parse_prompt(&prompt, data, j);
		if (k == -1)
			return (NULL);
		j = copy_to_data(&prompt, k, j, data);
		if (j == -1)
			return (NULL);
	}
	return (data);
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
