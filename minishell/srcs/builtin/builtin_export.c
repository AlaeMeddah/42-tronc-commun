/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:53:27 by alae              #+#    #+#             */
/*   Updated: 2025/08/08 14:42:27 by alae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_key(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	print_export(char **envp, int count)
{
	char	*tmp;
	int		i;
	int		j;

	while (envp[count])
		count++;
	i = -1;
	while (++i < count - 1)
	{
		j = -1;
		while (++j < count - i - 1)
		{
			if (ft_strcmp(envp[j], envp[j + 1]) > 0)
			{
				tmp = envp[j];
				envp[j] = envp[j + 1];
				envp[j + 1] = tmp;
			}
		}
	}
	i = -1;
	while (++i < count)
		printf("export %s\n", envp[i]);
	return (0);
}

char	**split_on_first_equal(char *str)
{
	char	**res;
	char	*eq_pos;
	size_t	key_len;

	res = malloc(sizeof(char *) * 3);
	if (!res)
		return (NULL);
	eq_pos = ft_strchr(str, '=');
	key_len = eq_pos - str;
	res[0] = ft_strncpy(str, key_len);
	res[1] = ft_strdup(eq_pos + 1);
	res[2] = NULL;
	return (res);
}

void	export_to_env(char *var, char ***envp)
{
	char	**sep;
	int		y;
	int		len;

	if (ft_strchr(var, '='))
	{
		sep = split_on_first_equal(var);
		*envp = ft_setenv(*envp, sep[0], sep[1]);
		free_char_list(sep);
	}
	else
	{
		y = 0;
		len = ft_strlen(var);
		while ((*envp)[y])
		{
			if (!ft_strncmp(var, (*envp)[y], len) && ((*envp)[y][len] == '='
					|| !((*envp)[y][len])))
				return ;
			y++;
		}
		*envp = add_var_to_env(*envp, ft_strdup(var));
	}
}

int	builtin_export(char **argv, char ***envp)
{
	int	i;
	int	valid;

	i = 1;
	valid = 0;
	if (!argv[i])
		return (print_export(*envp, 0));
	while (argv[i])
	{
		if (is_valid_key(argv[i]))
			export_to_env(argv[i], envp);
		else
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			valid = 1;
		}
		i++;
	}
	return (valid);
}
