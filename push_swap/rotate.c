/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ameddah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:46:49 by ameddah           #+#    #+#             */
/*   Updated: 2024/04/12 14:42:44 by ameddah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate(t_list **stack)
{
	t_list	*first;
	t_list	*last;
	t_list	*stack_;

	first = *stack;
	stack_ = *stack;
	last = ft_lstlast(stack_);
	stack_ = stack_->next;
	stack_->previous = NULL;
	first->next = NULL;
	first->previous = last;
	last->next = first;
	*stack = stack_;
	return ;
}

void	reverse_rotate(t_list **stack)
{
	t_list	*last;
	t_list	*stack_;

	stack_ = *stack;
	last = ft_lstlast(stack_);
	last->previous->next = NULL;
	last->previous = NULL;
	last->next = stack_;
	stack_->previous = last;
	*stack = last;
	return ;
}

void	double_rotate(t_list **a, t_list **b)
{
	rotate(a);
	rotate(b);
	ft_printf("rr\n");
	return ;
}

void	double_reverse_rotate(t_list **a, t_list **b)
{
	reverse_rotate(a);
	reverse_rotate(b);
	ft_printf("rrr\n");
	return ;
}
