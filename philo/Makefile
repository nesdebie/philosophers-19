SRCS	=	main.c \
			ft_error.c \
			init.c \
			utils.c \
			launcher.c

OBJS	= $(SRCS:.c=.o)

NAME	= philo

CC	= gcc

FLAGS	= -Wall -Wextra -Werror

INCLUDE	= -pthread -lpthread

HEADER	= philo.h

all:	$(NAME)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $<  -o $(<:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(INCLUDE) $(FLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS) $(B_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS)

re: fclean all

.PHONY:	clean fclean re