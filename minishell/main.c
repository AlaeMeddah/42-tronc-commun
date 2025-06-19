/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:27:05 by almeddah          #+#    #+#             */
/*   Updated: 2025/06/19 10:52:45 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*prompt;
	t_data		data;
	t_command	*list;

	// int			i;
	(void)argc;
	(void)argv;
	data.exit_code = 0;
	data.command_list = NULL;
	data.token_list = NULL;
	data.envp = envp;
	setup_signals();
	while (1)
	{
		prompt = readline("$> ");
		if (!prompt)
			break ;
		if (*prompt)
		{
			add_history(prompt);
			data.token_list = create_token_list(prompt);
			if (data.token_list)
			{
				data.command_list = create_command_list(data);
				free_char_list(data.token_list);
				list = data.command_list;
				execute_commands(list, data.envp);
				free_command_list(data.command_list);
			}
		}
		free(prompt);
	}
	return (0);
}
