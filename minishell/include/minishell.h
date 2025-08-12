/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:25:34 by almeddah          #+#    #+#             */
/*   Updated: 2025/08/12 17:00:55 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE
# include "../libft/libft.h"
# include "fcntl.h"
# include "readline/history.h"
# include "readline/readline.h"
# include "signal.h"
# include "stdio.h"
# include "unistd.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>

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
int								ft_strcmp(char *s1, char *s2);
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
void							setup_signals(void);
t_command						*create_command_list(t_data data);
int								redirection_error(char **data, int i);

int								setup_cmds(t_data *data);
int								builtin_echo(char **argv);
int								builtin_cd(char **argv, char **envp);
int								builtin_pwd(void);
int								builtin_export(char **argv, char ***envp);
int								builtin_unset(char **argv, char **envp);
int								builtin_env(char **envp);
int								builtin_exit(char **args, int exit_code);
char							**ft_setenv(char **envp, char *key,
									char *value);
char							*ft_getenv(char **envp, char *name);
int								setup_redirect(t_command *cmd);
int								exec_builtin(t_command *cmd, char ***envp,
									int in_fork, int exit_code);

int								is_builtin(char *cmd);
char							*ft_find_path(char *cmd, char **envp);
void							fork_child(t_command *cmd, t_data *data,
									int *prev_fd, int pipefd[2]);
int								fork_parent(t_command *cmd, int pid,
									int *prev_fd, int pipefd[2]);
char							**add_var_to_env(char **envp, char *new_var);
void							norm_function2(char **str, int *i,
									int *d_quote);

#endif
