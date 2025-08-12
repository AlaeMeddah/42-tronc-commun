/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:18:32 by alae              #+#    #+#             */
/*   Updated: 2025/08/12 18:42:27 by alae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_exit_status(pid_t pid, pid_t last_pid, int status, int exit_code)
{
	int	sig;

	if (pid == last_pid)
	{
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit_code = 128 + WTERMSIG(status);
	}
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
		{
			if (WCOREDUMP(status))
				ft_putstr_fd("Quit (core dumped)\n", 2);
			else
				ft_putstr_fd("Quit\n", 2);
		}
		else if (sig == SIGINT)
		{
			ft_putstr_fd("\n", 2);
		}
	}
	return (exit_code);
}

int	cmd_loop(t_data *data, pid_t *pid, pid_t *last_pid, t_command *cmd)
{
	int	prev_fd;
	int	pipefd[2];

	prev_fd = -1;
	while (cmd)
	{
		if (is_builtin(cmd->argv[0]) && !cmd->next && prev_fd == -1)
		{
			(*data).exit_code = exec_builtin(cmd, &(*data).envp, 0, data);
			return ((*data).exit_code);
		}
		if (cmd->next && pipe(pipefd) == -1)
			return (perror("pipe"), 1);
		*pid = fork();
		if (*pid == -1)
			return (perror("pid"), 1);
		if (*pid == 0)
			fork_child(cmd, data, &prev_fd, pipefd);
		else
			*last_pid = fork_parent(cmd, *pid, &prev_fd, pipefd);
		cmd = cmd->next;
	}
	return (-1);
}

int	setup_cmds(t_data *data)
{
	t_command	*cmd;
	pid_t		pid;
	pid_t		last_pid;
	int			status;

	cmd = (*data).command_list;
	(*data).exit_code = cmd_loop(data, &pid, &last_pid, cmd);
	if ((*data).exit_code != -1)
	{
		setup_signals();
		return ((*data).exit_code);
	}
	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		(*data).exit_code = get_exit_status(pid, last_pid, status,
				(*data).exit_code);
		pid = waitpid(-1, &status, 0);
	}
	setup_signals();
	return ((*data).exit_code);
}
