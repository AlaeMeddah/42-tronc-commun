/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:27:05 by almeddah          #+#    #+#             */
/*   Updated: 2025/05/08 22:02:45 by almeddah         ###   ########.fr       */
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

char	*trim_quote(char *str, int *trimmed)
{
	int		i;
	char	*res;
	char	*res_;

	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	res_ = res;
	while (*str)
	{
		if (*str == '\'' || *str == '"')
		{
			i = 1;
			*trimmed = 1;
			while (str[i] != *str && str[i])
			{
				*res = str[i];
				i++;
				res++;
			}
			str += i + 1;
		}
		else
		{
			*res = *str;
			str++;
			res++;
		}
	}
	*res = '\0';
	return (res_);
}

char	*expand_variable(char *data, char **envp, int *i)
{
	int	j;
	int	k;

	j = 0;
	data++;
	while (data[j] && data[j] != '\'' && data[j] != '"' && data[j] != ' ')
		j++;
	*i += j + 1;
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

char	*heredoc(char *delim, char **envp)
{
	static int	counter = 0;
	char		*filename;
	int			fd;
	char		*prompt;
	char		*itoa;
	int			quote;
	char		*str;
	int			i;

	quote = 0;
	delim = trim_quote(delim, &quote);
	printf("%s\n", delim);
	filename = malloc(sizeof(char) * (19));
	*filename = '\0';
	filename = ft_strncat(filename, "/tmp/heredoc_", 13);
	itoa = ft_itoa(counter);
	filename = ft_strncat(filename, itoa, 5);
	while (access(filename, F_OK) != -1)
	{
		counter++;
		if (counter > 99999)
			counter = 0;
		free(itoa);
		itoa = ft_itoa(counter);
		free(filename);
		filename = malloc(sizeof(char) * (19));
		*filename = '\0';
		filename = ft_strncat(filename, "/tmp/heredoc_", 13);
		filename = ft_strncat(filename, itoa, 5);
	}
	fd = open(filename, O_CREAT | O_EXCL | O_RDWR, 0600);
	while (1)
	{
		prompt = readline("$heredoc> ");
		if (!prompt)
		{
			printf("bash: warning: heredoc delimited by end-of-file (wanted	%s)\n",
					delim);
			break ;
		}
		if (!ft_strcmp(prompt, delim))
		{
			free(prompt);
			break ;
		}
		i = 0;
		while (prompt[i])
		{
			if (prompt[i] == '$' && !quote)
			{
				str = expand_variable(prompt + i, envp, &i);
				ft_putstr_fd(str, fd);
			}
			ft_putchar_fd(prompt[i], fd);
			i++;
		}
		free(prompt);
		ft_putchar_fd('\n', fd);
	}
	close(fd);
	return (filename);
}

t_input_redirect	*create_input_redirect(char *str1, char *str2, char **envp)
{
	t_input_redirect	*new_redir;

	if (!str2)
		return (NULL);
	new_redir = malloc(sizeof(t_input_redirect));
	if (!new_redir)
	{
		printf("redirection input allocation error\n");
		return (NULL);
	}
	new_redir->file = NULL;
	new_redir->heredoc = 0;
	if (!ft_strcmp(str1, "<"))
		new_redir->file = ft_strdup(str2);
	else
	{
		new_redir->file = heredoc(str2, envp);
		new_redir->heredoc = 1;
	}
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
	{
		printf("redirection output allocation error\n");
		return (NULL);
	}
	new_redir->file = ft_strdup(str2);
	new_redir->append = 0;
	if (!ft_strcmp(str1, ">>"))
		new_redir->append = 1;
	new_redir->next = NULL;
	return (new_redir);
}

int	is_redirection(char *str)
{
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, ">>"))
		return (1);
	if (!ft_strcmp(str, "<") || !ft_strcmp(str, "<<"))
		return (2);
	return (0);
}

void	free_input_redirect(t_input_redirect *input_redirect)
{
	t_input_redirect	*tmp;

	while (input_redirect)
	{
		tmp = input_redirect;
		if (input_redirect->file)
			free(input_redirect->file);
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

int	quote_skip(char *str)
{
	int	i;

	i = 1;
	while (str[i] != *str)
	{
		if (!str[i])
			return (0);
		i++;
	}
	return (i);
}

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
			i += quote_skip(data) - 1;
			data += quote_skip(data) + 1;
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

char	*ft_strncpy(char *src, int n)
{
	int		i;
	char	*dest;

	i = 0;
	dest = malloc(sizeof(char) * (n + 1));
	if (!dest)
	{
		printf("dest allocation error\n");
		return (NULL);
	}
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	free_char_list(char **data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		free(data[i]);
		i++;
	}
	free(data);
}

char	**create_data(char *prompt)
{
	char	**data;
	char	**new_data;
	int		i;
	int		j;
	int		k;
	int		l;

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
		k = 0;
		while (*prompt && ft_isspace(*prompt))
			prompt++;
		if (*prompt == '|')
			k++;
		else if (*prompt == '>' || *prompt == '<')
		{
			k++;
			if (*(prompt + 1) == *prompt)
				k++;
		}
		else
		{
			while (prompt[k] && !ft_isspace(prompt[k]) && prompt[k] != '|'
				&& prompt[k] != '<' && prompt[k] != '>')
			{
				if (prompt[k] == '\'' || prompt[k] == '"')
				{
					if (!quote_skip(prompt + k))
					{
						printf("unclosed quote\n");
						data[j] = NULL;
						free_char_list(data);
						return (NULL);
					}
					k += quote_skip(prompt + k);
				}
				k++;
			}
		}
		if (j >= i - 1)
		{
			i += 10;
			new_data = malloc(sizeof(char *) * i);
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
			data = new_data;
		}
		if (k)
		{
			data[j] = ft_strncpy(prompt, k);
			if (!data[j])
			{
				free_char_list(data);
				return (NULL);
			}
			j++;
		}
		prompt += k;
		data[j] = NULL;
	}
	return (data);
}

void	display_input_redirects(t_input_redirect *input_redirect)
{
	while (input_redirect)
	{
		if (input_redirect->heredoc)
			printf("<< %s ", input_redirect->file);
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
	display_input_redirects(cmd->input_redirect);
	display_output_redirects(cmd->output_redirect);
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

// void	print_data(char **data)
// {
// 	while (*data)
// 	{
// 		printf("%s\n", *data);
// 		data++;
// 	}
// 	printf("%p\n", *data);
// }

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
			if (!data)
				return (0);
			// print_data(data);
			cmd_list = create_command_list(data, envp);
			free_char_list(data);
			if (!cmd_list)
				return (0);
			display_command_list(cmd_list);
			free_command_list(cmd_list);
		}
		free(prompt);
	}
	return (0);
}
