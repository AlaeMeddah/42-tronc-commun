/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:46:49 by ameddah           #+#    #+#             */
/*   Updated: 2024/05/29 12:13:42 by alae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	rotate(t_list **stack)
{
	t_list	*first;
	t_list	*last;
	t_list	*stack_;

	if (ft_lstsize(*stack) < 2)
		return (1);
	first = *stack;
	stack_ = *stack;
	last = ft_lstlast(stack_);
	stack_ = stack_->next;
	stack_->previous = NULL;
	first->next = NULL;
	first->previous = last;
	last->next = first;
	*stack = stack_;
	return (0);
}

int	reverse_rotate(t_list **stack)
{
	t_list	*last;
	t_list	*stack_;

	if (ft_lstsize(*stack) < 2)
		return (1);
	stack_ = *stack;
	last = ft_lstlast(stack_);
	last->previous->next = NULL;
	last->previous = NULL;
	last->next = stack_;
	stack_->previous = last;
	*stack = last;
	return (0);
}

int	double_rotate(t_list **a, t_list **b)
{
	return (rotate(a) + rotate(b));
}

int	double_reverse_rotate(t_list **a, t_list **b)
{
	return (reverse_rotate(a) + reverse_rotate(b));
}
