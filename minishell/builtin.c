/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhpham <minhpham@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:25:07 by minhpham          #+#    #+#             */
/*   Updated: 2025/07/06 14:23:02 by minhpham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int ft_strcmp(const char *s1, const char *s2)
// {
// 	int i = 0;

// 	while (s1[i] && s2[i] && s1[i] == s2[i])
// 		i++;
// 	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// }

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env"));
}

int	exec_builtin(char **argv, t_env **env, int infork)
{
	if (!argv || !argv[0])
		return (1);
	if (!ft_strcmp(argv[0], "cd"))
		return (ft_cd(argv, env));
	if (!ft_strcmp(argv[0], "echo"))
		return (ft_echo(argv));
	if (!ft_strcmp(argv[0], "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(argv[0], "exit"))
		return (ft_exit(argv, infork));
	if (!ft_strcmp(argv[0], "export"))
		return (ft_export(argv, env));
	if (!ft_strcmp(argv[0], "unset"))
		return (ft_unset(argv, env));
	if (!ft_strcmp(argv[0], "env"))
		return (ft_env(*env));
	return (1);
}
