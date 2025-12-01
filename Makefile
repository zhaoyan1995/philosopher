NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -g

SRCS = check_end_of_program.c get_time.c parser.c parser_utils.c parser_utils2.c init_data.c init_mutex.c clean_up_data.c init_philo_struct.c main.c philo_routine.c philo_eating.c monitor.c create_threads.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

