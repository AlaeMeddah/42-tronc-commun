/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 17:20:02 by alae              #+#    #+#             */
/*   Updated: 2025/08/11 18:42:43 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fork_parent(t_command *cmd, int pid, int *prev_fd, int pipefd[2])
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
	return (pid);
}

void	check_cmd(t_command *cmd)
{
	struct stat	st;

	if (!cmd->argv[0])
		exit(0);
	if (ft_strchr(cmd->argv[0], '/') && stat(cmd->argv[0], &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->argv[0], 2);
			ft_putstr_fd(": Is a directory\n", 2);
			exit(126);
		}
	}
}

int	exec_cmd(t_command *cmd, char ***envp, int exit_code)
{
	char	*path;

	if (!setup_redirect(cmd))
		exit(1);
	if (is_builtin(cmd->argv[0]))
		exit(exec_builtin(cmd, envp, 1, exit_code));
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	check_cmd(cmd);
	path = ft_find_path(cmd->argv[0], *envp);
	if (!path)
	{
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	execve(path, cmd->argv, *envp);
	perror(cmd->argv[0]);
	free(path);
	exit(127);
}

void	fork_child(t_command *cmd, t_data *data, int *prev_fd, int pipefd[2])
{
	if (*prev_fd != -1)
	{
		dup2(*prev_fd, 0);
		close(*prev_fd);
	}
	if (cmd->next)
	{
		dup2(pipefd[1], 1);
		close(pipefd[0]);
		close(pipefd[1]);
	}
	exec_cmd(cmd, &(*data).envp, (*data).exit_code);
}
