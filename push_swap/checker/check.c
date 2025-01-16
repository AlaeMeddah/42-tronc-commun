/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:51:12 by ameddah           #+#    #+#             */
/*   Updated: 2024/05/23 21:37:25 by alae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	is_integer(const char *s)
{
	int		i;
	long	x;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] != '\0')
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	x = ft_atoi(s);
	if (x > 2147483647 || x < -2147483648)
		return (0);
	return (1);
}

int	verify_args(int argc, char **argv, char ***list)
{
	int		i;

	if (argc == 2)
		*list = ft_split(argv[1], ' ');
	else if (argc > 2)
	{
		*list = malloc((argc) * sizeof(char *));
		if (*list == NULL)
			return (0);
		i = 0;
		while (i < argc - 1)
		{
			(*list)[i] = ft_strdup(argv[i + 1]);
			i++;
		}
		(*list)[i] = NULL;
	}
	i = 0;
	while ((*list)[i])
	{
		if (!is_integer((*list)[i]))
			return (0);
		i++;
	}
	return (i);
}

int	*null_char_list(int n)
{
	int	*list;
	int	i;

	i = 0;
	list = malloc(n * sizeof(int));
	if (!list)
		return (list);
	i = 0;
	while (i < n - 1)
	{
		list[i] = '\0';
		i++;
	}
	return (list);
}

int	has_dup(int **list, int argc)
{
	int	i;
	int	j;
	int	*dup;

	dup = null_char_list(argc);
	if (!dup)
		return (-1);
	i = -1;
	while (list[++i])
	{
		j = 0;
		while (dup[j])
		{
			if (dup[j] == *(list)[i])
			{
				free(dup);
				return (1);
			}
			j++;
		}
		dup[j] = *(list)[i];
	}
	free(dup);
	return (0);
}

int	checks(int argc, char **argv, t_list **a)
{
	char	**list;
	int		**list_int;
	int		x;

	list = NULL;
	list_int = NULL;
	x = verify_args(argc, argv, &list);
	if (x)
	{
		if (convert_to_int(list, &list_int, x + 1))
		{
			if (!has_dup(list_int, x + 1))
			{
				*a = convert_to_stack(list_int);
				free_list((void **)list);
				free_list((void **)list_int);
				return (1);
			}
		}
	}
	if (list)
		free_list((void **)list);
	if (list_int)
		free_list((void **)list_int);
	return (0);
}
