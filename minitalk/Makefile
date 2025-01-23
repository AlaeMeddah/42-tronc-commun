SV = server
CL = client

SV_SRCS = server.c write.c
CL_SRCS = client.c write.c

SV_OBJS = $(SV_SRCS:.c=.o)
CL_OBJS = $(CL_SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(SV) $(CL)

$(SV): $(SV_OBJS)
	$(CC) $(CFLAGS) $(SV_OBJS) -o $(SV)

$(CL): $(CL_OBJS)
	$(CC) $(CFLAGS) $(CL_OBJS) -o $(CL)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SV_OBJS) $(CL_OBJS)

fclean: clean
	rm -f $(SV) $(CL)

re: fclean all

.PHONY: all clean fclean re