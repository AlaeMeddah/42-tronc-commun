/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilspaf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhpham <minhpham@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:52:45 by minhpham          #+#    #+#             */
/*   Updated: 2025/06/19 09:54:15 by minhpham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	exec(char *cmd, char **env)
// {
// 	char	**s_cmd;
// 	char	*path;

// 	s_cmd = ft_split(cmd, " ");
// 	path = ft_get_path(s_cmd[0], env);
// 	if (!path)
// 	{
// 		ft_free_tab(s_cmd);
// 		exit(1);
// 	}
// 	if (execve(path, s_cmd, env) == -1)
// 	{
// 		write_error("Error: Command not found\n");
// 		ft_free_tab(s_cmd);
// 		exit(1);
// 	}
// }

void exec_external(char **argv, char **env)
{
	char *path = ft_get_path(argv[0], env);

	if (!path)
		exit(127);

	execve(path, argv, env);
	perror(argv[0]);
	ft_free_tab(argv);
	exit(127);
}

char	*my_getenv(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	write_error("Error: PATH not found\n");
	return (NULL);
}

char	*ft_get_path(char *cmd, char **env)
{
	t_path	p;
	int		i;

	if (!cmd)
		return (write_error("nothing argument\n"), NULL);
	if (cmd[0] == '/')
		return (cmd);
	if (!my_getenv(env))
		return (NULL);
	p.s_cmd = ft_split(cmd, " ");
	p.allpath = ft_split(my_getenv(env), ":");
	i = -1;
	while (p.allpath[++i])
	{
		p.path_part = ft_strjoin(p.allpath[i], "/");
		p.exec = ft_strjoin(p.path_part, p.s_cmd[0]);
		free(p.path_part);
		if (access(p.exec, F_OK | X_OK) == 0)
			return (ft_free_tab(p.s_cmd), ft_free_tab(p.allpath), p.exec);
		free(p.exec);
	}
	return (ft_free_tab(p.allpath), ft_free_tab(p.s_cmd), cmd);
}

void	write_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
}

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	exit_handler(int n_exit)
{
	if (n_exit == 1)
		write_error("Error: Wrong number of arguments\n");
	else if (n_exit == 2)
		write_error("Error: Infile not found or not accessible\n");
	else if (n_exit == 3)
		write_error("Error: Outfile not possible\n");
	else if (n_exit == 4)
		write_error("Error: Pipe not possible\n");
	exit(1);
}

int	open_file(char *file, int in_or_out, int *error)
{
	int	fd;

	if (in_or_out == 0)
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
			*error = 2;
	}
	if (in_or_out == 1)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0755);
		if (fd == -1)
			*error = 3;
	}
	return (fd);
}