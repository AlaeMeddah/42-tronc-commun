#include "minishell.h"

int	setup_redirect(cmd)
{
}

int	is_builtin(char *cmd)
{
}

int	exec_builtin(t_command *cmd, char **envp)
{
	setup_redirect(cmd);
}

int	ft_find_path(char *cmd, char **envp)
{
}

int	exec_cmd(t_command *cmd, char **envp)
{
	int		status;
	char	*path;

	setup_redirect(cmd);
	if (is_builtin(cmd->argv[0]))
		exit(exec_builtin(cmd, envp));
	path = ft_find_path(cmd->argv[0], envp);
	if (!path)
	{
		perror(cmd->argv[0]);
		exit(127);
	}
	execve(path, cmd->argv, envp);
	perror(cmd->argv[0]);
	exit(127);
}

int	setup_cmds(t_command *cmd_list, char **envp)
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
			return (exec_builtin(cmd, envp));
		if (cmd->next && pipe(pipefd) == -1)
			return (perror("pipe"), 1);
		pid = fork();
		if (pid == -1)
			return (perror("pid"), 1);
		if (pid == 0)
		{
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
			exec_cmd(cmd, envp);
		}
		else
		{
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
}
