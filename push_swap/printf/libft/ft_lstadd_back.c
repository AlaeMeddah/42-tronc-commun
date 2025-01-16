/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ameddah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:20:37 by ameddah           #+#    #+#             */
/*   Updated: 2023/11/22 10:20:41 by ameddah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*previous;

	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		previous = ft_lstlast(*lst);
		previous->next = new;
		previous->next->previous = previous;
	}
}
