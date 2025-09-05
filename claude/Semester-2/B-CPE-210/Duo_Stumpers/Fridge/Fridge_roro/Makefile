##
## EPITECH PROJECT, 2025
## Fridge
## File description:
## Makefile
##

SRC	=	src/main.c		\
		src/fridge.c		\
		src/utils.c		\
		src/recipes.c		\
		src/save_load.c		\
		src/command_parser.c	\
		src/fridge_main.c

OBJ	=	$(SRC:.c=.o)

NAME	=	fridge

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
		gcc -o tests_run tests/test_fridge.c src/fridge.c src/utils.c src/recipes.c src/save_load.c src/command_parser.c src/fridge_main.c -I./include -lcriterion --coverage
		./tests_run
		gcov *.gcda

.PHONY:	all clean fclean re tests_run