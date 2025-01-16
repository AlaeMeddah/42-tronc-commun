/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:05:59 by ameddah           #+#    #+#             */
/*   Updated: 2024/05/29 13:28:32 by alae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

t_list	*convert_to_stack(int **list)
{
	int		i;
	t_list	*stack;

	stack = ft_lstnew(*list[0]);
	i = 1;
	while (list[i])
	{
		ft_lstadd_back(&stack, ft_lstnew(*list[i]));
		i++;
	}
	return (stack);
}

void	free_list(void **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
}

int	convert_to_int(char **list, int ***list_int, int argc)
{
	int	i;

	i = 0;
	*list_int = malloc((argc) * sizeof(int *));
	if (*list_int == NULL)
		return (0);
	while (list[i])
	{
		(*list_int)[i] = malloc(sizeof(int));
		if ((*list_int)[i] == NULL)
			return (0);
		*(*list_int)[i] = (int) ft_atoi(list[i]);
		i++;
	}
	(*list_int)[i] = 0;
	return (1);
}

void	free_stack(t_list *stack)
{
	t_list	*temp;

	while (stack->next)
	{
		temp = stack->next;
		free(stack);
		stack = temp;
	}
	free(stack);
}

int	main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;

	a = NULL;
	b = NULL;
	if (argc < 2)
		return (0);
	if (!checks(argc, argv, &a))
	{
		ft_printf("Error\n");
		return (0);
	}
	sort(&a, &b);
	if (a)
		free_stack(a);
	if (b)
		free_stack(b);
	return (0);
}
