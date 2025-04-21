/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:29:59 by almeddah          #+#    #+#             */
/*   Updated: 2025/04/21 17:58:30 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_sep(char c, char *sep)
{
	while (*sep)
	{
		if (c == *sep)
			return (1);
		sep++;
	}
	return (0);
}

static int	count_words(const char *str, char *sep)
{
	int	n;

	n = 0;
	while (is_sep(*str, sep) && *str)
		str++;
	while (*str)
	{
		while (!is_sep(*str, sep) && *str)
			str++;
		while (is_sep(*str, sep) && *str)
			str++;
		n++;
	}
	return (n);
}

static char	**ft_split2(const char *str, char **result, char *sep)
{
	int	i;
	int	j;

	j = 0;
	while (*str)
	{
		while (is_sep(*str, sep) && *str)
			str++;
		i = 0;
		while (!is_sep(str[i], sep) && str[i])
			i++;
		if (*str)
		{
			result[j] = malloc(sizeof(char) * (i + 1));
			if (!result[j])
				return (0);
			result[j][0] = '\0';
			ft_strncat(result[j++], str, i);
			str += i;
		}
	}
	return (result);
}

char	**ft_split(char const *s, char *sep)
{
	int		nb_words;
	char	**result;

	nb_words = count_words(s, sep);
	result = malloc(sizeof(char *) * (nb_words + 1));
	if (!result)
		return (0);
	ft_split2(s, result, sep);
	result[nb_words] = 0;
	return (result);
}
