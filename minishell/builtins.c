/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:17:26 by alae              #+#    #+#             */
/*   Updated: 2025/08/05 15:48:44 by alae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(char **argv)
{
	(void)argv;
	return (0);
}

int	builtin_cd(char **argv, char **envp)
{
	(void)envp;
	(void)argv;
	return (0);
}

int	builtin_pwd(void)
{
	return (0);
}

int	builtin_export(char **argv, char **envp)
{
	(void)envp;
	(void)argv;
	return (0);
}

int	builtin_unset(char **argv, char **envp)
{
	(void)argv;
	(void)envp;
	return (0);
}

int	builtin_env(char **envp)
{
	(void)envp;
	return (0);
}

int	builtin_exit(char **argv)
{
	(void)argv;
	return (0);
}
