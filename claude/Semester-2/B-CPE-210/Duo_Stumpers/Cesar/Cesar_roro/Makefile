##
## EPITECH PROJECT, 2025
## Cesar
## File description:
## Makefile
##

SRC	=	src/main.c		\
		src/utils.c		\
		src/caesar_cipher.c	\
		src/file_handler.c	\
		src/arg_parser.c	\
		src/cesar_main.c

OBJ	=	$(SRC:.c=.o)

NAME	=	cesar

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
		gcc -o tests_run tests/test_cesar.c src/utils.c src/caesar_cipher.c src/file_handler.c src/arg_parser.c src/cesar_main.c -I./include -lcriterion --coverage
		./tests_run
		gcov *.gcda

.PHONY:	all clean fclean re tests_run