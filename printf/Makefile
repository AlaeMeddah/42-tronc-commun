NAME = libftprintf.a

SRCS =	ft_printf.c ft_printf_hex.c ft_printf_nbr.c ft_printf_unsigned.c ft_printf_flags.c
OBJS = $(SRCS:.c=.o)

BONUS = ft_printf_bonus.c ft_printf_hex_bonus.c ft_printf_nbr_bonus.c ft_printf_unsigned_bonus.c ft_printf_flags_bonus.c
BONUS_OBJS = $(BONUS:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	ar rcs $(NAME) $(OBJS) $(LIBFT_DIR)/*.o

bonus: $(NAME) $(BONUS_OBJS) $(LIBFT)
	ar rcs $(NAME) $(BONUS_OBJS)

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
