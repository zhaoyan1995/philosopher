NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g
DEPFLAGS= -MMD -MP
HEADER_PATH=./include
SRCS_PATH= ./srcs/
OBJS_PATH= ./objs/

SRCS_FILES = get_time.c parser.c parser_utils.c parser_utils2.c init_data.c init_mutex.c clean_up_data.c init_philo_struct.c main.c philo_routine.c philo_eating.c monitor.c create_threads.c update_value_mutex.c read_value_mutex.c safe_print.c

SRCS=$(addprefix $(SRCS_PATH),$(SRCS_FILES))

OBJS=$(addprefix $(OBJS_PATH), $(SRCS_FILES:.c=.o))

DEPS=$(addprefix $(OBJS_PATH), $(SRCS_FILES:.c=.d))

all: init $(NAME)

-include $(DEPS)

init:
	@mkdir -p $(OBJS_PATH)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJS_PATH)%.o:$(SRCS_PATH)%.c | init
	$(CC) $(CFLAGS) $(DEPFLAGS) -I$(HEADER_PATH) -c $< -o $@

clean:
	rm -rf $(OBJS_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

