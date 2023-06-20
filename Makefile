SRCS	= main.c \
		  rest/support.c \
		  rest/schedule.c \
		  rest/dead.c \
		  rest/free.c

OBJS	= $(SRCS:.c=.o)

NAME	= Minishell

CC		= cc

CFLAGS	= #-Wall -Wextra -Werror -pthread -g 

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