/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:52:36 by alae              #+#    #+#             */
/*   Updated: 2025/08/07 15:53:04 by alae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(char **argv, char **envp)
{
	int		i;
	size_t	len;

	argv++;
	while (*argv)
	{
		i = 0;
		len = strlen(*argv);
		while (envp[i])
		{
			if (strncmp(envp[i], *argv, len) == 0 && envp[i][len] == '=')
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
		argv++;
	}
	return (0);
}
