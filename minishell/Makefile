NAME = Minishell

SRCS = main.c
OBJS = $(SRCS:.c=.o)


LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a


CC = gcc
CFLAGS = -Wall -Wextra -Werror
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) bonus

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