/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:44:25 by alae              #+#    #+#             */
/*   Updated: 2025/08/18 18:29:18 by alae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	norm_builtin(t_command *cmd, char ***envp, int fd, t_data *data)
{
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (builtin_echo(cmd->argv));
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (builtin_cd(cmd->argv, *envp));
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (builtin_export(cmd->argv, envp));
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (builtin_unset(cmd->argv, *envp));
	if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (builtin_env(*envp));
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (builtin_exit(cmd->argv, data, fd));
	return (1);
}

int	exec_builtin(t_command *cmd, char ***envp, int in_fork, t_data *data)
{
	int	return_value;
	int	saved_stdin;

	saved_stdin = dup(STDOUT_FILENO);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!in_fork && !setup_redirect(cmd))
		return (1);
	if (!in_fork && ft_strcmp(cmd->argv[0], "exit") == 0)
		ft_putstr_fd("exit\n", 2);
	return_value = norm_builtin(cmd, envp, saved_stdin, data);
	dup2(saved_stdin, STDOUT_FILENO);
	close(saved_stdin);
	if (in_fork)
	{
		free_command_list((*data).command_list);
		free_char_list(*envp);
	}
	return (return_value);
}
