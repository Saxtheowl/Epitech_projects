##
## EPITECH PROJECT, 2025
## My_navy_roro
## File description:
## Makefile
##

NAME	=	my_navy
SRC_DIR	=	src
INC_DIR	=	include

SRCS	=	$(SRC_DIR)/main.c \
			$(SRC_DIR)/map.c \
			$(SRC_DIR)/signals.c
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

TESTS_SRCS	=	tests/test_dummy.c

tests_run:	CFLAGS+=" --coverage"
tests_run:	LDFLAGS+=" --coverage -lcriterion"
tests_run:	$(OBJS) $(TESTS_SRCS)
	$(CC) $(CFLAGS) $(OBJS) $(TESTS_SRCS) -o unit_tests $(LDFLAGS)
	./unit_tests

.PHONY:	all clean fclean re tests_run
