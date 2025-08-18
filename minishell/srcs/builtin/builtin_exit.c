/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:50:23 by alae              #+#    #+#             */
/*   Updated: 2025/08/18 19:09:35 by alae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	clean_up(int fd, t_data *data)
{
	dup2(fd, STDOUT_FILENO);
	close(fd);
	free_char_list((*data).envp);
	free_command_list((*data).command_list);
}

int	builtin_exit(char **args, t_data *data, int fd)
{
	int	exit_code;

	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	if (!args[1])
	{
		clean_up(fd, data);
		exit((*data).exit_code);
	}
	if (!is_numeric(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		clean_up(fd, data);
		exit(2);
	}
	exit_code = ft_atoi(args[1]) % 256;
	clean_up(fd, data);
	exit(exit_code);
}
