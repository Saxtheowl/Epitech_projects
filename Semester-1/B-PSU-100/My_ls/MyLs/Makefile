##
## EPITECH PROJECT, 2025
## my_ls
## File description:
## Standard Makefile with required targets.
##

NAME	=	my_ls

SRC	=	\
	src/main.c \
	src/options.c \
	src/utils.c \
	src/path.c \
	src/sort.c \
	src/format.c \
	src/print.c \
	src/recursion.c \
	src/listing.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror -Iinclude
LDFLAGS	=

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

tests_run:	$(NAME)
	python3 tests_py/run_tests.py

.PHONY:	all clean fclean re tests_run
