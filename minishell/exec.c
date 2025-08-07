/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:18:32 by alae              #+#    #+#             */
/*   Updated: 2025/08/07 15:32:43 by alae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(t_command *cmd, char **envp, int exit_code)
{
	char	*path;

	if (!setup_redirect(cmd))
		exit(1);
	if (is_builtin(cmd->argv[0]))
		exit(exec_builtin(cmd, envp, 1, exit_code));
	path = ft_find_path(cmd->argv[0], envp);
	if (!path)
	{
		perror(cmd->argv[0]);
		exit(127);
	}
	execve(path, cmd->argv, envp);
	perror(cmd->argv[0]);
	free(path);
	exit(127);
}

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
				write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
			else
				write(STDOUT_FILENO, "Quit\n", 5);
		}
		else if (sig == SIGINT)
		{
			write(STDOUT_FILENO, "\n", 1);
		}
	}
	return (exit_code);
}

int	setup_cmds(t_command *cmd_list, char **envp, int exit_code)
{
	int			prev_fd;
	int			pipefd[2];
	t_command	*cmd;
	pid_t		pid;
	pid_t		last_pid;
	int			status;

	prev_fd = -1;
	cmd = cmd_list;
	while (cmd)
	{
		if (is_builtin(cmd->argv[0]) && !cmd->next && prev_fd == -1)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			exit_code = exec_builtin(cmd, envp, 0, exit_code);
			setup_signals();
			return (exit_code);
		}
		if (cmd->next && pipe(pipefd) == -1)
			return (perror("pipe"), 1);
		pid = fork();
		if (pid == -1)
			return (perror("pid"), 1);
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (prev_fd != -1)
			{
				dup2(prev_fd, 0);
				close(prev_fd);
			}
			if (cmd->next)
			{
				dup2(pipefd[1], 1);
				close(pipefd[0]);
				close(pipefd[1]);
			}
			exec_cmd(cmd, envp, exit_code);
		}
		else
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			last_pid = pid;
			if (prev_fd != -1)
				close(prev_fd);
			if (cmd->next)
			{
				close(pipefd[1]);
				prev_fd = pipefd[0];
			}
		}
		cmd = cmd->next;
	}
	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		exit_code = get_exit_status(pid, last_pid, status, exit_code);
		pid = waitpid(-1, &status, 0);
	}
	setup_signals();
	return (exit_code);
}
