/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:47:07 by ameddah           #+#    #+#             */
/*   Updated: 2024/05/29 13:05:10 by alae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "../printf/ft_printf.h"
# include "get_next_line/get_next_line.h"

int		double_rotate(t_list **a, t_list **b);
int		double_reverse_rotate(t_list **a, t_list **b);
int		double_swap(t_list **a, t_list **b);
int		rotate(t_list **stack);
int		reverse_rotate(t_list **stack);
int		swap(t_list **stack);
int		push(t_list **src, t_list **dst);
void	sort(t_list **a, t_list **b);
void	free_list(void **list);
int		checks(int argc, char **argv, t_list **a);
int		convert_to_int(char **list, int ***list_int, int argc);
t_list	*convert_to_stack(int **list);

#endif
