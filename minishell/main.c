/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:27:05 by almeddah          #+#    #+#             */
/*   Updated: 2025/08/05 15:42:23 by alae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_loop(t_data *data)
{
	char	*prompt;

	// t_env	*env;
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
			// env = env_to_list((*data).envp);
			// (*data).exit_code = execute_commands((*data).command_list, &env);
			setup_cmds((*data).command_list, (*data).envp);
			free_command_list((*data).command_list);
		}
	}
	free(prompt);
	return (0);
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
	data.envp = envp;
	setup_signals();
	while (!x)
		x = minishell_loop(&data);
	return (0);
}
