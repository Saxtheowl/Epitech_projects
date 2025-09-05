##
## EPITECH PROJECT, 2025
## Panoramix_roro Makefile
## File description:
## Build rules
##

NAME	=	panoramix

SRC	=	$(wildcard src/*.c)

OBJ	=	$(SRC:.c=.o)

INCDIR	=	include

CFLAGS	=	-Wall -Wextra -Werror -I $(INCDIR) -pthread
LDFLAGS	=	-pthread

TEST_NAME	=	unit_tests
TEST_SRC	=	tests/test_basic.c \
			src/core.c \
			src/druid.c \
			src/villager.c
TEST_FLAGS	=	-lcriterion -lgcov --coverage -I $(INCDIR) -pthread

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	rm -f $(OBJ)
	rm -f *.gcno *.gcda

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_NAME)

re: fclean all

tests_run:
	$(CC) $(TEST_SRC) -o $(TEST_NAME) $(TEST_FLAGS)
	./$(TEST_NAME)

.PHONY:	all clean fclean re tests_run

