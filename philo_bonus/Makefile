NAME	= philo_bonus

SRCS	=	./src/main.c \
			./src/errors.c \
			./src/init.c \
			./src/utils.c \
			./src/ft_kill.c \
			./src/ft_print_events.c \
			./src/checker.c \
			./src/philo.c \
			./src/philo_utils.c \
			./src/process_comm.c \
			./src/time.c

OBJS	= $(SRCS:.c=.o)

CC	= cc

FLAGS	= -Wall -Wextra -Werror

INCLUDE	= -pthread -lpthread

HEADER	= ./includes/philo_bonus.h

all:	$(NAME)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $<  -o $(<:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(INCLUDE) $(FLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS) $(B_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re