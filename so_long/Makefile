NAME = so_long

SRCS = so_long.c map_check.c image.c map_creation.c move.c set.c
OBJS = $(SRCS:.c=.o)

LIBFTPRINTF_DIR = printf
LIBFTPRINTF = $(LIBFTPRINTF_DIR)/libftprintf.a

GNL_DIR = get_next_line
GNL_SRCS = $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c
GNL_OBJS = $(GNL_SRCS:.c=.o)

MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lm -lX11 -lXext

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS) $(LIBFTPRINTF) $(GNL_OBJS) $(MLX_LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFTPRINTF) $(GNL_OBJS) $(MLX_FLAGS)

$(LIBFTPRINTF):
	$(MAKE) -C $(LIBFTPRINTF_DIR)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJS) $(GNL_OBJS)
	$(MAKE) -C $(LIBFTPRINTF_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFTPRINTF_DIR) fclean
	$(MAKE) -C $(MLX_DIR) clean

re: fclean all
