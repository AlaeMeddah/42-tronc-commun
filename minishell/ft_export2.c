/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhpham <minhpham@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 01:48:58 by minhpham          #+#    #+#             */
/*   Updated: 2025/04/21 07:38:10 by minhpham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_size(t_env *env)
{
	int	i = 0;

	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

t_env	**env_to_array(t_env *env, int *size)
{
	t_env	**array;
	int		i;

	*size = env_size(env);
	array = malloc(sizeof(t_env *) * (*size));
	if (!array)
		return (NULL);
	i = 0;
	while (env)
	{
		array[i++] = env;
		env = env->next;
	}
	return (array);
}

void	sort_env_array(t_env **array, int size)
{
	int		i;
	int		swapped;
	t_env	*tmp;

	if (!array || size < 2)
		return ;
	do {
		swapped = 0;
		i = 0;
		while (i < size - 1)
		{
			if (ft_strncmp(array[i]->key, array[i + 1]->key, ~0) > 0)
			{
				tmp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = tmp;
				swapped = 1;
			}
			i++;
		}
	} while (swapped);
}

void	print_export_line(t_env *env)
{
	write(1, "declare -x ", 11);
	write(1, env->key, ft_strlen(env->key));
	if (env->value)
	{
		write(1, "=\"", 2);
		write(1, env->value, ft_strlen(env->value));
		write(1, "\"", 1);
	}
	write(1, "\n", 1);
}

void	print_export(t_env *env)
{
	t_env	**array;
	int		size;
	int		i;

	array = env_to_array(env, &size);
	if (!array)
		return ;
	sort_env_array(array, size);
	i = 0;
	while (i < size)
		print_export_line(array[i++]);
	free(array);
}
