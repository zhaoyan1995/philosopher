NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = check_end_of_program.c \
       get_time.c \
       parser.c \
       parser_utils.c \
       parser_utils2.c \
       philo.c \
       init_data.c \
       init_mutex.c \
       init_philo_struct.c

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

