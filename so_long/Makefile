NAME = so_long
BONUS_NAME = so_long_bonus

SRCS_DIR = sources
SRCS = $(SRCS_DIR)/so_long.c $(SRCS_DIR)/map_check.c $(SRCS_DIR)/image.c $(SRCS_DIR)/map_creation.c $(SRCS_DIR)/move.c $(SRCS_DIR)/set.c
OBJS = $(SRCS:.c=.o)

BONUS_DIR = bonus
BONUS_SRCS = $(BONUS_DIR)/so_long.c $(BONUS_DIR)/map_check.c $(BONUS_DIR)/image.c $(BONUS_DIR)/map_creation.c $(BONUS_DIR)/move.c $(BONUS_DIR)/set.c
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

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

bonus: $(BONUS_NAME)

$(NAME): $(OBJS) $(LIBFTPRINTF) $(GNL_OBJS) $(MLX_LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFTPRINTF) $(GNL_OBJS) $(MLX_FLAGS)

$(BONUS_NAME): $(BONUS_OBJS) $(LIBFTPRINTF) $(GNL_OBJS) $(MLX_LIB)
	$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_OBJS) $(LIBFTPRINTF) $(GNL_OBJS) $(MLX_FLAGS)

$(LIBFTPRINTF):
	$(MAKE) -C $(LIBFTPRINTF_DIR)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJS) $(BONUS_OBJS) $(GNL_OBJS)
	$(MAKE) -C $(LIBFTPRINTF_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	$(MAKE) -C $(LIBFTPRINTF_DIR) fclean
	$(MAKE) -C $(MLX_DIR) clean

re: fclean all
