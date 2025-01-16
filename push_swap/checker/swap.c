/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:54:56 by ameddah           #+#    #+#             */
/*   Updated: 2024/05/29 12:56:35 by alae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	swap(t_list **stack)
{
	int		temp;
	t_list	*stack_;

	if (ft_lstsize(*stack) < 2)
		return (1);
	stack_ = *stack;
	temp = stack_->content;
	stack_->content = stack_->next->content;
	stack_->next->content = temp;
	*stack = stack_;
	return (0);
}

int	double_swap(t_list **a, t_list **b)
{
	return (swap(a) + swap(b));
}
