/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:40:27 by alae              #+#    #+#             */
/*   Updated: 2025/08/07 13:55:13 by alae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_out_redirect(t_command *cmd)
{
	t_output_redirect	*out;
	int					fd;

	out = cmd->output_redirect;
	while (out)
	{
		if (out->append)
			fd = open(out->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(out->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (perror(out->file), 1);
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (perror("dup2"), close(fd), 0);
		close(fd);
		out = out->next;
	}
	return (1);
}

int	setup_in_redirect(t_command *cmd)
{
	int					fd;
	t_input_redirect	*in;

	in = cmd->input_redirect;
	while (in)
	{
		fd = open(in->file, O_RDONLY);
		if (fd == -1)
			return (perror(in->file), 1);
		if (dup2(fd, STDIN_FILENO) == -1)
			return (perror("dup2"), close(fd), 0);
		close(fd);
		in = in->next;
	}
	return (1);
}

int	setup_redirect(t_command *cmd)
{
	if (!setup_in_redirect(cmd) || !setup_out_redirect(cmd))
		return (0);
	return (1);
}
