NAME	= philo

SRCS	=	main.c \
			ft_error.c \
			init.c \
			utils.c \
			threads.c

OBJS	= $(SRCS:.c=.o)

CC	= cc

FLAGS	= -Wall -Wextra -Werror

INCLUDE	= -pthread -lpthread

HEADER	= philo.h

all:	$(NAME)

%.o: %.c $(HEADER)
	@$(CC) $(FLAGS) -c $<  -o $(<:.c=.o)

$(NAME): $(OBJS)
	@$(CC) $(INCLUDE) $(FLAGS) -o $(NAME) $(OBJS)
	@echo "Compilation completed.\n./philo is ready to use !"

clean:
	@rm -f $(OBJS) $(B_OBJS)
	@echo "All <file>.o are removed."

fclean: clean
	@rm -f $(NAME)
	@echo "./philo is removed."

re: fclean all

.PHONY:	clean fclean re