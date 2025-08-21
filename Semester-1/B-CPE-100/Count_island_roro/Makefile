##
## EPITECH PROJECT, 2024
## Count_island
## File description:
## Makefile for count_island project
##

NAME	= count_island

SRC	= main.c count_island.c

OBJ	= $(SRC:.c=.o)

CFLAGS	= -Wall -Wextra -I./include

LDFLAGS	= -L./lib/my -lmy

all: $(NAME)

$(NAME): libmy $(OBJ)
	gcc -o $(NAME) $(OBJ) $(LDFLAGS)

libmy:
	cd lib/my && ./build.sh

clean:
	rm -f $(OBJ)
	cd lib/my && rm -f *.o

fclean: clean
	rm -f $(NAME)
	cd lib/my && rm -f libmy.a

re: fclean all

tests_run: all
	python3 tests_py/simple_test.py

.PHONY: all clean fclean re libmy tests_run