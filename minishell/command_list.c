/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:01:32 by almeddah          #+#    #+#             */
/*   Updated: 2025/07/06 04:22:37 by alae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*create_new_command(t_command *command_list, int i)
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_command));
	if (!new_command)
	{
		printf("command allocation error\n");
		free_command_list(command_list);
		return (NULL);
	}
	new_command->next = NULL;
	new_command->input_redirect = NULL;
	new_command->output_redirect = NULL;
	new_command->argv = malloc(sizeof(char *) * (i + 1));
	if (!new_command->argv)
	{
		printf("command arg allocation error\n");
		free_command_list(command_list);
		return (NULL);
	}
	return (new_command);
}

int	handle_new_command(t_data data, int *i, t_command *new_command)
{
	int	j;

	j = 0;
	while (data.token_list[*i] && ft_strcmp(data.token_list[*i], "|"))
	{
		if (is_redirection(data.token_list[*i]))
		{
			if (redirection_error(data.token_list, *i))
				return (0);
			else
			{
				if (!create_redirect(data, *i, new_command))
					return (0);
			}
			*i += 2;
		}
		else
		{
			new_command->argv[j] = expand_token(data.token_list[(*i)++], data);
			if (new_command->argv[j])
				j++;
		}
	}
	new_command->argv[j] = NULL;
	return (1);
}

int	add_command_to_list(t_data data, int *i, t_command **command_list)
{
	t_command	*new_command;

	*i = 0;
	while (data.token_list[*i] && ft_strcmp(data.token_list[*i], "|"))
		(*i)++;
	new_command = create_new_command(*command_list, *i);
	if (!new_command)
		return (0);
	*i = 0;
	if (!handle_new_command(data, i, new_command))
	{
		free_command_list(*command_list);
		return (0);
	}
	ft_add_back((void **)command_list, new_command);
	return (1);
}

void	*pipe_error(t_command *command_list)
{
	printf("pipe error\n");
	free_command_list(command_list);
	return (NULL);
}

t_command	*create_command_list(t_data data)
{
	t_command	*command_list;
	int			i;

	command_list = NULL;
	while (*data.token_list)
	{
		if (!ft_strcmp(*data.token_list, "|"))
			return (pipe_error(command_list));
		if (!add_command_to_list(data, &i, &command_list))
			return (NULL);
		data.token_list += i;
		if (*data.token_list)
		{
			if (!ft_strcmp(*data.token_list, "|") && (!*(data.token_list + 1)))
				return (pipe_error(command_list));
			data.token_list++;
		}
	}
	return (command_list);
}
