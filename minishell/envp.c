/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:32:15 by alae              #+#    #+#             */
/*   Updated: 2025/08/08 13:01:46 by alae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char **envp, char *name)
{
	size_t	len;
	int		i;

	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*join(char *key, char *value)
{
	char	*joined;

	joined = malloc(ft_strlen(key) + ft_strlen(value) + 2);
	if (!joined)
		return (NULL);
	joined[0] = '\0';
	joined = ft_strncat(joined, key, ft_strlen(key));
	joined = ft_strncat(joined, "=", 1);
	joined = ft_strncat(joined, value, ft_strlen(value));
	return (joined);
}

char	**add_var_to_env(char **envp, char *new_var)
{
	char	**new_envp;
	int		j;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		return (envp);
	j = 0;
	while (j < i)
	{
		new_envp[j] = ft_strdup(envp[j]);
		j++;
	}
	new_envp[i] = new_var;
	new_envp[i + 1] = NULL;
	free_char_list(envp);
	return (new_envp);
}

char	**ft_setenv(char **envp, char *key, char *value)
{
	int		i;
	char	*new_var;
	char	**new_envp;

	i = 0;
	new_var = join(key, value);
	if (!new_var)
		return (envp);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0
			&& (envp[i][ft_strlen(key)] == '=' || !(envp[i][ft_strlen(key)])))
		{
			free(envp[i]);
			envp[i] = new_var;
			return (envp);
		}
		i++;
	}
	new_envp = add_var_to_env(envp, new_var);
	if (!new_envp)
		return (envp);
	return (new_envp);
}
