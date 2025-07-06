/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhpham <minhpham@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 07:34:31 by minhpham          #+#    #+#             */
/*   Updated: 2025/07/06 15:13:50 by minhpham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env_var(const char *key, t_env **env)
{
	t_env	*cur = *env;
	t_env	*prev = NULL;

	while (cur)
	{
		if (strcmp(cur->key, key) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				*env = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			return;
		}
		prev = cur;
		cur = cur->next;
	}
}

int	ft_unset(char **args, t_env **env)
{
	int	i = 1;

	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			write(2, "minishell: unset: `", 20);
			write(2, args[i], strlen(args[i]));
			write(2, "': not a valid identifier\n", 27);
		}
		else
			remove_env_var(args[i], env);
		i++;
	}
	return (0);
}
