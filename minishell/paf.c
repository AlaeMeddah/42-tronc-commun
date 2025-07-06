/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:27:32 by minhpham          #+#    #+#             */
/*   Updated: 2025/07/06 17:40:11 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	apply_input_redirection(t_command *cmd, int prev_fd)
{
	int					fd;
	t_input_redirect	*redir;

	fd = -1;
	redir = cmd->input_redirect;
	while (redir)
	{
		if (fd != -1)
			close(fd);
		if (redir->heredoc == 1)
			fd = open(redir->file, O_RDONLY);
		else
			fd = open(redir->file, O_RDONLY);
		if (fd < 0)
			return (perror("open input"), -1);
		redir = redir->next;
	}
	if (fd != -1)
		dup2(fd, STDIN_FILENO);
	else if (prev_fd != -1)
		dup2(prev_fd, STDIN_FILENO);
	if (fd != -1)
		close(fd);
	return (0);
}

int	apply_output_redirection(t_command *cmd, int pipe_out)
{
	int					fd;
	t_output_redirect	*redir;

	fd = -1;
	redir = cmd->output_redirect;
	while (redir)
	{
		if (fd != -1)
			close(fd);
		if (redir->append == 1)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (perror("open output"), -1);
		redir = redir->next;
	}
	if (fd != -1)
		dup2(fd, STDOUT_FILENO);
	else if (pipe_out != -1)
		dup2(pipe_out, STDOUT_FILENO);
	if (fd != -1)
		close(fd);
	return (0);
}

int	get_exit_status(pid_t pid, pid_t last_pid, int status, int last_exit_status)
{
	int	sig;

	if (pid == last_pid)
	{
		if (WIFEXITED(status))
			last_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			last_exit_status = 128 + WTERMSIG(status);
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
	return (last_exit_status);
}

int	pid_autre(int pid, int *prev_fd, t_command *cmd, int pipefd[2])
{
	int	last_pid;

	last_pid = pid;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
	else
		*prev_fd = -1;
	return (last_pid);
}

int	pid_0(t_command *cmd, int prev_fd, t_env **env, int pipefd[2])
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (apply_input_redirection(cmd, prev_fd) == -1)
		return (1);
	if (apply_output_redirection(cmd, cmd->next ? pipefd[1] : -1) == -1)
		return (1);
	if (prev_fd != -1)
		close(prev_fd);
	if (cmd->next)
		close(pipefd[0]);
	if (is_builtin(cmd->argv[0]))
		exit(exec_builtin(cmd->argv, env, 1));
	else
		exec_external(cmd->argv, convert_env(*env));
	perror("exec");
	return (127);
}

int	exec_last_buitin(t_command *cmd, int prev_fd, t_env **env)
{
	int	last_exit_status;

	if (apply_input_redirection(cmd, prev_fd) == -1)
		return (1);
	if (apply_output_redirection(cmd, -1) == -1)
		return (1);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	last_exit_status = exec_builtin(cmd->argv, env, 0);
	setup_signals();
	return (last_exit_status);
}

int	loop_cmd(t_command *cmd, pid_t *pid, pid_t *last_pid, t_env **env)
{
	int	pipefd[2];
	int	prev_fd;

	prev_fd = -1;
	while (cmd)
	{
		if (cmd->next && pipe(pipefd) == -1)
			return (perror("pipe"), 1);
		if (!cmd->next && is_builtin(cmd->argv[0]))
			return (exec_last_buitin(cmd, prev_fd, env));
		*pid = fork();
		if (*pid == -1)
			return (perror("fork"), 1);
		if (*pid == 0)
			exit(pid_0(cmd, prev_fd, env, pipefd));
		else
			*last_pid = pid_autre(*pid, &prev_fd, cmd, pipefd);
		cmd = cmd->next;
	}
	return (-1);
}

int	execute_commands(t_command *cmd, t_env **env)
{
	pid_t	pid;
	pid_t	last_pid;
	int		status;
	int		last_exit_status;

	last_exit_status = loop_cmd(cmd, &pid, &last_pid, env);
	if (last_exit_status != -1)
		return (last_exit_status);
	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		last_exit_status = get_exit_status(pid, last_pid, status,
				last_exit_status);
		pid = waitpid(-1, &status, 0);
	}
	setup_signals();
	return (last_exit_status);
}
