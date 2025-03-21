NAME = philo

FLAGS = -lpthread

CFLAGS = -Wall -Werror -Wextra

CC = cc

SRCS = philosophers.c helper_functions/parsing.c helper_functions/mutex.c helper_functions/time.c helper_functions/print.c \
		helper_functions/dinner.c helper_functions/simulation.c helper_functions/actions.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(FLAGS)

%.o : %.c philosophers.h
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all
