SV = server
CL = client

SV_SRCS = server.c write.c
CL_SRCS = client.c write.c

SV_OBJS = $(SV_SRCS:.c=.o)
CL_OBJS = $(CL_SRCS:.c=.o)

SV_BONUS = server_bonus
CL_BONUS = client_bonus

SV_SRCS_BONUS = server_bonus.c write.c
CL_SRCS_BONUS = client_bonus.c write.c

SV_OBJS_BONUS = $(SV_SRCS_BONUS:.c=.o)
CL_OBJS_BONUS = $(CL_SRCS_BONUS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(SV) $(CL)

$(SV): $(SV_OBJS)
	$(CC) $(CFLAGS) $(SV_OBJS) -o $(SV)

$(CL): $(CL_OBJS)
	$(CC) $(CFLAGS) $(CL_OBJS) -o $(CL)

bonus: $(SV_BONUS) $(CL_BONUS)

$(SV_BONUS): $(SV_OBJS_BONUS)
	$(CC) $(CFLAGS) $(SV_OBJS_BONUS) -o $(SV_BONUS)

$(CL_BONUS): $(CL_OBJS_BONUS)
	$(CC) $(CFLAGS) $(CL_OBJS_BONUS) -o $(CL_BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SV_OBJS) $(CL_OBJS) $(SV_OBJS_BONUS) $(CL_OBJS_BONUS)

fclean: clean
	rm -f $(SV) $(CL) $(SV_BONUS) $(CL_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus