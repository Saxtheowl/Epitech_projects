##
## EPITECH PROJECT, 2025
## MyLs_roro
## File description:
## Makefile
##

NAME	=	my_ls
SRC_DIR	=	src
INC_DIR	=	include

SRCS	=	$(SRC_DIR)/main.c \
			$(SRC_DIR)/parse.c \
			$(SRC_DIR)/util.c \
			$(SRC_DIR)/format.c \
			$(SRC_DIR)/sort.c \
			$(SRC_DIR)/ls.c
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

TESTS_SRCS	=	tests/test_parse.c

tests_run:	CFLAGS+=" --coverage"
tests_run:	LDFLAGS+=" --coverage -lcriterion"
tests_run:	$(OBJS) $(TESTS_SRCS)
	$(CC) $(CFLAGS) $(OBJS) $(TESTS_SRCS) -o unit_tests $(LDFLAGS)
	./unit_tests

.PHONY:	all clean fclean re tests_run
