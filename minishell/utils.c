/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:46:11 by almeddah          #+#    #+#             */
/*   Updated: 2025/05/13 18:18:41 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_last(void *list)
{
	t_list	*node;

	node = (t_list *)list;
	if (node)
	{
		while (node->next)
			node = node->next;
	}
	return ((void *)node);
}

void	ft_add_back(void **list, void *new)
{
	t_list	*last;

	if (new)
	{
		if (*list == NULL)
			*list = new;
		else
		{
			last = (t_list *)ft_last(*list);
			last->next = (t_list *)new;
		}
	}
}

char	*ft_strncpy(char *src, int n)
{
	int		i;
	char	*dest;

	i = 0;
	dest = malloc(sizeof(char) * (n + 1));
	if (!dest)
	{
		printf("dest allocation error\n");
		return (NULL);
	}
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	nb_quoted_char(char *str)
{
	int	i;

	i = 1;
	while (str[i] != *str)
	{
		if (!str[i])
			return (0);
		i++;
	}
	return (i);
}
