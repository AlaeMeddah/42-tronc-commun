/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:54:13 by ameddah           #+#    #+#             */
/*   Updated: 2024/05/29 12:48:49 by alae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	push(t_list **src, t_list **dst)
{
	t_list	*src_;
	t_list	*dst_;
	t_list	*temp;

	if (ft_lstsize(*src) < 1)
		return (1);
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
	return (0);
}
