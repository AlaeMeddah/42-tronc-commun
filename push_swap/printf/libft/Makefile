NAME = libft.a

SRCS =  ft_abs.c ft_atoi.c ft_calloc.c ft_itoa.c ft_max.c \
		ft_memset.c ft_split.c ft_strdup.c ft_strlen.c \
		ft_lstadd_back.c ft_lstextremum.c ft_lstfirst.c \
		ft_lstlast.c ft_lstnew.c ft_lstsize.c ft_strncmp.c
OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
