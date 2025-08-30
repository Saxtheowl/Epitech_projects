##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile for match and nmatch project
##

CC = gcc
CFLAGS = -Wall -Wextra -I./include
LIBFLAGS = -L./lib/my -lmy

SRC_FILES = match.c nmatch.c
OBJ_FILES = $(SRC_FILES:.c=.o)

LIBMY = lib/my/libmy.a

all: $(LIBMY) $(OBJ_FILES)

$(LIBMY):
	cd lib/my && ./build.sh

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES)
	cd lib/my && rm -f *.o libmy.a

fclean: clean
	rm -f match nmatch test_match

re: fclean all

test: all
	$(CC) $(CFLAGS) -o test_match tests/test_main.c match.c nmatch.c \
		$(LIBFLAGS)
	./test_match

tests_run:
	$(CC) $(CFLAGS) -o tests_run tests/test_match.c match.c nmatch.c \
		$(LIBFLAGS) -lcriterion --coverage
	./tests_run

.PHONY: all clean fclean re test tests_run