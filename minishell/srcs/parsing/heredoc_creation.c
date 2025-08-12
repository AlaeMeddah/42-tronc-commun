/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_creation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:25:59 by almeddah          #+#    #+#             */
/*   Updated: 2025/08/11 18:42:43 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			*res++ = *str++;
	}
	*res = '\0';
	return (res_);
}

char	*heredoc_file_creation(void)
{
	static int	counter = 0;
	int			start;
	char		*filename;
	char		*itoa;

	start = counter;
	while (1)
	{
		counter++;
		if (counter > 99999)
			counter = 0;
		filename = malloc(sizeof(char) * (19));
		if (!filename || counter == start)
			return (NULL);
		itoa = ft_itoa(counter);
		*filename = '\0';
		ft_strncat(filename, "/tmp/heredoc_", ft_strlen("/tmp/heredoc_"));
		ft_strncat(filename, itoa, ft_strlen(itoa));
		free(itoa);
		if (access(filename, F_OK) == -1)
			return (filename);
		free(filename);
	}
}

void	paste_to_heredoc(char *str, int quote, int fd, t_data data)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && !quote)
			ft_putstr_fd(expand_variable(str + i, data, &i), fd);
		else
		{
			ft_putchar_fd(str[i], fd);
			i++;
		}
	}
	ft_putchar_fd('\n', fd);
}

int	stop_heredoc(char *prompt, char *delim, int y)
{
	if (!prompt)
	{
		ft_putstr_fd("minishell: warning: here-document at line ", 2);
		ft_putnbr_fd(y, 2);
		ft_putstr_fd(" delimited by end-of-file (wanted ", 2);
		ft_putstr_fd(delim, 2);
		ft_putstr_fd(")\n", 2);
		return (1);
	}
	if (!ft_strcmp(prompt, delim))
	{
		free(prompt);
		return (1);
	}
	return (0);
}

char	*heredoc(char *delim, t_data data)
{
	char	*filename;
	int		fd;
	char	*prompt;
	int		quote;
	int		y;

	quote = 0;
	delim = trim_quote(delim, &quote);
	filename = heredoc_file_creation();
	fd = open(filename, O_CREAT | O_EXCL | O_RDWR, 0600);
	y = 0;
	while (1)
	{
		prompt = readline("heredoc> ");
		y++;
		if (stop_heredoc(prompt, delim, y))
			break ;
		paste_to_heredoc(prompt, quote, fd, data);
		free(prompt);
	}
	close(fd);
	free(delim);
	return (filename);
}
