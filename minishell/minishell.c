/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 23:25:49 by minhpham          #+#    #+#             */
/*   Updated: 2025/04/24 19:34:26 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	ft_echo(argv);
// 	return (0);
// }

// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	(void)argv;
// 	ft_pwd();
// 	return (0);
// }

// int	main(int argc, char **argv)
// {
// 	ft_cd(argv);
// 	return (0);
// }

// int	main(int argc, char **argv)
// {
// 	ft_exit(argv, 0);
// 	return (0);
// }
// t_env	*new_env(char *key, char *value)
// {
// 	t_env	*env;

// 	env = malloc(sizeof(t_env));
// 	if (!env)
// 		return (NULL);
// 	env->key = key;
// 	env->value = value;
// 	env->next = NULL;
// 	return (env);
// }
// int	main(void)
// {
// 	t_env	*e1 = new_env("PATH", "/usr/bin:/bin");
// 	t_env	*e2 = new_env("SHELL", "/bin/bash");
// 	t_env	*e3 = new_env("EMPTY", NULL);
// 	e1->next = e2;
// 	e2->next = e3;
// 	ft_env(e1);
// 	return (0);
// }

// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	t_env	*env = NULL;
// 	ft_export(argv, &env);
// 	ft_env(env);
// 	return (0);
// }
