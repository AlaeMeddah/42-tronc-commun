/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:27:32 by minhpham          #+#    #+#             */
/*   Updated: 2025/06/20 13:20:14 by alae             ###   ########.fr       */
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

int	execute_commands(t_command *cmd, char **env)
{
	int		prev_fd;
	int		pipefd[2];
	pid_t	pid;

	prev_fd = -1;
	while (cmd)
	{
		if (cmd->next && pipe(pipefd) == -1)
			return (perror("pipe"), 1);
		pid = fork();
		if (pid == -1)
			return (perror("fork"), 1);
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (apply_input_redirection(cmd, prev_fd) == -1)
				exit(1);
			if (apply_output_redirection(cmd, cmd->next ? pipefd[1] : -1) == -1)
				exit(1);
			if (prev_fd != -1)
				close(prev_fd);
			if (cmd->next)
				close(pipefd[0]);
			exec_external(cmd->argv, env);
			perror("exec");
			exit(127);
		}
		else
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			if (prev_fd != -1)
				close(prev_fd);
			if (cmd->next)
			{
				close(pipefd[1]);
				prev_fd = pipefd[0];
			}
			else
				prev_fd = -1;
		}
		cmd = cmd->next;
	}
	while (wait(NULL) > 0)
		;
	setup_signals();
	return (0);
}
