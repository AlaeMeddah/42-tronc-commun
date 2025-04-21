/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeddah <almeddah@student.42lehavre.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:25:34 by almeddah          #+#    #+#             */
/*   Updated: 2025/04/21 18:30:51 by almeddah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "readline/history.h"
# include "readline/readline.h"
# include "stdio.h"

typedef struct s_output_redirect
{
	char						*file;
	int							append;
	struct s_output_redirect	*next;
}								t_output_redirect;

typedef struct s_input_redirect
{
	char						*file;
	char						*delim;
	struct s_input_redirect		*next;
}								t_input_redirect;

typedef struct s_command
{
	char						**argv;
	t_input_redirect			*input_redirect;
	t_output_redirect			*output_redirect;
	struct s_command			*next_pipe;
}								t_command;

#endif
