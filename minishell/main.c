/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:27:05 by almeddah          #+#    #+#             */
/*   Updated: 2025/08/08 17:16:45 by alae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_loop(t_data *data)
{
	char	*prompt;

	prompt = readline("$> ");
	if (!prompt)
		return (1);
	if (*prompt)
	{
		add_history(prompt);
		(*data).token_list = create_token_list(prompt);
		if ((*data).token_list)
		{
			(*data).command_list = create_command_list((*data));
			free_char_list((*data).token_list);
			(*data).exit_code = setup_cmds(data);
			free_command_list((*data).command_list);
		}
	}
	free(prompt);
	return (0);
}

char	**dup_env(char **envp)
{
	int		i;
	char	**copy;
	int		j;

	i = 0;
	while (envp[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	j = 0;
	while (j < i)
	{
		copy[j] = ft_strdup(envp[j]);
		j++;
	}
	copy[i] = NULL;
	return (copy);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		x;

	x = 0;
	(void)argc;
	(void)argv;
	data.exit_code = 0;
	data.command_list = NULL;
	data.token_list = NULL;
	data.envp = dup_env(envp);
	setup_signals();
	while (!x)
		x = minishell_loop(&data);
	free_char_list(data.envp);
	return (0);
}
