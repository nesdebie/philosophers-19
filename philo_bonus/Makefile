NAME	= philo_bonus

SRCS	=	./src/main.c \
			./src/errors.c \
			./src/clean_and_exit.c \
			./src/init.c \
			./src/checker.c \
			./src/process_killer.c \
			./src/event_printer.c \
			./src/child.c \
			./src/open_semaphores.c \
			./src/time.c \
			./src/parent.c

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