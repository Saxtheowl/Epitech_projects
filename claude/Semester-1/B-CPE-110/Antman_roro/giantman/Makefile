##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile for giantman decompression binary
##

CC = gcc
CFLAGS = -Wall -Wextra

SRC_FILES = giantman.c \
           ../shared/utils.c \
           ../shared/file_operations.c \
           ../shared/compression_algorithms.c \
           ../shared/decompression_algorithms.c

OBJ_FILES = $(SRC_FILES:.c=.o)

NAME = giantman

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

.PHONY: all clean fclean re