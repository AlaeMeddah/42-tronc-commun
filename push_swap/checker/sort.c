/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:58:37 by alae              #+#    #+#             */
/*   Updated: 2024/05/30 07:09:25 by alae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

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

int	move(t_list **a, t_list **b, char *line, int *error)
{
	if (ft_strncmp(line, "sa\n", 3) == 0)
		return (swap(a));
	else if (ft_strncmp(line, "sb\n", 3) == 0)
		return (swap(b));
	else if (ft_strncmp(line, "ss\n", 3) == 0)
		return (double_swap(a, b));
	else if (ft_strncmp(line, "pa\n", 3) == 0)
		return (push(b, a));
	else if (ft_strncmp(line, "pb\n", 3) == 0)
		return (push(a, b));
	else if (ft_strncmp(line, "ra\n", 3) == 0)
		return (rotate(a));
	else if (ft_strncmp(line, "rb\n", 3) == 0)
		return (rotate(b));
	else if (ft_strncmp(line, "rra\n", 4) == 0)
		return (reverse_rotate(a));
	else if (ft_strncmp(line, "rrb\n", 4) == 0)
		return (reverse_rotate(b));
	else if (ft_strncmp(line, "rr\n", 3) == 0)
		return (double_rotate(a, b));
	else if (ft_strncmp(line, "rrr\n", 4) == 0)
		return (double_reverse_rotate(a, b));
	*error = 1;
	return (1);
}

void	finish_reading(void)
{
	int		reading;
	char	*line;

	reading = 1;
	while (reading)
	{
		line = get_next_line(STDERR_FILENO);
		if (!line)
			reading = 0;
		free(line);
	}
}

void	sort(t_list **a, t_list **b)
{
	char	*line;
	int		reading;
	int		stop;
	int		error;

	reading = 1;
	error = 0;
	stop = 0;
	while (reading && !stop)
	{
		line = get_next_line(STDERR_FILENO);
		if (line)
			stop = move(a, b, line, &error);
		else
			reading = 0;
		free(line);
	}
	if (reading)
		finish_reading();
	if (error)
		ft_printf("Error\n");
	else if (stop || !sorted(*a))
		ft_printf("KO\n");
	else
		ft_printf("OK\n");
}
