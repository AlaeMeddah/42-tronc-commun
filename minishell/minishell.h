/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alae <alae@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:25:34 by almeddah          #+#    #+#             */
/*   Updated: 2025/06/13 10:05:43 by alae             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "fcntl.h"
# include "libft/libft.h"
# include "readline/history.h"
# include "readline/readline.h"
# include "signal.h"
# include "stdio.h"
# include "unistd.h"

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

typedef struct s_data
{
	int							exit_code;
	char						**token_list;
	char						**envp;
	t_command					*command_list;
}								t_data;

void							free_command_list(t_command *cmd_list);
void							free_char_list(char **data);
int								ft_strcmp(const char *s1, const char *s2);
char							*ft_strncpy(char *src, int n);
void							ft_add_back(void **list, void *new);
void							*ft_last(void *list);
int								nb_quoted_char(char *str);
char							*heredoc(char *delim, t_data data);
char							**create_token_list(char *prompt);
char							*expand_variable(char *str, t_data data,
									int *i);
char							*expand_token(char *str, t_data data);
int								create_redirect(t_data data, int i,
									t_command *new_command);
int								is_redirection(char *str);

void							display_command_list(t_command *cmd_list);
void							print_data(char **data);

#endif
