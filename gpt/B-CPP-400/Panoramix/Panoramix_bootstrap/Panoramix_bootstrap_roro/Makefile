##
## EPITECH PROJECT, 2025
## Panoramix_bootstrap_roro Makefile
## File description:
## Build rules
##

NAME	=	pano_bootstrap

SRC	=	$(wildcard src/*.c)

OBJ	=	$(SRC:.c=.o)

INCDIR	=	include

CFLAGS	=	-Wall -Wextra -Werror -I $(INCDIR) -pthread

LDFLAGS	=	-pthread

# Default macros for subject (can be overridden by CPPFLAGS)
CPPFLAGS	?=	-DNB_TRAINS=3 -DNB_MAX=1

TEST_NAME	=	unit_tests

TEST_SRC	=	tests/test_simulation.c \
			src/bridge.c \
			src/simulation.c

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
	$(CC) $(CPPFLAGS) $(TEST_SRC) -o $(TEST_NAME) $(TEST_FLAGS)
	./$(TEST_NAME)

.PHONY:	all clean fclean re tests_run
