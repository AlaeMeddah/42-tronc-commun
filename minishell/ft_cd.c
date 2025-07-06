/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minhpham <minhpham@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 02:13:31 by minhpham          #+#    #+#             */
/*   Updated: 2025/07/06 14:33:19 by minhpham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_env *env, const char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	set_env_value(t_env **env, const char *key, const char *value)
{
	t_env *curr = *env;

	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
		{
			free(curr->value);
			curr->value = ft_strdup(value);
			return ;
		}
		curr = curr->next;
	}
	t_env *new = env_new(ft_strdup(key), ft_strdup(value));
	if (!new)
		return ;
	new->next = *env;
	*env = new;
}

static char	*resolve_cd_target(char **args, t_env *env, int *print)
{
	char	*target;

	*print = 0;
	if (!args[1] || !ft_strcmp(args[1], "~"))
	{
		target = get_env_value(env, "HOME");
		if (!target)
			fprintf(stderr, "cd: HOME not set\n");
	}
	else if (!ft_strcmp(args[1], "-"))
	{
		target = get_env_value(env, "OLDPWD");
		if (!target)
			fprintf(stderr, "cd: OLDPWD not set\n");
		else
			*print = 1;
	}
	else
		target = args[1];
	return (target);
}

static void	update_pwd(t_env **env, char *oldpwd)
{
	char	cwd[PATH_MAX];

	set_env_value(env, "OLDPWD", oldpwd);
	if (getcwd(cwd, sizeof(cwd)))
		set_env_value(env, "PWD", cwd);
}

int	ft_cd(char **args, t_env **env)
{
	char	*oldpwd;
	char	*target;
	int		print;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (perror("cd"), 1);
	target = resolve_cd_target(args, *env, &print);
	if (!target)
		return (free(oldpwd), 1);
	if (chdir(target) != 0)
		return (perror("cd"), free(oldpwd), 1);
	if (print)
		printf("%s\n", target);
	update_pwd(env, oldpwd);
	free(oldpwd);
	return (0);
}
