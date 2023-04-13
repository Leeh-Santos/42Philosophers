SRCS	= main.c \
		  rest/support.c \
		  rest/schadule.c \
		  rest/dead.c \

OBJS	= $(SRCS:.c=.o)

NAME	= philo

CC		= cc

CFLAGS	=  -pthread -g -fsanitize=thread #-Wall -Wextra -Werror

RM		= rm -rf

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME) $(OBJS)

re: fclean all

r:
	make re && make clean && clear && ./philo 5 800 200 200

.PHONY: all clean fclean re