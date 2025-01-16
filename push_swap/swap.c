/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ameddah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:54:56 by ameddah           #+#    #+#             */
/*   Updated: 2024/04/12 14:43:00 by ameddah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(t_list **stack)
{
	int		temp;
	t_list	*stack_;

	stack_ = *stack;
	temp = stack_->content;
	stack_->content = stack_->next->content;
	stack_->next->content = temp;
	*stack = stack_;
	return ;
}
