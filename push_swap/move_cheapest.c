/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ameddah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:45:51 by ameddah           #+#    #+#             */
/*   Updated: 2024/04/12 14:58:53 by ameddah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_list	*find_cheapest(t_list *a)
{
	t_list	*cheapest;

	cheapest = a;
	while (a)
	{
		if ((a)->cost < cheapest->cost)
			cheapest = a;
		a = (a)->next;
	}
	return (cheapest);
}

void	move_cheapest_1(t_list *cheapest, t_list **a, t_list **b)
{
	while (*a != cheapest && *b != cheapest->target)
		double_rotate(a, b);
	while (*a != cheapest)
	{
		rotate(a);
		ft_printf("ra\n");
	}
	while (*b != cheapest->target)
	{
		rotate(b);
		ft_printf("rb\n");
	}
}

void	move_cheapest_2(t_list *cheapest, t_list **a, t_list **b)
{
	while (*a != cheapest && *b != cheapest->target)
		double_reverse_rotate(a, b);
	while (*a != cheapest)
	{
		reverse_rotate(a);
		ft_printf("rra\n");
	}
	while (*b != cheapest->target)
	{
		reverse_rotate(b);
		ft_printf("rrb\n");
	}
}

void	move_cheapest_3(t_list *cheapest, t_list **a)
{
	if (cheapest->mid == 0)
	{
		while (*a != cheapest)
		{
			rotate(a);
			ft_printf("ra\n");
		}
	}
	else
	{
		while (*a != cheapest)
		{
			reverse_rotate(a);
			ft_printf("rra\n");
		}
	}
}

void	move_cheapest_4(t_list *cheapest, t_list **b)
{
	if (cheapest->target->mid == 0)
	{
		while (*b != cheapest->target)
		{
			rotate(b);
			ft_printf("rb\n");
		}
	}
	else
	{
		while (*b != cheapest->target)
		{
			reverse_rotate(b);
			ft_printf("rrb\n");
		}
	}
}
