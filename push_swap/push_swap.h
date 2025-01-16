/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ameddah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:47:07 by ameddah           #+#    #+#             */
/*   Updated: 2024/04/12 15:06:14 by ameddah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "printf/ft_printf.h"

void	move_cheapest_1(t_list *cheapest, t_list **a, t_list **b);
void	move_cheapest_2(t_list *cheapest, t_list **a, t_list **b);
void	move_cheapest_3(t_list *cheapest, t_list **a);
void	move_cheapest_4(t_list *cheapest, t_list **b);
void	double_rotate(t_list **a, t_list **b);
void	double_reverse_rotate(t_list **a, t_list **b);
void	rotate(t_list **stack);
void	reverse_rotate(t_list **stack);
void	swap(t_list **stack);
void	push(t_list **src, t_list **dst);
void	sort(t_list **a, t_list **b);
void	finish_sort(t_list **a, t_list **b);
void	free_list(void **list);
void	assign_costs(t_list **a_);
void	assign_position(t_list **stack_);
void	assign_targets(t_list **a_, t_list **b_);
void	assign_targets_2(t_list **b, t_list **a);
int		checks(int argc, char **argv, t_list **a);
int		convert_to_int(char **list, int ***list_int, int argc);
t_list	*convert_to_stack(int **list);
t_list	*find_cheapest(t_list *a);

#endif
