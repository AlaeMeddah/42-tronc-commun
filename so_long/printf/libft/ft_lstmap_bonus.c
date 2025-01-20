/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:36:26 by almeddah          #+#    #+#             */
/*   Updated: 2025/01/20 18:49:20 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
// {
// 	t_list	*new_lst;
// 	t_list	*new_node;

// 	new_lst = 0;
// 	if (lst && f)
// 	{
// 		while (lst)
// 		{
// 			new_node = ft_lstnew(f(lst->content));
// 			if (!new_node)
// 			{
// 				ft_lstclear(&new_lst, del);
// 				return (0);
// 			}
// 			ft_lstadd_back(&new_lst, new_node);
// 			lst = lst->next;
// 		}
// 	}
// 	return (new_lst);
// }
