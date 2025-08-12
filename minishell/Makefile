NAME = minishell

SRC_DIR = srcs/
SRCS_FILES = builtin/builtin_cd.c builtin/builtin_echo.c builtin/builtin_env.c \
			builtin/builtin_exit.c builtin/builtin_export.c builtin/builtin_pwd.c \
			builtin/builtin_unset.c builtin/builtin.c executing/envp.c \
			executing/exec.c executing/find_path.c executing/fork.c \
			executing/redir.c parsing/token_list.c parsing/redirection.c \
			parsing/expansion.c parsing/command_list.c parsing/heredoc_creation.c \
			utils/free.c utils/signals.c utils/utils.c main.c
SRCS = $(addprefix $(SRC_DIR), $(SRCS_FILES))
OBJS = $(SRCS:.c=.o)

INCLUDE_DIR = include

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -I$(INCLUDE_DIR)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
