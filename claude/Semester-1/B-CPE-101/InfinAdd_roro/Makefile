##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile for infin_add project
##

CC = gcc
CFLAGS = -Wall -Wextra -I./include

SRC_FILES = src/main.c \
            src/infin_add.c \
            src/addition.c \
            src/subtraction.c \
            src/string_operations.c \
            src/utils.c \
            lib/my/my_putchar.c \
            lib/my/my_putstr.c

OBJ_FILES = $(SRC_FILES:.c=.o)

NAME = infin_add

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
	./$(NAME) "-876435" "987143265"
	./$(NAME) "-807965" "-34532"
	./$(NAME) "435439435845843984358439" "4535976678566582218241234325434343543333945959"

.PHONY: all clean fclean re tests_run