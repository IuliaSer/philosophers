
SRCS = main.c launch_philosophers.c  messages.c utils.c utils2.c check_state.c

OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror -I.

NAME = philo_three

all:	$(NAME)

$(NAME):	$(OBJS)
			gcc ${CFLAGS} -o ${NAME} ${OBJS} -g

clean:
	/bin/rm -f *.o

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
