/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:09:10 by alae              #+#    #+#             */
/*   Updated: 2025/08/08 17:11:22 by alae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_find_path2(char **paths, char *cmd)
{
	char		*full_path;
	char		*temp;
	int			i;
	struct stat	st;

	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (stat(full_path, &st) == 0)
		{
			if (access(full_path, X_OK) == 0)
			{
				free_char_list(paths);
				return (full_path);
			}
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			exit(126);
		}
		free(full_path);
	}
	return (NULL);
}

char	*is_path(char *cmd)
{
	struct stat	st;

	if (stat(cmd, &st) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
		{
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			exit(126);
		}
	}
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	exit(127);
}

char	*ft_find_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;
	char	*full_path;

	if (ft_strchr(cmd, '/'))
		return (is_path(cmd));
	path_env = ft_getenv(envp, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ":");
	if (!paths)
		return (NULL);
	full_path = ft_find_path2(paths, cmd);
	if (full_path)
		return (full_path);
	free_char_list(paths);
	return (NULL);
}
