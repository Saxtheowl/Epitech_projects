##
## EPITECH PROJECT, 2025
## Crocus
## File description:
## Makefile
##

SRC	=	src/main.c		\
		src/crocus.c		\
		src/parser.c		\
		src/display.c		\
		src/patterns.c		\
		src/utils.c

OBJ	=	$(SRC:.c=.o)

NAME	=	crocus

CFLAGS	=	-Wall -Wextra -Werror -I./include

CC	=	gcc

all:	$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ)

clean:
		rm -f $(OBJ)

fclean:	clean
		rm -f $(NAME)

re:	fclean all

tests_run:
		gcc -o tests_run tests/test_crocus.c src/crocus.c src/parser.c src/display.c src/patterns.c src/utils.c -I./include -lcriterion --coverage
		./tests_run
		gcov *.gcda

.PHONY:	all clean fclean re tests_run