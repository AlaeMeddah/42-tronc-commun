/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:37:57 by almeddah          #+#    #+#             */
/*   Updated: 2025/08/18 18:08:05 by alae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_input_redirect(t_input_redirect *input_redirect)
{
	t_input_redirect	*tmp;

	while (input_redirect)
	{
		tmp = input_redirect;
		if (input_redirect->heredoc)
			unlink(input_redirect->file);
		if (input_redirect->file)
			free(input_redirect->file);
		input_redirect = input_redirect->next;
		free(tmp);
	}
}

void	free_output_redirect(t_output_redirect *output_redirect)
{
	t_output_redirect	*tmp;

	while (output_redirect)
	{
		tmp = output_redirect;
		if (output_redirect->file)
			free(output_redirect->file);
		output_redirect = output_redirect->next;
		free(tmp);
	}
}

void	free_command(t_command *cmd)
{
	int	i;

	if (cmd)
	{
		if (cmd->argv)
		{
			i = 0;
			while (cmd->argv[i])
			{
				free(cmd->argv[i]);
				i++;
			}
			free(cmd->argv);
		}
		free_input_redirect(cmd->input_redirect);
		free_output_redirect(cmd->output_redirect);
		free(cmd);
	}
}

void	free_command_list(t_command *cmd_list)
{
	t_command	*tmp;

	while (cmd_list)
	{
		tmp = cmd_list;
		cmd_list = cmd_list->next;
		free_command(tmp);
	}
}

void	free_char_list(char **data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		free(data[i]);
		i++;
	}
	free(data);
}
