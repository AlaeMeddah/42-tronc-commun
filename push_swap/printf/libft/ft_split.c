/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ameddah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:46:05 by ameddah           #+#    #+#             */
/*   Updated: 2023/11/28 11:46:05 by ameddah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	words;

	words = 0;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			words++;
		s++;
	}
	return (words);
}

static void	free_(char **to_free)
{
	int	i;

	i = 0;
	while (to_free[i])
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
}

static void	fill(char *to_fill, char const *s, char c)
{
	while (*s && *s != c)
	{
		*to_fill = *s;
		s++;
		to_fill++;
	}
	*to_fill = '\0';
}

static void	splitting(char **splitted, char const *s, char c)
{
	size_t	char_number;
	int		i;

	i = 0;
	while (*s)
	{
		char_number = 0;
		while (*(s + char_number) && *(s + char_number) != c)
			char_number++;
		if (char_number)
		{
			splitted[i] = malloc(sizeof(char) * (char_number + 1));
			if (splitted[i] == NULL)
				return ;
			fill(splitted[i], s, c);
			s = s + char_number;
			i++;
		}
		else
			s++;
	}
	splitted[i] = NULL;
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	words;
	char	**splitted;

	words = count_words(s, c);
	splitted = malloc(sizeof(char *) * (words + 1));
	if (splitted == NULL)
		return (NULL);
	splitting(splitted, s, c);
	i = 0;
	while (i < words)
	{
		if (splitted[i] == NULL)
		{
			free_(splitted);
			return (NULL);
		}
		i++;
	}
	return (splitted);
}
