/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 23:59:35 by ameddah           #+#    #+#             */
/*   Updated: 2024/05/23 21:20:35 by alae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
	{
		len++;
	}
	return (len);
}

t_lis	*ft_lst_get_last(t_lis *stash)
{
	t_lis	*current;

	current = stash;
	while (current && current->next)
		current = current->next;
	return (current);
}

void	add_to_stash(t_lis **stash, char *content, int readed)
{
	int		i;
	t_lis	*last;
	t_lis	*new_node;

	new_node = malloc(sizeof(t_lis));
	if (new_node == NULL)
		return ;
	new_node->next = NULL;
	new_node->content = malloc(sizeof(char) * (readed + 1));
	if (new_node->content == NULL)
		return ;
	i = 0;
	while (content[i] && i < readed)
	{
		new_node->content[i] = content[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*stash == NULL)
	{
		*stash = new_node;
		return ;
	}
	last = ft_lst_get_last(*stash);
	last->next = new_node;
}

void	free_stash(t_lis *stash)
{
	t_lis	*node;
	t_lis	*next;

	node = stash;
	while (node)
	{
		free(node->content);
		next = node->next;
		free(node);
		node = next;
	}
}

void	clean_stash(t_lis **stash)
{
	t_lis	*last;
	t_lis	*clean_node;
	int		i;
	int		j;

	clean_node = malloc(sizeof(t_lis));
	if (stash == NULL || clean_node == NULL)
		return ;
	clean_node->next = NULL;
	last = ft_lst_get_last(*stash);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	clean_node->content = malloc(sizeof(char)
			* ((ft_strlen(last->content) - i) + 1));
	if (clean_node->content == NULL)
		return ;
	j = 0;
	while (last->content[i])
		clean_node->content[j++] = last->content[i++];
	clean_node->content[j] = '\0';
	free_stash(*stash);
	*stash = clean_node;
}
