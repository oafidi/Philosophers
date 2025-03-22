NAME = philo_bonus

FLAGS = -lpthread

CFLAGS = -Wall -Werror -Wextra

CC = cc

SRCS = philo_bonus.c helper_functions/parsing_bonus.c helper_functions/semaphore_bonus.c helper_functions/time_bonus.c helper_functions/print_bonus.c \
		helper_functions/dinner_bonus.c helper_functions/simulation_bonus.c helper_functions/actions_bonus.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(FLAGS)

%.o : %.c philo_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all
