/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhpham <minhpham@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 01:48:58 by minhpham          #+#    #+#             */
/*   Updated: 2025/07/03 15:37:01 by minhpham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_env(t_env *env, const char *key)
{
	while (env)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(key) + 1))
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	is_valid_identifier(const char *key)
{
	int	i = 0;

	if (!((key[0] >= 'A' && key[0] <= 'Z')
		|| (key[0] >= 'a' && key[0] <= 'z')
		|| key[0] == '_'))
		return (0);
	while (key[i])
	{
		if (!(key[i] == '_' || (key[i] >= 'a' && key[i] <= 'z')
			|| (key[i] >= 'A' && key[i] <= 'Z')
			|| (key[i] >= '0' && key[i] <= '9')))
			return (0);
		i++;
	}
	return (1);
}

int	ft_export(char **args, t_env **env)
{
	int		i;
	char	*equal;
	t_env	*var;
	char	*key;
	char	*val;

	i = 1;
	if (!args[1])
	{
		print_export(*env);
		return (0);
	}
	while (args[i])
	{
		equal = ft_strchr(args[i], '=');
		if (equal)
		{
			key = ft_substr(args[i], 0, equal - args[i]);
			val = ft_strdup(equal + 1);
		}
		else
		{
			key = ft_strdup(args[i]);
			val = NULL;
		}
		if (!is_valid_identifier(key))
		{
			write(2, "export: `", 9);
			write(2, key, ft_strlen(key));
			write(2, "': not a valid identifier\n", 27);
			free(key);
			if (val)
				free(val);
			i++;
			continue ;
		}
		var = find_env(*env, key);
		if (var)
		{
			free(var->value);
			var->value = val;
			free(key);
		}
		else
		{
			t_env	*new = malloc(sizeof(t_env));
			new->key = key;
			new->value = val;
			new->next = *env;
			*env = new;
		}
		i++;
	}
	return (0);
}
