##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile for BSQ project
##

CC = gcc
CFLAGS = -Wall -Wextra -I./include

SRC_FILES = src/main.c \
            src/utils.c \
            src/file_operations.c \
            src/map_parser.c \
            src/bsq_algorithm.c \
            src/display.c

OBJ_FILES = $(SRC_FILES:.c=.o)

NAME = bsq

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) -o $(NAME) $(OBJ_FILES)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

tests_run: $(NAME)
	@echo "Creating test map..."
	@echo "9" > test_map
	@echo "..........................." >> test_map
	@echo "....o......................" >> test_map
	@echo "............o.............." >> test_map
	@echo "..........................." >> test_map
	@echo "....o......................" >> test_map
	@echo "..............o............" >> test_map
	@echo "..........................." >> test_map
	@echo "......o..............o....." >> test_map
	@echo "..o.......o................" >> test_map
	./$(NAME) test_map
	rm -f test_map

.PHONY: all clean fclean re tests_run