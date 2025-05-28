/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:41:24 by almeddah          #+#    #+#             */
/*   Updated: 2025/05/28 12:12:05 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_input_redirects(t_input_redirect *input_redirect)
{
	while (input_redirect)
	{
		if (input_redirect->heredoc)
			printf("<< %s ", input_redirect->file);
		else
			printf("< %s ", input_redirect->file);
		input_redirect = input_redirect->next;
	}
}

void	display_output_redirects(t_output_redirect *output_redirect)
{
	while (output_redirect)
	{
		if (output_redirect->append)
			printf(">> %s ", output_redirect->file);
		else
			printf("> %s ", output_redirect->file);
		output_redirect = output_redirect->next;
	}
}

void	display_command(t_command *cmd)
{
	int	i;

	if (!cmd)
	{
		printf("No command\n");
		return ;
	}
	display_input_redirects(cmd->input_redirect);
	display_output_redirects(cmd->output_redirect);
	if (cmd->argv)
	{
		i = 0;
		while (cmd->argv[i])
		{
			printf("%s ", cmd->argv[i]);
			i++;
		}
	}
	printf("\n");
}

void	display_command_list(t_command *cmd_list)
{
	while (cmd_list)
	{
		display_command(cmd_list);
		cmd_list = cmd_list->next;
	}
}

void	print_data(char **data)
{
	while (*data)
	{
		printf("%s\n", *data);
		data++;
	}
	printf("%p\n", *data);
}
