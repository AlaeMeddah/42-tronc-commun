/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:11:42 by almeddah          #+#    #+#             */
/*   Updated: 2025/05/30 14:22:05 by alae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_input_redirect	*create_input_redirect(char *str1, char *str2, char **envp)
{
	t_input_redirect	*new_redir;

	if (!str2)
		return (NULL);
	new_redir = malloc(sizeof(t_input_redirect));
	if (!new_redir)
	{
		printf("redirection input allocation error\n");
		return (NULL);
	}
	new_redir->file = NULL;
	new_redir->heredoc = 0;
	if (!ft_strcmp(str1, "<"))
		new_redir->file = expand_token(str2, envp);
	else
	{
		new_redir->file = heredoc(str2, envp);
		new_redir->heredoc = 1;
	}
	new_redir->next = NULL;
	return (new_redir);
}

t_output_redirect	*create_output_redirect(char *str1, char *str2, char **envp)
{
	t_output_redirect	*new_redir;

	if (!str2)
		return (NULL);
	new_redir = malloc(sizeof(t_output_redirect));
	if (!new_redir)
	{
		printf("redirection output allocation error\n");
		return (NULL);
	}
	new_redir->file = expand_token(str2, envp);
	new_redir->append = 0;
	if (!ft_strcmp(str1, ">>"))
		new_redir->append = 1;
	new_redir->next = NULL;
	return (new_redir);
}
