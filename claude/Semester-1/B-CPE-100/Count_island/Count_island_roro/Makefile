##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile for count_island project
##

CC = gcc
CFLAGS = -Wall -Wextra -I./include
LIBFLAGS = -L./lib/my -lmy

SRC_DIR = src
SRC_FILES = $(SRC_DIR)/count_island.c \
            $(SRC_DIR)/flood_fill.c \
            $(SRC_DIR)/utils.c

OBJ_FILES = $(SRC_FILES:.c=.o)

LIBMY = lib/my/libmy.a

NAME = count_island

all: $(LIBMY) $(OBJ_FILES)

$(LIBMY):
	cd lib/my && ./build.sh

$(NAME): $(OBJ_FILES) $(LIBMY) main.o
	$(CC) -o $(NAME) $(OBJ_FILES) main.o $(LIBFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES)
	cd lib/my && rm -f *.o libmy.a

fclean: clean
	rm -f $(NAME)

re: fclean all

tests_run: $(LIBMY)
	$(CC) $(CFLAGS) -o tests_run tests/test_count_island.c $(SRC_FILES) \
		$(LIBFLAGS) -lcriterion --coverage
	./tests_run
	gcov $(SRC_FILES)

.PHONY: all clean fclean re tests_run