/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ameddah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:46:38 by ameddah           #+#    #+#             */
/*   Updated: 2024/04/12 15:10:21 by ameddah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_small(t_list **stack)
{
	t_list	*max;
	int		size;

	max = ft_lstmax(*stack);
	size = ft_lstsize(*stack);
	if (*stack == max)
	{
		rotate(stack);
		ft_printf("ra\n");
	}
	if (size == 2)
		return ;
	if ((*stack)->next == max)
	{
		reverse_rotate(stack);
		ft_printf("rra\n");
	}
	if ((*stack)->content > (*stack)->next->content)
	{
		swap(stack);
		ft_printf("sa\n");
	}
}

void	move_cheapest(t_list **a, t_list **b)
{
	t_list	*cheapest;

	cheapest = find_cheapest(*a);
	if (cheapest->mid == cheapest->target->mid)
	{
		if (cheapest->mid == 0)
			move_cheapest_1(cheapest, a, b);
		else
			move_cheapest_2(cheapest, a, b);
	}
	else
	{
		move_cheapest_3(cheapest, a);
		move_cheapest_4(cheapest, b);
	}
	push(a, b);
	ft_printf("pb\n");
}

int	sorted(t_list *a)
{
	long	x;

	x = LONG_MIN;
	while (a)
	{
		if ((long) a->content < x)
			return (0);
		x = (long) a->content;
		a = a->next;
	}
	return (1);
}

void	sort(t_list **a, t_list **b)
{
	int			size;

	size = ft_lstsize(*a);
	if (sorted(*a))
		return ;
	if (size > 3)
	{
		push(a, b);
		push(a, b);
		ft_printf("pb\npb\n");
		size -= 2;
		while (size > 3)
		{
			assign_position(a);
			assign_position(b);
			assign_targets(a, b);
			assign_costs(a);
			move_cheapest(a, b);
			size--;
		}
		sort_small(a);
		finish_sort(a, b);
	}
	else
		sort_small(a);
}
