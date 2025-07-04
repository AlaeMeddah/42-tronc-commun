/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:25:34 by almeddah          #+#    #+#             */
/*   Updated: 2025/06/19 12:29:15 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE
# include "fcntl.h"
# include "libft/libft.h"
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

typedef struct s_env
{
	char						*key;
	char						*value;
	struct s_env				*next;
}								t_env;

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
void							setup_signals(void);
t_command						*create_command_list(t_data data);
int								redirection_error(char **data, int i);

void							display_command_list(t_command *cmd_list);
void							print_data(char **data);

typedef struct s_path
{
	char						**allpath;
	char						**s_cmd;
	char						*path_part;
	char						*exec;
	char						*tmp;
	char						*trimmed_cmd;
}								t_path;

int								ft_echo(char **args);
int								ft_pwd(void);
int								ft_cd(char **args);
int								ft_exit(char **args, int in_fork);
int								ft_env(t_env *env);
int								ft_export(char **args, t_env **env);
int								is_valid_identifier(const char *key);
t_env							*find_env(t_env *env, const char *key);

int								execute_commands(t_command *cmd_list,
									char **env);

char							*ft_get_path(char *cmd, char **env);
char							*my_getenv(char **env);
// void	exec(char *cmd, char **env);
void							exec_external(char **argv, char **env);
void							exit_handler(int code);
int								open_file(char *filename, int type, int *error);
void							ft_free_tab(char **tab);
void							write_error(char *msg);

#endif
