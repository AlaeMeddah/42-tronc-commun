/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ameddah <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 10:48:45 by ameddah           #+#    #+#             */
/*   Updated: 2023/11/24 09:38:36 by ameddah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_list
{
	int				content;
	struct s_list	*previous;
	struct s_list	*next;
	struct s_list	*target;
	long			diff_target;
	int				position;
	int				mid;
	int				cost;
}	t_list;

long	ft_atoi(const char *str);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_itoa(int n);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strdup(const char *src);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
t_list	*ft_lstnew(int content);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_abs(int n);
int		ft_max(int a, int b);
t_list	*ft_lstfirst(t_list *lst);
t_list	*ft_lstmax(t_list *lst);
t_list	*ft_lstmin(t_list *lst);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
