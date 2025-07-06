/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:27:05 by almeddah          #+#    #+#             */
/*   Updated: 2025/07/06 17:56:37 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_loop(t_data *data)
{
	char	*prompt;
	t_env	*env;

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
			env = env_to_list((*data).envp);
			(*data).exit_code = execute_commands((*data).command_list, &env);
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
