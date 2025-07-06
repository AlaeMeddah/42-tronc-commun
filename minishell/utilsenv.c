/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhpham <minhpham@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:22:57 by minhpham          #+#    #+#             */
/*   Updated: 2025/07/06 14:12:37 by minhpham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_new(char *key, char *value)
{
	t_env	*node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

t_env	*env_to_list(char **envp)
{
	t_env	*head = NULL;
	t_env	*curr = NULL;
	char	*equal;
	char	*key;
	char	*val;

	for (int i = 0; envp[i]; i++)
	{
		equal = ft_strchr(envp[i], '=');
		if (!equal)
			continue;
		key = ft_substr(envp[i], 0, equal - envp[i]);
		val = ft_strdup(equal + 1);
		t_env *new = env_new(key, val);
		if (!head)
			head = new;
		else
			curr->next = new;
		curr = new;
	}
	return (head);
}
