/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:54:37 by alae              #+#    #+#             */
/*   Updated: 2025/08/07 16:09:30 by alae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_target(char *old, char **envp, char *oldpwd, char **args)
{
	char	*target;

	target = NULL;
	if (!args[1])
		target = ft_getenv(envp, "HOME");
	else if (strcmp(args[1], "-") == 0)
	{
		if (!old)
		{
			fprintf(stderr, "minishell: cd: OLDPWD not set\n");
			free(oldpwd);
			return (NULL);
		}
		target = old;
	}
	else
		target = args[1];
	if (!target)
	{
		fprintf(stderr, "minishell: cd: HOME not set\n");
		free(oldpwd);
		return (NULL);
	}
	return (target);
}

int	builtin_cd(char **args, char **envp)
{
	char	*target;
	char	*oldpwd;
	char	*old;
	char	*newpwd;

	oldpwd = getcwd(NULL, 0);
	old = ft_getenv(envp, "OLDPWD");
	target = set_target(old, envp, oldpwd, args);
	if (!target)
		return (1);
	if (chdir(target) == -1)
	{
		perror("minishell: cd");
		free(oldpwd);
		return (1);
	}
	ft_setenv(envp, "OLDPWD", oldpwd);
	newpwd = getcwd(NULL, 0);
	if (newpwd)
		ft_setenv(envp, "PWD", newpwd);
	if (args[1] && strcmp(args[1], "-") == 0)
		printf("%s\n", newpwd);
	free(oldpwd);
	free(newpwd);
	return (0);
}
