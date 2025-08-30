##
## EPITECH PROJECT, 2025
## mini_printf_roro
## File description:
## Makefile
##

NAME	=	mini_printf
SRC_DIR	=	src
INC_DIR	=	include

SRCS	=	$(SRC_DIR)/main.c \
			$(SRC_DIR)/mini_printf.c \
			$(SRC_DIR)/mini_put.c
OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror -I $(INC_DIR)
LDFLAGS	=

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS) *.gcno *.gcda

fclean:	clean
	$(RM) $(NAME) unit_tests

re:	fclean all

TESTS_SRCS	=	tests/test_mini.c

tests_run:	CFLAGS+=" --coverage"
tests_run:	LDFLAGS+=" --coverage -lcriterion"
tests_run:	$(OBJS) $(TESTS_SRCS)
	$(CC) $(CFLAGS) $(OBJS) $(TESTS_SRCS) -o unit_tests $(LDFLAGS)
	./unit_tests

.PHONY:	all clean fclean re tests_run
