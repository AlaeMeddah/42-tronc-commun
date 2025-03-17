/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ameddah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:50:39 by ameddah           #+#    #+#             */
/*   Updated: 2024/04/08 15:50:40 by ameddah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmax(t_list *lst)
{
	t_list	*temp;

	if (lst)
	{
		temp = lst;
		while (lst)
		{
			if (temp->content < lst->content)
				temp = lst;
			lst = lst->next;
		}
	}
	return (temp);
}

t_list	*ft_lstmin(t_list *lst)
{
	t_list	*temp;

	if (lst)
	{
		temp = lst;
		while (lst)
		{
			if (temp->content > lst->content)
				temp = lst;
			lst = lst->next;
		}
	}
	return (temp);
}
