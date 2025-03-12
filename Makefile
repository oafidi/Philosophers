NAME = philo

FLAGS = -lpthread

CFLAGS = -Wall -Werror -Wextra

CC = cc

SRCS = philosophers.c helper_functions/atol.c helper_functions/mutex.c helper_functions/time.c helper_functions/print.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(FLAGS) $(OBJS) -o $(NAME)

%.o : %.c philosophers.h
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all
