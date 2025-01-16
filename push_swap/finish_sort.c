/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:02:07 by ameddah           #+#    #+#             */
/*   Updated: 2024/05/30 07:00:50 by alae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	finish_sort_2(t_list **a, t_list **b)
{
	while (*b)
	{
		if ((*a)->content != (*b)->target->content)
		{
			assign_targets_2(b, a);
			if (!(*b)->target->mid)
			{
				while (*a != (*b)->target)
				{
					rotate(a);
					ft_printf("ra\n");
				}
			}
			else
			{
				while (*a != (*b)->target)
				{
					reverse_rotate(a);
					ft_printf("rra\n");
				}
			}
		}
		push(b, a);
		ft_printf("pa\n");
	}
}

void	finish_sort_1(t_list **a, t_list **b)
{
	assign_targets_2(b, a);
	if (!(*b)->target->mid)
	{
		while (*a != (*b)->target)
		{
			rotate(a);
			ft_printf("ra\n");
		}
	}
	else
	{
		while (*a != (*b)->target)
		{
			reverse_rotate(a);
			ft_printf("rra\n");
		}
	}
}

void	finish_sort(t_list **a, t_list **b)
{
	t_list	*min;

	finish_sort_1(a, b);
	finish_sort_2(a, b);
	assign_position(a);
	min = ft_lstmin(*a);
	if (!min->mid)
	{
		while (*a != min)
		{
			rotate(a);
			ft_printf("ra\n");
		}
	}
	else
	{
		while (*a != min)
		{
			reverse_rotate(a);
			ft_printf("rra\n");
		}
	}
}
