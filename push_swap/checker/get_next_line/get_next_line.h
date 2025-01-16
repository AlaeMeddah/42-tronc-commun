/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 20:15:39 by ameddah           #+#    #+#             */
/*   Updated: 2024/05/23 21:19:56 by alae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_lis
{
	char			*content;
	struct s_lis	*next;
}	t_lis;

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
void	add_to_stash(t_lis **stash, char *buf, int readed);
void	clean_stash(t_lis **stash);
t_lis	*ft_lst_get_last(t_lis *stash);
void	free_stash(t_lis *stash);

#endif
