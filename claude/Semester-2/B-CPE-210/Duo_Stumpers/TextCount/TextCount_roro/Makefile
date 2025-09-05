##
## EPITECH PROJECT, 2025
## TextCount
## File description:
## Makefile
##

SRC	=	src/main.c		\
		src/text_count.c	\
		src/sort.c		\
		src/print.c

OBJ	=	$(SRC:.c=.o)

NAME	=	text_count

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
		gcc -o tests_run tests/test_text_count.c src/text_count.c src/sort.c src/print.c -I./include -lcriterion --coverage
		./tests_run
		gcov *.gcda

.PHONY:	all clean fclean re tests_run