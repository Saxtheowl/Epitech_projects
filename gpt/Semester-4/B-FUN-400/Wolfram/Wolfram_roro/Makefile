##
## EPITECH PROJECT, 2025
## Wolfram_roro
## File description:
## Makefile
##

NAME	=	wolfram

SRC	=	$(wildcard src/*.c)
OBJ	=	$(SRC:.c=.o)
INCDIR	=	include

CFLAGS	=	-Wall -Wextra -Werror -I $(INCDIR)

TEST_NAME	=	unit_tests
TEST_SRC	=	tests/test_basic.c \
			src/parse.c \
			src/sim.c
TEST_FLAGS	=	-lcriterion -lgcov --coverage -I $(INCDIR)

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)
	rm -f *.gcno *.gcda

fclean: clean
	rm -f $(NAME) $(TEST_NAME)

re: fclean all

tests_run:
	$(CC) $(TEST_SRC) -o $(TEST_NAME) $(TEST_FLAGS)
	./$(TEST_NAME)

.PHONY:	all clean fclean re tests_run
