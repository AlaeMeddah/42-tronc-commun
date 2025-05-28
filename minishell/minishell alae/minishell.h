/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:25:34 by almeddah          #+#    #+#             */
/*   Updated: 2025/05/28 12:12:21 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "fcntl.h"
# include "libft/libft.h"
# include "readline/history.h"
# include "readline/readline.h"
# include "stdio.h"

typedef struct s_output_redirect
{
	struct s_output_redirect	*next;
	char						*file;
	int							append;
}								t_output_redirect;

typedef struct s_input_redirect
{
	struct s_input_redirect		*next;
	char						*file;
	int							heredoc;
}								t_input_redirect;

typedef struct s_command
{
	struct s_command			*next;
	char						**argv;
	t_input_redirect			*input_redirect;
	t_output_redirect			*output_redirect;
}								t_command;

void							free_command_list(t_command *cmd_list);
void							free_char_list(char **data);
int								ft_strcmp(const char *s1, const char *s2);
char							*ft_strncpy(char *src, int n);
void							ft_add_back(void **list, void *new);
void							*ft_last(void *list);
int								nb_quoted_char(char *str);
t_output_redirect				*create_output_redirect(char *str1, char *str2);
t_input_redirect				*create_input_redirect(char *str1, char *str2,
									char **envp);
char							*heredoc(char *delim, char **envp);
void							display_command_list(t_command *cmd_list);
void							print_data(char **data);

#endif
