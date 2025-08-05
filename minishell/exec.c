#include "minishell.h"

int	setup_redirect(t_command *cmd)
{
	t_input_redirect	*in;
	t_output_redirect	*out;
	int					fd;

	in = cmd->input_redirect;
	while (in)
	{
		fd = open(in->file, O_RDONLY);
		if (fd == -1)
			return (perror(in->file), 1);
		if (dup2(fd, STDIN_FILENO) == -1)
			return (perror("dup2"), close(fd), 1);
		close(fd);
		in = in->next;
	}
	out = cmd->output_redirect;
	while (out)
	{
		if (out->append)
			fd = open(out->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(out->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (perror(out->file), 1);
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (perror("dup2"), close(fd), 1);
		close(fd);
		out = out->next;
	}
	return (0);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (strcmp(cmd, "echo") == 0)
		return (1);
	if (strcmp(cmd, "cd") == 0)
		return (1);
	if (strcmp(cmd, "pwd") == 0)
		return (1);
	if (strcmp(cmd, "export") == 0)
		return (1);
	if (strcmp(cmd, "unset") == 0)
		return (1);
	if (strcmp(cmd, "env") == 0)
		return (1);
	if (strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_command *cmd, char **envp)
{
	if (strcmp(cmd->argv[0], "echo") == 0)
		return (builtin_echo(cmd->argv));
	if (strcmp(cmd->argv[0], "cd") == 0)
		return (builtin_cd(cmd->argv, envp));
	if (strcmp(cmd->argv[0], "pwd") == 0)
		return (builtin_pwd());
	if (strcmp(cmd->argv[0], "export") == 0)
		return (builtin_export(cmd->argv, envp));
	if (strcmp(cmd->argv[0], "unset") == 0)
		return (builtin_unset(cmd->argv, envp));
	if (strcmp(cmd->argv[0], "env") == 0)
		return (builtin_env(envp));
	if (strcmp(cmd->argv[0], "exit") == 0)
		return (builtin_exit(cmd->argv));
	return (1);
}

char	*get_env_value(char **envp, const char *name)
{
	size_t	len;
	int		i;

	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1); // Return pointer to value (after '=')
		i++;
	}
	return (NULL); // Not found
}

char	*ft_find_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;
	int		i;
	char	*temp;
	char	*full_path;

	path_env = get_env_value(envp, "PATH");
	if (!path_env)
		return (NULL);
	// weird shit
	paths = ft_split(path_env, ":");
	// free path_env;
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, X_OK) == 0)
		{
			// ft_free_split(paths);
			printf("%s\n", full_path);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	// ft_free_split(paths);
	return (NULL);
}

int	exec_cmd(t_command *cmd, char **envp)
{
	char	*path;

	path = NULL;
	if (is_builtin(cmd->argv[0]))
		exit(exec_builtin(cmd, envp));
	if (!setup_redirect(cmd))
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

int	setup_cmds(t_command *cmd_list, char **envp)
{
	int			prev_fd;
	int			pipefd[2];
	t_command	*cmd;
	pid_t		pid;
	pid_t		last_pid;
	int			status;
	int			last;

	prev_fd = -1;
	cmd = cmd_list;
	while (cmd)
	{
		if (is_builtin(cmd->argv[0]) && !cmd->next && prev_fd == -1)
		{
			if (setup_redirect(cmd))
				return (1);
			return (exec_builtin(cmd, envp));
		}
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
	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		last = get_exit_status(pid, last_pid, status, last);
		pid = waitpid(-1, &status, 0);
	}
	setup_signals();
	return (last);
}
