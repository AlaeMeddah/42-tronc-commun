/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ameddah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:54:13 by ameddah           #+#    #+#             */
/*   Updated: 2024/04/12 14:42:03 by ameddah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push(t_list **src, t_list **dst)
{
	t_list	*src_;
	t_list	*dst_;
	t_list	*temp;

	src_ = *src;
	dst_ = *dst;
	temp = src_;
	src_ = src_->next;
	if (src_)
		src_->previous = NULL;
	if (dst_)
		dst_->previous = temp;
	temp->next = dst_;
	*dst = temp;
	*src = src_;
	return ;
}
