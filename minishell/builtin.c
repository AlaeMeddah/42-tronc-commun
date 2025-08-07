/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:44:25 by alae              #+#    #+#             */
/*   Updated: 2025/08/07 14:40:45 by alae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	exec_builtin(t_command *cmd, char **envp, int in_fork, int exit_code)
{
	if (!in_fork)
	{
		if (!setup_redirect(cmd))
			return (1);
	}
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
	{
		if (!in_fork)
			write(STDERR_FILENO, "exit\n", 5);
		return (builtin_exit(cmd->argv, exit_code));
	}
	return (1);
}
