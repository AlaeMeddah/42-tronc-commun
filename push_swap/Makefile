NAME = push_swap

SRCS = main.c check.c sort.c update_stack.c rotate.c push.c swap.c move_cheapest.c finish_sort.c
OBJS = $(SRCS:.c=.o)

LIBFTPRINTF_DIR = printf
LIBFTPRINTF = $(LIBFTPRINTF_DIR)/libftprintf.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS) $(LIBFTPRINTF)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFTPRINTF)

$(LIBFTPRINTF):
	$(MAKE) -C $(LIBFTPRINTF_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFTPRINTF_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFTPRINTF_DIR) fclean

re: fclean all