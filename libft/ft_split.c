/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:29:59 by almeddah          #+#    #+#             */
/*   Updated: 2024/10/16 14:32:32 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strncat(char *dest, const char *src, unsigned int nb)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j] && j < nb)
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

static int	is_sep(char c, char sep)
{
	if (c == sep)
		return (1);
	return (0);
}

static int	count_words(const char *str, char sep, int n)
{
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

static char	**ft_split2(const char *str, char **result, char sep)
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
			result[j][0] = '\0';
			ft_strncat(result[j++], str, i);
			str += i;
		}
	}
	return (result);
}

char	**ft_split(char const *s, char c)
{
	int		nb_words;
	char	**result;

	nb_words = count_words(s, c, 0);
	result = malloc(sizeof(char *) * (nb_words + 1));
	ft_split2(s, result, c);
	result[nb_words] = 0;
	return (result);
}
