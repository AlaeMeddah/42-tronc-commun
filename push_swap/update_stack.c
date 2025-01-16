/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ameddah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:49:33 by ameddah           #+#    #+#             */
/*   Updated: 2024/04/12 14:55:01 by ameddah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	assign_targets_2(t_list **b, t_list **a)
{
	t_list	*b_;

	assign_position(a);
	assign_targets(b, a);
	b_ = *b;
	while (b_)
	{
		b_->target = b_->target->next;
		if (!b_->target)
			b_->target = *a;
		b_ = b_->next;
	}
}

void	assign_targets(t_list **a_, t_list **b_)
{
	long	temp;
	t_list	*a;
	t_list	*b;

	a = *a_;
	b = *b_;
	while (a)
	{
		a->diff_target = LONG_MAX;
		a->target = ft_lstmax(b);
		while (b)
		{
			temp = (long)(a->content - b->content);
			if (temp < a->diff_target && temp > 0)
			{
				a->diff_target = temp;
				a->target = b;
			}
			b = b->next;
		}
		b = *b_;
		a = a->next;
	}
}

void	assign_costs(t_list **a_)
{
	t_list	*a;
	t_list	*b;

	a = *a_;
	while (a)
	{
		b = a->target;
		if (a->mid == b->mid)
			a->cost = ft_max(a->position, b->position);
		else
			a->cost = a->position + b->position;
		a = a->next;
	}
}

void	assign_position(t_list **stack_)
{
	int		i;
	int		len;
	int		mid;
	t_list	*stack;

	i = -1;
	mid = 0;
	stack = *stack_;
	len = ft_lstsize(stack);
	while (stack)
	{
		if (!mid)
			i++;
		else
			i--;
		stack->mid = mid;
		stack->position = i;
		if (mid)
			stack->position += 1;
		if (len % 2 == 0 && i == len / 2 - 1 && !mid)
			i++;
		if (i == len / 2)
			mid = 1;
		stack = stack->next;
	}
}
