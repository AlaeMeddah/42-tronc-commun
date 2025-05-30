NAME = Minishell

SRCS = main.c free.c utils.c redirection.c heredoc_creation.c parse_to_data.c \
temp_display.c
OBJS = $(SRCS:.c=.o)


LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a


CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJS) $(BONUS_OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re