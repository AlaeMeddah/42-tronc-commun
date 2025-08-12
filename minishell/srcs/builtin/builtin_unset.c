/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:52:36 by alae              #+#    #+#             */
/*   Updated: 2025/08/11 18:39:16 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(char **argv, char **envp)
{
	int		i;
	size_t	len;

	while (*(++argv))
	{
		i = 0;
		len = ft_strlen(*argv);
		while (envp[i])
		{
			if (ft_strncmp(envp[i], *argv, len) == 0 && (envp[i][len] == '='
					|| envp[i][len] == '\0'))
			{
				free(envp[i]);
				while (envp[i + 1])
				{
					envp[i] = envp[i + 1];
					i++;
				}
				envp[i] = NULL;
			}
			i++;
		}
	}
	return (0);
}
